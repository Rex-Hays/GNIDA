using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TUP.AsmResolver;
using TUP.AsmResolver.ASM;
using System.Runtime.InteropServices;


namespace GNIDA
{
    //[StructLayout(LayoutKind.Explicit)]
    public struct OPERAND
    {
        public value1 value;
        public struct value1
        {
            public reg1 reg;
            //[StructLayout(LayoutKind.Explicit)]
            public struct reg1
            {
                //[FieldOffset(0)]
                public byte code;
                //[FieldOffset(1)]
                public byte type;
            };
            public imm1 imm;
            //[StructLayout(LayoutKind.Explicit)]
            public struct imm1
            {
                //[FieldOffset(0)]
                public byte imm8;
                //[FieldOffset(0)]
                public UInt16 imm16;
                //[FieldOffset(0)]
                public UInt32 imm32;
                //[FieldOffset(0)]
                public UInt64 imm64;
                //[FieldOffset(8)]
                public byte size;
                //[FieldOffset(9)]
                public byte offset;
            }

            //[StructLayout(LayoutKind.Explicit)]
            public far_addr1 far_addr;
            public struct far_addr1
            {
                //[StructLayout(LayoutKind.Explicit)]
                public far_addr321 far_addr32;
                public struct far_addr321
                {
                    //[FieldOffset(0)]
                    public UInt16 offset;
                    //[FieldOffset(2)]
                    public UInt16 seg;
                }
                public far_addr481 far_addr48;
                //[StructLayout(LayoutKind.Explicit)]
                public struct far_addr481
                {
                    //[FieldOffset(0)]
                    public UInt32 offset;
                    //[FieldOffset(4)]
                    public UInt16 seg;
                }
                //[FieldOffset(6)]
                public byte offset;
            }
            //    [StructLayout(LayoutKind.Explicit)]
            public addr1 addr;
            public struct addr1
            {
                //[FieldOffset(0)]
                public byte seg;
                //[FieldOffset(0)]
                public byte mod;
                //[FieldOffset(0)]
                public byte bas;
                //[FieldOffset(0)]
                public byte index;
                //[FieldOffset(0)]
                public byte scale;
            }
        }
        public UInt16 size; //Fuck... I need 16_t only for 'stx' size qualifier.
        public byte flags;
    };
    public class mediana
    {
        static uint MAX_MNEMONIC_LEN = 0x0C;
        static uint MAX_INSTRUCTION_LEN = 0x0F;

/*******************
* Instructions' IDs.
********************
*/
static ushort ID_NULL       = 0x0;
static ushort ID_SWITCH     = 0x1;
static ushort ID_0F         = 0x2;
static ushort ID_66         = 0x3;
static ushort ID_67         = 0x4;
static ushort ID_AAA        = 0x5;
static ushort ID_AAD        = 0x6;
static ushort ID_AAM        = 0x7;
static ushort ID_AAS        = 0x8;
static ushort ID_ADC        = 0x9;
static ushort ID_ADD        = 0xA;
static ushort ID_ADDPD      = 0xB;
static ushort ID_ADDPS      = 0xC;
static ushort ID_ADDSD      = 0xD;
static ushort ID_ADDSS      = 0xE;
static ushort ID_ADDSUBPD   = 0xF;
static ushort ID_ADDSUBPS   = 0x10;
static ushort ID_ALTER      = 0x11;
static ushort ID_AND        = 0x12;
static ushort ID_ANDNPD     = 0x13;
static ushort ID_ANDNPS     = 0x14;
static ushort ID_ANDPD      = 0x15;
static ushort ID_ANDPS      = 0x16;
static ushort ID_ARPL       = 0x17;
static ushort ID_BLENDPD    = 0x18;
static ushort ID_BLENDPS    = 0x19;
static ushort ID_BLENDVPD   = 0x1A;
static ushort ID_BLENDVPS   = 0x1B;
static ushort ID_BOUND      = 0x1C;
static ushort ID_BSF        = 0x1D;
static ushort ID_BSR        = 0x1E;
static ushort ID_BSWAP      = 0x1F;
static ushort ID_BT         = 0x20;
static ushort ID_BTC        = 0x21;
static ushort ID_BTR        = 0x22;
static ushort ID_BTS        = 0x23;
static ushort ID_CALL       = 0x24;
static ushort ID_CALLF      = 0x25;
static ushort ID_CBW        = 0x26;
static ushort ID_CLC        = 0x27;
static ushort ID_CLD        = 0x28;
static ushort ID_CLFLUSH    = 0x29;
static ushort ID_CLI        = 0x2A;
static ushort ID_CLTS       = 0x2B;
static ushort ID_CMC        = 0x2C;
static ushort ID_CMOVA      = 0x2D;
static ushort ID_CMOVAE     = 0x2E;
static ushort ID_CMOVB      = 0x2F;
static ushort ID_CMOVBE     = 0x30;
static ushort ID_CMOVG      = 0x31;
static ushort ID_CMOVGE     = 0x32;
static ushort ID_CMOVL      = 0x33;
static ushort ID_CMOVLE     = 0x34;
static ushort ID_CMOVNO     = 0x35;
static ushort ID_CMOVNP     = 0x36;
static ushort ID_CMOVNS     = 0x37;
static ushort ID_CMOVNZ     = 0x38;
static ushort ID_CMOVO      = 0x39;
static ushort ID_CMOVP      = 0x3A;
static ushort ID_CMOVS      = 0x3B;
static ushort ID_CMOVZ      = 0x3C;
static ushort ID_CMP        = 0x3D;
static ushort ID_CMPPD      = 0x3E;
static ushort ID_CMPPS      = 0x3F;
static ushort ID_CMPS       = 0x40;
static ushort ID_CMPSD      = 0x41;
static ushort ID_CMPSS      = 0x42;
static ushort ID_CMPXCHG    = 0x43;
static ushort ID_CMPXCHG8B  = 0x44;
static ushort ID_COMISD     = 0x45;
static ushort ID_COMISS     = 0x46;
static ushort ID_CPUID      = 0x47;
static ushort ID_CRC32      = 0x48;
static ushort ID_CS         = 0x49;
static ushort ID_CVTDQ2PD   = 0x4A;
static ushort ID_CVTDQ2PS   = 0x4B;
static ushort ID_CVTPD2DQ   = 0x4C;
static ushort ID_CVTPD2PI   = 0x4D;
static ushort ID_CVTPD2PS   = 0x4E;
static ushort ID_CVTPI2PD   = 0x4F;
static ushort ID_CVTPI2PS   = 0x50;
static ushort ID_CVTPS2DQ   = 0x51;
static ushort ID_CVTPS2PD   = 0x52;
static ushort ID_CVTPS2PI   = 0x53;
static ushort ID_CVTSD2SI   = 0x54;
static ushort ID_CVTSD2SS   = 0x55;
static ushort ID_CVTSI2SD   = 0x56;
static ushort ID_CVTSI2SS   = 0x57;
static ushort ID_CVTSS2SD   = 0x58;
static ushort ID_CVTSS2SI   = 0x59;
static ushort ID_CVTTPD2DQ  = 0x5A;
static ushort ID_CVTTPD2PI  = 0x5B;
static ushort ID_CVTTPS2DQ  = 0x5C;
static ushort ID_CVTTPS2PI  = 0x5D;
static ushort ID_CVTTSD2SI  = 0x5E;
static ushort ID_CVTTSS2SI  = 0x5F;
static ushort ID_CWD        = 0x60;
static ushort ID_DAA        = 0x61;
static ushort ID_DAS        = 0x62;
static ushort ID_DEC        = 0x63;
static ushort ID_DIV        = 0x64;
static ushort ID_DIVPD      = 0x65;
static ushort ID_DIVPS      = 0x66;
static ushort ID_DIVSD      = 0x67;
static ushort ID_DIVSS      = 0x68;
static ushort ID_DPPD       = 0x69;
static ushort ID_DPPS       = 0x6A;
static ushort ID_DS         = 0x6B;
static ushort ID_EMMS       = 0x6C;
static ushort ID_ENTER      = 0x6D;
static ushort ID_ES         = 0x6E;
static ushort ID_EXTRACTPS  = 0x6F;
static ushort ID_F2XM1      = 0x70;
static ushort ID_FABS       = 0x71;
static ushort ID_FADD       = 0x72;
static ushort ID_FADDP      = 0x73;
static ushort ID_FBLD       = 0x74;
static ushort ID_FBSTP      = 0x75;
static ushort ID_FCHS       = 0x76;
static ushort ID_FCMOVA     = 0x77;
static ushort ID_FCMOVB     = 0x78;
static ushort ID_FCMOVBE    = 0x79;
static ushort ID_FCMOVNB    = 0x7A;
static ushort ID_FCMOVNU    = 0x7B;
static ushort ID_FCMOVNZ    = 0x7C;
static ushort ID_FCMOVU     = 0x7D;
static ushort ID_FCMOVZ     = 0x7E;
static ushort ID_FCOM       = 0x7F;
static ushort ID_FCOM2      = 0x80;
static ushort ID_FCOMI      = 0x81;
static ushort ID_FCOMIP     = 0x82;
static ushort ID_FCOMP      = 0x83;
static ushort ID_FCOMP3     = 0x84;
static ushort ID_FCOMP5     = 0x85;
static ushort ID_FCOMPP     = 0x86;
static ushort ID_FCOS       = 0x87;
static ushort ID_FDECSTP    = 0x88;
static ushort ID_FDIV       = 0x89;
static ushort ID_FDIVP      = 0x8A;
static ushort ID_FDIVR      = 0x8B;
static ushort ID_FDIVRP     = 0x8C;
static ushort ID_FFREE      = 0x8D;
static ushort ID_FFREEP     = 0x8E;
static ushort ID_FIADD      = 0x8F;
static ushort ID_FICOM      = 0x90;
static ushort ID_FICOMP     = 0x91;
static ushort ID_FIDIV      = 0x92;
static ushort ID_FIDIVR     = 0x93;
static ushort ID_FILD       = 0x94;
static ushort ID_FIMUL      = 0x95;
static ushort ID_FINCSTP    = 0x96;
static ushort ID_FIST       = 0x97;
static ushort ID_FISTP      = 0x98;
static ushort ID_FISTTP     = 0x99;
static ushort ID_FISUB      = 0x9A;
static ushort ID_FISUBR     = 0x9B;
static ushort ID_FLD        = 0x9C;
static ushort ID_FLD1       = 0x9D;
static ushort ID_FLD2LE     = 0x9E;
static ushort ID_FLD2LT     = 0x9F;
static ushort ID_FLDCW      = 0xA0;
static ushort ID_FLDENV     = 0xA1;
static ushort ID_FLDLG2     = 0xA2;
static ushort ID_FLDLN2     = 0xA3;
static ushort ID_FLDPI      = 0xA4;
static ushort ID_FLDZ       = 0xA5;
static ushort ID_FMUL       = 0xA6;
static ushort ID_FMULP      = 0xA7;
static ushort ID_FNCLEX     = 0xA8;
static ushort ID_FNDISI     = 0xA9;
static ushort ID_FNENI      = 0xAA;
static ushort ID_FNINIT     = 0xAB;
static ushort ID_FNOP       = 0xAC;
static ushort ID_FNSAVE     = 0xAD;
static ushort ID_FNSETPM    = 0xAE;
static ushort ID_FNSTCW     = 0xAF;
static ushort ID_FNSTENV    = 0xB0;
static ushort ID_FNSTSW     = 0xB1;
static ushort ID_FPATAN     = 0xB2;
static ushort ID_FPREM      = 0xB3;
static ushort ID_FPREM1     = 0xB4;
static ushort ID_FPTAN      = 0xB5;
static ushort ID_FRNDINT    = 0xB6;
static ushort ID_FRSTOR     = 0xB7;
static ushort ID_FS         = 0xB8;
static ushort ID_FSCALE     = 0xB9;
static ushort ID_FSIN       = 0xBA;
static ushort ID_FSINCOS    = 0xBB;
static ushort ID_FSQRT      = 0xBC;
static ushort ID_FST        = 0xBD;
static ushort ID_FSTP       = 0xBE;
static ushort ID_FSTP1      = 0xBF;
static ushort ID_FSTP8      = 0xC0;
static ushort ID_FSTP9      = 0xC1;
static ushort ID_FSUB       = 0xC2;
static ushort ID_FSUBP      = 0xC3;
static ushort ID_FSUBR      = 0xC4;
static ushort ID_FSUBRP     = 0xC5;
static ushort ID_FTST       = 0xC6;
static ushort ID_FUCOM      = 0xC7;
static ushort ID_FUCOMI     = 0xC8;
static ushort ID_FUCOMIP    = 0xC9;
static ushort ID_FUCOMP     = 0xCA;
static ushort ID_FUCOMPP    = 0xCB;
static ushort ID_FWAIT      = 0xCC;
static ushort ID_FXAM       = 0xCD;
static ushort ID_FXCH       = 0xCE;
static ushort ID_FXCH4      = 0xCF;
static ushort ID_FXCH7      = 0xD0;
static ushort ID_FXRSTOR    = 0xD1;
static ushort ID_FXSAVE     = 0xD2;
static ushort ID_FXTRACT    = 0xD3;
static ushort ID_FYL2X      = 0xD4;
static ushort ID_FYL2XP1    = 0xD5;
static ushort ID_GETSEC     = 0xD6;
static ushort ID_GS         = 0xD7;
static ushort ID_HADDPD     = 0xD8;
static ushort ID_HADDPS     = 0xD9;
static ushort ID_HINTNOP    = 0xDA;
static ushort ID_HLT        = 0xDB;
static ushort ID_HSUBPD     = 0xDC;
static ushort ID_HSUBPS     = 0xDD;
static ushort ID_ICEBP      = 0xDE;
static ushort ID_IDIV       = 0xDF;
static ushort ID_IMUL       = 0xE0;
static ushort ID_IN         = 0xE1;
static ushort ID_INC        = 0xE2;
static ushort ID_INS        = 0xE3;
static ushort ID_INSERTPS   = 0xE4;
static ushort ID_INT        = 0xE5;
static ushort ID_INTO       = 0xE6;
static ushort ID_INVD       = 0xE7;
static ushort ID_INVEPT     = 0xE8;
static ushort ID_INVLPG     = 0xE9;
static ushort ID_INVVPID    = 0xEA;
static ushort ID_IRET       = 0xEB;
static ushort ID_JA         = 0xEC;
static ushort ID_JAE        = 0xED;
static ushort ID_JB         = 0xEE;
static ushort ID_JBE        = 0xEF;
static ushort ID_JCXZ       = 0xF0;
static ushort ID_JG         = 0xF1;
static ushort ID_JGE        = 0xF2;
static ushort ID_JL         = 0xF3;
static ushort ID_JLE        = 0xF4;
static ushort ID_JMP        = 0xF5;
static ushort ID_JMPE       = 0xF6;
static ushort ID_JMPF       = 0xF7;
static ushort ID_JNO        = 0xF8;
static ushort ID_JNP        = 0xF9;
static ushort ID_JNS        = 0xFA;
static ushort ID_JNZ        = 0xFB;
static ushort ID_JO         = 0xFC;
static ushort ID_JP         = 0xFD;
static ushort ID_JS         = 0xFE;
static ushort ID_JZ         = 0xFF;
static ushort ID_LAHF       = 0x100;
static ushort ID_LAR        = 0x101;
static ushort ID_LDDQU      = 0x102;
static ushort ID_LDMXCSR    = 0x103;
static ushort ID_LDS        = 0x104;
static ushort ID_LEA        = 0x105;
static ushort ID_LEAVE      = 0x106;
static ushort ID_LES        = 0x107;
static ushort ID_LFENCE     = 0x108;
static ushort ID_LFS        = 0x109;
static ushort ID_LGDT       = 0x10A;
static ushort ID_LGS        = 0x10B;
static ushort ID_LIDT       = 0x10C;
static ushort ID_LLDT       = 0x10D;
static ushort ID_LMSW       = 0x10E;
static ushort ID_LOADALL    = 0x10F;
static ushort ID_LOCK       = 0x110;
static ushort ID_LODS       = 0x111;
static ushort ID_LOOP       = 0x112;
static ushort ID_LOOPNZ     = 0x113;
static ushort ID_LOOPZ      = 0x114;
static ushort ID_LSL        = 0x115;
static ushort ID_LSS        = 0x116;
static ushort ID_LTR        = 0x117;
static ushort ID_MASKMOVDQU = 0x118;
static ushort ID_MASKMOVQ   = 0x119;
static ushort ID_MAXPD      = 0x11A;
static ushort ID_MAXPS      = 0x11B;
static ushort ID_MAXSD      = 0x11C;
static ushort ID_MAXSS      = 0x11D;
static ushort ID_MFENCE     = 0x11E;
static ushort ID_MINPD      = 0x11F;
static ushort ID_MINPS      = 0x120;
static ushort ID_MINSD      = 0x121;
static ushort ID_MINSS      = 0x122;
static ushort ID_MONITOR    = 0x123;
static ushort ID_MOV        = 0x124;
static ushort ID_MOVAPD     = 0x125;
static ushort ID_MOVAPS     = 0x126;
static ushort ID_MOVBE      = 0x127;
static ushort ID_MOVD       = 0x128;
static ushort ID_MOVDDUP    = 0x129;
static ushort ID_MOVDQ2Q    = 0x12A;
static ushort ID_MOVDQA     = 0x12B;
static ushort ID_MOVDQU     = 0x12C;
static ushort ID_MOVHLPS    = 0x12D;
static ushort ID_MOVHPD     = 0x12E;
static ushort ID_MOVHPS     = 0x12F;
static ushort ID_MOVLPD     = 0x130;
static ushort ID_MOVLPS     = 0x131;
static ushort ID_MOVMSKPD   = 0x132;
static ushort ID_MOVMSKPS   = 0x133;
static ushort ID_MOVNTDQ    = 0x134;
static ushort ID_MOVNTDQA   = 0x135;
static ushort ID_MOVNTI     = 0x136;
static ushort ID_MOVNTPD    = 0x137;
static ushort ID_MOVNTPS    = 0x138;
static ushort ID_MOVNTQ     = 0x139;
static ushort ID_MOVQ       = 0x13A;
static ushort ID_MOVQ2DQ    = 0x13B;
static ushort ID_MOVS       = 0x13C;
static ushort ID_MOVSD      = 0x13D;
static ushort ID_MOVSHDUP   = 0x13E;
static ushort ID_MOVSLDUP   = 0x13F;
static ushort ID_MOVSS      = 0x140;
static ushort ID_MOVSX      = 0x141;
static ushort ID_MOVSXD     = 0x142;
static ushort ID_MOVUPD     = 0x143;
static ushort ID_MOVUPS     = 0x144;
static ushort ID_MOVZX      = 0x145;
static ushort ID_MPSADBW    = 0x146;
static ushort ID_MUL        = 0x147;
static ushort ID_MULPD      = 0x148;
static ushort ID_MULPS      = 0x149;
static ushort ID_MULSD      = 0x14A;
static ushort ID_MULSS      = 0x14B;
static ushort ID_MWAIT      = 0x14C;
static ushort ID_NEG        = 0x14D;
static ushort ID_NOP        = 0x14E;
static ushort ID_NOT        = 0x14F;
static ushort ID_OR         = 0x150;
static ushort ID_ORPD       = 0x151;
static ushort ID_ORPS       = 0x152;
static ushort ID_OUT        = 0x153;
static ushort ID_OUTS       = 0x154;
static ushort ID_PABSB      = 0x155;
static ushort ID_PABSD      = 0x156;
static ushort ID_PABSW      = 0x157;
static ushort ID_PACKSSDW   = 0x158;
static ushort ID_PACKSSWB   = 0x159;
static ushort ID_PACKUSDW   = 0x15A;
static ushort ID_PACKUSWB   = 0x15B;
static ushort ID_PADDB      = 0x15C;
static ushort ID_PADDD      = 0x15D;
static ushort ID_PADDQ      = 0x15E;
static ushort ID_PADDSB     = 0x15F;
static ushort ID_PADDSW     = 0x160;
static ushort ID_PADDUSB    = 0x161;
static ushort ID_PADDUSW    = 0x162;
static ushort ID_PADDW      = 0x163;
static ushort ID_PALIGNR    = 0x164;
static ushort ID_PAND       = 0x165;
static ushort ID_PANDN      = 0x166;
static ushort ID_PAUSE      = 0x167;
static ushort ID_PAVGB      = 0x168;
static ushort ID_PAVGW      = 0x169;
static ushort ID_PBLENDVB   = 0x16A;
static ushort ID_PBLENDW    = 0x16B;
static ushort ID_PCMPEQB    = 0x16C;
static ushort ID_PCMPEQD    = 0x16D;
static ushort ID_PCMPEQQ    = 0x16E;
static ushort ID_PCMPEQW    = 0x16F;
static ushort ID_PCMPESTRI  = 0x170;
static ushort ID_PCMPESTRM  = 0x171;
static ushort ID_PCMPGTB    = 0x172;
static ushort ID_PCMPGTD    = 0x173;
static ushort ID_PCMPGTQ    = 0x174;
static ushort ID_PCMPGTW    = 0x175;
static ushort ID_PCMPISTRI  = 0x176;
static ushort ID_PCMPISTRM  = 0x177;
static ushort ID_PEXTRB     = 0x178;
static ushort ID_PEXTRQ     = 0x179;
static ushort ID_PEXTRW     = 0x17A;
static ushort ID_PHADDD     = 0x17B;
static ushort ID_PHADDSW    = 0x17C;
static ushort ID_PHADDW     = 0x17D;
static ushort ID_PHMINPOSUW = 0x17E;
static ushort ID_PHSUBD     = 0x17F;
static ushort ID_PHSUBSW    = 0x180;
static ushort ID_PHSUBW     = 0x181;
static ushort ID_PINSRB     = 0x182;
static ushort ID_PINSRQ     = 0x183;
static ushort ID_PINSRW     = 0x184;
static ushort ID_PMADDUBSW  = 0x185;
static ushort ID_PMADDWD    = 0x186;
static ushort ID_PMAXSB     = 0x187;
static ushort ID_PMAXSD     = 0x188;
static ushort ID_PMAXSW     = 0x189;
static ushort ID_PMAXUB     = 0x18A;
static ushort ID_PMAXUD     = 0x18B;
static ushort ID_PMAXUW     = 0x18C;
static ushort ID_PMINSB     = 0x18D;
static ushort ID_PMINSD     = 0x18E;
static ushort ID_PMINSW     = 0x18F;
static ushort ID_PMINUB     = 0x190;
static ushort ID_PMINUD     = 0x191;
static ushort ID_PMINUW     = 0x192;
static ushort ID_PMOVMSKB   = 0x193;
static ushort ID_PMOVSXBD   = 0x194;
static ushort ID_PMOVSXBQ   = 0x195;
static ushort ID_PMOVSXBW   = 0x196;
static ushort ID_PMOVSXDQ   = 0x197;
static ushort ID_PMOVSXWD   = 0x198;
static ushort ID_PMOVSXWQ   = 0x199;
static ushort ID_PMOVZXBD   = 0x19A;
static ushort ID_PMOVZXBQ   = 0x19B;
static ushort ID_PMOVZXBW   = 0x19C;
static ushort ID_PMOVZXDQ   = 0x19D;
static ushort ID_PMOVZXWD   = 0x19E;
static ushort ID_PMOVZXWQ   = 0x19F;
static ushort ID_PMULDQ     = 0x1A0;
static ushort ID_PMULHRSW   = 0x1A1;
static ushort ID_PMULHUW    = 0x1A2;
static ushort ID_PMULHW     = 0x1A3;
static ushort ID_PMULLD     = 0x1A4;
static ushort ID_PMULLW     = 0x1A5;
static ushort ID_PMULUDQ    = 0x1A6;
static ushort ID_POP        = 0x1A7;
static ushort ID_POPA       = 0x1A8;
static ushort ID_POPCNT     = 0x1A9;
static ushort ID_POPF       = 0x1AA;
static ushort ID_POR        = 0x1AB;
static ushort ID_PREFETCHNTA= 0x1AC;
static ushort ID_PREFETCHT0 = 0x1AD;
static ushort ID_PREFETCHT1 = 0x1AE;
static ushort ID_PREFETCHT2 = 0x1AF;
static ushort ID_PSADBW     = 0x1B0;
static ushort ID_PSHUFB     = 0x1B1;
static ushort ID_PSHUFD     = 0x1B2;
static ushort ID_PSHUFHW    = 0x1B3;
static ushort ID_PSHUFLW    = 0x1B4;
static ushort ID_PSHUFW     = 0x1B5;
static ushort ID_PSIGNB     = 0x1B6;
static ushort ID_PSIGND     = 0x1B7;
static ushort ID_PSIGNW     = 0x1B8;
static ushort ID_PSLLD      = 0x1B9;
static ushort ID_PSLLDQ     = 0x1BA;
static ushort ID_PSLLQ      = 0x1BB;
static ushort ID_PSLLW      = 0x1BC;
static ushort ID_PSRAD      = 0x1BD;
static ushort ID_PSRAW      = 0x1BE;
static ushort ID_PSRLD      = 0x1BF;
static ushort ID_PSRLDQ     = 0x1C0;
static ushort ID_PSRLQ      = 0x1C1;
static ushort ID_PSRLW      = 0x1C2;
static ushort ID_PSUBB      = 0x1C3;
static ushort ID_PSUBD      = 0x1C4;
static ushort ID_PSUBQ      = 0x1C5;
static ushort ID_PSUBSB     = 0x1C6;
static ushort ID_PSUBSW     = 0x1C7;
static ushort ID_PSUBUSB    = 0x1C8;
static ushort ID_PSUBUSW    = 0x1C9;
static ushort ID_PSUBW      = 0x1CA;
static ushort ID_PTEST      = 0x1CB;
static ushort ID_PUNPCKHBD  = 0x1CC;
static ushort ID_PUNPCKHBDQ = 0x1CD;
static ushort ID_PUNPCKHBW  = 0x1CE;
static ushort ID_PUNPCKHDQ  = 0x1CF;
static ushort ID_PUNPCKHQDQ = 0x1D0;
static ushort ID_PUNPCKHWD  = 0x1D1;
static ushort ID_PUNPCKLBW  = 0x1D2;
static ushort ID_PUNPCKLDQ  = 0x1D3;
static ushort ID_PUNPCKLQDQ = 0x1D4;
static ushort ID_PUNPCKLWD  = 0x1D5;
static ushort ID_PUSH       = 0x1D6;
static ushort ID_PUSHA      = 0x1D7;
static ushort ID_PUSHF      = 0x1D8;
static ushort ID_PXOR       = 0x1D9;
static ushort ID_RCL        = 0x1DA;
static ushort ID_RCPPS      = 0x1DB;
static ushort ID_RCPSS      = 0x1DC;
static ushort ID_RCR        = 0x1DD;
static ushort ID_RDMSR      = 0x1DE;
static ushort ID_RDPMC      = 0x1DF;
static ushort ID_RDTSC      = 0x1E0;
static ushort ID_RDTSCP     = 0x1E1;
static ushort ID_REPNZ      = 0x1E2;
static ushort ID_REPZ       = 0x1E3;
static ushort ID_RETF       = 0x1E4;
static ushort ID_RETN       = 0x1E5;
static ushort ID_ROL        = 0x1E6;
static ushort ID_ROR        = 0x1E7;
static ushort ID_ROUNDPD    = 0x1E8;
static ushort ID_ROUNDPS    = 0x1E9;
static ushort ID_ROUNDSD    = 0x1EA;
static ushort ID_ROUNDSS    = 0x1EB;
static ushort ID_RSM        = 0x1EC;
static ushort ID_RSQRTPS    = 0x1ED;
static ushort ID_RSQRTSS    = 0x1EE;
static ushort ID_SAHF       = 0x1EF;
static ushort ID_SAL        = 0x1F0;
static ushort ID_SAR        = 0x1F1;
static ushort ID_SBB        = 0x1F2;
static ushort ID_SCAS       = 0x1F3;
static ushort ID_SETA       = 0x1F4;
static ushort ID_SETAE      = 0x1F5;
static ushort ID_SETALC     = 0x1F6;
static ushort ID_SETB       = 0x1F7;
static ushort ID_SETBE      = 0x1F8;
static ushort ID_SETG       = 0x1F9;
static ushort ID_SETGE      = 0x1FA;
static ushort ID_SETL       = 0x1FB;
static ushort ID_SETLE      = 0x1FC;
static ushort ID_SETNO      = 0x1FD;
static ushort ID_SETNP      = 0x1FE;
static ushort ID_SETNS      = 0x1FF;
static ushort ID_SETNZ      = 0x200;
static ushort ID_SETO       = 0x201;
static ushort ID_SETP       = 0x202;
static ushort ID_SETS       = 0x203;
static ushort ID_SETZ       = 0x204;
static ushort ID_SFENCE     = 0x205;
static ushort ID_SGDT       = 0x206;
static ushort ID_SHL        = 0x207;
static ushort ID_SHLD       = 0x208;
static ushort ID_SHR        = 0x209;
static ushort ID_SHRD       = 0x20A;
static ushort ID_SHUFPD     = 0x20B;
static ushort ID_SHUFPS     = 0x20C;
static ushort ID_SIDT       = 0x20D;
static ushort ID_SLDT       = 0x20E;
static ushort ID_SMSW       = 0x20F;
static ushort ID_SQRTPD     = 0x210;
static ushort ID_SQRTPS     = 0x211;
static ushort ID_SQRTSD     = 0x212;
static ushort ID_SQRTSS     = 0x213;
static ushort ID_SS         = 0x214;
static ushort ID_STC        = 0x215;
static ushort ID_STD        = 0x216;
static ushort ID_STI        = 0x217;
static ushort ID_STMXCSR    = 0x218;
static ushort ID_STOS       = 0x219;
static ushort ID_STR        = 0x21A;
static ushort ID_SUB        = 0x21B;
static ushort ID_SUBPD      = 0x21C;
static ushort ID_SUBPS      = 0x21D;
static ushort ID_SUBSD      = 0x21E;
static ushort ID_SUBSS      = 0x21F;
static ushort ID_SWAPGS     = 0x220;
static ushort ID_SYSCALL    = 0x221;
static ushort ID_SYSENTER   = 0x222;
static ushort ID_SYSEXIT    = 0x223;
static ushort ID_SYSRET     = 0x224;
static ushort ID_TEST       = 0x225;
static ushort ID_UCOMISD    = 0x226;
static ushort ID_UCOMISS    = 0x227;
static ushort ID_UD         = 0x228;
static ushort ID_UD2        = 0x229;
static ushort ID_UNPCKHPD   = 0x22A;
static ushort ID_UNPCKHPS   = 0x22B;
static ushort ID_UNPCKLPD   = 0x22C;
static ushort ID_UNPCKLPS   = 0x22D;
static ushort ID_VERR       = 0x22E;
static ushort ID_VERW       = 0x22F;
static ushort ID_VMCALL     = 0x230;
static ushort ID_VMCLEAR    = 0x231;
static ushort ID_VMLAUNCH   = 0x232;
static ushort ID_VMPTRLD    = 0x233;
static ushort ID_VMPTRST    = 0x234;
static ushort ID_VMREAD     = 0x235;
static ushort ID_VMRESUME   = 0x236;
static ushort ID_VMWRITE    = 0x237;
static ushort ID_VMXOFF     = 0x238;
static ushort ID_VMXON      = 0x239;
static ushort ID_WBINVD     = 0x23A;
static ushort ID_WRMSR      = 0x23B;
static ushort ID_XADD       = 0x23C;
static ushort ID_XCHG       = 0x23D;
static ushort ID_XGETBV     = 0x23E;
static ushort ID_XLAT       = 0x23F;
static ushort ID_XOR        = 0x240;
static ushort ID_XORPD      = 0x241;
static ushort ID_XORPS      = 0x242;
static ushort ID_XRSTOR     = 0x243;
static ushort ID_XSAVE      = 0x244;
static ushort ID_XSETBV     = 0x245;




static ushort PROP_LOCK = 0x1;
static ushort PROP_I64 = 0x2;
static ushort PROP_O64 = 0x4;
static ushort PROP_IOPL = 0x8;
static ushort PROP_RING0 = 0x10;
static ushort PROP_SERIAL = 0x20;
static ushort PROP_MODRM = 0x40;
static ushort PROP_UNDOC = 0x80;
static ushort PROP_POST_PROC = 0x100;

static byte TQ_NULL = 0xFF;
static byte TQ_1    = 0x0;
static byte TQ_3    = 0x1;
static byte TQ_A    = 0x2;
static byte TQ_C    = 0x3;
static byte TQ_D    = 0x4;
static byte TQ_E    = 0x5;
static byte TQ_G    = 0x6;
static byte TQ_H    = 0x7;
static byte TQ_I    = 0x8;
static byte TQ_J    = 0x9;
static byte TQ_M    = 0xA;
static byte TQ_N    = 0xB;
static byte TQ_O    = 0xC;
static byte TQ_P    = 0xD;
static byte TQ_Q    = 0xE;
static byte TQ_R    = 0xF;
static byte TQ_S    = 0x10;
static byte TQ_T    = 0x11;
static byte TQ_U    = 0x12;
static byte TQ_V    = 0x13;
static byte TQ_W    = 0x14;
static byte TQ_X    = 0x15;
static byte TQ_Y    = 0x16;
static byte TQ_Z    = 0x17;
static byte TQ_rAX  = 0x18;
static byte TQ_rCX  = 0x19;
static byte TQ_rDX  = 0x1A;
static byte TQ_rBX  = 0x1B;
static byte TQ_rSP  = 0x1C;
static byte TQ_rBP  = 0x1D;
static byte TQ_rSI  = 0x1E;
static byte TQ_rDI  = 0x1F;
static byte TQ_fES  = 0x20;
static byte TQ_fEST = 0x21;
static byte TQ_fST0 = 0x22;
static byte TQ_CS   = 0x23;
static byte TQ_DS   = 0x24;
static byte TQ_ES   = 0x25;
static byte TQ_SS   = 0x26;
static byte TQ_FS   = 0x27;
static byte TQ_GS   = 0x28;
static byte TQ_PREF_CS = 0x29;
static byte TQ_PREF_DS = 0x2A;
static byte TQ_PREF_ES = 0x2B;
static byte TQ_PREF_SS = 0x2C;
static byte TQ_PREF_FS = 0x2D;
static byte TQ_PREF_GS = 0x2E;
static byte TQ_PREF_66 = 0x2F;
static byte TQ_PREF_67 = 0x30;
static byte TQ_PREF_F2 = 0x31;
static byte TQ_PREF_F3 = 0x32;
static byte TQ_PREF_F0 = 0x33;

static byte SQ_NULL   = 0xFF;
static byte SQ_a      = 0x0;
static byte SQ_b      = 0x1;
static byte SQ_bcd    = 0x2;
static byte SQ_bdqp   = 0x3;
static byte SQ_bs     = 0x4;
static byte SQ_bss    = 0x5;
static byte SQ_d      = 0x6;
static byte SQ_ddq    = 0x7;
static byte SQ_di     = 0x8;
static byte SQ_dq     = 0x9;
static byte SQ_dq64   = 0xA;
static byte SQ_dqp    = 0xB;
static byte SQ_dr     = 0xC;
static byte SQ_ds     = 0xD;
static byte SQ_e      = 0xE;
static byte SQ_er     = 0xF;
static byte SQ_p      = 0x10;
static byte SQ_pd     = 0x11;
static byte SQ_pi     = 0x12;
static byte SQ_ps     = 0x13;
static byte SQ_psq    = 0x14;
static byte SQ_ptp    = 0x15;
static byte SQ_q      = 0x16;
static byte SQ_qdq    = 0x17;
static byte SQ_qi     = 0x18;
static byte SQ_s      = 0x19;
static byte SQ_sd     = 0x1A;
static byte SQ_sr     = 0x1B;
static byte SQ_ss     = 0x1C;
static byte SQ_st     = 0x1D;
static byte SQ_stx    = 0x1E;
static byte SQ_v      = 0x1F;
static byte SQ_v67q64 = 0x20;
static byte SQ_vd64   = 0x21;
static byte SQ_vds    = 0x22;
static byte SQ_vq64   = 0x23;
static byte SQ_vqp    = 0x24;
static byte SQ_vs     = 0x25;
static byte SQ_w      = 0x26;
static byte SQ_wdq    = 0x27;
static byte SQ_wdqp   = 0x28;
static byte SQ_wi     = 0x29;
static byte SQ_wv     = 0x2A;
static byte SQ_wvqp   = 0x2B;

static byte IDX_1BYTE    = 0x0;
static byte IDX_80       = 0x1;
static byte IDX_81       = 0x2;
static byte IDX_82       = 0x3;
static byte IDX_83       = 0x4;
static byte IDX_8F       = 0x5;
static byte IDX_C0       = 0x6;
static byte IDX_C1       = 0x7;
static byte IDX_C6       = 0x8;
static byte IDX_C7       = 0x9;
static byte IDX_D0       = 0xA;
static byte IDX_D1       = 0xB;
static byte IDX_D2       = 0xC;
static byte IDX_D3       = 0xD;
static byte IDX_F6       = 0xE;
static byte IDX_F7       = 0xF;
static byte IDX_FE       = 0x10;
static byte IDX_FF       = 0x11;

static byte IDX_D8_SWTCH = 0x12;
static byte IDX_D8_MEM   = 0x13;
static byte IDX_D8_NOMEM = 0x14;

static byte IDX_D9_SWTCH = 0x15;
static byte IDX_D9_MEM   = 0x16;
static byte IDX_D9_NOMEM = 0x17;

static byte IDX_DA_SWTCH = 0x18;
static byte IDX_DA_MEM   = 0x19;
static byte IDX_DA_NOMEM = 0x1A;

static byte IDX_DB_SWTCH = 0x1B;
static byte IDX_DB_MEM   = 0x1C;
static byte IDX_DB_NOMEM = 0x1D;

static byte IDX_DC_SWTCH = 0x1E;
static byte IDX_DC_MEM   = 0x1F;
static byte IDX_DC_NOMEM = 0x20;

static byte IDX_DD_SWTCH = 0x21;
static byte IDX_DD_MEM   = 0x22;
static byte IDX_DD_NOMEM = 0x23;

static byte IDX_DE_SWTCH = 0x24;
static byte IDX_DE_MEM   = 0x25;
static byte IDX_DE_NOMEM = 0x26;

static byte IDX_DF_SWTCH = 0x27;
static byte IDX_DF_MEM   = 0x28;
static byte IDX_DF_NOMEM = 0x29;

static byte IDX_0F                = 0x2A;
static byte IDX_0F_00             = 0x2B;
static byte IDX_0F_01_SWTCH       = 0x2C;
static byte IDX_0F_01_MEM         = 0x2D;
static byte IDX_0F_01_NOMEM_SWTCH = 0x2E;
static byte IDX_0F_01_NOMEM_00    = 0x2F;
static byte IDX_0F_01_NOMEM_01    = 0x30;
static byte IDX_0F_01_NOMEM_02    = 0x31;
static byte IDX_0F_01_NOMEM_07    = 0x32;
static byte IDX_0F_12             = 0x33;
static byte IDX_0F_16             = 0x34;
static byte IDX_0F_18             = 0x35;
static byte IDX_0F_19             = 0x36;
static byte IDX_0F_71             = 0x37;
static byte IDX_0F_72             = 0x38;
static byte IDX_0F_73             = 0x39;
static byte IDX_0F_AE_SWTCH       = 0x3A;
static byte IDX_0F_AE_MEM         = 0x3B;
static byte IDX_0F_AE_NOMEM       = 0x3C;
static byte IDX_0F_BA             = 0x3D;
static byte IDX_0F_C7             = 0x3E;
static byte IDX_66_0F_JMP         = 0x3F;
static byte IDX_66_0F             = 0x40;
static byte IDX_66_0F71           = 0x41;
static byte IDX_66_0F72           = 0x42;
static byte IDX_66_0F73           = 0x43;
static byte IDX_66_0FC7           = 0x44;
static byte IDX_F2_0F_JMP         = 0x45;
static byte IDX_F2_0F             = 0x46;
static byte IDX_F3_0F_JMP         = 0x47;
static byte IDX_F3_0F             = 0x48;
static byte IDX_F3_0FC7           = 0x49;

static byte IDX_0F_38   = 0x4A;
static byte IDX_66_0F38 = 0x4B;
static byte IDX_F2_0F38 = 0x4C;
static byte IDX_0F_3A   = 0x4D;
static byte IDX_66_0F3A = 0x4E;

static int POST_PROC_SHIFT = 0xC;

static int POST_PROC_ARPL_MOVSXD = 0x0;
static int POST_PROC_NOP_PAUSE   = 0x1 << POST_PROC_SHIFT;
static int POST_PROC_MULTINOP    = 0x2 << POST_PROC_SHIFT;
static int POST_PROC_CMPXCHG8B   = 0x3 << POST_PROC_SHIFT;
static int POST_PROC_JCXZ        = 0x4 << POST_PROC_SHIFT;


static uint TBL_PROP_MODRM  = 0x1;
static uint TBL_PROP_SUFFIX = 0x2;


/**********************
* Disassembling errors.
***********************
*/
static byte ERR_OK          = 0x0;
static byte ERR_BADCODE     = 0x1;
static byte ERR_TOO_LONG    = 0x2;
static byte ERR_NON_LOCKABLE= 0x3;
static byte ERR_RM_REG      = 0x4;
static byte ERR_RM_MEM      = 0x5;
static byte ERR_16_32_ONLY  = 0x6;
static byte ERR_64_ONLY     = 0x7;
static byte ERR_REX_NOOPCD  = 0x8;
static byte ERR_ANOT_ARCH   = 0x9;
static byte ERR_INTERNAL    = 0xA;



/*******************
* Disassemble modes.
********************
*/
static byte DISASSEMBLE_MODE_16 = 0x1;
static byte DISASSEMBLE_MODE_32 = 0x2;
static byte DISASSEMBLE_MODE_64 = 0x4;



/**********************
* Instructions' groups.
***********************
*/
static ulong GRP_NULL = 0x0000000000000000L;
static ulong GRP_SWITCH = 0x0000000000000001L;
static ulong GRP_ARITH  = 0x0000000000000002L;
static ulong GRP_BINARY = 0x0000000000000004L;
static ulong GRP_BIT    = 0x0000000000000008L;
static ulong GRP_BRANCH = 0x0000000000000010L;
static ulong GRP_BREAK  = 0x0000000000000020L;
static ulong GRP_CACHECT= 0x0000000000000040L;
static ulong GRP_COMPAR = 0x0000000000000080L;
static ulong GRP_COND   = 0x0000000000000100L;
static ulong GRP_CONTROL= 0x0000000000000200L;
static ulong GRP_CONVER = 0x0000000000000400L;
static ulong GRP_DATAMOV= 0x0000000000000800L;
static ulong GRP_DECIMAL= 0x0000000000001000L;
static ulong GRP_FETCH  = 0x0000000000002000L;
static ulong GRP_FLGCTRL= 0x0000000000004000L;
static ulong GRP_GEN    = 0x0000000000008000L;
static ulong GRP_INOUT  = 0x0000000000010000L;
static ulong GRP_LDCONST= 0x0000000000020000L;
static ulong GRP_LOGICAL= 0x0000000000040000L;
static ulong GRP_MMX    = 0x0000000000080000L;
static ulong GRP_MXCSRSM= 0x0000000000100000L;
static ulong GRP_ORDER  = 0x0000000000200000L;
static ulong GRP_PCKSCLR= 0x0000000000400000L;
static ulong GRP_PCKSP  = 0x0000000000800000L;
static ulong GRP_PREFIX = 0x0000000001000000L;
static ulong GRP_SEGREG = 0x0000000002000000L;
static ulong GRP_SHFTROT= 0x0000000004000000L;
static ulong GRP_SHIFT  = 0x0000000008000000L;
static ulong GRP_SHUNPCK= 0x0000000010000000L;
static ulong GRP_SIMDFP = 0x0000000020000000L;
static ulong GRP_SIMDINT= 0x0000000040000000L;
static ulong GRP_SM     = 0x0000000080000000L;
static ulong GRP_SMX    = 0x0000000100000000L;
static ulong GRP_SSE1   = 0x0000000200000000L;
static ulong GRP_SSE2   = 0x0000000400000000L;
static ulong GRP_SSE3   = 0x0000000800000000L;
static ulong GRP_SSE41  = 0x0000001000000000L;
static ulong GRP_SSE42  = 0x0000002000000000L;
static ulong GRP_SSSE3  = 0x0000004000000000L;
static ulong GRP_STACK  = 0x0000008000000000L;
static ulong GRP_STRING = 0x0000010000000000L;
static ulong GRP_STRTXT = 0x0000020000000000L;
static ulong GRP_SYNC   = 0x0000040000000000L;
static ulong GRP_SYSTEM = 0x0000080000000000L;
static ulong GRP_TRANS  = 0x0000100000000000L;
static ulong GRP_UNPACK = 0x0000200000000000L;
static ulong GRP_VMX    = 0x0000400000000000L;
static ulong GRP_X87FPU = 0x0000800000000000L;


static byte PREF_SEG_INDEX      = 0x0;
static byte PREF_OPSIZE_INDEX   = 0x1;
static byte PREF_ADDRSIZE_INDEX = 0x2;
static byte PREF_REP_INDEX      = 0x3;
static byte PREF_LOCK_INDEX     = 0x4;
static byte PREF_REX_INDEX      = 0x5;

static byte PREFIX_COUNT = 0x6;


//PREF_SEG_*
static byte PREF_CS_ID       = 0x0;
static byte PREF_DS_ID       = 0x1;
static byte PREF_ES_ID       = 0x2;
static byte PREF_SS_ID       = 0x3;
static byte PREF_FS_ID       = 0x4;
static byte PREF_GS_ID       = 0x5;

//PREF_OPSIZE_*
static byte PREF_OPSIZE_ID   = 0x6;

//PREF_ADDRSIZE_*
static byte PREF_ADDRSIZE_ID = 0x7;

//PREF_REP_*
static byte PREF_REPZ_ID     = 0x8;
static byte PREF_REPNZ_ID    = 0x9;

//PREF_LOCK_*
static byte PREF_LOCK_ID     = 0xA;

//PREF_REX_*
static byte PREF_REX_ID      = 0xB;


/************************
* Defines and structs for
* instruction.
*************************
*/
//INSTRUCTION.flag's values:
static ushort INSTR_FLAG_MODRM = 0x0001;
static ushort INSTR_FLAG_SIB = 0x0002;
static ushort INSTR_FLAG_SF_PREFIXES = 0x0004;
static ushort INSTR_FLAG_IOPL = 0x0008;
static ushort INSTR_FLAG_RING0 = 0x0010;
static ushort INSTR_FLAG_SERIAL = 0x0020;
static ushort INSTR_FLAG_UNDOC = 0x0040;

//INSTRUCTION.prefixes values.
//Segment prefixes:
static UInt16 INSTR_PREFIX_CS = 0x0001;
static UInt16 INSTR_PREFIX_DS = 0x0002;
static UInt16 INSTR_PREFIX_ES = 0x0004;
static UInt16 INSTR_PREFIX_SS = 0x0008;
static UInt16 INSTR_PREFIX_FS = 0x0010;
static UInt16 INSTR_PREFIX_GS = 0x0020;
//Segment prefixes mask:
static uint INSTR_PREFIX_SEG_MASK  = 0x003F;
//Repeat prefixes:
static UInt16 INSTR_PREFIX_REPZ = 0x0040;
static UInt16 INSTR_PREFIX_REPNZ = 0x0080;
//Repeat prefixes mask:
static uint INSTR_PREFIX_REP_MASK  = 0x00C0;
//Size override prefixes:
static UInt16 INSTR_PREFIX_OPSIZE = 0x0100;
static UInt16 INSTR_PREFIX_ADDRSIZE = 0x0200;
static UInt16 INSTR_PREFIX_REX = 0x0400;
//Operand size prefixes mask:
static uint INSTR_PREFIX_SIZE_MASK = 0x0300;
//LOCK prefix:
static UInt16 INSTR_PREFIX_LOCK = 0x0800;

//[StructLayout(LayoutKind.Explicit)]
        public struct DISPLACEMENT
        {
    //[FieldOffset(0)]
            public byte size;
    //[FieldOffset(1)]
            public byte offset;
    //[FieldOffset(2)]
    public value1 value;
    public struct value1
    {
        //[FieldOffset(2)]
        public UInt16 d16;
        //[FieldOffset(2)]
        public UInt32 d32;
        //[FieldOffset(2)]
        public UInt64 d64;
    }
};
public struct INSTRUCTION
{
    public UInt64 groups;
    public UInt16 id;
    public UInt16 flags;
    public UInt16 prefixes;
    public byte opcode_offset;

