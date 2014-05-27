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
static uint ID_NULL       = 0x0;
static uint ID_SWITCH     = 0x1;
static uint ID_0F         = 0x2;
static uint ID_66         = 0x3;
static uint ID_67         = 0x4;
static uint ID_AAA        = 0x5;
static uint ID_AAD        = 0x6;
static uint ID_AAM        = 0x7;
static uint ID_AAS        = 0x8;
static uint ID_ADC        = 0x9;
static uint ID_ADD        = 0xA;
static uint ID_ADDPD      = 0xB;
static uint ID_ADDPS      = 0xC;
static uint ID_ADDSD      = 0xD;
static uint ID_ADDSS      = 0xE;
static uint ID_ADDSUBPD   = 0xF;
static uint ID_ADDSUBPS   = 0x10;
static uint ID_ALTER      = 0x11;
static uint ID_AND        = 0x12;
static uint ID_ANDNPD     = 0x13;
static uint ID_ANDNPS     = 0x14;
static uint ID_ANDPD      = 0x15;
static uint ID_ANDPS      = 0x16;
static uint ID_ARPL       = 0x17;
static uint ID_BLENDPD    = 0x18;
static uint ID_BLENDPS    = 0x19;
static uint ID_BLENDVPD   = 0x1A;
static uint ID_BLENDVPS   = 0x1B;
static uint ID_BOUND      = 0x1C;
static uint ID_BSF        = 0x1D;
static uint ID_BSR        = 0x1E;
static uint ID_BSWAP      = 0x1F;
static uint ID_BT         = 0x20;
static uint ID_BTC        = 0x21;
static uint ID_BTR        = 0x22;
static uint ID_BTS        = 0x23;
static uint ID_CALL       = 0x24;
static uint ID_CALLF      = 0x25;
static uint ID_CBW        = 0x26;
static uint ID_CLC        = 0x27;
static uint ID_CLD        = 0x28;
static uint ID_CLFLUSH    = 0x29;
static uint ID_CLI        = 0x2A;
static uint ID_CLTS       = 0x2B;
static uint ID_CMC        = 0x2C;
static uint ID_CMOVA      = 0x2D;
static uint ID_CMOVAE     = 0x2E;
static uint ID_CMOVB      = 0x2F;
static uint ID_CMOVBE     = 0x30;
static uint ID_CMOVG      = 0x31;
static uint ID_CMOVGE     = 0x32;
static uint ID_CMOVL      = 0x33;
static uint ID_CMOVLE     = 0x34;
static uint ID_CMOVNO     = 0x35;
static uint ID_CMOVNP     = 0x36;
static uint ID_CMOVNS     = 0x37;
static uint ID_CMOVNZ     = 0x38;
static uint ID_CMOVO      = 0x39;
static uint ID_CMOVP      = 0x3A;
static uint ID_CMOVS      = 0x3B;
static uint ID_CMOVZ      = 0x3C;
static uint ID_CMP        = 0x3D;
static uint ID_CMPPD      = 0x3E;
static uint ID_CMPPS      = 0x3F;
static uint ID_CMPS       = 0x40;
static uint ID_CMPSD      = 0x41;
static uint ID_CMPSS      = 0x42;
static uint ID_CMPXCHG    = 0x43;
static uint ID_CMPXCHG8B  = 0x44;
static uint ID_COMISD     = 0x45;
static uint ID_COMISS     = 0x46;
static uint ID_CPUID      = 0x47;
static uint ID_CRC32      = 0x48;
static uint ID_CS         = 0x49;
static uint ID_CVTDQ2PD   = 0x4A;
static uint ID_CVTDQ2PS   = 0x4B;
static uint ID_CVTPD2DQ   = 0x4C;
static uint ID_CVTPD2PI   = 0x4D;
static uint ID_CVTPD2PS   = 0x4E;
static uint ID_CVTPI2PD   = 0x4F;
static uint ID_CVTPI2PS   = 0x50;
static uint ID_CVTPS2DQ   = 0x51;
static uint ID_CVTPS2PD   = 0x52;
static uint ID_CVTPS2PI   = 0x53;
static uint ID_CVTSD2SI   = 0x54;
static uint ID_CVTSD2SS   = 0x55;
static uint ID_CVTSI2SD   = 0x56;
static uint ID_CVTSI2SS   = 0x57;
static uint ID_CVTSS2SD   = 0x58;
static uint ID_CVTSS2SI   = 0x59;
static uint ID_CVTTPD2DQ  = 0x5A;
static uint ID_CVTTPD2PI  = 0x5B;
static uint ID_CVTTPS2DQ  = 0x5C;
static uint ID_CVTTPS2PI  = 0x5D;
static uint ID_CVTTSD2SI  = 0x5E;
static uint ID_CVTTSS2SI  = 0x5F;
static uint ID_CWD        = 0x60;
static uint ID_DAA        = 0x61;
static uint ID_DAS        = 0x62;
static uint ID_DEC        = 0x63;
static uint ID_DIV        = 0x64;
static uint ID_DIVPD      = 0x65;
static uint ID_DIVPS      = 0x66;
static uint ID_DIVSD      = 0x67;
static uint ID_DIVSS      = 0x68;
static uint ID_DPPD       = 0x69;
static uint ID_DPPS       = 0x6A;
static uint ID_DS         = 0x6B;
static uint ID_EMMS       = 0x6C;
static uint ID_ENTER      = 0x6D;
static uint ID_ES         = 0x6E;
static uint ID_EXTRACTPS  = 0x6F;
static uint ID_F2XM1      = 0x70;
static uint ID_FABS       = 0x71;
static uint ID_FADD       = 0x72;
static uint ID_FADDP      = 0x73;
static uint ID_FBLD       = 0x74;
static uint ID_FBSTP      = 0x75;
static uint ID_FCHS       = 0x76;
static uint ID_FCMOVA     = 0x77;
static uint ID_FCMOVB     = 0x78;
static uint ID_FCMOVBE    = 0x79;
static uint ID_FCMOVNB    = 0x7A;
static uint ID_FCMOVNU    = 0x7B;
static uint ID_FCMOVNZ    = 0x7C;
static uint ID_FCMOVU     = 0x7D;
static uint ID_FCMOVZ     = 0x7E;
static uint ID_FCOM       = 0x7F;
static uint ID_FCOM2      = 0x80;
static uint ID_FCOMI      = 0x81;
static uint ID_FCOMIP     = 0x82;
static uint ID_FCOMP      = 0x83;
static uint ID_FCOMP3     = 0x84;
static uint ID_FCOMP5     = 0x85;
static uint ID_FCOMPP     = 0x86;
static uint ID_FCOS       = 0x87;
static uint ID_FDECSTP    = 0x88;
static uint ID_FDIV       = 0x89;
static uint ID_FDIVP      = 0x8A;
static uint ID_FDIVR      = 0x8B;
static uint ID_FDIVRP     = 0x8C;
static uint ID_FFREE      = 0x8D;
static uint ID_FFREEP     = 0x8E;
static uint ID_FIADD      = 0x8F;
static uint ID_FICOM      = 0x90;
static uint ID_FICOMP     = 0x91;
static uint ID_FIDIV      = 0x92;
static uint ID_FIDIVR     = 0x93;
static uint ID_FILD       = 0x94;
static uint ID_FIMUL      = 0x95;
static uint ID_FINCSTP    = 0x96;
static uint ID_FIST       = 0x97;
static uint ID_FISTP      = 0x98;
static uint ID_FISTTP     = 0x99;
static uint ID_FISUB      = 0x9A;
static uint ID_FISUBR     = 0x9B;
static uint ID_FLD        = 0x9C;
static uint ID_FLD1       = 0x9D;
static uint ID_FLD2LE     = 0x9E;
static uint ID_FLD2LT     = 0x9F;
static uint ID_FLDCW      = 0xA0;
static uint ID_FLDENV     = 0xA1;
static uint ID_FLDLG2     = 0xA2;
static uint ID_FLDLN2     = 0xA3;
static uint ID_FLDPI      = 0xA4;
static uint ID_FLDZ       = 0xA5;
static uint ID_FMUL       = 0xA6;
static uint ID_FMULP      = 0xA7;
static uint ID_FNCLEX     = 0xA8;
static uint ID_FNDISI     = 0xA9;
static uint ID_FNENI      = 0xAA;
static uint ID_FNINIT     = 0xAB;
static uint ID_FNOP       = 0xAC;
static uint ID_FNSAVE     = 0xAD;
static uint ID_FNSETPM    = 0xAE;
static uint ID_FNSTCW     = 0xAF;
static uint ID_FNSTENV    = 0xB0;
static uint ID_FNSTSW     = 0xB1;
static uint ID_FPATAN     = 0xB2;
static uint ID_FPREM      = 0xB3;
static uint ID_FPREM1     = 0xB4;
static uint ID_FPTAN      = 0xB5;
static uint ID_FRNDINT    = 0xB6;
static uint ID_FRSTOR     = 0xB7;
static uint ID_FS         = 0xB8;
static uint ID_FSCALE     = 0xB9;
static uint ID_FSIN       = 0xBA;
static uint ID_FSINCOS    = 0xBB;
static uint ID_FSQRT      = 0xBC;
static uint ID_FST        = 0xBD;
static uint ID_FSTP       = 0xBE;
static uint ID_FSTP1      = 0xBF;
static uint ID_FSTP8      = 0xC0;
static uint ID_FSTP9      = 0xC1;
static uint ID_FSUB       = 0xC2;
static uint ID_FSUBP      = 0xC3;
static uint ID_FSUBR      = 0xC4;
static uint ID_FSUBRP     = 0xC5;
static uint ID_FTST       = 0xC6;
static uint ID_FUCOM      = 0xC7;
static uint ID_FUCOMI     = 0xC8;
static uint ID_FUCOMIP    = 0xC9;
static uint ID_FUCOMP     = 0xCA;
static uint ID_FUCOMPP    = 0xCB;
static uint ID_FWAIT      = 0xCC;
static uint ID_FXAM       = 0xCD;
static uint ID_FXCH       = 0xCE;
static uint ID_FXCH4      = 0xCF;
static uint ID_FXCH7      = 0xD0;
static uint ID_FXRSTOR    = 0xD1;
static uint ID_FXSAVE     = 0xD2;
static uint ID_FXTRACT    = 0xD3;
static uint ID_FYL2X      = 0xD4;
static uint ID_FYL2XP1    = 0xD5;
static uint ID_GETSEC     = 0xD6;
static uint ID_GS         = 0xD7;
static uint ID_HADDPD     = 0xD8;
static uint ID_HADDPS     = 0xD9;
static uint ID_HINTNOP    = 0xDA;
static uint ID_HLT        = 0xDB;
static uint ID_HSUBPD     = 0xDC;
static uint ID_HSUBPS     = 0xDD;
static uint ID_ICEBP      = 0xDE;
static uint ID_IDIV       = 0xDF;
static uint ID_IMUL       = 0xE0;
static uint ID_IN         = 0xE1;
static uint ID_INC        = 0xE2;
static uint ID_INS        = 0xE3;
static uint ID_INSERTPS   = 0xE4;
static uint ID_INT        = 0xE5;
static uint ID_INTO       = 0xE6;
static uint ID_INVD       = 0xE7;
static uint ID_INVEPT     = 0xE8;
static uint ID_INVLPG     = 0xE9;
static uint ID_INVVPID    = 0xEA;
static uint ID_IRET       = 0xEB;
static uint ID_JA         = 0xEC;
static uint ID_JAE        = 0xED;
static uint ID_JB         = 0xEE;
static uint ID_JBE        = 0xEF;
static uint ID_JCXZ       = 0xF0;
static uint ID_JG         = 0xF1;
static uint ID_JGE        = 0xF2;
static uint ID_JL         = 0xF3;
static uint ID_JLE        = 0xF4;
static uint ID_JMP        = 0xF5;
static uint ID_JMPE       = 0xF6;
static uint ID_JMPF       = 0xF7;
static uint ID_JNO        = 0xF8;
static uint ID_JNP        = 0xF9;
static uint ID_JNS        = 0xFA;
static uint ID_JNZ        = 0xFB;
static uint ID_JO         = 0xFC;
static uint ID_JP         = 0xFD;
static uint ID_JS         = 0xFE;
static uint ID_JZ         = 0xFF;
static uint ID_LAHF       = 0x100;
static uint ID_LAR        = 0x101;
static uint ID_LDDQU      = 0x102;
static uint ID_LDMXCSR    = 0x103;
static uint ID_LDS        = 0x104;
static uint ID_LEA        = 0x105;
static uint ID_LEAVE      = 0x106;
static uint ID_LES        = 0x107;
static uint ID_LFENCE     = 0x108;
static uint ID_LFS        = 0x109;
static uint ID_LGDT       = 0x10A;
static uint ID_LGS        = 0x10B;
static uint ID_LIDT       = 0x10C;
static uint ID_LLDT       = 0x10D;
static uint ID_LMSW       = 0x10E;
static uint ID_LOADALL    = 0x10F;
static uint ID_LOCK       = 0x110;
static uint ID_LODS       = 0x111;
static uint ID_LOOP       = 0x112;
static uint ID_LOOPNZ     = 0x113;
static uint ID_LOOPZ      = 0x114;
static uint ID_LSL        = 0x115;
static uint ID_LSS        = 0x116;
static uint ID_LTR        = 0x117;
static uint ID_MASKMOVDQU = 0x118;
static uint ID_MASKMOVQ   = 0x119;
static uint ID_MAXPD      = 0x11A;
static uint ID_MAXPS      = 0x11B;
static uint ID_MAXSD      = 0x11C;
static uint ID_MAXSS      = 0x11D;
static uint ID_MFENCE     = 0x11E;
static uint ID_MINPD      = 0x11F;
static uint ID_MINPS      = 0x120;
static uint ID_MINSD      = 0x121;
static uint ID_MINSS      = 0x122;
static uint ID_MONITOR    = 0x123;
static uint ID_MOV        = 0x124;
static uint ID_MOVAPD     = 0x125;
static uint ID_MOVAPS     = 0x126;
static uint ID_MOVBE      = 0x127;
static uint ID_MOVD       = 0x128;
static uint ID_MOVDDUP    = 0x129;
static uint ID_MOVDQ2Q    = 0x12A;
static uint ID_MOVDQA     = 0x12B;
static uint ID_MOVDQU     = 0x12C;
static uint ID_MOVHLPS    = 0x12D;
static uint ID_MOVHPD     = 0x12E;
static uint ID_MOVHPS     = 0x12F;
static uint ID_MOVLPD     = 0x130;
static uint ID_MOVLPS     = 0x131;
static uint ID_MOVMSKPD   = 0x132;
static uint ID_MOVMSKPS   = 0x133;
static uint ID_MOVNTDQ    = 0x134;
static uint ID_MOVNTDQA   = 0x135;
static uint ID_MOVNTI     = 0x136;
static uint ID_MOVNTPD    = 0x137;
static uint ID_MOVNTPS    = 0x138;
static uint ID_MOVNTQ     = 0x139;
static uint ID_MOVQ       = 0x13A;
static uint ID_MOVQ2DQ    = 0x13B;
static uint ID_MOVS       = 0x13C;
static uint ID_MOVSD      = 0x13D;
static uint ID_MOVSHDUP   = 0x13E;
static uint ID_MOVSLDUP   = 0x13F;
static uint ID_MOVSS      = 0x140;
static uint ID_MOVSX      = 0x141;
static uint ID_MOVSXD     = 0x142;
static uint ID_MOVUPD     = 0x143;
static uint ID_MOVUPS     = 0x144;
static uint ID_MOVZX      = 0x145;
static uint ID_MPSADBW    = 0x146;
static uint ID_MUL        = 0x147;
static uint ID_MULPD      = 0x148;
static uint ID_MULPS      = 0x149;
static uint ID_MULSD      = 0x14A;
static uint ID_MULSS      = 0x14B;
static uint ID_MWAIT      = 0x14C;
static uint ID_NEG        = 0x14D;
static uint ID_NOP        = 0x14E;
static uint ID_NOT        = 0x14F;
static uint ID_OR         = 0x150;
static uint ID_ORPD       = 0x151;
static uint ID_ORPS       = 0x152;
static uint ID_OUT        = 0x153;
static uint ID_OUTS       = 0x154;
static uint ID_PABSB      = 0x155;
static uint ID_PABSD      = 0x156;
static uint ID_PABSW      = 0x157;
static uint ID_PACKSSDW   = 0x158;
static uint ID_PACKSSWB   = 0x159;
static uint ID_PACKUSDW   = 0x15A;
static uint ID_PACKUSWB   = 0x15B;
static uint ID_PADDB      = 0x15C;
static uint ID_PADDD      = 0x15D;
static uint ID_PADDQ      = 0x15E;
static uint ID_PADDSB     = 0x15F;
static uint ID_PADDSW     = 0x160;
static uint ID_PADDUSB    = 0x161;
static uint ID_PADDUSW    = 0x162;
static uint ID_PADDW      = 0x163;
static uint ID_PALIGNR    = 0x164;
static uint ID_PAND       = 0x165;
static uint ID_PANDN      = 0x166;
static uint ID_PAUSE      = 0x167;
static uint ID_PAVGB      = 0x168;
static uint ID_PAVGW      = 0x169;
static uint ID_PBLENDVB   = 0x16A;
static uint ID_PBLENDW    = 0x16B;
static uint ID_PCMPEQB    = 0x16C;
static uint ID_PCMPEQD    = 0x16D;
static uint ID_PCMPEQQ    = 0x16E;
static uint ID_PCMPEQW    = 0x16F;
static uint ID_PCMPESTRI  = 0x170;
static uint ID_PCMPESTRM  = 0x171;
static uint ID_PCMPGTB    = 0x172;
static uint ID_PCMPGTD    = 0x173;
static uint ID_PCMPGTQ    = 0x174;
static uint ID_PCMPGTW    = 0x175;
static uint ID_PCMPISTRI  = 0x176;
static uint ID_PCMPISTRM  = 0x177;
static uint ID_PEXTRB     = 0x178;
static uint ID_PEXTRQ     = 0x179;
static uint ID_PEXTRW     = 0x17A;
static uint ID_PHADDD     = 0x17B;
static uint ID_PHADDSW    = 0x17C;
static uint ID_PHADDW     = 0x17D;
static uint ID_PHMINPOSUW = 0x17E;
static uint ID_PHSUBD     = 0x17F;
static uint ID_PHSUBSW    = 0x180;
static uint ID_PHSUBW     = 0x181;
static uint ID_PINSRB     = 0x182;
static uint ID_PINSRQ     = 0x183;
static uint ID_PINSRW     = 0x184;
static uint ID_PMADDUBSW  = 0x185;
static uint ID_PMADDWD    = 0x186;
static uint ID_PMAXSB     = 0x187;
static uint ID_PMAXSD     = 0x188;
static uint ID_PMAXSW     = 0x189;
static uint ID_PMAXUB     = 0x18A;
static uint ID_PMAXUD     = 0x18B;
static uint ID_PMAXUW     = 0x18C;
static uint ID_PMINSB     = 0x18D;
static uint ID_PMINSD     = 0x18E;
static uint ID_PMINSW     = 0x18F;
static uint ID_PMINUB     = 0x190;
static uint ID_PMINUD     = 0x191;
static uint ID_PMINUW     = 0x192;
static uint ID_PMOVMSKB   = 0x193;
static uint ID_PMOVSXBD   = 0x194;
static uint ID_PMOVSXBQ   = 0x195;
static uint ID_PMOVSXBW   = 0x196;
static uint ID_PMOVSXDQ   = 0x197;
static uint ID_PMOVSXWD   = 0x198;
static uint ID_PMOVSXWQ   = 0x199;
static uint ID_PMOVZXBD   = 0x19A;
static uint ID_PMOVZXBQ   = 0x19B;
static uint ID_PMOVZXBW   = 0x19C;
static uint ID_PMOVZXDQ   = 0x19D;
static uint ID_PMOVZXWD   = 0x19E;
static uint ID_PMOVZXWQ   = 0x19F;
static uint ID_PMULDQ     = 0x1A0;
static uint ID_PMULHRSW   = 0x1A1;
static uint ID_PMULHUW    = 0x1A2;
static uint ID_PMULHW     = 0x1A3;
static uint ID_PMULLD     = 0x1A4;
static uint ID_PMULLW     = 0x1A5;
static uint ID_PMULUDQ    = 0x1A6;
static uint ID_POP        = 0x1A7;
static uint ID_POPA       = 0x1A8;
static uint ID_POPCNT     = 0x1A9;
static uint ID_POPF       = 0x1AA;
static uint ID_POR        = 0x1AB;
static uint ID_PREFETCHNTA= 0x1AC;
static uint ID_PREFETCHT0 = 0x1AD;
static uint ID_PREFETCHT1 = 0x1AE;
static uint ID_PREFETCHT2 = 0x1AF;
static uint ID_PSADBW     = 0x1B0;
static uint ID_PSHUFB     = 0x1B1;
static uint ID_PSHUFD     = 0x1B2;
static uint ID_PSHUFHW    = 0x1B3;
static uint ID_PSHUFLW    = 0x1B4;
static uint ID_PSHUFW     = 0x1B5;
static uint ID_PSIGNB     = 0x1B6;
static uint ID_PSIGND     = 0x1B7;
static uint ID_PSIGNW     = 0x1B8;
static uint ID_PSLLD      = 0x1B9;
static uint ID_PSLLDQ     = 0x1BA;
static uint ID_PSLLQ      = 0x1BB;
static uint ID_PSLLW      = 0x1BC;
static uint ID_PSRAD      = 0x1BD;
static uint ID_PSRAW      = 0x1BE;
static uint ID_PSRLD      = 0x1BF;
static uint ID_PSRLDQ     = 0x1C0;
static uint ID_PSRLQ      = 0x1C1;
static uint ID_PSRLW      = 0x1C2;
static uint ID_PSUBB      = 0x1C3;
static uint ID_PSUBD      = 0x1C4;
static uint ID_PSUBQ      = 0x1C5;
static uint ID_PSUBSB     = 0x1C6;
static uint ID_PSUBSW     = 0x1C7;
static uint ID_PSUBUSB    = 0x1C8;
static uint ID_PSUBUSW    = 0x1C9;
static uint ID_PSUBW      = 0x1CA;
static uint ID_PTEST      = 0x1CB;
static uint ID_PUNPCKHBD  = 0x1CC;
static uint ID_PUNPCKHBDQ = 0x1CD;
static uint ID_PUNPCKHBW  = 0x1CE;
static uint ID_PUNPCKHDQ  = 0x1CF;
static uint ID_PUNPCKHQDQ = 0x1D0;
static uint ID_PUNPCKHWD  = 0x1D1;
static uint ID_PUNPCKLBW  = 0x1D2;
static uint ID_PUNPCKLDQ  = 0x1D3;
static uint ID_PUNPCKLQDQ = 0x1D4;
static uint ID_PUNPCKLWD  = 0x1D5;
static uint ID_PUSH       = 0x1D6;
static uint ID_PUSHA      = 0x1D7;
static uint ID_PUSHF      = 0x1D8;
static uint ID_PXOR       = 0x1D9;
static uint ID_RCL        = 0x1DA;
static uint ID_RCPPS      = 0x1DB;
static uint ID_RCPSS      = 0x1DC;
static uint ID_RCR        = 0x1DD;
static uint ID_RDMSR      = 0x1DE;
static uint ID_RDPMC      = 0x1DF;
static uint ID_RDTSC      = 0x1E0;
static uint ID_RDTSCP     = 0x1E1;
static uint ID_REPNZ      = 0x1E2;
static uint ID_REPZ       = 0x1E3;
static uint ID_RETF       = 0x1E4;
static uint ID_RETN       = 0x1E5;
static uint ID_ROL        = 0x1E6;
static uint ID_ROR        = 0x1E7;
static uint ID_ROUNDPD    = 0x1E8;
static uint ID_ROUNDPS    = 0x1E9;
static uint ID_ROUNDSD    = 0x1EA;
static uint ID_ROUNDSS    = 0x1EB;
static uint ID_RSM        = 0x1EC;
static uint ID_RSQRTPS    = 0x1ED;
static uint ID_RSQRTSS    = 0x1EE;
static uint ID_SAHF       = 0x1EF;
static uint ID_SAL        = 0x1F0;
static uint ID_SAR        = 0x1F1;
static uint ID_SBB        = 0x1F2;
static uint ID_SCAS       = 0x1F3;
static uint ID_SETA       = 0x1F4;
static uint ID_SETAE      = 0x1F5;
static uint ID_SETALC     = 0x1F6;
static uint ID_SETB       = 0x1F7;
static uint ID_SETBE      = 0x1F8;
static uint ID_SETG       = 0x1F9;
static uint ID_SETGE      = 0x1FA;
static uint ID_SETL       = 0x1FB;
static uint ID_SETLE      = 0x1FC;
static uint ID_SETNO      = 0x1FD;
static uint ID_SETNP      = 0x1FE;
static uint ID_SETNS      = 0x1FF;
static uint ID_SETNZ      = 0x200;
static uint ID_SETO       = 0x201;
static uint ID_SETP       = 0x202;
static uint ID_SETS       = 0x203;
static uint ID_SETZ       = 0x204;
static uint ID_SFENCE     = 0x205;
static uint ID_SGDT       = 0x206;
static uint ID_SHL        = 0x207;
static uint ID_SHLD       = 0x208;
static uint ID_SHR        = 0x209;
static uint ID_SHRD       = 0x20A;
static uint ID_SHUFPD     = 0x20B;
static uint ID_SHUFPS     = 0x20C;
static uint ID_SIDT       = 0x20D;
static uint ID_SLDT       = 0x20E;
static uint ID_SMSW       = 0x20F;
static uint ID_SQRTPD     = 0x210;
static uint ID_SQRTPS     = 0x211;
static uint ID_SQRTSD     = 0x212;
static uint ID_SQRTSS     = 0x213;
static uint ID_SS         = 0x214;
static uint ID_STC        = 0x215;
static uint ID_STD        = 0x216;
static uint ID_STI        = 0x217;
static uint ID_STMXCSR    = 0x218;
static uint ID_STOS       = 0x219;
static uint ID_STR        = 0x21A;
static uint ID_SUB        = 0x21B;
static uint ID_SUBPD      = 0x21C;
static uint ID_SUBPS      = 0x21D;
static uint ID_SUBSD      = 0x21E;
static uint ID_SUBSS      = 0x21F;
static uint ID_SWAPGS     = 0x220;
static uint ID_SYSCALL    = 0x221;
static uint ID_SYSENTER   = 0x222;
static uint ID_SYSEXIT    = 0x223;
static uint ID_SYSRET     = 0x224;
static uint ID_TEST       = 0x225;
static uint ID_UCOMISD    = 0x226;
static uint ID_UCOMISS    = 0x227;
static uint ID_UD         = 0x228;
static uint ID_UD2        = 0x229;
static uint ID_UNPCKHPD   = 0x22A;
static uint ID_UNPCKHPS   = 0x22B;
static uint ID_UNPCKLPD   = 0x22C;
static uint ID_UNPCKLPS   = 0x22D;
static uint ID_VERR       = 0x22E;
static uint ID_VERW       = 0x22F;
static uint ID_VMCALL     = 0x230;
static uint ID_VMCLEAR    = 0x231;
static uint ID_VMLAUNCH   = 0x232;
static uint ID_VMPTRLD    = 0x233;
static uint ID_VMPTRST    = 0x234;
static uint ID_VMREAD     = 0x235;
static uint ID_VMRESUME   = 0x236;
static uint ID_VMWRITE    = 0x237;
static uint ID_VMXOFF     = 0x238;
static uint ID_VMXON      = 0x239;
static uint ID_WBINVD     = 0x23A;
static uint ID_WRMSR      = 0x23B;
static uint ID_XADD       = 0x23C;
static uint ID_XCHG       = 0x23D;
static uint ID_XGETBV     = 0x23E;
static uint ID_XLAT       = 0x23F;
static uint ID_XOR        = 0x240;
static uint ID_XORPD      = 0x241;
static uint ID_XORPS      = 0x242;
static uint ID_XRSTOR     = 0x243;
static uint ID_XSAVE      = 0x244;
static uint ID_XSETBV     = 0x245;




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
public struct INTERNAL_DATA
{
    public byte[] prefixes;//[PREFIX_COUNT]; //Valuable prefixes.
    public byte severe_err;             //Severe disassembling error.
    public byte err;                    //DIsassembling error.
    public byte is_opsize_used;         //
    public byte is_addrsize_used;       //Prefixes were used during disassembling.
    public byte is_rex_used;            //
};

