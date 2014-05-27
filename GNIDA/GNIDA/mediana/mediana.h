/******************************************************************************
* Copyright (c) 2010, Mikae
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 3. All advertising materials mentioning features or use of this software
*    must display the following acknowledgement:
*    This product includes software developed by the Mikae.
* 4. Neither the name of Mikae nor the
*    names of its contributors may be used to endorse or promote products
*    derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY Mikae ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Mikae BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************
*/

#include "pstdint.h"
#include "mediana_ctrl.h"

#ifndef __MEDIANA_H__
#define __MEDIANA_H__

/*****************
* Unicode support.
******************
*/
#ifdef UNICODE
typedef wchar_t unichar_t;
#define _UT(s) L##s
#define unistrcpy  wcscpy_s
#define unistrncpy wcsncpy
#define unistrchr  wcschr
#define unistrlen  wcslen
#else
typedef char unichar_t;
#define _UT(s) s
#define unistrcpy  strcpy
#define unistrncpy strncpy
#define unistrchr  strchr
#define unistrlen  strlen
#endif

/************************
* Defines and structs for
* operand.
*************************
*/
//OPERAND.flags' values:
#define OPERAND_TYPE_REG  0x01
#define OPERAND_TYPE_MEM  0x02
#define OPERAND_TYPE_IMM  0x04
#define OPERAND_TYPE_DIR  0x08
#define OPERAND_TYPE_MASK 0x0F

#define OPERAND_FLAG_PRESENT 0x10
#define OPERAND_FLAG_REL     0x20

//OPERAND.size's values:
#define OPERAND_SIZE_8    0x0001
#define OPERAND_SIZE_16   0x0002
#define OPERAND_SIZE_32   0x0004
#define OPERAND_SIZE_48   0x0006
#define OPERAND_SIZE_64   0x0008
#define OPERAND_SIZE_80   0x000A
#define OPERAND_SIZE_128  0x0010
#define OPERAND_SIZE_14   0x000E
#define OPERAND_SIZE_28   0x001C
#define OPERAND_SIZE_94   0x005E
#define OPERAND_SIZE_108  0x006C
#define OPERAND_SIZE_512  0x0200

//OPERAND.ADDR.mod's bits:
#define ADDR_MOD_BASE 0x1
#define ADDR_MOD_IDX  0x2
#define ADDR_MOD_DISP 0x4

//OPERAND.REG.type's values:
#define REG_TYPE_GEN 0x0
#define REG_TYPE_SEG 0x1
#define REG_TYPE_CR  0x2
#define REG_TYPE_DBG 0x3
#define REG_TYPE_TR  0x4
#define REG_TYPE_FPU 0x5
#define REG_TYPE_MMX 0x7
#define REG_TYPE_XMM 0x8

//OPERAND.REG.code's values (GPR):
#define REG_CODE_AX  0x0
#define REG_CODE_CX  0x1
#define REG_CODE_DX  0x2
#define REG_CODE_BX  0x3
#define REG_CODE_SP  0x4
#define REG_CODE_BP  0x5
#define REG_CODE_SI  0x6
#define REG_CODE_DI  0x7

#define REG_CODE_64  0x8

#define REG_CODE_R8  0x8
#define REG_CODE_R9  0x9
#define REG_CODE_R10 0xA
#define REG_CODE_R11 0xB
#define REG_CODE_R12 0xC
#define REG_CODE_R13 0xD
#define REG_CODE_R14 0xE
#define REG_CODE_R15 0xF
#define REG_CODE_SPL 0x10
#define REG_CODE_BPL 0x11
#define REG_CODE_SIL 0x12
#define REG_CODE_DIL 0x13
#define REG_CODE_IP  0x14

//OPERAND.REG.code's values (segment registers):
#define SREG_CODE_CS 0x0
#define SREG_CODE_DS 0x1
#define SREG_CODE_ES 0x2
#define SREG_CODE_SS 0x3
#define SREG_CODE_FS 0x4
#define SREG_CODE_GS 0x5

//OPERAND.REG.code's values (FPU registers):
#define FREG_CODE_ST0 0x0
#define FREG_CODE_ST1 0x1
#define FREG_CODE_ST2 0x2
#define FREG_CODE_ST3 0x3
#define FREG_CODE_ST4 0x4
#define FREG_CODE_ST5 0x5
#define FREG_CODE_ST6 0x6
#define FREG_CODE_ST7 0x7

//OPERAND.REG.code's values (control registers):
#define CREG_CODE_CR0 0x0
#define CREG_CODE_CR1 0x1
#define CREG_CODE_CR2 0x2
#define CREG_CODE_CR3 0x3
#define CREG_CODE_CR4 0x4
#define CREG_CODE_CR5 0x5
#define CREG_CODE_CR6 0x6
#define CREG_CODE_CR7 0x7

//OPERAND.REG.code's values (debug registers):
#define DREG_CODE_DR0 0x0
#define DREG_CODE_DR1 0x1
#define DREG_CODE_DR2 0x2
#define DREG_CODE_DR3 0x3
#define DREG_CODE_DR4 0x4
#define DREG_CODE_DR5 0x5
#define DREG_CODE_DR6 0x6
#define DREG_CODE_DR7 0x7