    public OPERAND[] ops;//OPERAND[3];
    public DISPLACEMENT disp;

    public byte addrsize;
    public byte opsize;
    public byte modrm;
    public byte sib;
    public byte rex;

    public byte tested_flags;
    public byte modified_flags;
    public byte set_flags;
    public byte cleared_flags;
    public byte undefined_flags;

    public string mnemonic;//[MAX_MNEMONIC_LEN];
}

public struct DISASM_INOUT_PARAMS
{
    public int sf_prefixes_len;
    public byte[] sf_prefixes;
    public UInt32 errcode;
    public byte arch;
    public byte mode;
    public byte options;
    public UInt64 bas;
};
public class INTERNAL_DATA
{
    public byte[] prefixes;//[PREFIX_COUNT]; //Valuable prefixes.
    public byte severe_err;             //Severe disassembling error.
    public byte err;                    //DIsassembling error.
    public byte is_opsize_used;         //
    public byte is_addrsize_used;       //Prefixes were used during disassembling.
    public byte is_rex_used;            //
    public INTERNAL_DATA()
    {
        prefixes = new byte[PREFIX_COUNT];
    }
    public INTERNAL_DATA(byte val)
    {
        prefixes = new byte[PREFIX_COUNT];
        for (byte i = 0; i < PREFIX_COUNT; i++)
            prefixes[i] = val;
    }
};

public class MULTI_MNEMONIC : MNEMONIC
{
    public char indicator;
    public uint size;
    //public SQ b;
    public string[] values;
    public MULTI_MNEMONIC() : base("")
    { 
    }
    public MULTI_MNEMONIC(string val) : base(val) { }
    public MULTI_MNEMONIC(char _indicator, uint _size, string[] _values)
        : base("")
    {
    indicator = _indicator;
    size = _size;
    values = _values;
    }
}
//static struct MULTI_MNEMONIC pusha  = { MM_INDICATOR, SQ_v,      { _UT("pusha"),   _UT("pushad"),  _UT("bad_mnem")  } };
public class MNEMONIC
{
    public string value;
    public MNEMONIC(string val)
    {
        value = val;
    }
};

public struct INTERNAL_OPERAND
{
    public byte type;
    public byte size;
    public INTERNAL_OPERAND(byte _type, byte _size)
    {
        type = _type;
        size = _size;
    }
};
public struct OPCODE_DESCRIPTOR
{
    public UInt64 groups;
    public MULTI_MNEMONIC mnemonic;
    public UInt16 id;
    public INTERNAL_OPERAND[] ops;//[3]
    public ushort props;
    public byte tested_flags;
    public byte modified_flags;
    public byte set_flags;
    public byte cleared_flags;
    public byte undefined_flags;
    public byte arch;
    public OPCODE_DESCRIPTOR(
    UInt64 _groups,
    MULTI_MNEMONIC _mnemonic,
    UInt16 _id,
    INTERNAL_OPERAND[] _ops,
    UInt16 _props,
    byte _tested_flags,
    byte _modified_flags,
    byte _set_flags,
    byte _cleared_flags,
    byte _undefined_flags,
    byte _arch)
    {
    groups = _groups;
    mnemonic = _mnemonic;
    id = _id;
    ops =_ops;
    props = _props;
    tested_flags = _tested_flags;
    modified_flags = _modified_flags;
    set_flags = _set_flags;
    cleared_flags = _cleared_flags;
    undefined_flags = _undefined_flags;
    arch = _arch;
    }

};
public struct TABLE_DESCRIPTOR
{
    public byte min, max, mask, shift, props;
    public OPCODE_DESCRIPTOR[] opcodes;
    public TABLE_DESCRIPTOR(byte _min, byte _max, byte _mask, byte _shift, byte _props, OPCODE_DESCRIPTOR[] _opcodes)
    {
    min = _min;
    max = _max;
    mask = _mask;
    shift = _shift;
    props = _props;
    opcodes = _opcodes;
    }
}

public struct OPERAND_SIZE
{
    public UInt16 size_in_stream;
    public UInt16 size;
    public byte sign;
}




public delegate void SQ(OPERAND_SIZE opsize, INSTRUCTION instr, INTERNAL_DATA idata, byte mode);

/*******************************************************
* Operand's size qualifiers (SQ_*) handlers' prototypes.
********************************************************
*/
public static SQ[] sq_handlers;

public SQ
    sq_a,
    sq_b,
    sq_bcd,
    sq_bdqp,
    sq_bs,
    sq_bss,
    sq_d,
    sq_ddq,
    sq_di,
    sq_dq,
    sq_dq64,
    sq_dqp,
    sq_dr,
    sq_ds,
    sq_e,
    sq_er,
    sq_p,
    sq_pd,
    sq_pi,
    sq_ps,
    sq_psq,
    sq_ptp,
    sq_q,
    sq_qdq,
    sq_qi,
    sq_s,
    sq_sd,
    sq_sr,
    sq_ss,
    sq_st,
    sq_stx,
    sq_v,
    sq_v67q64,
    sq_vd64,
    sq_vds,
    sq_vq64,
    sq_vqp,
    sq_vs,
    sq_w,
    sq_wdq,
    sq_wdqp,
    sq_wi,
    sq_wv,
    sq_wvqp;


/***************************************
* Postprocessing functions's prototypes.
****************************************
*/

public delegate UInt32 PP(ulong origin_offset, ulong offset, INSTRUCTION instr, INTERNAL_DATA idata, byte mode);

public static PP[] postprocs;

public PP
    post_proc_arpl_movsxd,
    post_proc_nop_pause,
    post_proc_multinop,
    post_proc_cmpxchg8b;

public delegate UInt32 TQ(ulong origin_offset, ulong offset, INSTRUCTION instr, int op_index, OPERAND_SIZE opsize, INTERNAL_DATA idata, byte mode);

/*
 Operand's type qualifers (TQ_) handlers' prototypes.

*/
public static TQ[] tq_handlers;

public TQ 
tq_1,
tq_3,
tq_A
,tq_C
,tq_D
,tq_E
,tq_G
,tq_H
,tq_I
,tq_J
,tq_M
,tq_N
,tq_O
,tq_P
,tq_Q
,tq_R
,tq_S
,tq_T
,tq_U
,tq_V
,tq_W
,tq_X
,tq_Y
,tq_Z
,tq_rAX
,tq_rCX
,tq_rDX
,tq_rBX
,tq_rSP
,tq_rBP
,tq_rSI
,tq_rDI
,tq_fST0
,tq_fES
,tq_fEST
,tq_CS
,tq_DS
,tq_SS
,tq_ES
,tq_FS
,tq_GS,
pref_CS_set,
pref_DS_set,
pref_SS_set,
pref_ES_set,
pref_FS_set,
pref_GS_set,
pref_OPSIZE_set,
pref_ADDRSIZE_set,
pref_REPZ_set,
pref_REPNZ_set,
pref_LOCK_set;

/************************
* Defines and structs for
* operand.
*************************
*/
//OPERAND.flags' values:
static ushort OPERAND_TYPE_REG = 0x01;
static ushort OPERAND_TYPE_MEM = 0x02;
static ushort OPERAND_TYPE_IMM = 0x04;
static ushort OPERAND_TYPE_DIR = 0x08;
static ushort OPERAND_TYPE_MASK= 0x0F;

static byte OPERAND_FLAG_PRESENT= 0x10;
static byte OPERAND_FLAG_REL    = 0x20;

//OPERAND.size's values:
static ushort OPERAND_SIZE_8   = 0x0001;
static ushort OPERAND_SIZE_16  = 0x0002;
static ushort OPERAND_SIZE_32  = 0x0004;
static ushort OPERAND_SIZE_48  = 0x0006;
static ushort OPERAND_SIZE_64  = 0x0008;
static ushort OPERAND_SIZE_80  = 0x000A;
static ushort OPERAND_SIZE_128 = 0x0010;
static ushort OPERAND_SIZE_14  = 0x000E;
static ushort OPERAND_SIZE_28  = 0x001C;
static ushort OPERAND_SIZE_94  = 0x005E;
static ushort OPERAND_SIZE_108 = 0x006C;
static ushort OPERAND_SIZE_512 = 0x0200;

//OPERAND.ADDR.mod's bits:
static byte ADDR_MOD_BASE = 0x1;
static byte ADDR_MOD_IDX  = 0x2;
static byte ADDR_MOD_DISP = 0x4;

//OPERAND.REG.type's values:
static ushort REG_TYPE_GEN= 0x0;
static ushort REG_TYPE_SEG= 0x1;
static ushort REG_TYPE_CR = 0x2;
static ushort REG_TYPE_DBG= 0x3;
static ushort REG_TYPE_TR = 0x4;
static ushort REG_TYPE_FPU= 0x5;
static ushort REG_TYPE_MMX= 0x7;
static ushort REG_TYPE_XMM= 0x8;

//OPERAND.REG.code's values (GPR):
static ushort REG_CODE_AX = 0x0;
static ushort REG_CODE_CX = 0x1;
static ushort REG_CODE_DX = 0x2;
static ushort REG_CODE_BX = 0x3;
static ushort REG_CODE_SP = 0x4;
static ushort REG_CODE_BP = 0x5;
static ushort REG_CODE_SI = 0x6;
static ushort REG_CODE_DI = 0x7;

static ushort REG_CODE_64 = 0x8;

static ushort REG_CODE_R8 = 0x8;
static ushort REG_CODE_R9 = 0x9;
static ushort REG_CODE_R10= 0xA;
static ushort REG_CODE_R11= 0xB;
static ushort REG_CODE_R12= 0xC;
static ushort REG_CODE_R13= 0xD;
static ushort REG_CODE_R14= 0xE;
static ushort REG_CODE_R15= 0xF;
static ushort REG_CODE_SPL= 0x10;
static ushort REG_CODE_BPL= 0x11;
static ushort REG_CODE_SIL= 0x12;
static ushort REG_CODE_DIL= 0x13;
static ushort REG_CODE_IP = 0x14;

//OPERAND.REG.code's values (segment registers):
static ushort SREG_CODE_CS= 0x0;
static ushort SREG_CODE_DS= 0x1;
static ushort SREG_CODE_ES= 0x2;
static ushort SREG_CODE_SS= 0x3;
static ushort SREG_CODE_FS= 0x4;
static ushort SREG_CODE_GS= 0x5;

//OPERAND.REG.code's values (FPU registers):
static ushort FREG_CODE_ST0= 0x0;
static ushort FREG_CODE_ST1= 0x1;
static ushort FREG_CODE_ST2= 0x2;
static ushort FREG_CODE_ST3= 0x3;
static ushort FREG_CODE_ST4= 0x4;
static ushort FREG_CODE_ST5= 0x5;
static ushort FREG_CODE_ST6= 0x6;
static ushort FREG_CODE_ST7= 0x7;

//OPERAND.REG.code's values (control registers):
static ushort CREG_CODE_CR0= 0x0;
static ushort CREG_CODE_CR1= 0x1;
static ushort CREG_CODE_CR2= 0x2;
static ushort CREG_CODE_CR3= 0x3;
static ushort CREG_CODE_CR4= 0x4;
static ushort CREG_CODE_CR5= 0x5;
static ushort CREG_CODE_CR6= 0x6;
static ushort CREG_CODE_CR7= 0x7;

//OPERAND.REG.code's values (debug registers):
static ushort DREG_CODE_DR0= 0x0;
static ushort DREG_CODE_DR1= 0x1;
static ushort DREG_CODE_DR2= 0x2;
static ushort DREG_CODE_DR3= 0x3;
static ushort DREG_CODE_DR4= 0x4;
static ushort DREG_CODE_DR5= 0x5;
static ushort DREG_CODE_DR6= 0x6;
static ushort DREG_CODE_DR7= 0x7;

//OPERAND.REG.code's values (MMX registers):
static ushort MREG_CODE_MM0= 0x0;
static ushort MREG_CODE_MM1= 0x1;
static ushort MREG_CODE_MM2= 0x2;
static ushort MREG_CODE_MM3= 0x3;
static ushort MREG_CODE_MM4= 0x4;
static ushort MREG_CODE_MM5= 0x5;
static ushort MREG_CODE_MM6= 0x6;
static ushort MREG_CODE_MM7= 0x7;

//OPERAND.REG.code's values (XMM registers):
static ushort XREG_CODE_XMM0 = 0x0;
static ushort XREG_CODE_XMM1 = 0x1;
static ushort XREG_CODE_XMM2 = 0x2;
static ushort XREG_CODE_XMM3 = 0x3;
static ushort XREG_CODE_XMM4 = 0x4;
static ushort XREG_CODE_XMM5 = 0x5;
static ushort XREG_CODE_XMM6 = 0x6;
static ushort XREG_CODE_XMM7 = 0x7;

static ushort XREG_CODE_XMM8 = 0x8;
static ushort XREG_CODE_XMM9 = 0x9;
static ushort XREG_CODE_XMM10= 0xA;
static ushort XREG_CODE_XMM11= 0xB;
static ushort XREG_CODE_XMM12= 0xC;
static ushort XREG_CODE_XMM13= 0xD;
static ushort XREG_CODE_XMM14= 0xE;
static ushort XREG_CODE_XMM15 = 0xF;

public static UInt16[] pref_bits = 
{
    INSTR_PREFIX_CS,
    INSTR_PREFIX_DS,
    INSTR_PREFIX_ES,
    INSTR_PREFIX_SS,
    INSTR_PREFIX_FS,
    INSTR_PREFIX_GS,
    INSTR_PREFIX_OPSIZE,
    INSTR_PREFIX_ADDRSIZE,
    INSTR_PREFIX_REPZ,
    INSTR_PREFIX_REPNZ,
    INSTR_PREFIX_LOCK,
    INSTR_PREFIX_REX};

//INSTRUCTION.addrsize's values:
static byte ADDR_SIZE_16 = 0x2;
static byte ADDR_SIZE_32 = 0x4;
static byte ADDR_SIZE_64 = 0x8;

//DISASM_INOUT_PARAMS.options' bits:
static byte DISASM_OPTION_APPLY_REL     = 0x1;
static byte DISASM_OPTION_OPTIMIZE_DISP = 0x2;


static char MM_INDICATOR = '*';

public static byte[] pref_opcodes =
{
    0x2E, //CS
    0x3E, //DS
    0x26, //ES
    0x36, //SS
    0x64, //FS
    0x66, //GS
    0x66, //OPSIZE
    0x67, //ADDRSIZE
    0xF2, //REPZ
    0xF3, //REPNZ
    0xF0  //LOCK
};

static byte ARCH_COMMON = 0x1;
static byte ARCH_INTEL  = 0x2;
static byte ARCH_AMD    = 0x4;
static byte ARCH_ALL = (byte)((int)ARCH_COMMON | (int)ARCH_INTEL | (int)ARCH_AMD);


//Warning: may contain a lot of tables!

/*60*/
static MULTI_MNEMONIC pusha = new MULTI_MNEMONIC(MM_INDICATOR, SQ_v, new[] { "pusha", "pushad", "bad_mnem" });
/*61*/ static MULTI_MNEMONIC popa   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_v,   new[]     {"popa",  "popad",   "bad_mnem" });
/*6D*/ static MULTI_MNEMONIC ins    = new MULTI_MNEMONIC( MM_INDICATOR, SQ_v,   new[]     { "insw",  "insd",    "bad_mnem" });
/*6F*/ static MULTI_MNEMONIC outs   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_v,   new[]     { "outsw", "outsd",   "bad_mnem" });
/*98*/ static MULTI_MNEMONIC cbw    = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp, new[]     { "cbw",    "cwde",    "cdqe"    });
/*99*/ static MULTI_MNEMONIC cwd    = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp, new[]     { "cwd}",   "cdq",     "cqo"     });
/*9C*/
static MULTI_MNEMONIC pushf = new MULTI_MNEMONIC(MM_INDICATOR, SQ_vd64, new[] { "pushfw", "pushfd", "pushfq" });
/*9D*/ static MULTI_MNEMONIC popf   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vd64,  new[] { "popfw",   "popfd",   "popfq"});
/*A5*/ static MULTI_MNEMONIC movs   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp,   new[] { "movsw",   "movsd",   "movsq"});
/*A7*/ static MULTI_MNEMONIC cmps   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp,   new[] { "cmpsw",   "cmpsd",   "cmpsq"});
/*AB*/ static MULTI_MNEMONIC stos   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp,   new[] { "stosw",   "stosd",   "stosq"});
/*AD*/ static MULTI_MNEMONIC lods   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp,   new[] { "lodsw",   "lodsd",   "lodsq"});
/*AF*/ static MULTI_MNEMONIC scas   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp,   new[] { "scasw",   "scasd",   "scasq"});
/*CF*/ static MULTI_MNEMONIC iret   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_vqp,   new[] { "iretw",   "iretd",   "iretq"});
/*E0*/ static MULTI_MNEMONIC loopnz = new MULTI_MNEMONIC( MM_INDICATOR, SQ_v67q64,new[] { "loopwnz", "loopdnz", "loopqnz"});
/*E1*/ static MULTI_MNEMONIC loopz  = new MULTI_MNEMONIC( MM_INDICATOR, SQ_v67q64,new[] { "loopwz",  "loopdz",  "loopqz"});
/*E2*/ static MULTI_MNEMONIC loop   = new MULTI_MNEMONIC( MM_INDICATOR, SQ_v67q64,new[] { "loopw",   "loopd",   "loopq"});
/*E3*/
static MULTI_MNEMONIC jcxz = new MULTI_MNEMONIC(MM_INDICATOR, SQ_v67q64, new[] { "jcxz", "jecxz", "jrcxz" });


