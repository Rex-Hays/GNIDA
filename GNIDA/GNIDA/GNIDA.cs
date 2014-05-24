using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TUP.AsmResolver;
using TUP.AsmResolver.ASM;
using System.ComponentModel;

namespace GNIDA
{
    /*
    public class CmmDisassembler : x86Disassembler
    {
        public CmmDisassembler()
        {
            LoadOpCodes();
        }
    }
     * */
    public static class stringExt
    {
        static object obj;
        public static void SetObj(this string ss, object Obj)
        {
            obj = Obj;
        }
    }
    public class VarDictionary : Dictionary<ulong, TVar>
    {
        public GNIDA Parent;
        public void AddVar(TVar value)
        {
            if (!this.ContainsKey(value.Addr))
            {
                this.Add(value.Addr, value);
                Parent.RaiseVarFuncEvent(this, value);
            }
        }
    }

    public class TVar
    {
        public ulong Addr;
        public string FName;
        public uint type;
        public string ToStr()
        {
            switch(type)
            {
                case 0: return "void " + FName;
                case 1: return "byte " + FName;
                case 2: return "word " + FName;
                case 4: return "dword " + FName;
                default : return "void " + FName;
            }
        }
        public TVar(ulong addr, string Name = "", uint Type = 0)
        {
            Addr = addr;
            type = Type;
            if (Name != "") FName = Name;
            else
                switch (Type)
                {
                    case 1: FName = "byte_" + Addr.ToString("X8"); break;
                    case 2: FName = "word_" + Addr.ToString("X8"); break;
                    case 4: FName = "dword_" + Addr.ToString("X8"); break;
                    default: FName = "unk_" + Addr.ToString("X8"); break;
                }
        }
    }
    public class MyDictionary : Dictionary<ulong, TFunc>
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
    public static class OperandExtensions
    {
        public static string ToString(this Operand Op)
        {
            return "0x" + Op.ToString(false);
        }
    }
    public static class X86Extensions
    {
        private static string AddProc(Offset x, MyDictionary ProcList, Dictionary<ulong, TFunc> NewSubs)
        {
            if (ProcList.ContainsKey(x.Va)) return ProcList[x.Va].FName + "();";
            TFunc tmpfunc = new TFunc(x.Va, 1);
            if (!NewSubs.ContainsKey(x.Va)) NewSubs.Add(x.Va, tmpfunc);
            return "Sub_" + x.Va.ToString("X8") + "();";
        }
        public static string ToCmmString(this x86Instruction inst, MyDictionary ProcList, VarDictionary VarDict, Dictionary<ulong, TFunc> NewSubs)
        {
            switch(inst.OpCode.OpCodeBytes[0])
            {
                case 0x74: return "$JZ Loc_" + inst.Operand1.ToString(true);
                case 0xA3://mov somevar, EAX
                    {
                        TVar Var1 = new TVar(((Offset)inst.Operand1.Value).Va, "", 4);
                        if (!VarDict.ContainsKey(((Offset)inst.Operand1.Value).Va))
                        {
                            VarDict.AddVar(Var1);
                        };
                        return "$MOV " + VarDict[((Offset)inst.Operand1.Value).Va].FName + ", EAX";
                    }
                case 0x75: return "$JNZ Loc_" + inst.Operand1.ToString(true);
                case 0xEB: return "$JMP Loc_" + inst.Operand1.ToString(true);
                case 0xC3: return "$RET";
                case 0xE8:
                    {
                        if (inst.Operand1.ValueType == OperandType.Normal)
                        {
                            return AddProc((Offset)inst.Operand1.Value, ProcList, NewSubs);
                        }
                    }break;
                case 0xFF:
                    {
                        if (inst.OpCode.OpCodeBytes[1] == 0x15)
                        if (inst.Operand1.ValueType == OperandType.DwordPointer)
                        {
                            return AddProc((Offset)inst.Operand1.Value, ProcList, NewSubs);
                        }
                    }break;
            }
            string str = inst.ToAsmString();
            str = str.Replace(" PTR ", "");
            return '$'+str;
        }
    }
    public class TFunc
    {
        public ulong Addr;
        public uint Length;
        public string FName;
        public string LibraryName;
        public uint type;
        public uint Ordinal;
        public TFunc(ulong addr, uint Type, uint Ord = 0, string Name = "", string LibName = "")
        {
            Addr = addr;
            type = Type;
            Ordinal = Ord;
            LibraryName = LibName;
            if (Name != "") FName = Name;
            else FName = "Sub_" + Addr.ToString("X8");
        }
    }
    public class GNIDA
    {
        public static Win32Assembly assembly;
        public static x86Disassembler xMy()
        {
            return new x86Disassembler(assembly);
        }
        public BackgroundWorker bw = new BackgroundWorker();
        public MyDictionary FullProcList = new MyDictionary();
        public MyDictionary ToDisasmFuncList = new MyDictionary();
        public MyDictionary DisasmedFuncList = new MyDictionary();
        public VarDictionary VarDict = new VarDictionary();
        public GNIDA()
        {
            //assembly = new Win32Assembly();
            //assembly.Disassembler = new CmmDisassembler();
            FullProcList.Parent = this;
            VarDict.Parent = this;
        }
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
            GNIDA Parent;
            public uint addr;
            public string UpComment;
            public string Comment;
            public string SubComment;
            public x86Instruction Inst;
            public string Label ="";
            public Stroka(GNIDA Prnt, x86Instruction Ins, string UpC = "", string Com = "", string SubC = "")
            {
                Parent = Prnt;
                Inst = Ins;
                UpComment = UpC;
                Comment = Com;
                SubComment = SubC;
                addr = Ins.Offset.FileOffset;
            }
            public string ToCmmString(Dictionary<ulong, TFunc> NewSubs)
            {
                string tmp = "";
                if (Label != "") tmp = "/*" + (Inst.Offset.Rva + assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/ " + Label + ":\n";
                tmp += "/*" + (Inst.Offset.Rva + assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/  " + Inst.ToCmmString(Parent.FullProcList, Parent.VarDict, NewSubs);
                if (Comment != "") tmp += "// " + Comment;
                tmp += "\n";
                if (SubComment != "") tmp += "/*" + (Inst.Offset.Rva + assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/ // " + SubComment + "\n";
                return tmp;
            }
        }
        public List<Stroka> DisasmFunc(ulong addr, MyDictionary ProcList)
        {
            List<Stroka> lst = new List<Stroka>();
            List<ulong> Tasks = new List<ulong>();
            List<int> LabelList = new List<int>();
            Tasks.Add(addr);
            for (uint i = 0; Tasks.Count > 0; i++)
            {
                assembly.Disassembler.CurrentOffset = (uint)Tasks[0];
                Tasks.Remove(Tasks[0]);
                x86Instruction instruction = assembly.Disassembler.DisassembleNextInstruction();
                lst.Add(new Stroka(this, instruction));
                switch (instruction.OpCode.OpCodeBytes[0])
                {
                    case 0x74://Jxx
                        {
                            int val = instruction.OperandBytes[0] + (int)instruction.Offset.FileOffset + instruction.Size;
                            if (!LabelList.Contains(val))
                            {
                                LabelList.Add(val);
                                Tasks.Add((uint)val);//Add jmp adress to disasm tasks
                            }
                        }break;
                    case 0xC2://retn XX;
                    case 0xC3://retn
                        continue;// Don't disasm after it
                    case 0xEB://jmp;
                        int val1 = instruction.OperandBytes[0] + (int)instruction.Offset.FileOffset + instruction.Size;
                        if (!LabelList.Contains(val1))
                        {
                            LabelList.Add(val1);
                            Tasks.Add((uint)val1);//Add jmp adress to disasm tasks
                        }
                        continue;// Don't disasm after it
                    case 0xFF:
                        Console.WriteLine("--");
                        Console.WriteLine(instruction.OperandBytes[0].ToString("X2"));
                        Console.WriteLine(instruction.OperandBytes[1].ToString("X2"));
                        if (instruction.OpCode.OpCodeBytes[1] == 0x15)//Call
                            {
                                ulong a = ((Offset)instruction.Operand1.Value).Va;
                                if(ProcList.ContainsKey(a))
                                    if(ProcList[a].FName.Contains("ExitProcess"))continue;
                            }
                            break;
                }
                Tasks.Add(instruction.Offset.FileOffset + (uint)instruction.Size);
            }
            foreach (uint Addr in LabelList)
            {
                Stroka result = lst.Find(
                     delegate(Stroka sstr){return sstr.addr == Addr;}
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
            bw.RunWorkerCompleted += bw_RunWorkerCompleted;
            bw.RunWorkerAsync();
        }
        MyDictionary NewSubs = new MyDictionary();
        void bw_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (NewSubs.Count > 0)
            {
                foreach (KeyValuePair<ulong, TFunc> dct1 in NewSubs)
                    FullProcList.AddFunc(dct1.Value);
                NewSubs.Clear();
                (sender as BackgroundWorker).RunWorkerAsync();
            }
        }
        public ulong RVA2FO(ulong RVA)
        {
            uint addr = 0;
            RVA -= assembly.NTHeader.OptionalHeader.ImageBase;
            foreach (Section sct in assembly.NTHeader.Sections)
            {
                if (sct.ContainsRva((uint)RVA)) addr = sct.RVAToFileOffset((uint)RVA);
            }
            return addr;
        }

        private void bw_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            foreach (KeyValuePair<ulong, TFunc> dct in ToDisasmFuncList)
            { 
                if ((worker.CancellationPending == true))
                {
                    e.Cancel = true;
                    break;
                }
                RaiseAddStrEvent("/*" + dct.Key.ToString("X8") + "*/ void " + dct.Value.FName + "(){\n");
                List<Stroka> tmp = DisasmFunc(RVA2FO(dct.Key), FullProcList);
                foreach(Stroka t in tmp)
                {
                    RaiseAddStrEvent(t.ToCmmString(NewSubs));
                }
                DisasmedFuncList.Add(dct.Key, dct.Value);
                RaiseAddStrEvent("};//" + dct.Value.FName + "\n");
            }
            ToDisasmFuncList.Clear();
        }
        public delegate void LogEvent(object sender, string LogStr);
        public delegate void VarEvent(object sender, TVar Var);
        public delegate void AddFuncEvent(object sender, TFunc Func);
        public delegate void AddStrEvent(string Str);
        public event LogEvent OnLogEvent;
        public event VarEvent OnVarEvent;
        public event AddFuncEvent OnAddFunc;
        public event AddStrEvent OnAddStr;
        public void RaiseVarFuncEvent(object sender, TVar Var)
        {
            if (OnVarEvent != null) OnVarEvent(sender, Var);
        }
        private void RaiseLogEvent(object sender, string LogStr)
        {
            if (OnLogEvent != null) OnLogEvent(sender, LogStr);
        }
        public void RaiseAddFuncEvent(object sender, TFunc Func)
        {
            if (OnAddFunc != null) OnAddFunc(sender, Func);
        }
        private void RaiseAddStrEvent( string Str)
        {
            if (OnAddStr != null) OnAddStr(Str);
        }
        
    }

}