//OPERAND.REG.code's values (MMX registers):
#define MREG_CODE_MM0 0x0
#define MREG_CODE_MM1 0x1
#define MREG_CODE_MM2 0x2
#define MREG_CODE_MM3 0x3
#define MREG_CODE_MM4 0x4
#define MREG_CODE_MM5 0x5
#define MREG_CODE_MM6 0x6
#define MREG_CODE_MM7 0x7

//OPERAND.REG.code's values (XMM registers):
#define XREG_CODE_XMM0  0x0
#define XREG_CODE_XMM1  0x1
#define XREG_CODE_XMM2  0x2
#define XREG_CODE_XMM3  0x3
#define XREG_CODE_XMM4  0x4
#define XREG_CODE_XMM5  0x5
#define XREG_CODE_XMM6  0x6
#define XREG_CODE_XMM7  0x7

#define XREG_CODE_XMM8  0x8
#define XREG_CODE_XMM9  0x9
#define XREG_CODE_XMM10 0xA
#define XREG_CODE_XMM11 0xB
#define XREG_CODE_XMM12 0xC
#define XREG_CODE_XMM13 0xD
#define XREG_CODE_XMM14 0xE
#define XREG_CODE_XMM15 0xF

#pragma pack(push, MEDIANA_CTRL_OPERAND_PACK)
struct OPERAND
{
	union
	{
		struct REG
		{
			uint8_t code;
			uint8_t type;
		} reg;

		struct IMM
		{
			union
			{
				uint8_t  imm8;
				uint16_t imm16;
				uint32_t imm32;
				uint64_t imm64;
			};
			uint8_t size;
			uint8_t offset;
		} imm;

		struct FAR_ADDR
		{
			union
			{
				struct FAR_ADDR32
				{
					uint16_t offset;
					uint16_t seg;
				} far_addr32;

				struct FAR_ADDR48
				{
					uint32_t offset;
					uint16_t seg;
				} far_addr48;
			};

			uint8_t offset;
		} far_addr;

		struct ADDR
		{
			uint8_t seg;
			uint8_t mod;
			uint8_t base;
			uint8_t index;
			uint8_t scale;
		} addr;
	} value;

	uint16_t size; //Fuck... I need 16_t only for 'stx' size qualifier.
	uint8_t flags;
};
#pragma pack (pop)

/************************
* Defines and structs for
* instruction.
*************************
*/
//INSTRUCTION.flag's values:
#define INSTR_FLAG_MODRM       0x0001
#define INSTR_FLAG_SIB         0x0002
#define INSTR_FLAG_SF_PREFIXES 0x0004
#define INSTR_FLAG_IOPL        0x0008
#define INSTR_FLAG_RING0       0x0010
#define INSTR_FLAG_SERIAL      0x0020
#define INSTR_FLAG_UNDOC       0x0040

//INSTRUCTION.prefixes values.
//Segment prefixes:
#define INSTR_PREFIX_CS 0x0001
#define INSTR_PREFIX_DS 0x0002
#define INSTR_PREFIX_ES 0x0004
#define INSTR_PREFIX_SS 0x0008
#define INSTR_PREFIX_FS 0x0010
#define INSTR_PREFIX_GS 0x0020
//Segment prefixes mask:
#define INSTR_PREFIX_SEG_MASK  0x003F
//Repeat prefixes:
#define INSTR_PREFIX_REPZ      0x0040
#define INSTR_PREFIX_REPNZ     0x0080
//Repeat prefixes mask:
#define INSTR_PREFIX_REP_MASK  0x00C0
//Size override prefixes:
#define INSTR_PREFIX_OPSIZE    0x0100
#define INSTR_PREFIX_ADDRSIZE  0x0200
#define INSTR_PREFIX_REX       0x0400
//Operand size prefixes mask:
#define INSTR_PREFIX_SIZE_MASK 0x0300
//LOCK prefix:
#define INSTR_PREFIX_LOCK      0x0800

//INSTRUCTION.rex's bits:
#define PREFIX_REX_W 0x8
#define PREFIX_REX_R 0x4
#define PREFIX_REX_X 0x2
#define PREFIX_REX_B 0x1

#define MAX_MNEMONIC_LEN    0x0C * sizeof(unichar_t)
#define MAX_INSTRUCTION_LEN 0x0F

//INSTRUCTION.addrsize's values:
#define ADDR_SIZE_16 0x2
#define ADDR_SIZE_32 0x4
#define ADDR_SIZE_64 0x8

//INSTRUCTION.xxx_flags' bits:
#define EFLAG_C 0x01
#define EFLAG_P 0x02
#define EFLAG_A 0x04
#define EFLAG_Z 0x08
#define EFLAG_S 0x10
#define EFLAG_I 0x20
#define EFLAG_D 0x40
#define EFLAG_O 0x80

#define FPU_FLAG0 0x01
#define FPU_FLAG1 0x02
#define FPU_FLAG2 0x04
#define FPU_FLAG3 0x08

