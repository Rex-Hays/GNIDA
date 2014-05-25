using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TUP.AsmResolver;
using TUP.AsmResolver.ASM;

namespace GNIDA
{
    public class Opnd : Operand
    {

        public Opnd(object value) : base(value, OperandType.Normal, 0) { }
        public Opnd(object value, OperandType type): base(value, type, 0){}
        public Opnd(object value, OperandType type, int addition) : base(value, type, addition) { }
        public override string ToString(bool virtualString)
        {
            string additionstr = "";
            if (Addition > 0)
                additionstr = "+ 0x" + Addition.ToString("X");
            else if (Addition < 0)
                additionstr = "- 0x" + (Addition * -1).ToString("X");

            string valueString = ToCmmString(virtualString);
            switch (ValueType)
            {
                case OperandType.Normal:
                    return valueString;
                case OperandType.BytePointer:
                    return "BYTE PTR [" + valueString + additionstr + "]";
                case OperandType.WordPointer:
                    return "WORD PTR [" + valueString + additionstr + "]";
                case OperandType.DwordPointer:
                    return "DWORD PTR [" + valueString + additionstr + "]";
                case OperandType.FwordPointer:
                    return "FWORD PTR [" + valueString + additionstr + "]";
                case OperandType.QwordPointer:
                    return "QWORD PTR [" + valueString + additionstr + "]";
                case OperandType.LeaRegister:
                    return "[" + valueString + additionstr + "]";
            }
            return valueString;
        }
        private string ToCmmString(bool virtualString)
        {
            if (Value is byte)
                return "0x" + ((byte)Value).ToString("X2");
            if (Value is sbyte)
                return "0x" + ((sbyte)Value).ToString("X2");
            if (Value is short)
                return "0x" + ((short)Value).ToString("X4");
            if (Value is ushort)
                return "0x" + ((ushort)Value).ToString("X4");
            if (Value is int)
                return "0x" + ((int)Value).ToString("X8");
            if (Value is uint)
                return "0x" + ((uint)Value).ToString("X8");
            if (Value is long)
                return "0x" + ((long)Value).ToString("X16");
            if (Value is ulong)
                return "0x" + ((ulong)Value).ToString("X16");
            if (Value is Offset)
            {
                Offset offset = ((Offset)Value);
                string format = "v";
                if (!virtualString)
                {
                    if (this.ValueType == OperandType.Normal)
                        format = "o";
                    else
                        format = "v";
                }
                return offset.ToString(format);
            }
            if (Value is x86Instruction)
                return ((x86Instruction)Value).ToAsmString(virtualString);
            return Value.ToString();
        }
    }

    public class Myx86Instruction : x86Instruction
    {
        internal Myx86Instruction()
        {
            OpCode = x86OpCodes.Unknown;
            Offset = new Offset(0, 0, 0);
        }

        public static Myx86Instruction Create(x86OpCode opcode, Opnd operand1, Opnd operand2)
        {
            Myx86Instruction newInstruction = new Myx86Instruction();
            newInstruction.OpCode = opcode;
            newInstruction.operand1 = operand1;
            newInstruction.operand2 = operand2;
            newInstruction.GenerateBytes();
            return newInstruction;
        }

        public Opnd Operand1
        {
            get
            {
                return (Opnd)operand1;
            }
            set
            {
                operand1 = (Opnd)value;
            }
        }
        public Opnd Operand2
        {
            get
            {
                return (Opnd)operand2;
            }
            set
            {
                operand2 = value;
            }
        }
    }
}
