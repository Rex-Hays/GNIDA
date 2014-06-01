using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TUP.AsmResolver;
using TUP.AsmResolver.ASM;
using System.ComponentModel;
using AlphaOmega.Debug;

namespace GNIDA
{
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
    public class MyDictionary : Dictionary<long, TFunc>
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
    public class TFunc
    {
        public long Addr;
        public long Length;
        public byte[] bytes;
        public string FName;
        public string LibraryName;
        public uint type;
        public uint Ordinal;
        public TFunc(long addr, uint Type, uint Ord = 0, string Name = "", string LibName = "")
        {
            Addr = addr;
            type = Type;
            Ordinal = Ord;
            LibraryName = LibName;
            if (Name != "") FName = Name;
            else FName = "proc_" + Addr.ToString("X8");
        }
    }
    public class GNIDA
    {
        public Win32Assembly assembly;
        public mediana MeDisasm;
        public BackgroundWorker bw = new BackgroundWorker();
        public MyDictionary FullProcList = new MyDictionary();
        public MyDictionary ToDisasmFuncList = new MyDictionary();
        public MyDictionary DisasmedFuncList = new MyDictionary();
        public VarDictionary VarDict = new VarDictionary();
        public StreamLoader PE;
        public PEDirectory info;
        public Flirt flirt;
        MyDictionary NewSubs = new MyDictionary();
        public GNIDA(string FlirtCfg)
        {

            flirt = new Flirt(FlirtCfg);
            FullProcList.Parent = this;
            VarDict.Parent = this;
        }
        public int RenameFunction(TFunc f, string NName)
        {
            if (f != null) { f.FName = NName; RaiseFuncChanged(this, f); return 1; }
            return 0;
        }
        public class Stroka
        {
            GNIDA Parent;
            public uint addr;
            public string UpComment;
            public string Comment;
            public string SubComment;
            public mediana.INSTRUCTION Inst;
            public string Label ="";
            public Stroka(GNIDA Prnt, mediana.INSTRUCTION Ins, string UpC = "", string Com = "", string SubC = "")
            {
                Parent = Prnt;
                Inst = Ins;
                UpComment = UpC;
                Comment = Com;
                SubComment = SubC;
                addr = (uint)Prnt.FO2RVA(Ins.Addr);
            }
            public string ToCmmString(Dictionary<long, TFunc> NewSubs)
            {
                string tmp = "";
                if (Label != "") tmp = "/*" + (Inst.Addr + Parent.assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/ " + Label + ":\n";
                tmp += "/*" + (Inst.Addr).ToString("X8") + "*/  " + Inst.ToString(Parent.FullProcList, Parent.VarDict, NewSubs);
                if (Comment != "") tmp += "// " + Comment;
                tmp += "\n";
                if (SubComment != "") tmp += "/*" + (Inst.Addr + Parent.assembly.NTHeader.OptionalHeader.ImageBase).ToString("X8") + "*/ // " + SubComment + "\n";
                return tmp;
            }
        }
        public long DisasmFunc(List<Stroka> lst, long addr, MyDictionary ProcList)
        {
            //List<Stroka> lst = new List<Stroka>();
            List<long> Tasks = new List<long>();
            List<long> DTasks = new List<long>();
            List<int> LabelList = new List<int>();
            long StartAdr = addr;
            long EndAddr = addr;
            mediana.DISASM_INOUT_PARAMS param = new mediana.DISASM_INOUT_PARAMS();
            uint Len = 0;
            byte[] sf_prefixes = new byte[mediana.MAX_INSTRUCTION_LEN];
            param.arch = mediana.ARCH_ALL;
            param.sf_prefixes = sf_prefixes;
            param.mode = mediana.DISMODE.DISASSEMBLE_MODE_32;
            param.options = (byte)(mediana.DISASM_OPTION_APPLY_REL | mediana.DISASM_OPTION_OPTIMIZE_DISP);
            param.bas = assembly.NTHeader.OptionalHeader.ImageBase+2000;
            mediana.INSTRUCTION instr1 = new mediana.INSTRUCTION();

            Tasks.Add(addr);
            for (uint i = 0; Tasks.Count > 0; i++)
            {
                instr1 = new mediana.INSTRUCTION();
                Len = MeDisasm.medi_disassemble(Tasks[0], ref instr1, ref param);
                if (EndAddr < (Tasks[0] + Len)) EndAddr = Tasks[0] + Len;
                Console.WriteLine(instr1.mnemonic);
                DTasks.Add(Tasks[0]);
                Tasks.Remove(Tasks[0]);
                lst.Add(new Stroka(this, instr1));
                switch (instr1.bytes[0])
                {
                    case 0x0F: switch(instr1.bytes[1])
                        {
                            case 0x84://jz
                            case 0x85://jz
                            case 0x86://jbe
                                int val = (int)((int)instr1.bytes[2] + (int)instr1.Addr + Len);
                                if (!LabelList.Contains(val))
                                {
                                    if ((!DTasks.Contains((uint)val)) && (!Tasks.Contains((uint)val))) Tasks.Add((uint)val);
                                    //Tasks.Add((uint)val);//Add jmp adress to disasm tasks
                                    val = (int)FO2RVA((ulong)val);
                                    instr1.ops[0].value.imm.imm64 = (ulong)val;
                                    LabelList.Add(val);
                                }break;
                        }
                        break;        
                    case 0x74://Jz
                    case 0x75://Jnz
                        {
                            int val = (int)((int)instr1.bytes[1] + (int)instr1.Addr + Len);
                            if (!LabelList.Contains(val))
                            {
                                if ((!DTasks.Contains((uint)val)) && (!Tasks.Contains((uint)val))) Tasks.Add((uint)val);
                                //Tasks.Add((uint)val);//Add jmp adress to disasm tasks
                                val = (int)FO2RVA((ulong)val);
                                instr1.ops[0].value.imm.imm64 = (ulong)val;
                                LabelList.Add(val);
                            }
                        } break;
                    case 0xC2://retn XX;
                    case 0xC3://retn                        
                        goto _end;
                        //continue;// Don't disasm after it
                    case 0xE8://Call;
                        int val3 = (int)instr1.bytes[1] + (int)Len + (int)instr1.Addr;
                        val3 = (int)FO2RVA((ulong)val3);
                        instr1.ops[0].value.imm.imm64 = (ulong)val3;
                        break;
                    case 0xEB://jmp;
                        int val1 = (int)instr1.bytes[1] + (int)Len + (int)instr1.Addr;
                        if (!LabelList.Contains(val1))
                        {
                            LabelList.Add(val1);
                            if((!DTasks.Contains((uint)val1)) && (!Tasks.Contains((uint)val1))) Tasks.Add((uint)val1);
                            //Tasks.Add((uint)val1);//Add jmp adress to disasm tasks
                        }
                        continue;// Don't disasm after it
                    case 0xE9://jmp;

                        int val2 = (int)instr1.bytes[1] + (int)Len + (int)instr1.Addr;
                        if (!LabelList.Contains(val2))
                        {
                            if ((!DTasks.Contains((uint)val2)) && (!Tasks.Contains((uint)val2))) Tasks.Add((uint)val2);
                            //Tasks.Add((uint)val2);//Add jmp adress to disasm tasks
                            val2 = (int)FO2RVA((ulong)val2);
                            instr1.ops[0].value.imm.imm64 = (ulong)val2;
                            LabelList.Add(val2);
                        }
                        continue;// Don't disasm after it
                    case 0xFF:
                        if (instr1.bytes[1] == 0x15)//Call
                        {
                                long a = (long)instr1.disp.value.d64;
                                Console.WriteLine(a.ToString("X"));
                                if(ProcList.ContainsKey(a))
                                    if(ProcList[a].FName.Contains("ExitProcess"))continue;
                            }
                            break;
                }
                //Tasks.Add( instruction.Offset.FileOffset + (uint)instruction.Size);
                if ((!DTasks.Contains((long)instr1.Addr + Len)) && (!Tasks.Contains((long)instr1.Addr + Len)))
                    Tasks.Add((long)instr1.Addr + Len);
                instr1.Addr = FO2RVA((ulong)instr1.Addr);
                //                 += assembly.NTHeader.OptionalHeader.ImageBase;
            }
            _end:
            instr1.Addr = FO2RVA((ulong)instr1.Addr);
            lst.Sort(delegate(Stroka x, Stroka y)
            {
                if (x.addr > y.addr) return 1;
                if (x.addr == y.addr) return 0;
                return -1;
            });
            foreach (uint Addr in LabelList)
            {
                Stroka result = lst.Find(
                     delegate(Stroka sstr){return sstr.addr == Addr;}
                    );
                if (result != null)
                {
                    result.Label = "Loc_" + result.Inst.Addr.ToString("X8").Remove(0,2);
                }
            }
            return EndAddr-StartAdr;
        }