#pragma pack(push, MEDIANA_CTRL_DISP_PACK)
struct DISPLACEMENT
{
    uint8_t size;
    uint8_t offset;
    union VALUE
    {
        int16_t d16;
        int32_t d32;
        int64_t d64;
    } value;
};
#pragma pack(pop)

#pragma pack(push, MEDIANA_CTRL_INSTRUCTION_PACK)
struct INSTRUCTION
{
	uint64_t groups;
	uint16_t id;
	uint16_t flags;
	uint16_t prefixes;
	uint8_t  opcode_offset;

	struct OPERAND ops[3];
	struct DISPLACEMENT disp;

	uint8_t addrsize;
	uint8_t opsize;
	uint8_t modrm;
	uint8_t sib;
	uint8_t rex;

	uint8_t tested_flags;
	uint8_t modified_flags;
	uint8_t set_flags;
	uint8_t cleared_flags;
	uint8_t undefined_flags;

	unichar_t mnemonic[MAX_MNEMONIC_LEN];
};
#pragma pack(pop)

/***********************************
* Structure for passing input/output
* disassembling parameters.
************************************
*/
struct DISASM_INOUT_PARAMS
{
    int      sf_prefixes_len;
    uint8_t *sf_prefixes;
    uint32_t errcode;
    uint8_t  arch;
    uint8_t  mode;
    uint8_t  options;
    uint64_t base;
};

//DISASM_INOUT_PARAMS.options' bits:
#define DISASM_OPTION_APPLY_REL     0x1
#define DISASM_OPTION_OPTIMIZE_DISP 0x2