public static OPCODE_DESCRIPTOR[] opcodes_1byte = new[] {
/*00*/    new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("add"), ID_ADD, 
                            new[] {
                                    new INTERNAL_OPERAND(TQ_E, SQ_b),
                                    new INTERNAL_OPERAND(TQ_G, SQ_b),
                                    new INTERNAL_OPERAND(TQ_NULL, SQ_NULL)
                                  },
                            (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
/*01*/    new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("add"), ID_ADD, 
                            new[] {
                                    new INTERNAL_OPERAND(TQ_E, SQ_vqp),
                                    new INTERNAL_OPERAND(TQ_G, SQ_vqp),
                                    new INTERNAL_OPERAND(TQ_NULL, SQ_NULL)
                                  },
                            (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("add"), ID_ADD, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("add"), ID_ADD, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("add"), ID_ADD, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("add"), ID_ADD, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_STACK | GRP_SEGREG, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_ES, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_STACK | GRP_SEGREG, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_ES, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("or"), ID_OR, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR(  GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("or"), ID_OR, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("or"), ID_OR, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("or"), ID_OR, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("or"), ID_OR, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("or"), ID_OR, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK | GRP_SEGREG, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_CS, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_0F, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_0F, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("adc"), ID_ADC, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("adc"), ID_ADC, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("adc"), ID_ADC, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("adc"), ID_ADC, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("adc"), ID_ADC, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("adc"), ID_ADC, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK | GRP_SEGREG, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_SS, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK | GRP_SEGREG, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_SS, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sbb"), ID_SBB, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sbb"), ID_SBB, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sbb"), ID_SBB, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sbb"), ID_SBB, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sbb"), ID_SBB, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sbb"), ID_SBB, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK | GRP_SEGREG, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_DS, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK | GRP_SEGREG, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_DS, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("and"), ID_AND, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("and"), ID_AND, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("and"), ID_AND, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("and"), ID_AND, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("and"), ID_AND, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("and"), ID_AND, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_ES, new[] {new INTERNAL_OPERAND(TQ_PREF_ES, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_DECIMAL, new MULTI_MNEMONIC("daa"), ID_DAA, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x5, 0x9F, 0x0, 0x0, 0x80, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sub"), ID_SUB, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sub"), ID_SUB, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sub"), ID_SUB, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sub"), ID_SUB, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sub"), ID_SUB, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("sub"), ID_SUB, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_CS, new[] {new INTERNAL_OPERAND(TQ_PREF_CS, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_DECIMAL, new MULTI_MNEMONIC("das"), ID_DAS, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x5, 0x9F, 0x0, 0x0, 0x80, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("xor"), ID_XOR, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("xor"), ID_XOR, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("xor"), ID_XOR, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("xor"), ID_XOR, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("xor"), ID_XOR, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("xor"), ID_XOR, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_SS, new[] {new INTERNAL_OPERAND(TQ_PREF_SS, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_DECIMAL, new MULTI_MNEMONIC("aaa"), ID_AAA, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x4, 0x9F, 0x0, 0x0, 0x9A, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("cmp"), ID_CMP, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("cmp"), ID_CMP, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("cmp"), ID_CMP, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("cmp"), ID_CMP, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("cmp"), ID_CMP, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("cmp"), ID_CMP, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_DS, new[] {new INTERNAL_OPERAND(TQ_PREF_DS, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_DECIMAL, new MULTI_MNEMONIC("aas"), ID_AAS, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x4, 0x9F, 0x0, 0x0, 0x9A, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("inc"), ID_INC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("dec"), ID_DEC, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9E, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("pop"), ID_POP, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vd64 ),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, pusha, ID_PUSHA, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, popa, ID_POPA, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BREAK | GRP_STACK, new MULTI_MNEMONIC("bound"), ID_BOUND, new[] {new INTERNAL_OPERAND(TQ_G, SQ_v),new INTERNAL_OPERAND(TQ_M, SQ_a),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_MODRM | PROP_IOPL | PROP_I64), 0x0, 0x20, 0x0, 0x20, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SYSTEM, new MULTI_MNEMONIC("arpl"), ID_ARPL, new[] {new INTERNAL_OPERAND(TQ_E, SQ_w),new INTERNAL_OPERAND(TQ_G, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_MODRM | PROP_POST_PROC | POST_PROC_ARPL_MOVSXD), 0x0, 0x8, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_FS, new[] {new INTERNAL_OPERAND(TQ_PREF_FS, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_GS, new[] {new INTERNAL_OPERAND(TQ_PREF_GS, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_66, new[] {new INTERNAL_OPERAND(TQ_PREF_66, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_66_0F_JMP, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC(""), ID_67, new[] {new INTERNAL_OPERAND(TQ_PREF_67, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_I, SQ_vs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("imul"), ID_IMUL, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x1E, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("push"), ID_PUSH, new[] {new INTERNAL_OPERAND(TQ_I, SQ_bss),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("imul"), ID_IMUL, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_bs) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x0, 0x1E, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT | GRP_STRING, new MULTI_MNEMONIC("insb"), ID_INS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT | GRP_STRING, ins, ID_INS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT | GRP_STRING, new MULTI_MNEMONIC("outsb"), ID_OUTS, new[] {new INTERNAL_OPERAND(TQ_X, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT | GRP_STRING, outs, ID_OUTS, new[] {new INTERNAL_OPERAND(TQ_X, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jo"), ID_JO, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x80, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jno"), ID_JNO, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x80, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jb"), ID_JB, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jae"), ID_JAE, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jz"), ID_JZ, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x8, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jnz"), ID_JNZ, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x8, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jbe"), ID_JBE, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x9, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("ja"), ID_JA, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x9, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("js"), ID_JS, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x10, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jns"), ID_JNS, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x10, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jp"), ID_JP, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x2, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jnp"), ID_JNP, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x2, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jl"), ID_JL, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x90, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jge"), ID_JGE, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x90, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jle"), ID_JLE, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x98, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, new MULTI_MNEMONIC("jg"), ID_JG, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x98, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_80, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_81, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_82, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_83, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("test"), ID_TEST, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_BINARY, new MULTI_MNEMONIC("test"), ID_TEST, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_LOCK | PROP_MODRM), 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_G, SQ_b),new INTERNAL_OPERAND(TQ_E, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_E, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_E, SQ_wv),new INTERNAL_OPERAND(TQ_S, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("lea"), ID_LEA, new[] {new INTERNAL_OPERAND(TQ_G, SQ_vqp),new INTERNAL_OPERAND(TQ_M, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_S, SQ_w),new INTERNAL_OPERAND(TQ_E, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_MODRM, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_8F, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_CONTROL, new MULTI_MNEMONIC("nop"), ID_NOP, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_POST_PROC | POST_PROC_NOP_PAUSE), 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xchg"), ID_XCHG, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_CONVER, cbw, ID_CBW, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_CONVER, cwd, ID_CWD, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_STACK, new MULTI_MNEMONIC("callf"), ID_CALLF, new[] {new INTERNAL_OPERAND(TQ_A, SQ_p),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_X87FPU | GRP_CONTROL, new MULTI_MNEMONIC("fwait"), ID_FWAIT, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK | GRP_FLGCTRL, pushf, ID_PUSHF, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK | GRP_FLGCTRL, popf, ID_POPF, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_FLGCTRL, new MULTI_MNEMONIC("sahf"), ID_SAHF, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x1F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_FLGCTRL, new MULTI_MNEMONIC("lahf"), ID_LAHF, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1F, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_O, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_O, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_O, SQ_b),new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_O, SQ_vqp),new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_STRING, new MULTI_MNEMONIC("movsb"), ID_MOVS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_b),new INTERNAL_OPERAND(TQ_X, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_STRING, movs, ID_MOVS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_vqp),new INTERNAL_OPERAND(TQ_X, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_STRING | GRP_BINARY, new MULTI_MNEMONIC("cmpsb"), ID_CMPS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_b),new INTERNAL_OPERAND(TQ_X, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_STRING | GRP_BINARY, cmps, ID_CMPS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_vqp),new INTERNAL_OPERAND(TQ_X, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("test"), ID_TEST, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_LOGICAL, new MULTI_MNEMONIC("test"), ID_TEST, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x9F, 0x0, 0x81, 0x4, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_STRING, new MULTI_MNEMONIC("stosb"), ID_STOS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_b),new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_STRING, stos, ID_STOS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_vqp),new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_STRING, new MULTI_MNEMONIC("lodsb"), ID_LODS, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_X, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_STRING, lods, ID_LODS, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_X, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_STRING | GRP_BINARY, new MULTI_MNEMONIC("scasb"), ID_SCAS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_b),new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_STRING | GRP_BINARY, scas, ID_SCAS, new[] {new INTERNAL_OPERAND(TQ_Y, SQ_vqp),new INTERNAL_OPERAND(TQ_rAX, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x40, 0x9F, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("mov"), ID_MOV, new[] {new INTERNAL_OPERAND(TQ_Z, SQ_vqp),new INTERNAL_OPERAND(TQ_I, SQ_vqp),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_C0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_C1, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_STACK, new MULTI_MNEMONIC("retn"), ID_RETN, new[] {new INTERNAL_OPERAND(TQ_I, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_STACK, new MULTI_MNEMONIC("retn"), ID_RETN, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_SEGREG, new MULTI_MNEMONIC("les"), ID_LES, new[] {new INTERNAL_OPERAND(TQ_G, SQ_v),new INTERNAL_OPERAND(TQ_M, SQ_p),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_MODRM | PROP_I64), 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV | GRP_SEGREG, new MULTI_MNEMONIC("lds"), ID_LDS, new[] {new INTERNAL_OPERAND(TQ_G, SQ_v),new INTERNAL_OPERAND(TQ_M, SQ_p),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_MODRM | PROP_I64), 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_C6, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_C7, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("enter"), ID_ENTER, new[] {new INTERNAL_OPERAND(TQ_I, SQ_w),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_STACK, new MULTI_MNEMONIC("leave"), ID_LEAVE, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_STACK, new MULTI_MNEMONIC("retf"), ID_RETF, new[] {new INTERNAL_OPERAND(TQ_I, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_STACK, new MULTI_MNEMONIC("retf"), ID_RETF, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BREAK | GRP_STACK, new MULTI_MNEMONIC("int"), ID_INT, new[] {new INTERNAL_OPERAND(TQ_3, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x20, 0x0, 0x20, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BREAK | GRP_STACK, new MULTI_MNEMONIC("int"), ID_INT, new[] {new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x20, 0x0, 0x20, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BREAK | GRP_STACK, new MULTI_MNEMONIC("into"), ID_INTO, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x80, 0x20, 0x0, 0x20, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BREAK | GRP_STACK, iret, ID_IRET, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_D0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_D1, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_D2, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_D3, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_DECIMAL, new MULTI_MNEMONIC("aam"), ID_AAM, new[] {new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9F, 0x0, 0x0, 0x85, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_ARITH | GRP_DECIMAL, new MULTI_MNEMONIC("aad"), ID_AAD, new[] {new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x9F, 0x0, 0x0, 0x85, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("setalc"), ID_SETALC, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, (ushort)(PROP_I64 | PROP_UNDOC), 0x1, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_DATAMOV, new MULTI_MNEMONIC("xlat"), ID_XLAT, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_D8_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_D9_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_DA_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_DB_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_DC_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_DD_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_DE_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_DF_SWTCH, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, loopnz, ID_LOOPNZ, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x8, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, loopz, ID_LOOPZ, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x8, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, loop, ID_LOOP, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_COND, jcxz, ID_JCXZ, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("in"), ID_IN, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("in"), ID_IN, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_v),new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("out"), ID_OUT, new[] {new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("out"), ID_OUT, new[] {new INTERNAL_OPERAND(TQ_I, SQ_b),new INTERNAL_OPERAND(TQ_rAX, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH | GRP_STACK, new MULTI_MNEMONIC("call"), ID_CALL, new[] {new INTERNAL_OPERAND(TQ_J, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH, new MULTI_MNEMONIC("jmp"), ID_JMP, new[] {new INTERNAL_OPERAND(TQ_J, SQ_vds),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH, new MULTI_MNEMONIC("jmpf"), ID_JMPF, new[] {new INTERNAL_OPERAND(TQ_A, SQ_p),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_I64, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BRANCH, new MULTI_MNEMONIC("jmp"), ID_JMP, new[] {new INTERNAL_OPERAND(TQ_J, SQ_bs),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("in"), ID_IN, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_rDX, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("in"), ID_IN, new[] {new INTERNAL_OPERAND(TQ_rAX, SQ_v),new INTERNAL_OPERAND(TQ_rDX, SQ_w),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("out"), ID_OUT, new[] {new INTERNAL_OPERAND(TQ_rDX, SQ_w),new INTERNAL_OPERAND(TQ_rAX, SQ_b),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_INOUT, new MULTI_MNEMONIC("out"), ID_OUT, new[] {new INTERNAL_OPERAND(TQ_rDX, SQ_w),new INTERNAL_OPERAND(TQ_rAX, SQ_v),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC("lock"), ID_LOCK, new[] {new INTERNAL_OPERAND(TQ_PREF_F0, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_BREAK | GRP_STACK, new MULTI_MNEMONIC("icebp"), ID_ICEBP, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_UNDOC, 0x0, 0x20, 0x0, 0x20, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC("repnz"), ID_REPNZ, new[] {new INTERNAL_OPERAND(TQ_PREF_F2, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_F2_0F_JMP, 0x8, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_PREFIX, new MULTI_MNEMONIC("repz"), ID_REPZ, new[] {new INTERNAL_OPERAND(TQ_PREF_F3, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_F3_0F_JMP, 0x8, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SYSTEM, new MULTI_MNEMONIC("hlt"), ID_HLT, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_RING0, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_FLGCTRL, new MULTI_MNEMONIC("cmc"), ID_CMC, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x1, 0x1, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_F6, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_F7, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_FLGCTRL, new MULTI_MNEMONIC("clc"), ID_CLC, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x1, 0x0, 0x1, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_FLGCTRL, new MULTI_MNEMONIC("stc"), ID_STC, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x1, 0x1, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_FLGCTRL, new MULTI_MNEMONIC("cli"), ID_CLI, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x20, 0x0, 0x20, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_FLGCTRL, new MULTI_MNEMONIC("sti"), ID_STI, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, PROP_IOPL, 0x0, 0x20, 0x20, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_FLGCTRL, new MULTI_MNEMONIC("cld"), ID_CLD, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x40, 0x0, 0x40, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_GEN | GRP_FLGCTRL, new MULTI_MNEMONIC("std"), ID_STD, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, 0, 0x0, 0x40, 0x40, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_FE, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
new OPCODE_DESCRIPTOR( GRP_SWITCH, new MULTI_MNEMONIC(""), ID_NULL, new[] {new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL),new INTERNAL_OPERAND(TQ_NULL, SQ_NULL) }, IDX_FF, 0x0, 0x0, 0x0, 0x0, 0x0, ARCH_COMMON ),
};

