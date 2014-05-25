using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TUP.AsmResolver.ASM;
using TUP.AsmResolver;
using System.Reflection;

namespace GNIDA
{
    public class CmmDisassembler : x86Disassembler
    {
        //static List<x86OpCode> opcodeList;
        public CmmDisassembler()
        {
            LoadOpCodes();
        }
        public CmmDisassembler(Win32Assembly assembly)
            : base(assembly)
        {
        }
        public override void LoadOpCodes()
        {
            opcodeList = new List<x86OpCode>();
            foreach (FieldInfo info in typeof(Myx86OpCodes).GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Static))
            {
                if (info.FieldType == typeof(x86OpCode))
                {
                    opcodeList.Add((x86OpCode)info.GetValue(null));
                }
            }
        }

        internal void ProcessRegisterOperands(Myx86Instruction instruction)
        {
            switch (instruction.OpCode.GetRegisterOperandType())
            {
                case x86OperandType.Multiple32Register:
                case x86OperandType.Multiple32Or8Register:
                case x86OperandType.Multiple16Register:
                case x86OperandType.RegisterLeaRegister:
                    DecodeDoubleRegisters(instruction, instruction.code._opcodeBytes[instruction.code._opcodeBytes.Length - 1]);
                    break;
                case x86OperandType.Register8:
                case x86OperandType.Register32:
                case x86OperandType.Register32Or8:
                    DecodeSingleRegister(instruction, instruction.code._opcodeBytes[instruction.code._opcodeBytes.Length - 1]);
                    break;
            }
        }

        private void DecodeDoubleRegisters(Myx86Instruction instruction, byte registersToken)
        {
            Myx86Instruction result = instruction;
            x86OpCode resultopcode = instruction.OpCode;
            if (resultopcode._variableByteIndex == -1)
                return;
            resultopcode._opcodeBytes[instruction.OpCode._variableByteIndex] = registersToken;
            result.OpCode = resultopcode;

            // lea instructions has got different notations.
            bool isLEA = instruction.OpCode.IsBasedOn(x86OpCodes.Lea);

            x86Register register1;
            x86Register register2;

            DecodeRegisterPair(instruction, registersToken, out register1, out register2);

            // one register is a dword pointer
            if (registersToken <= 0x3F)
            {
                instruction.operand1 = new Opnd(register1, OperandType.DwordPointer);
                instruction.operand2 = new Opnd(register2, OperandType.Normal);
            }
            // one register is a dword pointer with an sbyte addition
            else if (registersToken > 0x3F && registersToken < 0x7F)
            {
                instruction.operandbytes = reader.ReadBytes(1);
                instruction.code._operandLength++;
                instruction.operand1 = new Opnd(register1, isLEA ? OperandType.LeaRegister : OperandType.DwordPointer, ASMGlobals.ByteToSByte(instruction.operandbytes[0]));
                instruction.operand2 = new Opnd(register2, OperandType.Normal);
            }
            // one register is a dword pointer with an int32 addition
            else if (registersToken >= 0x80 && registersToken <= 0xBF)
            {
                instruction.operandbytes = reader.ReadBytes(4);
                instruction.code._operandLength += 4;
                int addition = BitConverter.ToInt32(instruction.operandbytes, 0);
                instruction.operand1 = new Opnd(register1, isLEA ? OperandType.LeaRegister : OperandType.DwordPointer, addition);
                instruction.operand2 = new Opnd(register2, OperandType.Normal);
            }
            // normal multiple registers.
            else if (registersToken >= 0xC0 && registersToken <= 0xFF)
            {
                instruction.operand1 = new Opnd(register1, isLEA ? OperandType.LeaRegister : OperandType.Normal);
                instruction.operand2 = new Opnd(register2, OperandType.Normal);
            }
        }

        private void DecodeSingleRegister(Myx86Instruction instruction, byte registersToken)
        {
            Myx86Instruction result = instruction;
            x86OpCode resultopcode = instruction.OpCode;
            resultopcode._opcodeBytes[instruction.OpCode._variableByteIndex] = registersToken;
            result.OpCode = resultopcode;

            bool isGroupOpCode = MatchWithOpCodes(instruction.OpCode._opcodeBytes[0]).Length > 1;

            int actualregister = registersToken % 8;

            OperandType registerValueType = OperandType.Normal;
            int addition = 0;
            if (registersToken < 0x40)
            {
                //normal dword pointer
                if (!isGroupOpCode && registersToken >= 0x8)
                {
                    ProcessInvalidInstruction(instruction);
                    return;
                }
                registerValueType = OperandType.DwordPointer;

            }
            else if (registersToken >= 0x40 && registersToken < 0x80)
            {
                //dword pointer + sbyte addition
                if (!isGroupOpCode && registersToken >= 0x48)
                {
                    ProcessInvalidInstruction(instruction);
                    return;
                }
                registerValueType = OperandType.DwordPointer;
                instruction.operandbytes = new byte[] { reader.ReadByte() };
                instruction.OpCode._operandLength++;
                addition = ASMGlobals.ByteToSByte(instruction.operandbytes[0]);
            }
            else if (registersToken >= 0x80 && registersToken < 0xC0)
            {
                //dword pointer + int addition
                if (!isGroupOpCode && registersToken >= 0x88)
                {
                    ProcessInvalidInstruction(instruction);
                    return;
                }
                registerValueType = OperandType.DwordPointer;
                instruction.operandbytes = reader.ReadBytes(4);
                instruction.OpCode._operandLength += 4;
                addition = BitConverter.ToInt32(instruction.operandbytes, 0);
            }
            else if (registersToken >= 0xC0 && registersToken <= 0xFF)
            {
                // normal register -> do nothing.
                if (!isGroupOpCode && registersToken >= 0xC8)
                {
                    ProcessInvalidInstruction(instruction);
                    return;
                }
            }
            else
            {
                // TODO: Invalid single register token.

            }
            if (instruction.OpCode._operandType.HasFlag(x86OperandType.Register8))
            {
                actualregister |= (byte)x86Register.Bit8Mask;
            }
            if (instruction.OpCode._operandType.HasFlag(x86OperandType.Register32Or8))
            {
                actualregister |= GetSingleRegisterMask(registersToken);
            }

            instruction.operand1 = new Opnd((x86Register)actualregister, registerValueType, addition);
        }