/*******************
* Instructions' IDs.
********************
*/
#define ID_NULL        0x0
#define ID_SWITCH      0x1
#define ID_0F          0x2
#define ID_66          0x3
#define ID_67          0x4
#define ID_AAA         0x5
#define ID_AAD         0x6
#define ID_AAM         0x7
#define ID_AAS         0x8
#define ID_ADC         0x9
#define ID_ADD         0xA
#define ID_ADDPD       0xB
#define ID_ADDPS       0xC
#define ID_ADDSD       0xD
#define ID_ADDSS       0xE
#define ID_ADDSUBPD    0xF
#define ID_ADDSUBPS    0x10
#define ID_ALTER       0x11
#define ID_AND         0x12
#define ID_ANDNPD      0x13
#define ID_ANDNPS      0x14
#define ID_ANDPD       0x15
#define ID_ANDPS       0x16
#define ID_ARPL        0x17
#define ID_BLENDPD     0x18
#define ID_BLENDPS     0x19
#define ID_BLENDVPD    0x1A
#define ID_BLENDVPS    0x1B
#define ID_BOUND       0x1C
#define ID_BSF         0x1D
#define ID_BSR         0x1E
#define ID_BSWAP       0x1F
#define ID_BT          0x20
#define ID_BTC         0x21
#define ID_BTR         0x22
#define ID_BTS         0x23
#define ID_CALL        0x24
#define ID_CALLF       0x25
#define ID_CBW         0x26
#define ID_CLC         0x27
#define ID_CLD         0x28
#define ID_CLFLUSH     0x29
#define ID_CLI         0x2A
#define ID_CLTS        0x2B
#define ID_CMC         0x2C
#define ID_CMOVA       0x2D
#define ID_CMOVAE      0x2E
#define ID_CMOVB       0x2F
#define ID_CMOVBE      0x30
#define ID_CMOVG       0x31
#define ID_CMOVGE      0x32
#define ID_CMOVL       0x33
#define ID_CMOVLE      0x34
#define ID_CMOVNO      0x35
#define ID_CMOVNP      0x36
#define ID_CMOVNS      0x37
#define ID_CMOVNZ      0x38
#define ID_CMOVO       0x39
#define ID_CMOVP       0x3A
#define ID_CMOVS       0x3B
#define ID_CMOVZ       0x3C
#define ID_CMP         0x3D
#define ID_CMPPD       0x3E
#define ID_CMPPS       0x3F
#define ID_CMPS        0x40
#define ID_CMPSD       0x41
#define ID_CMPSS       0x42
#define ID_CMPXCHG     0x43
#define ID_CMPXCHG8B   0x44
#define ID_COMISD      0x45
#define ID_COMISS      0x46
#define ID_CPUID       0x47
#define ID_CRC32       0x48
#define ID_CS          0x49
#define ID_CVTDQ2PD    0x4A
#define ID_CVTDQ2PS    0x4B
#define ID_CVTPD2DQ    0x4C
#define ID_CVTPD2PI    0x4D
#define ID_CVTPD2PS    0x4E
#define ID_CVTPI2PD    0x4F
#define ID_CVTPI2PS    0x50
#define ID_CVTPS2DQ    0x51
#define ID_CVTPS2PD    0x52
#define ID_CVTPS2PI    0x53
#define ID_CVTSD2SI    0x54
#define ID_CVTSD2SS    0x55
#define ID_CVTSI2SD    0x56
#define ID_CVTSI2SS    0x57
#define ID_CVTSS2SD    0x58
#define ID_CVTSS2SI    0x59
#define ID_CVTTPD2DQ   0x5A
#define ID_CVTTPD2PI   0x5B
#define ID_CVTTPS2DQ   0x5C
#define ID_CVTTPS2PI   0x5D
#define ID_CVTTSD2SI   0x5E
#define ID_CVTTSS2SI   0x5F
#define ID_CWD         0x60
#define ID_DAA         0x61
#define ID_DAS         0x62
#define ID_DEC         0x63
#define ID_DIV         0x64
#define ID_DIVPD       0x65
#define ID_DIVPS       0x66
#define ID_DIVSD       0x67
#define ID_DIVSS       0x68
#define ID_DPPD        0x69
#define ID_DPPS        0x6A
#define ID_DS          0x6B
#define ID_EMMS        0x6C
#define ID_ENTER       0x6D
#define ID_ES          0x6E
#define ID_EXTRACTPS   0x6F
#define ID_F2XM1       0x70
#define ID_FABS        0x71
#define ID_FADD        0x72
#define ID_FADDP       0x73
#define ID_FBLD        0x74
#define ID_FBSTP       0x75
#define ID_FCHS        0x76
#define ID_FCMOVA      0x77
#define ID_FCMOVB      0x78
#define ID_FCMOVBE     0x79
#define ID_FCMOVNB     0x7A
#define ID_FCMOVNU     0x7B
#define ID_FCMOVNZ     0x7C
#define ID_FCMOVU      0x7D
#define ID_FCMOVZ      0x7E
#define ID_FCOM        0x7F
#define ID_FCOM2       0x80
#define ID_FCOMI       0x81
#define ID_FCOMIP      0x82
#define ID_FCOMP       0x83
#define ID_FCOMP3      0x84
#define ID_FCOMP5      0x85
#define ID_FCOMPP      0x86
#define ID_FCOS        0x87
#define ID_FDECSTP     0x88
#define ID_FDIV        0x89
#define ID_FDIVP       0x8A
#define ID_FDIVR       0x8B
#define ID_FDIVRP      0x8C
#define ID_FFREE       0x8D
#define ID_FFREEP      0x8E
#define ID_FIADD       0x8F
#define ID_FICOM       0x90
#define ID_FICOMP      0x91
#define ID_FIDIV       0x92
#define ID_FIDIVR      0x93
#define ID_FILD        0x94
#define ID_FIMUL       0x95
#define ID_FINCSTP     0x96
#define ID_FIST        0x97
#define ID_FISTP       0x98
#define ID_FISTTP      0x99
#define ID_FISUB       0x9A
#define ID_FISUBR      0x9B
#define ID_FLD         0x9C
#define ID_FLD1        0x9D
#define ID_FLD2LE      0x9E
#define ID_FLD2LT      0x9F
#define ID_FLDCW       0xA0
#define ID_FLDENV      0xA1
#define ID_FLDLG2      0xA2
#define ID_FLDLN2      0xA3
#define ID_FLDPI       0xA4
#define ID_FLDZ        0xA5
#define ID_FMUL        0xA6
#define ID_FMULP       0xA7
#define ID_FNCLEX      0xA8
#define ID_FNDISI      0xA9
#define ID_FNENI       0xAA
#define ID_FNINIT      0xAB
#define ID_FNOP        0xAC
#define ID_FNSAVE      0xAD
#define ID_FNSETPM     0xAE
#define ID_FNSTCW      0xAF
#define ID_FNSTENV     0xB0
#define ID_FNSTSW      0xB1
#define ID_FPATAN      0xB2
#define ID_FPREM       0xB3
#define ID_FPREM1      0xB4
#define ID_FPTAN       0xB5
#define ID_FRNDINT     0xB6
#define ID_FRSTOR      0xB7
#define ID_FS          0xB8
#define ID_FSCALE      0xB9
#define ID_FSIN        0xBA
#define ID_FSINCOS     0xBB
#define ID_FSQRT       0xBC
#define ID_FST         0xBD
#define ID_FSTP        0xBE
#define ID_FSTP1       0xBF
#define ID_FSTP8       0xC0
#define ID_FSTP9       0xC1
#define ID_FSUB        0xC2
#define ID_FSUBP       0xC3
#define ID_FSUBR       0xC4
#define ID_FSUBRP      0xC5
#define ID_FTST        0xC6
#define ID_FUCOM       0xC7
#define ID_FUCOMI      0xC8
#define ID_FUCOMIP     0xC9
#define ID_FUCOMP      0xCA
#define ID_FUCOMPP     0xCB
#define ID_FWAIT       0xCC
#define ID_FXAM        0xCD
#define ID_FXCH        0xCE
#define ID_FXCH4       0xCF
#define ID_FXCH7       0xD0
#define ID_FXRSTOR     0xD1
#define ID_FXSAVE      0xD2
#define ID_FXTRACT     0xD3
#define ID_FYL2X       0xD4
#define ID_FYL2XP1     0xD5
#define ID_GETSEC      0xD6
#define ID_GS          0xD7
#define ID_HADDPD      0xD8
#define ID_HADDPS      0xD9
#define ID_HINTNOP     0xDA
#define ID_HLT         0xDB
#define ID_HSUBPD      0xDC
#define ID_HSUBPS      0xDD
#define ID_ICEBP       0xDE
#define ID_IDIV        0xDF
#define ID_IMUL        0xE0
#define ID_IN          0xE1
#define ID_INC         0xE2
#define ID_INS         0xE3
#define ID_INSERTPS    0xE4
#define ID_INT         0xE5
#define ID_INTO        0xE6
#define ID_INVD        0xE7
#define ID_INVEPT      0xE8
#define ID_INVLPG      0xE9
#define ID_INVVPID     0xEA
#define ID_IRET        0xEB
#define ID_JA          0xEC
#define ID_JAE         0xED
#define ID_JB          0xEE
#define ID_JBE         0xEF
#define ID_JCXZ        0xF0
#define ID_JG          0xF1
#define ID_JGE         0xF2
#define ID_JL          0xF3
#define ID_JLE         0xF4
#define ID_JMP         0xF5
#define ID_JMPE        0xF6
#define ID_JMPF        0xF7
#define ID_JNO         0xF8
#define ID_JNP         0xF9
#define ID_JNS         0xFA
#define ID_JNZ         0xFB
#define ID_JO          0xFC
#define ID_JP          0xFD
#define ID_JS          0xFE
#define ID_JZ          0xFF
#define ID_LAHF        0x100
#define ID_LAR         0x101
#define ID_LDDQU       0x102
#define ID_LDMXCSR     0x103
#define ID_LDS         0x104
#define ID_LEA         0x105
#define ID_LEAVE       0x106
#define ID_LES         0x107
#define ID_LFENCE      0x108
#define ID_LFS         0x109
#define ID_LGDT        0x10A
#define ID_LGS         0x10B
#define ID_LIDT        0x10C
#define ID_LLDT        0x10D
#define ID_LMSW        0x10E
#define ID_LOADALL     0x10F
#define ID_LOCK        0x110
#define ID_LODS        0x111
#define ID_LOOP        0x112
#define ID_LOOPNZ      0x113
#define ID_LOOPZ       0x114
#define ID_LSL         0x115
#define ID_LSS         0x116
#define ID_LTR         0x117
#define ID_MASKMOVDQU  0x118
#define ID_MASKMOVQ    0x119
#define ID_MAXPD       0x11A
#define ID_MAXPS       0x11B
#define ID_MAXSD       0x11C
#define ID_MAXSS       0x11D
#define ID_MFENCE      0x11E
#define ID_MINPD       0x11F
#define ID_MINPS       0x120
#define ID_MINSD       0x121
#define ID_MINSS       0x122
#define ID_MONITOR     0x123
#define ID_MOV         0x124
#define ID_MOVAPD      0x125
#define ID_MOVAPS      0x126
#define ID_MOVBE       0x127
#define ID_MOVD        0x128
#define ID_MOVDDUP     0x129
#define ID_MOVDQ2Q     0x12A
#define ID_MOVDQA      0x12B
#define ID_MOVDQU      0x12C
#define ID_MOVHLPS     0x12D
#define ID_MOVHPD      0x12E
#define ID_MOVHPS      0x12F
#define ID_MOVLPD      0x130
#define ID_MOVLPS      0x131
#define ID_MOVMSKPD    0x132
#define ID_MOVMSKPS    0x133
#define ID_MOVNTDQ     0x134
#define ID_MOVNTDQA    0x135
#define ID_MOVNTI      0x136
#define ID_MOVNTPD     0x137
#define ID_MOVNTPS     0x138
#define ID_MOVNTQ      0x139
#define ID_MOVQ        0x13A
#define ID_MOVQ2DQ     0x13B
#define ID_MOVS        0x13C
#define ID_MOVSD       0x13D
#define ID_MOVSHDUP    0x13E
#define ID_MOVSLDUP    0x13F
#define ID_MOVSS       0x140
#define ID_MOVSX       0x141
#define ID_MOVSXD      0x142
#define ID_MOVUPD      0x143
#define ID_MOVUPS      0x144
#define ID_MOVZX       0x145
#define ID_MPSADBW     0x146
#define ID_MUL         0x147
#define ID_MULPD       0x148
#define ID_MULPS       0x149
#define ID_MULSD       0x14A
#define ID_MULSS       0x14B
#define ID_MWAIT       0x14C
#define ID_NEG         0x14D
#define ID_NOP         0x14E
#define ID_NOT         0x14F
#define ID_OR          0x150
#define ID_ORPD        0x151
#define ID_ORPS        0x152
#define ID_OUT         0x153
#define ID_OUTS        0x154
#define ID_PABSB       0x155
#define ID_PABSD       0x156
#define ID_PABSW       0x157
#define ID_PACKSSDW    0x158
#define ID_PACKSSWB    0x159
#define ID_PACKUSDW    0x15A
#define ID_PACKUSWB    0x15B
#define ID_PADDB       0x15C
#define ID_PADDD       0x15D
#define ID_PADDQ       0x15E
#define ID_PADDSB      0x15F
#define ID_PADDSW      0x160
#define ID_PADDUSB     0x161
#define ID_PADDUSW     0x162
#define ID_PADDW       0x163
#define ID_PALIGNR     0x164
#define ID_PAND        0x165
#define ID_PANDN       0x166
#define ID_PAUSE       0x167
#define ID_PAVGB       0x168
#define ID_PAVGW       0x169
#define ID_PBLENDVB    0x16A
#define ID_PBLENDW     0x16B
#define ID_PCMPEQB     0x16C
#define ID_PCMPEQD     0x16D
#define ID_PCMPEQQ     0x16E
#define ID_PCMPEQW     0x16F
#define ID_PCMPESTRI   0x170
#define ID_PCMPESTRM   0x171
#define ID_PCMPGTB     0x172
#define ID_PCMPGTD     0x173
#define ID_PCMPGTQ     0x174
#define ID_PCMPGTW     0x175
#define ID_PCMPISTRI   0x176
#define ID_PCMPISTRM   0x177
#define ID_PEXTRB      0x178
#define ID_PEXTRQ      0x179
#define ID_PEXTRW      0x17A
#define ID_PHADDD      0x17B
#define ID_PHADDSW     0x17C
#define ID_PHADDW      0x17D
#define ID_PHMINPOSUW  0x17E
#define ID_PHSUBD      0x17F
#define ID_PHSUBSW     0x180
#define ID_PHSUBW      0x181
#define ID_PINSRB      0x182
#define ID_PINSRQ      0x183
#define ID_PINSRW      0x184
#define ID_PMADDUBSW   0x185
#define ID_PMADDWD     0x186
#define ID_PMAXSB      0x187
#define ID_PMAXSD      0x188
#define ID_PMAXSW      0x189
#define ID_PMAXUB      0x18A
#define ID_PMAXUD      0x18B
#define ID_PMAXUW      0x18C
#define ID_PMINSB      0x18D
#define ID_PMINSD      0x18E
#define ID_PMINSW      0x18F
#define ID_PMINUB      0x190
#define ID_PMINUD      0x191
#define ID_PMINUW      0x192
#define ID_PMOVMSKB    0x193
#define ID_PMOVSXBD    0x194
#define ID_PMOVSXBQ    0x195
#define ID_PMOVSXBW    0x196
#define ID_PMOVSXDQ    0x197
#define ID_PMOVSXWD    0x198
#define ID_PMOVSXWQ    0x199
#define ID_PMOVZXBD    0x19A
#define ID_PMOVZXBQ    0x19B
#define ID_PMOVZXBW    0x19C
#define ID_PMOVZXDQ    0x19D
#define ID_PMOVZXWD    0x19E
#define ID_PMOVZXWQ    0x19F
#define ID_PMULDQ      0x1A0
#define ID_PMULHRSW    0x1A1
#define ID_PMULHUW     0x1A2
#define ID_PMULHW      0x1A3
#define ID_PMULLD      0x1A4
#define ID_PMULLW      0x1A5
#define ID_PMULUDQ     0x1A6
#define ID_POP         0x1A7
#define ID_POPA        0x1A8
#define ID_POPCNT      0x1A9
#define ID_POPF        0x1AA
#define ID_POR         0x1AB
#define ID_PREFETCHNTA 0x1AC
#define ID_PREFETCHT0  0x1AD
#define ID_PREFETCHT1  0x1AE
#define ID_PREFETCHT2  0x1AF
#define ID_PSADBW      0x1B0
#define ID_PSHUFB      0x1B1
#define ID_PSHUFD      0x1B2
#define ID_PSHUFHW     0x1B3
#define ID_PSHUFLW     0x1B4
#define ID_PSHUFW      0x1B5
#define ID_PSIGNB      0x1B6
#define ID_PSIGND      0x1B7
#define ID_PSIGNW      0x1B8
#define ID_PSLLD       0x1B9
#define ID_PSLLDQ      0x1BA
#define ID_PSLLQ       0x1BB
#define ID_PSLLW       0x1BC
#define ID_PSRAD       0x1BD
#define ID_PSRAW       0x1BE
#define ID_PSRLD       0x1BF
#define ID_PSRLDQ      0x1C0
#define ID_PSRLQ       0x1C1
#define ID_PSRLW       0x1C2
#define ID_PSUBB       0x1C3
#define ID_PSUBD       0x1C4
#define ID_PSUBQ       0x1C5
#define ID_PSUBSB      0x1C6
#define ID_PSUBSW      0x1C7
#define ID_PSUBUSB     0x1C8
#define ID_PSUBUSW     0x1C9
#define ID_PSUBW       0x1CA
#define ID_PTEST       0x1CB
#define ID_PUNPCKHBD   0x1CC
#define ID_PUNPCKHBDQ  0x1CD
#define ID_PUNPCKHBW   0x1CE
#define ID_PUNPCKHDQ   0x1CF
#define ID_PUNPCKHQDQ  0x1D0
#define ID_PUNPCKHWD   0x1D1
#define ID_PUNPCKLBW   0x1D2
#define ID_PUNPCKLDQ   0x1D3
#define ID_PUNPCKLQDQ  0x1D4
#define ID_PUNPCKLWD   0x1D5
#define ID_PUSH        0x1D6
#define ID_PUSHA       0x1D7
#define ID_PUSHF       0x1D8
#define ID_PXOR        0x1D9
#define ID_RCL         0x1DA
#define ID_RCPPS       0x1DB
#define ID_RCPSS       0x1DC
#define ID_RCR         0x1DD
#define ID_RDMSR       0x1DE
#define ID_RDPMC       0x1DF
#define ID_RDTSC       0x1E0
#define ID_RDTSCP      0x1E1
#define ID_REPNZ       0x1E2
#define ID_REPZ        0x1E3
#define ID_RETF        0x1E4
#define ID_RETN        0x1E5
#define ID_ROL         0x1E6
#define ID_ROR         0x1E7
#define ID_ROUNDPD     0x1E8
#define ID_ROUNDPS     0x1E9
#define ID_ROUNDSD     0x1EA
#define ID_ROUNDSS     0x1EB
#define ID_RSM         0x1EC
#define ID_RSQRTPS     0x1ED
#define ID_RSQRTSS     0x1EE
#define ID_SAHF        0x1EF
#define ID_SAL         0x1F0
#define ID_SAR         0x1F1
#define ID_SBB         0x1F2
#define ID_SCAS        0x1F3
#define ID_SETA        0x1F4
#define ID_SETAE       0x1F5
#define ID_SETALC      0x1F6
#define ID_SETB        0x1F7
#define ID_SETBE       0x1F8
#define ID_SETG        0x1F9
#define ID_SETGE       0x1FA
#define ID_SETL        0x1FB
#define ID_SETLE       0x1FC
#define ID_SETNO       0x1FD
#define ID_SETNP       0x1FE
#define ID_SETNS       0x1FF
#define ID_SETNZ       0x200
#define ID_SETO        0x201
#define ID_SETP        0x202
#define ID_SETS        0x203
#define ID_SETZ        0x204
#define ID_SFENCE      0x205
#define ID_SGDT        0x206
#define ID_SHL         0x207
#define ID_SHLD        0x208
#define ID_SHR         0x209
#define ID_SHRD        0x20A
#define ID_SHUFPD      0x20B
#define ID_SHUFPS      0x20C
#define ID_SIDT        0x20D
#define ID_SLDT        0x20E
#define ID_SMSW        0x20F
#define ID_SQRTPD      0x210
#define ID_SQRTPS      0x211
#define ID_SQRTSD      0x212
#define ID_SQRTSS      0x213
#define ID_SS          0x214
#define ID_STC         0x215
#define ID_STD         0x216
#define ID_STI         0x217
#define ID_STMXCSR     0x218
#define ID_STOS        0x219
#define ID_STR         0x21A
#define ID_SUB         0x21B
#define ID_SUBPD       0x21C
#define ID_SUBPS       0x21D
#define ID_SUBSD       0x21E
#define ID_SUBSS       0x21F
#define ID_SWAPGS      0x220
#define ID_SYSCALL     0x221
#define ID_SYSENTER    0x222
#define ID_SYSEXIT     0x223
#define ID_SYSRET      0x224
#define ID_TEST        0x225
#define ID_UCOMISD     0x226
#define ID_UCOMISS     0x227
#define ID_UD          0x228
#define ID_UD2         0x229
#define ID_UNPCKHPD    0x22A
#define ID_UNPCKHPS    0x22B
#define ID_UNPCKLPD    0x22C
#define ID_UNPCKLPS    0x22D
#define ID_VERR        0x22E
#define ID_VERW        0x22F
#define ID_VMCALL      0x230
#define ID_VMCLEAR     0x231
#define ID_VMLAUNCH    0x232
#define ID_VMPTRLD     0x233
#define ID_VMPTRST     0x234
#define ID_VMREAD      0x235
#define ID_VMRESUME    0x236
#define ID_VMWRITE     0x237
#define ID_VMXOFF      0x238
#define ID_VMXON       0x239
#define ID_WBINVD      0x23A
#define ID_WRMSR       0x23B
#define ID_XADD        0x23C
#define ID_XCHG        0x23D
#define ID_XGETBV      0x23E
#define ID_XLAT        0x23F
#define ID_XOR         0x240
#define ID_XORPD       0x241
#define ID_XORPS       0x242
#define ID_XRSTOR      0x243
#define ID_XSAVE       0x244
#define ID_XSETBV      0x245