public static TABLE_DESCRIPTOR[] tables = new[] {
    new TABLE_DESCRIPTOR(0x0, 0xFF, 0xFF, 0x0, 0x0, opcodes_1byte) };
/*0x0 IDX_1BYTE */
    //min //max //mask //shift //props         //table
//    {{ 0x0, 0xFF, 0xFF, 0x0, 0x0, "opcodes_1byte" }};


//If DISASM_INOUT_PARAMS.sf_prefixes != NULL, copies superfluous prefix's value to the array.
static void add_sf_prefix_value(byte[] prefixes, int index, byte value, INSTRUCTION instr, DISASM_INOUT_PARAMS param)
{
    instr.flags |= INSTR_FLAG_SF_PREFIXES;

    //if (param.sf_prefixes!=0)
        param.sf_prefixes[param.sf_prefixes_len++] = value;
    prefixes[index] = 0xFF;    
}

//Gets superfluous prefix's value by its index and call to function above :).
static void add_sf_prefix(byte[] prefixes, int index, INSTRUCTION instr, DISASM_INOUT_PARAMS param)
{
    add_sf_prefix_value(prefixes, index, pref_opcodes[prefixes[index]], instr, param);
}

//Main function for parsing prefixes. Reads input stream until meets non-prefix byte
// or maximum instruction length is exceeded. The function checks if a prefix of the same group
// was already met and if so, replaces old prefix with a new one.
// Old prefix is added to superfluous prefixes array.
 // The function also checks if a prefix is opcode-extension.
