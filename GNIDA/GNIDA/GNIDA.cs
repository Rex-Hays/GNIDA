using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TUP.AsmResolver;
using TUP.AsmResolver.ASM;
using System.ComponentModel;

namespace GNIDA
{   public static class X86Extensions
    {
        public static string ToCmmString(this x86Instruction inst, uint ImageBase)
        {
            //uint val = inst.OperandBytes[0];
            if (inst.OpCode.OpCodeBytes[0] == 0x74) return "$JZ Loc_" + inst.Operand1.ToString(true);
            if (inst.OpCode.OpCodeBytes[0] == 0x75) return "$JNZ Loc_" + inst.Operand1.ToString(true);
            if (inst.OpCode.OpCodeBytes[0] == 0xEB) return "$JMP Loc_" + inst.Operand1.ToString(true);
            string str = inst.ToAsmString();
            str = str.Replace(" PTR ", "");
            return '$'+str;
        }
    }
    public class TFunc
    {
        public uint Addr;
        public uint Length;
        public string FName;
        public string LibraryName;
        public uint type;
        public uint Ordinal;
        public TFunc(uint addr, uint Type, uint Ord, string Name = "", string LibName = "")
        {
            Addr = addr;
            type = Type;
            Ordinal = Ord;
            LibraryName = LibName;
            if (Name != "") FName = Name;
            else FName = "Func_" + Addr.ToString("X8");
        }
    }
    class GNIDA
    {
        class MyDictionary : Dictionary<uint, TFunc>
        {
            public GNIDA Parent;
            public void AddFunc(TFunc value)
            {
                if (!this.ContainsKey(value.Addr))
                {
                    this.Add(value.Addr, value);
                    Parent.RaiseAddFuncEvent(this, value);
                    if (value.type != 3)
                        if ((!Parent.ToDisasmFuncList.ContainsKey(value.Addr))
                          || (!Parent.DisasmedFuncList.ContainsKey(value.Addr))) Parent.ToDisasmFuncList.Add(value.Addr, value);
                }
            }
        }
        public static Win32Assembly assembly;
        public BackgroundWorker bw = new BackgroundWorker();
        MyDictionary FullProcList = new MyDictionary();
        MyDictionary ToDisasmFuncList = new MyDictionary();
        MyDictionary DisasmedFuncList = new MyDictionary();
        public void StopWork()
        {
            bw.CancelAsync();
        }
        public List<Section> Sections()
        {
            return assembly.NTHeader.Sections;
        }
        public class Stroka
        {
            public uint addr;
            public string UpComment;
            public string Comment;
            public string SubComment;
            public x86Instruction Inst;
            public string Label ="";
            public Stroka(x86Instruction Ins, string UpC = "", string Com = "", string SubC = "")
            {
                Inst = Ins;
                UpComment = UpC;
                Comment = Com;
                SubComment = SubC;
                addr = Ins.Offset.FileOffset;
            }
            public string ToAsmString()
            {
                string tmp = "";
                if (Label != "") tmp = "/*" + (Inst.Offset.Rva + assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/ " + Label + ":\n";
                tmp += "/*" + (Inst.Offset.Rva + assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/  " + Inst.ToCmmString((uint)assembly.NTHeader.OptionalHeader.ImageBase);
                if (Comment != "") tmp += "// " + Comment;
                tmp += "\n";
                if (SubComment != "") tmp += "/*" + (Inst.Offset.Rva + assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/ // " + SubComment + "\n";
                return tmp;
            }
        }
        public List<Stroka> DisasmFunc(uint addr)
        {
            List<Stroka> lst = new List<Stroka>();
            List<uint> Tasks = new List<uint>();
            List<int> LabelList = new List<int>();
            Tasks.Add(addr);
            for (uint i = 0; Tasks.Count > 0; i++)
            {
                //to-do 
                assembly.Disassembler.CurrentOffset = Tasks[0];
                Tasks.Remove(Tasks[0]);
                x86Instruction instruction = assembly.Disassembler.DisassembleNextInstruction();
                lst.Add(new Stroka(instruction));
                if (instruction.OpCode.OpCodeBytes[0] == 0xC3) continue;//retn
                if (instruction.OpCode.OpCodeBytes[0] == 0xC2) continue;//retn XX;
                if (instruction.OpCode.OpCodeBytes[0] == 0xEB) continue;//jmp;
                if (instruction.OpCode.OpCodeBytes[0] == 0x74)// je/jz;
                {
                    int val = instruction.OperandBytes[0] + (int)instruction.Offset.FileOffset + instruction.Size;
                    if (!LabelList.Contains(val))
                    {
                        LabelList.Add(val);
                        Tasks.Add((uint)val);
                    }
                }
                Tasks.Add(instruction.Offset.FileOffset + (uint)instruction.Size);
            }
            foreach (uint Addr in LabelList)
            {
                Stroka result = lst.Find(
                    delegate(Stroka sstr)
                    {
                        return sstr.addr == Addr;
                    }
                    );
                if (result != null)
                {
                    result.Label = "Loc_" + result.Inst.Offset.Rva.ToString("X8");
                }
            }
            return lst;
        }
        public void LoadFile(string FName)
        {
            RaiseLogEvent(this, "Loading " + FName);
            assembly = Win32Assembly.LoadFile(FName);
            FullProcList.Parent = this;
            int i = 0;
            foreach (Section sect in assembly.NTHeader.Sections)
            {
                RaiseLogEvent(this, i.ToString() + ". Creating a new segment " + sect.RVA.ToString("X8") + " - " + (sect.RVA + sect.VirtualSize).ToString("X8") + "... ... OK");
                i++;
            }

            TFunc fnc = new TFunc((uint)assembly.NTHeader.OptionalHeader.ImageBase + assembly.NTHeader.OptionalHeader.Entrypoint.Rva, 0, 0, "main");
            FullProcList.AddFunc(fnc);
            foreach (ExportMethod func in assembly.LibraryExports)
            {
                
                TFunc tmpfunc = new TFunc((uint)assembly.NTHeader.OptionalHeader.ImageBase + func.RVA, 2, func.Ordinal, func.Name);
                FullProcList.AddFunc(tmpfunc);
            }
            foreach (LibraryReference lib in assembly.LibraryImports)
            {
                foreach (ImportMethod func in lib.ImportMethods)
                {
                    TFunc tmpfunc = new TFunc((uint)assembly.NTHeader.OptionalHeader.ImageBase + func.RVA, 3, func.Ordinal, func.Name, lib.LibraryName);
                    FullProcList.AddFunc(tmpfunc);
                }
            }
            bw.WorkerSupportsCancellation = true;
            bw.WorkerReportsProgress = false;
            bw.DoWork += bw_DoWork;
            bw.RunWorkerAsync();
        }
        public uint RVA2FO(uint RVA)
        {
            uint addr = 0;
            RVA -= (uint)assembly.NTHeader.OptionalHeader.ImageBase;
            foreach (Section sct in assembly.NTHeader.Sections)
            {
                if (sct.ContainsRva(RVA)) addr = sct.RVAToFileOffset(RVA);
            }
            return addr;
        }

        private void bw_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            foreach(KeyValuePair<uint, TFunc> dct in ToDisasmFuncList)
            { 
                if ((worker.CancellationPending == true))
                {
                    e.Cancel = true;
                    break;
                }

                RaiseAddStrEvent("/*" + dct.Key.ToString("X8") + "*/ void " + dct.Value.FName + "(){\n");
                List<Stroka> tmp = DisasmFunc(RVA2FO(dct.Key));
                foreach(Stroka t in tmp)
                {
                    RaiseAddStrEvent(t.ToAsmString());
                }
                DisasmedFuncList.Add(dct.Key, dct.Value);
                RaiseAddStrEvent("};//" + dct.Value.FName + "\n");
                //ToDisasmFuncList.Remove(dct.Key);
            }
        }
        public delegate void LogEvent(object sender, string LogStr);
        public delegate void AddFuncEvent(object sender, TFunc Func);
        public delegate void AddStrEvent(string Str);
        public event LogEvent OnLogEvent;
        public event AddFuncEvent OnAddFunc;
        public event AddStrEvent OnAddStr;
        private void RaiseLogEvent(object sender, string LogStr)
        {
            if (OnLogEvent != null) OnLogEvent(sender, LogStr);
        }
        private void RaiseAddFuncEvent(object sender, TFunc Func)
        {
            if (OnAddFunc != null) OnAddFunc(sender, Func);
        }
        private void RaiseAddStrEvent( string Str)
        {
            if (OnAddStr != null) OnAddStr(Str);
        }
        
    }

}