/**********************
* Instructions' groups.
***********************
*/
#define GRP_NULL    0x0000000000000000L
#define GRP_SWITCH  0x0000000000000001L
#define GRP_ARITH   0x0000000000000002L
#define GRP_BINARY  0x0000000000000004L
#define GRP_BIT     0x0000000000000008L
#define GRP_BRANCH  0x0000000000000010L
#define GRP_BREAK   0x0000000000000020L
#define GRP_CACHECT 0x0000000000000040L
#define GRP_COMPAR  0x0000000000000080L
#define GRP_COND    0x0000000000000100L
#define GRP_CONTROL 0x0000000000000200L
#define GRP_CONVER  0x0000000000000400L
#define GRP_DATAMOV 0x0000000000000800L
#define GRP_DECIMAL 0x0000000000001000L
#define GRP_FETCH   0x0000000000002000L
#define GRP_FLGCTRL 0x0000000000004000L
#define GRP_GEN     0x0000000000008000L
#define GRP_INOUT   0x0000000000010000L
#define GRP_LDCONST 0x0000000000020000L
#define GRP_LOGICAL 0x0000000000040000L
#define GRP_MMX     0x0000000000080000L
#define GRP_MXCSRSM 0x0000000000100000L
#define GRP_ORDER   0x0000000000200000L
#define GRP_PCKSCLR 0x0000000000400000L
#define GRP_PCKSP   0x0000000000800000L
#define GRP_PREFIX  0x0000000001000000L
#define GRP_SEGREG  0x0000000002000000L
#define GRP_SHFTROT 0x0000000004000000L
#define GRP_SHIFT   0x0000000008000000L
#define GRP_SHUNPCK 0x0000000010000000L
#define GRP_SIMDFP  0x0000000020000000L
#define GRP_SIMDINT 0x0000000040000000L
#define GRP_SM      0x0000000080000000L
#define GRP_SMX     0x0000000100000000L
#define GRP_SSE1    0x0000000200000000L
#define GRP_SSE2    0x0000000400000000L
#define GRP_SSE3    0x0000000800000000L
#define GRP_SSE41   0x0000001000000000L
#define GRP_SSE42   0x0000002000000000L
#define GRP_SSSE3   0x0000004000000000L
#define GRP_STACK   0x0000008000000000L
#define GRP_STRING  0x0000010000000000L
#define GRP_STRTXT  0x0000020000000000L
#define GRP_SYNC    0x0000040000000000L
#define GRP_SYSTEM  0x0000080000000000L
#define GRP_TRANS   0x0000100000000000L
#define GRP_UNPACK  0x0000200000000000L
#define GRP_VMX     0x0000400000000000L
#define GRP_X87FPU  0x0000800000000000L