static UInt32 parse_prefixes(ulong offset, INSTRUCTION instr, INTERNAL_DATA idata, byte ext_table_index, byte ext_pref_index, DISASM_INOUT_PARAMS param)
{
    byte pref_code;
    byte rex_found;
    byte pref_id;
    byte pref_index;
    UInt32 res;
    UInt32 tmp;
    OPCODE_DESCRIPTOR ptr;

    res = 0;
    rex_found = 0;

    while(true)
    {
        //pref_code = *offset;
        pref_code = 0;

        if (res > MAX_INSTRUCTION_LEN)
        {
            idata.severe_err = ERR_TOO_LONG;//error: instruction too long.
            break;
        }

        ptr = tables[IDX_1BYTE].opcodes[pref_code];
        if ( !( ((ptr.groups & GRP_PREFIX)!=0) ||
                (param.mode == DISASSEMBLE_MODE_64 && (pref_code >= 0x40) && (pref_code <= 0x4F) && (rex_found==0)) ) )
        {
            break;
        }
        else
        {
            if (rex_found!=0)
            {
                idata.severe_err = ERR_REX_NOOPCD;//error: an opcode should follow after rex.
                break;
            }

            if ( (rex_found!=0) && (param.mode == DISASSEMBLE_MODE_64))
            {
                if ( (pref_code >= 0x40) && (pref_code <= 0x4F) )
                {
                    idata.prefixes[PREF_REX_INDEX] = PREF_REX_ID;
                    instr.rex = pref_code;
                    rex_found = 1;

                    res++;
                    offset++;
                    continue;
                }
            }

            tmp = tq_handlers[ptr.ops[0].type](0, 0, instr, 0, new OPERAND_SIZE(), new INTERNAL_DATA(), param.mode);
            pref_index = (byte)(tmp >> 8);
            pref_id = (byte)tmp;// &0xFF;
            if (idata.prefixes[pref_index] != 0xFF)
            {
                add_sf_prefix(idata.prefixes, pref_index, instr, param);
            }
            idata.prefixes[pref_index] = pref_id;

            //Used later for prefix table switch.
            if (ptr.id == ID_66 || ptr.id == ID_REPZ || ptr.id == ID_REPNZ)
            {
                ext_table_index =(byte)(ptr.props);
                ext_pref_index = pref_index;
            }

            res++;
            offset++;
        }
    }

    return res;
}