public struct MULTI_MNEMONIC
{
    public char indicator;
    public uint size;
    //public SQ b;
    public string[] values;
}
//static struct MULTI_MNEMONIC pusha  = { MM_INDICATOR, SQ_v,      { _UT("pusha"),   _UT("pushad"),  _UT("bad_mnem")  } };
public struct MNEMONIC
{
    public string value;
    public MULTI_MNEMONIC multi_mnemonic;
};

public struct INTERNAL_OPERAND
{
    public byte type;
    public byte size;
};
public struct OPCODE_DESCRIPTOR
{
    public UInt64 groups;
    public MNEMONIC mnemonic;
    public UInt16 id;
    public INTERNAL_OPERAND[] ops;//[3]
    public UInt16 props;
    public byte tested_flags;
    public byte modified_flags;
    public byte set_flags;
    public byte cleared_flags;
    public byte undefined_flags;
    public byte arch;
};
public struct TABLE_DESCRIPTOR
{
    public byte min, max, mask, shift, props;
    public OPCODE_DESCRIPTOR[] opcodes;
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

//INSTRUCTION.addrsize's values:
static byte ADDR_SIZE_16 = 0x2;
static byte ADDR_SIZE_32 = 0x4;
static byte ADDR_SIZE_64 = 0x8;

//DISASM_INOUT_PARAMS.options' bits:
static byte DISASM_OPTION_APPLY_REL     = 0x1;
static byte DISASM_OPTION_OPTIMIZE_DISP = 0x2;


static char MM_INDICATOR = '*';

public static TABLE_DESCRIPTOR[] tables;// =
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
        get_instruction_opsize(opcode.mnemonic.multi_mnemonic, instr, idata, mode);
        instr.mnemonic = opcode.mnemonic.multi_mnemonic.values[bsr(instr.opsize) - 1];
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
        }
        public UInt32 medi_disassemble(ulong offset, INSTRUCTION instr, DISASM_INOUT_PARAMS param)
        {
            UInt32 len;
            UInt32 res;
            OPCODE_DESCRIPTOR opcode = new OPCODE_DESCRIPTOR();
            INTERNAL_DATA idata = new INTERNAL_DATA();
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