/****************************
* Instructions' architecture.
*****************************
*/
#define ARCH_COMMON 0x1
#define ARCH_INTEL  0x2
#define ARCH_AMD    0x4
#define ARCH_ALL    (ARCH_COMMON | ARCH_INTEL | ARCH_AMD)

/*******************
* Disassemble modes.
********************
*/
#define DISASSEMBLE_MODE_16 0x1
#define DISASSEMBLE_MODE_32 0x2
#define DISASSEMBLE_MODE_64 0x4

/**********************
* Disassembling errors.
***********************
*/
#define ERR_OK           0x0
#define ERR_BADCODE      0x1
#define ERR_TOO_LONG     0x2
#define ERR_NON_LOCKABLE 0x3
#define ERR_RM_REG       0x4
#define ERR_RM_MEM       0x5
#define ERR_16_32_ONLY   0x6
#define ERR_64_ONLY      0x7
#define ERR_REX_NOOPCD   0x8
#define ERR_ANOT_ARCH    0x9
#define ERR_INTERNAL     0xA

/*********************************
* Dumping parameters and routines.
**********************************
*/
#define DUMP_OPTION_IMM_HEX   0x01
#define DUMP_OPTION_IMM_UHEX  0x02
#define DUMP_OPTION_IMM_DEC   0x04
#define DUMP_OPTION_IMM_UDEC  0x08
#define DUMP_OPTION_IMM_MASK  0x0F