//Reads input stream and iterates through tables looking up appropriate struct OPCODE_DESCRIPTOR.
// Byte value at [offset] is used as index, the function checks tables limits and max instruction's length.
static UInt32 lookup_opcode(ulong offset, byte table, OPCODE_DESCRIPTOR opcode_descr, INTERNAL_DATA idata)
{
    byte max;
    byte opcode;
    UInt32 res;

    res = 0;
    //opcode_descr = NULL;
    do
    {
        //opcode = *offset;
        opcode = 0;

        opcode >>= tables[table].shift;
        opcode &= tables[table].mask;
        opcode -= tables[table].min;
        //It looks strange, but I want that table descriptors contain
        // "real" values.
        max = (byte)(tables[table].max - tables[table].min);
        if (opcode > max)
        {
            idata.severe_err = ERR_BADCODE;
            break;
        }

        if (res > MAX_INSTRUCTION_LEN)
        {
            idata.severe_err = ERR_TOO_LONG;
            break;
        }

        if ( (tables[table].props & TBL_PROP_MODRM)!=0 )
        {
            res++;
            offset++;
        }

        if ((tables[table].opcodes[opcode].groups & GRP_SWITCH)!=0)
        {
            table = (byte)tables[table].opcodes[opcode].props;// &0xFF;
            continue;
        }
        break;
    }
    while(true);

    if (idata.severe_err!=0)
        opcode_descr = tables[table].opcodes[opcode];

    return res;
}