        #region Загружаем и работаем
        public void LoadFile(string FName)
        {
            byte[] sf_prefixes = new byte[mediana.MAX_INSTRUCTION_LEN];
            mediana.INSTRUCTION instr1 = new mediana.INSTRUCTION();
            mediana.DISASM_INOUT_PARAMS param = new mediana.DISASM_INOUT_PARAMS();

            PE = StreamLoader.FromFile(FName);
            info = new PEDirectory(PE);

            RaiseLogEvent(this, "Loading " + FName);
            assembly = Win32Assembly.LoadFile(FName);
            MeDisasm = new mediana(assembly);
            int i = 0;
            foreach (Section sect in assembly.NTHeader.Sections)
            {
                RaiseLogEvent(this, i.ToString() + ". Creating a new segment " + sect.RVA.ToString("X8") + " - " + (sect.RVA + sect.VirtualSize).ToString("X8") + "... ... OK");
                i++;
            }

            TFunc fnc = new TFunc((uint)assembly.NTHeader.OptionalHeader.ImageBase + assembly.NTHeader.OptionalHeader.Entrypoint.Rva, 0, 0, "main");

            param.arch = mediana.ARCH_ALL;
            param.sf_prefixes = sf_prefixes;
            param.mode = mediana.DISMODE.DISASSEMBLE_MODE_32;
            param.options = (byte)(mediana.DISASM_OPTION_APPLY_REL | mediana.DISASM_OPTION_OPTIMIZE_DISP);
            param.bas = assembly.NTHeader.OptionalHeader.ImageBase;
            MeDisasm.medi_disassemble(RVA2FO(fnc.Addr), ref instr1, ref param);
            Console.WriteLine(instr1.mnemonic);
            //MeDisasm.medi_dump(instr, buff, OUT_BUFF_SIZE, DUMP_OPTION_IMM_UHEX | DUMP_OPTION_DISP_HEX);
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
        public void StopWork()
        {
            bw.CancelAsync();
        }

        void bw_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (NewSubs.Count > 0)
            {
                foreach (KeyValuePair<long, TFunc> dct1 in NewSubs)
                    FullProcList.AddFunc(dct1.Value);
                NewSubs.Clear();
                (sender as BackgroundWorker).RunWorkerAsync();
            }
        }