#define DUMP_OPTION_DISP_HEX  0x10
#define DUMP_OPTION_DISP_UHEX 0x20
#define DUMP_OPTION_DISP_DEC  0x40
#define DUMP_OPTION_DISP_UDEC 0x80
#define DUMP_OPTION_DISP_MASK 0xF0

#ifdef __cplusplus
extern "C" {
#endif

#if defined (MEDIANA_CTRL_DUMP)
int medi_dump(struct INSTRUCTION *instr, unichar_t *buff, int bufflen, int options);

int medi_dump_mnemonic(struct INSTRUCTION *instr, unichar_t *buff, int bufflen);
int medi_dump_operand(struct INSTRUCTION *instr, int op_index, int options, unichar_t *buff, int bufflen);
int medi_dump_prefixes(struct INSTRUCTION *instr, int options, unichar_t *buff, int bufflen);
#endif //defined (MEDIANA_CTRL_DUMP)

#if defined (MEDIANA_CTRL_DBG_DUMP)
int medi_dbg_dump(struct INSTRUCTION *instr, uint8_t *sf_prefixes, int sf_prefixes_len, unichar_t *buff, int len);
#endif

/***************************
* Disassembler's entry point
****************************
*/
unsigned int medi_disassemble(uint8_t *offset, struct INSTRUCTION *instr, struct DISASM_INOUT_PARAMS *inout_params);

#ifdef __cplusplus
}
#endif

#endif //__MEDIANA_H__