//Checks opcode-extension prefixes (repz, repnz, opsize) are superfluous.
static void check_ext_sf_prefixes(byte[] prefixes, INSTRUCTION instr, DISASM_INOUT_PARAMS param)
{
    if (prefixes[PREF_OPSIZE_INDEX] != 0xFF)
        add_sf_prefix(prefixes, PREF_OPSIZE_INDEX, instr, param);
    if (prefixes[PREF_REP_INDEX] != 0xFF)
        add_sf_prefix(prefixes, PREF_OPSIZE_INDEX, instr, param);
}
//Main function for parsing opcode and prefixes. First of all it parses all prefixes and then
// looks up for struct OPCODE_DESCRIPTOR. The following algorithm is used to handle instructions that
// use prefixes as opcode extension:
//
// * Have we prefix that may be opcode extension?
//   No: Lookup starts from 1byte table.
//       * Is instruction found?
//         No: Error.
//         Yes: Success.
//   Yes: Lookup starts from 'ext_table_index' table.
//        * Is instruction found?
//          No: Lookup starts from 1byte table.
//              * Is instruction found?
//                No: Error.
//                Yes: Success.
//          Yes: Success.
static UInt32 parse_opcode(ulong offset, OPCODE_DESCRIPTOR opcode_descr, INSTRUCTION instr, INTERNAL_DATA idata, DISASM_INOUT_PARAMS param)
{
    byte ext_table_index  = 0xFF;
    byte ext_prefix_index = 0;
    UInt32 res;
    UInt32 tmp;

    res = parse_prefixes(offset, instr, idata, ext_table_index, ext_prefix_index, param);
    if (idata.severe_err==0)
    {
        instr.opcode_offset = (byte)res;
        offset += res;

        if ((ext_table_index != 0xFF) && (offset == 0xF))
        {
            tmp = lookup_opcode(offset, ext_table_index, opcode_descr, idata);
            if ((idata.severe_err==0) && (opcode_descr.id != ID_NULL))
            {
                idata.prefixes[ext_prefix_index] = 0xFF;
                check_ext_sf_prefixes(idata.prefixes, instr, param);
                res += tmp;
            }
            else
            {
                idata.severe_err = 0;
                res += lookup_opcode(offset, IDX_1BYTE, opcode_descr, idata);
            }
        }
        else
        {
            res += lookup_opcode(offset, IDX_1BYTE, opcode_descr, idata);
        }

        if ((idata.severe_err==0) && (opcode_descr.id == ID_NULL))
        {
            idata.severe_err = ERR_BADCODE;//error: invalid opcode.
        }
    }

    return res;
}

//Applies disassembling options.
static void apply_disasm_options(INSTRUCTION instr, UInt32 len, DISASM_INOUT_PARAMS param)
{
    for (int i = 0; i < 3; i++)
    {
        if ((param.options & DISASM_OPTION_APPLY_REL)!=0)
        {
            if ((instr.ops[i].flags & OPERAND_FLAG_REL)!=0)
            {
                instr.ops[i].value.imm.imm64 += len + param.bas;
            }
        }

        if ((param.options & DISASM_OPTION_OPTIMIZE_DISP)!=0)
        {
            if (((instr.ops[i].flags & OPERAND_TYPE_MEM)!=0) && (instr.ops[i].value.addr.mod != ADDR_MOD_DISP))
            {
                if (instr.disp.value.d64 == 0x0)
                    instr.ops[i].value.addr.mod &= (byte)(~(uint)ADDR_MOD_DISP);
            }
        }
    }
}