        private Opnd CreateTargetOffset(uint offset, OperandType offsetType = OperandType.Normal)
        {
            return new Opnd(Offset.FromFileOffset(offset, assembly));
        }

        internal void ProcessOperandBytes(Myx86Instruction instruction)
        {
            uint nextOffset = (uint)(instruction.Offset.FileOffset + instruction.Size);

            Operand operandValue = null;
            switch (instruction.OpCode.GetNormalOperandType())
            {
                case x86OperandType.Byte:
                    operandValue = new Opnd(instruction.operandbytes[0]);
                    break;
                case x86OperandType.Word:
                    operandValue = new Opnd(BitConverter.ToInt16(instruction.operandbytes, 0));
                    break;
                case x86OperandType.WordAndByte:
                    break; // TODO
                case x86OperandType.Dword:
                    operandValue = new Opnd(BitConverter.ToUInt32(instruction.operandbytes, 0));
                    break;
                case x86OperandType.Fword:
                    break; // TODO
                case x86OperandType.Qword:
                    operandValue = new Opnd(BitConverter.ToUInt64(instruction.operandbytes, 0));
                    break;
                case x86OperandType.InstructionAddress:
                    operandValue = CreateTargetOffset((uint)(nextOffset + BitConverter.ToInt32(instruction.operandbytes, 0)));
                    break;
                case x86OperandType.ShortInstructionAddress:
                    operandValue = CreateTargetOffset((uint)(nextOffset + ASMGlobals.ByteToSByte(instruction.operandbytes[0])));
                    break;
                case x86OperandType.Register32:
                    DecodeSingleRegister(instruction, instruction.code._opcodeBytes[instruction.code._opcodeBytes.Length - 1]);
                    break;
                case x86OperandType.Instruction:
                    // opcode is prefix.
                    x86Instruction nextInstruction = DisassembleNextInstruction();
                    operandValue = new Operand(nextInstruction);
                    instruction.operandbytes = ASMGlobals.MergeBytes(nextInstruction.code.OpCodeBytes, nextInstruction.operandbytes);
                    instruction.code._operandLength = nextInstruction.Size;
                    break;
                case x86OperandType.None:
                    if (instruction.code.IsBasedOn(x86OpCodes.Unknown))
                        operandValue = new Operand(instruction.code._opcodeBytes[0]);
                    break;
            }

            if (operandValue != null)
            {
                if (instruction.operand1 != null)
                    instruction.operand2 = operandValue;
                else
                    instruction.operand1 = operandValue;
            }
        }
        internal Opnd CreatePtr(uint offset, OperandType offsetType = OperandType.DwordPointer)
        {
            return new Opnd(Offset.FromVa(offset, assembly), OperandType.DwordPointer);
        }
        internal void ProcessOverrideOperand(Myx86Instruction instruction)
        {
            x86OperandType operandType = instruction.OpCode.GetOverrideOperandType();
            if (operandType.HasFlag(x86OperandType.ForceDwordPointer))
            {

                if (instruction.operand2 != null)
                    if (instruction.operand2.Value is uint)
                        instruction.operand2 = CreatePtr((uint)instruction.operand2.Value, OperandType.DwordPointer);
                    else
                        instruction.operand2.ValueType = OperandType.DwordPointer;
                else
                    if (instruction.operand1.Value is uint)
                        instruction.operand1 = CreatePtr((uint)instruction.operand1.Value, OperandType.DwordPointer);
                    else
                        instruction.operand1.ValueType = OperandType.DwordPointer;
            }
            if (operandType.HasFlag(x86OperandType.OverrideOperandOrder))
            {
                Opnd temp = (Opnd)instruction.operand1;
                instruction.operand1 = instruction.operand2;
                instruction.operand2 = temp;
            }
        }
        public override x86Instruction DisassembleNextInstruction()
        {
            Myx86Instruction newInstruction = new Myx86Instruction();
            newInstruction.Offset = Offset.FromFileOffset((uint)reader.BaseStream.Position, assembly);

            newInstruction.OpCode = RetrieveNextOpCode();
            ProcessVariableByteIndex(ref newInstruction.code);

            ProcessRegisterOperands(newInstruction);
            byte[] rawOperand = ReadRawOperand(newInstruction.OpCode);
            newInstruction.operandbytes = ASMGlobals.MergeBytes(newInstruction.operandbytes, rawOperand);
            ProcessOperandBytes(newInstruction);

            ProcessOverrideOperand(newInstruction);

            return (x86Instruction)newInstruction;
        }
    }
}