        private void bw_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            foreach (KeyValuePair<long, TFunc> dct in ToDisasmFuncList)
            { 
                if ((worker.CancellationPending == true))
                {
                    e.Cancel = true;
                    break;
                }
                RaiseAddStrEvent("/*" + dct.Key.ToString("X8") + "*/ void " + dct.Value.FName + "(){\n");
                List<Stroka> tmp = new List<Stroka>();
                long Len = DisasmFunc(tmp, RVA2FO(dct.Key), FullProcList);
                dct.Value.Length = Len;
                dct.Value.bytes = assembly.Image.ReadBytes(RVA2FO(dct.Key), (int)Len);
                foreach(Stroka t in tmp)
                {
                    RaiseAddStrEvent(t.ToCmmString(NewSubs));
                }
                DisasmedFuncList.Add(dct.Key, dct.Value);
                RaiseAddStrEvent("};//" + dct.Value.FName  + "  Length:0x"+ dct.Value.Length.ToString("X") + " bytes \n\n");

            }
            ToDisasmFuncList.Clear();
        }
        #endregion

        #region Some stuff
        public ulong FO2RVA(ulong FO)
        {
            ulong addr = 0;
            foreach (Section sct in assembly.NTHeader.Sections)
            {
                if (sct.ContainsRawOffset((uint)FO))
                {
                    addr = (ulong)(sct.RVA + FO - sct.RawOffset + assembly.NTHeader.OptionalHeader.ImageBase);
                }
            }
            return addr;
        }
        public long RVA2FO(long RVA)
        {
            uint addr = 0;
            RVA -= (long)assembly.NTHeader.OptionalHeader.ImageBase;
            foreach (Section sct in assembly.NTHeader.Sections)
            {
                if (sct.ContainsRva((uint)RVA)) addr = sct.RVAToFileOffset((uint)RVA);
            }
            return addr;
        }
        #endregion

        #region Обработчики событий

        public delegate void FuncChanged(object sender, TFunc Func);
        public delegate void LogEvent(object sender, string LogStr);
        public delegate void VarEvent(object sender, TVar Var);
        public delegate void AddFuncEvent(object sender, TFunc Func);
        public delegate void AddStrEvent(string Str);
        public event LogEvent OnLogEvent;
        public event FuncChanged OnFuncChanged;
        public event VarEvent OnVarEvent;
        public event AddFuncEvent OnAddFunc;
        public event AddStrEvent OnAddStr;
        public void RaiseFuncChanged(object sender, TFunc Func)
        {
            if (OnFuncChanged != null) OnFuncChanged(sender, Func);
        }
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
        #endregion

    }

}