static UInt32 parse_operand( ulong origin_offset, ulong offset, INTERNAL_OPERAND iop, INSTRUCTION instr, int op_index, INTERNAL_DATA idata, byte mode)
{
    UInt32 res = 0;
    OPERAND_SIZE opsize = new OPERAND_SIZE();

    if (iop.type != TQ_NULL)
    {
        instr.ops[op_index].flags |= OPERAND_FLAG_PRESENT;
        if (iop.size >= sq_handlers.Count())
        {
            idata.severe_err = ERR_INTERNAL;
        }
        else
        {
            sq_handlers[iop.size](opsize, instr, idata, mode);
        }
        
        if (iop.size >= tq_handlers.Count())
        {
            idata.severe_err = ERR_INTERNAL;
        }
        else
        {
            res = tq_handlers[iop.type](origin_offset, offset, instr, op_index, opsize, idata, mode);
        }
    }

    return res;
}

//Returns address size. Address size is common for all operands.
static void get_address_size(INSTRUCTION instr, byte[] prefixes, byte mode)
{
    if (mode == DISASSEMBLE_MODE_64)
    {
        if (prefixes[PREF_ADDRSIZE_INDEX] != 0xFF)
            instr.addrsize = ADDR_SIZE_32;
        else
            instr.addrsize = ADDR_SIZE_64;
    }
    else
    {
        if (prefixes[PREF_ADDRSIZE_INDEX] != 0xFF)
            mode ^= (byte)(DISASSEMBLE_MODE_16 | DISASSEMBLE_MODE_32);

        if (mode == DISASSEMBLE_MODE_16)
            instr.addrsize = ADDR_SIZE_16;
        else
            instr.addrsize = ADDR_SIZE_32;
    }
}

//Copies MODRM and SIB bytes to struct INSTRUCTION.
static byte parse_modrm_sib(ulong offset, INSTRUCTION instr, OPCODE_DESCRIPTOR opcode)
{
    byte len = 0;

    if ((opcode.props & PROP_MODRM)!=0)
    {
        len++;
        instr.flags |= INSTR_FLAG_MODRM;
        //instr.modrm = *offset;
        instr.modrm = 0;
        if (instr.addrsize != ADDR_SIZE_16)
        {
            if ((instr.modrm & 0x7) == 0x4 && (instr.modrm & 0xC0) != 0xC0)
            {
                len++;
                instr.flags |= INSTR_FLAG_SIB;
                //instr.sib = offset[1];
                instr.sib = 1;
            }
        }
    }

    return len;
}

static void copy_eflags(INSTRUCTION instr, OPCODE_DESCRIPTOR opcode)
{
    instr.tested_flags = opcode.tested_flags;
    instr.modified_flags = opcode.modified_flags;
    instr.set_flags = opcode.set_flags;
    instr.cleared_flags = opcode.cleared_flags;
    instr.undefined_flags = opcode.undefined_flags;
}


//Copies instruction's flags from struct OPCODE_DESCRIPTOR to struct INSTRUCTION.
static void copy_instr_flags(INSTRUCTION instr, OPCODE_DESCRIPTOR opcode)
{
    if ((opcode.props & PROP_IOPL)!=0)
        instr.flags |= INSTR_FLAG_IOPL;
    if ((opcode.props & PROP_RING0)!=0)
        instr.flags |= INSTR_FLAG_RING0;
    if ((opcode.props & PROP_SERIAL)!=0)
        instr.flags |= INSTR_FLAG_SERIAL;
    if ((opcode.props & PROP_UNDOC) != 0)
        instr.flags |= INSTR_FLAG_UNDOC;
}


static byte bsr(byte src)
{
    byte res;

    for (res = 0; src!=0; src >>= 0x1)
    {
        if ((src & 0x1)!=0)break;
        res++;
    }
    return res;
}


//Get instruction's size. Well, really this is size of implicit operand
// that influences on instruction's mnemonic.
static void get_instruction_opsize(MULTI_MNEMONIC multi_mnemonic, INSTRUCTION instr, INTERNAL_DATA idata, byte mode)
{
    OPERAND_SIZE opsize = new OPERAND_SIZE();

    if (multi_mnemonic.size >= sq_handlers.Count())
    {
        idata.severe_err = ERR_INTERNAL;
    }
    else
    {
        sq_handlers[multi_mnemonic.size](opsize, instr, idata, mode);
    }

    instr.opsize = (byte)opsize.size; //Possible sizes are 2/4/8.
}

//Parses instruction's mnemonic. If mnemonic is simple, it is just copied to
// struct INSTRUCTION. If mnemonic contains has multi mnemonic indicator (MM_INDICATOR)
// at first character then it depends on implicit operand's size. In this case the function
// calls get_instruction_opsize and builds choses mnemonic basing on result.
static void parse_mnemonic(OPCODE_DESCRIPTOR opcode, INSTRUCTION instr, INTERNAL_DATA idata, byte mode)
{
    if (opcode.mnemonic.value[0] != MM_INDICATOR)
    {
        instr.mnemonic = opcode.mnemonic.value;
    }
    else
    {
        get_instruction_opsize(opcode.mnemonic, instr, idata, mode);
        instr.mnemonic = opcode.mnemonic.values[bsr(instr.opsize) - 1];
    }
}


//Checks if segment override prefix is superfluous.
static void check_seg_sf_prefixes(INSTRUCTION instr, byte[] prefixes, DISASM_INOUT_PARAMS param)
{
    uint i;
    bool mem_op_found = false;

    if (prefixes[PREF_SEG_INDEX] != 0xFF)
    {
        for (i = 0; i < 3; i++)
        {
            if ((instr.ops[i].flags & OPERAND_TYPE_MEM)!=0)
            {
                if (param.mode == DISASSEMBLE_MODE_64)
                {
                    if ( !((prefixes[PREF_SEG_INDEX] == PREF_FS_ID) || (prefixes[PREF_SEG_INDEX] == PREF_GS_ID)) )
                    {
                        add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, param);
                    }
                }
                else
                {
                    if ( (instr.ops[i].value.addr.mod & ADDR_MOD_BASE)==0 )
                    {
                        if (instr.ops[i].value.addr.seg == SREG_CODE_DS)
                            add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, param);
                    }
                    else
                    {
                        if ((instr.ops[i].value.addr.bas == REG_CODE_BP) || (instr.ops[i].value.addr.bas == REG_CODE_SP))
                        {
                            if (instr.ops[i].value.addr.seg == SREG_CODE_SS)
                                add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, param);
                        }
                        else
                        {
                            if (instr.ops[i].value.addr.seg == SREG_CODE_DS)
                                add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, param);
                        }
                    }
                }

                mem_op_found = true;
            }
        }

        if (!mem_op_found)
            add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, param);
    }
}


//Converts prefixes from internal to external representation.
static void convert_prefixes(INSTRUCTION instr, byte[] prefixes)
{
    for (int i = 0; i < PREFIX_COUNT; i++)
    {
        if (prefixes[i] != 0xFF)
            instr.prefixes |= pref_bits[prefixes[i]];
    }
}


        Win32Assembly a;
        public OPERAND b;
        public mediana(Win32Assembly assembly)
        {
            a = assembly;
            //tables = new TABLE_DESCRIPTOR[1]() = {0x0, 0xFF, 0xFF, 0x0, 0x0, "opcodes_1byte" };
        }
        public UInt32 medi_disassemble(ulong offset, INSTRUCTION instr, DISASM_INOUT_PARAMS param)
        {
            UInt32 len;
            UInt32 res;
            OPCODE_DESCRIPTOR opcode = new OPCODE_DESCRIPTOR();
            INTERNAL_DATA idata = new INTERNAL_DATA(0xFF);

            //Setup everything.
            //memset(instr, 0x0, sizeof(*instr));
            //memset(&idata, 0x0, sizeof(idata));
            //memset(idata.prefixes, 0xFF, sizeof(idata.prefixes));
            param.sf_prefixes_len = 0;
            param.errcode = 0;
            len = res = 0;
            //Lookup opcode.
            res = parse_opcode(offset, opcode, instr, idata, param);
            if (idata.severe_err!=ERR_OK)
            {
                param.errcode = idata.severe_err;
                return 0;
            }
            len += res;

	if (len > MAX_INSTRUCTION_LEN)
    {
        param.errcode = ERR_TOO_LONG;
        return 0;
    }

    get_address_size(instr, idata.prefixes, param.mode);

    //Parse MODRM and SIB bytes.
    len += parse_modrm_sib(offset + len, instr, opcode);
    if (len > MAX_INSTRUCTION_LEN)
    {
        param.errcode = ERR_TOO_LONG;
        return 0;
    }

    //Copy flags, eflags, id, groups.
    copy_eflags(instr, opcode);
    copy_instr_flags(instr, opcode);
    instr.id = opcode.id;
    instr.groups = opcode.groups;

    //Parse mnemonic.
    parse_mnemonic(opcode, instr, idata, param.mode);
    if (idata.severe_err!=ERR_OK)
    {
        param.errcode = idata.severe_err;
        return 0;
    }

    //Deal with operands.
    res = parse_operand(offset, offset + len, opcode.ops[0], instr, 0, idata, param.mode);
    if (idata.severe_err!=ERR_OK)
    {
        param.errcode = idata.severe_err;
        return 0;
    }
    len += res;
    if (len > MAX_INSTRUCTION_LEN)
    {
        param.errcode = ERR_TOO_LONG;
        return 0;
    }

    res = parse_operand(offset, offset + len, opcode.ops[1], instr, 1, idata, param.mode);
    if (idata.severe_err!=ERR_OK)
    {
        param.errcode = idata.severe_err;
        return 0;
    }
    len += res;
    if (len > MAX_INSTRUCTION_LEN)
    {
        param.errcode = ERR_TOO_LONG;
        return 0;
    }

    res = parse_operand(offset, offset + len, opcode.ops[2], instr, 2, idata, param.mode);
    if (idata.severe_err!=ERR_OK)
    {
        param.errcode = idata.severe_err;
        return 0;
    }
    len += res;
    if (len > MAX_INSTRUCTION_LEN)
    {
        param.errcode = ERR_TOO_LONG;
        return 0;
    }

    //Do postprocessing if necessary.
    if ((opcode.props & PROP_POST_PROC)!=0)
    {
        res = postprocs[opcode.props >> POST_PROC_SHIFT](offset, offset, instr, idata, param.mode);
        if (idata.severe_err!=ERR_OK)
        {
            param.errcode = idata.severe_err;
            return 0;
        }
        if (res>0)
        {
            len = res;
            if (len > MAX_INSTRUCTION_LEN)
            {
                param.errcode = ERR_TOO_LONG;
                return 0;
            }
        }
    }

    //Check if REX is superfluous.
    if ((param.mode == DISASSEMBLE_MODE_64) && (idata.is_rex_used!=0))
        add_sf_prefix_value(idata.prefixes, PREF_REX_INDEX, instr.rex, instr, param);
    //Check if segment prefix is superfluous.
    check_seg_sf_prefixes(instr, idata.prefixes, param);
    //Check if opsize is superfluous. 
    if ((idata.is_opsize_used!=0) && idata.prefixes[PREF_OPSIZE_INDEX] != 0xFF)
        add_sf_prefix(idata.prefixes, PREF_OPSIZE_INDEX, instr, param);
    //Check if addrsize is superfluous. 
    if ((idata.is_addrsize_used!=0) && idata.prefixes[PREF_ADDRSIZE_INDEX] != 0xFF)
        add_sf_prefix(idata.prefixes, PREF_ADDRSIZE_INDEX, instr, param);

    //Convert prefixes to output representation.
    convert_prefixes(instr, idata.prefixes);

    //Copy error if exists.
    param.errcode = idata.err;

    //And post checks.
    if ((param.arch & opcode.arch)!=0)
        param.errcode = ERR_ANOT_ARCH;//error: another architecture.
    else if ( ((instr.prefixes & INSTR_PREFIX_LOCK)!=0) && ((opcode.props & PROP_LOCK)==0) )
        param.errcode = ERR_NON_LOCKABLE;//error: prefix lock non-lockable instruction.
    else if (((opcode.props & PROP_I64)!=0) && (param.mode == DISASSEMBLE_MODE_64))
        param.errcode = ERR_16_32_ONLY;//error: instruction is 16/32bit mode only.
    else if (((opcode.props & PROP_O64)!=0) && (param.mode != DISASSEMBLE_MODE_64))
        param.errcode = ERR_64_ONLY;//error: instruction is 64bit mode only.

    apply_disasm_options(instr, len, param);

            return len;
        }
    }
}


