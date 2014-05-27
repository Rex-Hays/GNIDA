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

#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include "mediana.h"

struct STREAM
{
	unichar_t *buff;
	int bufflen;
	unsigned int reallen;
	unsigned int options;
};

#if defined(MEDIANA_CTRL_DUMP) || defined(MEDIANA_CTRL_DBG_DUMP)

unichar_t *regs8[] = 
{
	_UT("al"), _UT("cl"), _UT("dl"), _UT("bl"), _UT("ah"), _UT("ch"), _UT("dh"), _UT("bh"),
	_UT("r8b"), _UT("r9b"), _UT("r10b"), _UT("r11b"), _UT("r12b"), _UT("r13b"), _UT("r14b"), _UT("r15b"),
	_UT("spl"), _UT("bpl"), _UT("sil"), _UT("dil"), _UT("badreg8")
};

unichar_t *regs16[] = 
{
	_UT("ax"), _UT("cx"), _UT("dx"), _UT("bx"), _UT("sp"), _UT("bp"), _UT("si"), _UT("di"),
	_UT("r8w"), _UT("r9w"), _UT("r10w"), _UT("r11w"), _UT("r12w"), _UT("r13w"), _UT("r14w"), _UT("r15w"),
	_UT("badreg16_1"), _UT("badreg16_2"), _UT("badreg16_3"), _UT("badreg16_4"), _UT("badreg16_5"),
};

unichar_t *regs32[] = 
{
	_UT("eax"), _UT("ecx"), _UT("edx"), _UT("ebx"), _UT("esp"), _UT("ebp"), _UT("esi"), _UT("edi"),
	_UT("r8d"), _UT("r9d"), _UT("r10d"), _UT("r11d"), _UT("r12d"), _UT("r13d"), _UT("r14d"), _UT("r15d"),
	_UT("badreg32_1"), _UT("badreg32_2"), _UT("badreg32_3"), _UT("badreg32_4"), _UT("eip"),
};

unichar_t *regs64[] = 
{
	_UT("rax"), _UT("rcx"), _UT("rdx"), _UT("rbx"), _UT("rsp"), _UT("rbp"), _UT("rsi"), _UT("rdi"),
	_UT("r8"), _UT("r9"), _UT("r10"), _UT("r11"), _UT("r12"), _UT("r13"), _UT("r14"), _UT("r15"),
	_UT("badreg64_1"), _UT("badreg64_2"), _UT("badreg64_3"), _UT("badreg64_4"), _UT("rip"),
};

unichar_t *sregs[] = 
{
	_UT("cs"), _UT("ds"), _UT("es"), _UT("ss"), _UT("fs"), _UT("gs"), _UT("badsreg7"), _UT("badsreg8")
};

unichar_t *fregs[] = 
{
	_UT("st0"), _UT("st1"), _UT("st2"), _UT("st3"), _UT("st4"), _UT("st5"), _UT("st6"), _UT("st7"), _UT("badfreg8")
};

unichar_t *cregs[] = 
{
	_UT("cr0"), _UT("cr1"), _UT("cr2"), _UT("cr3"), _UT("cr4"), _UT("cr5"), _UT("cr6"), _UT("cr7"), _UT("cr8"), _UT("badcreg9")
};

unichar_t *dregs[] = 
{
	_UT("dr0"), _UT("dr1"), _UT("dr2"), _UT("dr3"), _UT("dr4"), _UT("dr5"), _UT("dr6"), _UT("dr7"), _UT("baddreg")
};

unichar_t *tregs[] = 
{
	_UT("tr0"), _UT("tr1"), _UT("tr2"), _UT("tr3"), _UT("tr4"), _UT("tr5"), _UT("tr6"), _UT("tr7"), _UT("badtreg")
};

unichar_t *mregs[] = 
{
	_UT("mm0"), _UT("mm1"), _UT("mm2"), _UT("mm3"), _UT("mm4"), _UT("mm5"), _UT("mm6"), _UT("mm7"), _UT("badmreg8")
};

unichar_t *xregs[] = 
{
	_UT("xmm0"), _UT("xmm1"), _UT("xmm2"), _UT("xmm3"), _UT("xmm4"), _UT("xmm5"), _UT("xmm6"), _UT("xmm7"),
	_UT("xmm8"), _UT("xmm9"), _UT("xmm10"), _UT("xmm11"), _UT("xmm12"), _UT("xmm13"), _UT("xmm14"), _UT("xmm15"),
	_UT("badxreg16")
};

//Common dump functions.
static void safe_copy_unichar(struct STREAM *stream, unichar_t ch)
{
	if (stream ->bufflen)
	{
		*stream ->buff = ch;
		stream ->bufflen--;
		stream ->buff++;
	}
	stream ->reallen++;
}

static void safe_unistrncpy(struct STREAM *stream, const unichar_t *src)
{
	while (*src)
	{
		safe_copy_unichar(stream, *src);
		src++;
	}
}

static void itoa(struct STREAM *stream, uint64_t num, uint16_t size, int is_signed, int radix)
{
	char dig;
	uint64_t div;
	uint64_t tmp;

	div = 1;
	if (is_signed)
	{
		uint8_t *ptr = (uint8_t *)&num;
		ptr += size - 1;
		if (*ptr & 0x80)
		{
			safe_copy_unichar(stream, '-');
			num = ~num; //Just to shut up warning.
			num++;
		}
	}

	tmp = 0xFFFFFFFFFFFFFFFFL;
	for(size = 8 - size + 1; size; size--)
	{
		num &= tmp;
		tmp >>= 0x8;
	}

	if (radix == 0x10)
		safe_unistrncpy(stream, _UT("0x"));

	while(num / div >= radix)
		div *= radix;
	while(div)
	{
		dig = (uint8_t)((num / div) % radix);
		if (dig >= 10)
			dig += 'A' - 10;
		else
			dig += '0';
		safe_copy_unichar(stream, dig);
		div /= radix;
	}
}
#endif //defined(MEDIANA_CTRL_DUMP) || defined(MEDIANA_CTRL_DUMP_DBG)

#ifdef MEDIANA_CTRL_DUMP
static void dump_imm(struct STREAM *stream, struct OPERAND *op)
{
	switch(stream ->options & DUMP_OPTION_IMM_MASK)
	{
	case DUMP_OPTION_IMM_HEX:
		itoa(stream, op ->value.imm.imm64, op ->size, 0x1, 0x10);
		break;
	case DUMP_OPTION_IMM_UHEX:
		itoa(stream, op ->value.imm.imm64, op ->size, 0x0, 0x10);
		break;
	case DUMP_OPTION_IMM_DEC:
		itoa(stream, op ->value.imm.imm64, op ->size, 0x0, 0xA);
		break;
	case DUMP_OPTION_IMM_UDEC:
		itoa(stream, op ->value.imm.imm64, op ->size, 0x1, 0xA);
		break;
	default:
		itoa(stream, op ->value.imm.imm64, op ->size, 0x0, 0x10);
		break;
	}
}

static void dump_reg_sreg(struct STREAM *stream, uint8_t code)
{
	safe_unistrncpy(stream, sregs[code]);
}

static void dump_reg_gen(struct STREAM *stream, uint8_t code, uint16_t size)
{
	switch(size)
	{
	case OPERAND_SIZE_8:
		safe_unistrncpy(stream, regs8[code]);
		break;
	case OPERAND_SIZE_16:
		safe_unistrncpy(stream, regs16[code]);
		break;
	case OPERAND_SIZE_32:
		safe_unistrncpy(stream, regs32[code]);
		break;
	case OPERAND_SIZE_64:
		safe_unistrncpy(stream, regs64[code]);
		break;
	}
}

static void dump_reg_freg(struct STREAM *stream, uint8_t code)
{
	safe_unistrncpy(stream, fregs[code]);
}

static void dump_reg_creg(struct STREAM *stream, uint8_t code)
{
	safe_unistrncpy(stream, cregs[code]);
}

static void dump_reg_dreg(struct STREAM *stream, uint8_t code)
{
	safe_unistrncpy(stream, dregs[code]);
}

static void dump_reg_treg(struct STREAM *stream, uint8_t code)
{
	safe_unistrncpy(stream, tregs[code]);
}

static void dump_reg_mreg(struct STREAM *stream, uint8_t code)
{
	safe_unistrncpy(stream, mregs[code]);
}

static void dump_reg_xreg(struct STREAM *stream, uint8_t code)
{
	safe_unistrncpy(stream, xregs[code]);
}

static void dump_reg(struct STREAM *stream, uint8_t type, uint8_t code, uint16_t size)
{
	switch(type)
	{
	case REG_TYPE_GEN:
		dump_reg_gen(stream, code, size);
		break;
	case REG_TYPE_SEG:
		dump_reg_sreg(stream, code);
		break;
	case REG_TYPE_FPU:
		dump_reg_freg(stream, code);
		break;
	case REG_TYPE_CR:
		dump_reg_creg(stream, code);
		break;
	case REG_TYPE_DBG:
		dump_reg_dreg(stream, code);
		break;
	case REG_TYPE_TR:
		dump_reg_treg(stream, code);
		break;
	case REG_TYPE_MMX:
		dump_reg_mreg(stream, code);
		break;
	case REG_TYPE_XMM:
		dump_reg_xreg(stream, code);
		break;
	default:
		safe_unistrncpy(stream, _UT("internal error"));
		break;
	}
}

static void dump_disp(struct STREAM *stream, uint8_t mod, struct INSTRUCTION *instr)
{
	unsigned int options;

	options = stream ->options;
	if (mod == ADDR_MOD_BASE)
	{
		switch(options & DUMP_OPTION_DISP_MASK)
		{
		case DUMP_OPTION_DISP_HEX:
			options &= ~DUMP_OPTION_DISP_HEX;
			options |= DUMP_OPTION_DISP_UHEX;
			break;
		case DUMP_OPTION_DISP_DEC:
			options &= ~DUMP_OPTION_DISP_DEC;
			options |= DUMP_OPTION_DISP_UDEC;
			break;
		}
	}

	switch(options & DUMP_OPTION_DISP_MASK)
	{
	case DUMP_OPTION_DISP_HEX:
		itoa(stream, instr ->disp.value.d64, instr ->addrsize, 0x1, 0x10);
		break;
	case DUMP_OPTION_DISP_UHEX:
		itoa(stream, instr ->disp.value.d64, instr ->addrsize, 0x0, 0x10);
		break;
	case DUMP_OPTION_DISP_DEC:
		itoa(stream, instr ->disp.value.d64, instr ->addrsize, 0x1, 0xA);
		break;
	case DUMP_OPTION_DISP_UDEC:
		itoa(stream, instr ->disp.value.d64, instr ->addrsize, 0x0, 0xA);
		break;
	default:
		itoa(stream, instr ->disp.value.d64, instr ->addrsize, 0x0, 0x10);
		break;
	}
}

static void dump_ptr_size(struct STREAM *stream, struct OPERAND *op)
{
	switch(op ->size)
	{
	case OPERAND_SIZE_8:
		safe_unistrncpy(stream, _UT("byte ptr"));
		break;
	case OPERAND_SIZE_16:
		safe_unistrncpy(stream, _UT("word ptr"));
		break;
	case OPERAND_SIZE_32:
		safe_unistrncpy(stream, _UT("dword ptr"));
		break;
	case OPERAND_SIZE_48:
		safe_unistrncpy(stream, _UT("fword ptr"));
		break;
	case OPERAND_SIZE_64:
		safe_unistrncpy(stream, _UT("qword ptr"));
		break;
	case OPERAND_SIZE_80:
		safe_unistrncpy(stream, _UT("tbyte ptr"));
		break;
	case OPERAND_SIZE_128:
		safe_unistrncpy(stream, _UT("dqword ptr"));
		break;
	case OPERAND_SIZE_14:
		safe_unistrncpy(stream, _UT("14bytes ptr"));
		break;
	case OPERAND_SIZE_28:
		safe_unistrncpy(stream, _UT("28bytes ptr"));
		break;
	case OPERAND_SIZE_94:
		safe_unistrncpy(stream, _UT("94bytes ptr"));
		break;
	case OPERAND_SIZE_108:
		safe_unistrncpy(stream, _UT("108bytes ptr"));
		break;
	case OPERAND_SIZE_512:
		safe_unistrncpy(stream, _UT("512bytes ptr"));
		break;
	default:
		safe_unistrncpy(stream, _UT("strange ptr"));
		break;
	}
}

static void dump_addr(struct STREAM *stream, struct INSTRUCTION *instr, struct OPERAND *op)
{
	dump_ptr_size(stream, op);

	safe_copy_unichar(stream, ' ');

	safe_unistrncpy(stream, sregs[op ->value.addr.seg]);
	safe_copy_unichar(stream, ':');
	safe_copy_unichar(stream, '[');
	if (op ->value.addr.mod & ADDR_MOD_BASE)
	{
		dump_reg_gen(stream, op ->value.addr.base, instr ->addrsize);
	}
	if (op ->value.addr.mod & ADDR_MOD_IDX)
	{
		if (op ->value.addr.mod & ADDR_MOD_BASE)
		{
			safe_copy_unichar(stream, '+');
		}
		dump_reg_gen(stream, op ->value.addr.index, instr ->addrsize);
		if (op ->value.addr.scale != 0x1)
		{
			safe_copy_unichar(stream, '*');
			itoa(stream, op ->value.addr.scale, 0x1, 0x0, 0xA);
		}
	}
	if (op ->value.addr.mod & ADDR_MOD_DISP)
	{
		if (op ->value.addr.mod & ~ADDR_MOD_DISP)
		{
			if ((stream ->options & DUMP_OPTION_DISP_UHEX) || (stream ->options & DUMP_OPTION_DISP_UDEC))
			{
				safe_copy_unichar(stream, '+');
			}
			else
			{
				uint8_t *ptr = (uint8_t *)(&(instr ->disp.value));
				ptr += instr ->addrsize - 1;

				if (!(*ptr & 0x80))
				{
					safe_copy_unichar(stream, '+');
				}
			}
		}

		dump_disp(stream, op ->value.addr.mod, instr);
	}

	safe_copy_unichar(stream, ']');
}

static void dump_dir(struct STREAM *stream, struct OPERAND *op)
{
	switch (op ->size)
	{
	case OPERAND_SIZE_32:
		itoa(stream, op ->value.far_addr.far_addr32.seg, 0x2, 0x0, 0x10);
		safe_copy_unichar(stream, ':');
		itoa(stream, op ->value.far_addr.far_addr32.offset, 0x2, 0x0, 0x10);
		break;
	case OPERAND_SIZE_48:
		itoa(stream, op ->value.far_addr.far_addr48.seg, 0x2, 0x0, 0x10);
		safe_copy_unichar(stream, ':');
		itoa(stream, op ->value.far_addr.far_addr48.offset, 0x4, 0x0, 0x10);
		break;
	default:
		safe_unistrncpy(stream, _UT("internal error"));
		break;
	}
}

static int internal_dump_operand(struct STREAM *stream, struct INSTRUCTION *instr, int op_index)
{
	struct OPERAND *op;

	if (op_index > 3 || op_index < 0)
		return -1;

	op = instr ->ops + op_index;
	if (op ->flags & OPERAND_FLAG_PRESENT)
	{
        switch (op ->flags & OPERAND_TYPE_MASK)
		{
		case OPERAND_TYPE_REG:
			dump_reg(stream, op ->value.reg.type, op ->value.reg.code, op ->size);
			break;
		case OPERAND_TYPE_MEM:
			dump_addr(stream, instr, op);
			break;
		case OPERAND_TYPE_IMM:
			dump_imm(stream, op);
			break;
		case OPERAND_TYPE_DIR:
			dump_dir(stream, op);
			break;
		default:
			safe_unistrncpy(stream, _UT("internal error"));
			break;
		}
	}

	return stream ->reallen;
}

int medi_dump_operand(struct INSTRUCTION *instr, int op_index, int options, unichar_t *buff, int len)
{
	struct STREAM stream;

	stream.buff = buff;
	stream.bufflen = len;
	stream.reallen = 0;
	stream.options = options;

	return internal_dump_operand(&stream, instr, op_index);
}

static int internal_dump_mnemonic(struct STREAM *stream, struct INSTRUCTION *instr)
{
	safe_unistrncpy(stream, instr ->mnemonic);

	return stream ->reallen;
}

int medi_dump_mnemonic(struct INSTRUCTION *instr, unichar_t *buff, int len)
{
	struct STREAM stream;

	stream.buff = buff;
	stream.bufflen = len;
	stream.reallen = 0;

	internal_dump_mnemonic(&stream, instr);

	return stream.reallen;
}

static int internal_dump_prefixes(struct STREAM *stream, struct INSTRUCTION *instr)
{
	if (instr ->prefixes & INSTR_PREFIX_LOCK)
		safe_unistrncpy(stream, _UT("lock "));
	if (instr ->prefixes & INSTR_PREFIX_REPZ)
		safe_unistrncpy(stream, _UT("repz "));
	if (instr ->prefixes & INSTR_PREFIX_REPNZ)
		safe_unistrncpy(stream, _UT("repnz "));

	return stream ->reallen;
}

int medi_dump_prefixes(struct INSTRUCTION *instr, int options, unichar_t *buff, int bufflen)
{
	struct STREAM stream;

	stream.buff = buff;
	stream.bufflen = bufflen;
	stream.options = options;
	stream.reallen = 0;

	return internal_dump_prefixes(&stream, instr);
}

int medi_dump(struct INSTRUCTION *instr, unichar_t *buff, int bufflen, int options)
{
	struct STREAM stream;

	stream.buff = buff;
	stream.bufflen = bufflen;
	stream.options = options;
	stream.reallen = 0;

	internal_dump_prefixes(&stream, instr);
	internal_dump_mnemonic(&stream, instr);

	if (instr ->ops[0].flags & OPERAND_FLAG_PRESENT)
	{
		unsigned int i;

		safe_copy_unichar(&stream, ' ');
		for (i = 0; i < 3; i++)
		{
			if (instr ->ops[i].flags & OPERAND_FLAG_PRESENT)
			{
				internal_dump_operand(&stream, instr, i);
				safe_unistrncpy(&stream, _UT(", "));
			}
		}
		stream.reallen -= 2;
		stream.bufflen += 2;
		stream.buff += 2;
	}

	return stream.reallen;
}
#endif //MEDIANA_CTRL_DUMP

#ifdef MEDIANA_CTRL_DBG_DUMP
static void dbg_dump_sf_prefixes(struct STREAM *stream, uint8_t *sf_prefixes, int sf_prefixes_len)
{
	int i;

	if (!sf_prefixes)
	{
		safe_unistrncpy(stream, _UT("unknown"));
	}
	else
	{
		if (!sf_prefixes_len)
			safe_unistrncpy(stream, _UT("none"));
		else
		{
            for(i = 0; i < sf_prefixes_len; i++)
			{
				itoa(stream, sf_prefixes[i], 0x1, 0x0, 0x10);
				safe_unistrncpy(stream, _UT(", "));
			}
		}
	}

    stream ->bufflen += 2;
	stream ->buff -= 2;
	stream ->reallen -= 2;
}

static void dbg_dump_prefixes(struct STREAM *stream, struct INSTRUCTION *instr)
{
	if (!instr ->prefixes)
		safe_unistrncpy(stream, _UT("none"));
	else
	{
		if (instr ->prefixes & INSTR_PREFIX_CS)
			safe_unistrncpy(stream, _UT("CS, "));
		if (instr ->prefixes & INSTR_PREFIX_DS)
			safe_unistrncpy(stream, _UT("DS, "));
		if (instr ->prefixes & INSTR_PREFIX_ES)
			safe_unistrncpy(stream, _UT("ES, "));
		if (instr ->prefixes & INSTR_PREFIX_SS)
			safe_unistrncpy(stream, _UT("SS, "));
		if (instr ->prefixes & INSTR_PREFIX_FS)
			safe_unistrncpy(stream, _UT("FS, "));
		if (instr ->prefixes & INSTR_PREFIX_GS)
			safe_unistrncpy(stream, _UT("GS, "));
		if (instr ->prefixes & INSTR_PREFIX_OPSIZE)
			safe_unistrncpy(stream, _UT("OPSIZE, "));
		if (instr ->prefixes & INSTR_PREFIX_ADDRSIZE)
			safe_unistrncpy(stream, _UT("ADDRSIZE, "));
		if (instr ->prefixes & INSTR_PREFIX_REX)
		{
			safe_unistrncpy(stream, _UT("REX ("));
			itoa(stream, instr ->rex, 0x1, 0x0, 0x10);
			safe_unistrncpy(stream, _UT("), "));
		}
		if (instr ->prefixes & INSTR_PREFIX_LOCK)
			safe_unistrncpy(stream, _UT("LOCK, "));

		stream ->bufflen += 2;
		stream ->buff -= 2;
		stream ->reallen -= 2;
	}
}

static void dbg_dump_flags(struct STREAM *stream, struct INSTRUCTION *instr)
{
	if (!instr ->flags)
		safe_unistrncpy(stream, _UT("none"));
	else
	{
		if (instr ->flags & INSTR_FLAG_MODRM)
		{
			safe_unistrncpy(stream, _UT("MODRM ("));
			itoa(stream, instr ->modrm, 0x1, 0x0, 0x10);
			safe_unistrncpy(stream, _UT("), "));
		}
		if (instr ->flags & INSTR_FLAG_SIB)
		{
			safe_unistrncpy(stream, _UT("SIB ("));
			itoa(stream, instr ->sib, 0x1, 0x0, 0x10);
			safe_unistrncpy(stream, _UT("), "));
		}
		if (instr ->flags & INSTR_FLAG_SF_PREFIXES)
			safe_unistrncpy(stream, _UT("SF_PREFIXES, "));
        if (instr ->flags & INSTR_FLAG_IOPL)
            safe_unistrncpy(stream, _UT("IOPL, "));
        if (instr ->flags & INSTR_FLAG_RING0)
            safe_unistrncpy(stream, _UT("RING0, "));
        if (instr ->flags & INSTR_FLAG_SERIAL)
            safe_unistrncpy(stream, _UT("SERIAL, "));
        if (instr ->flags & INSTR_FLAG_UNDOC)
            safe_unistrncpy(stream, _UT("UNDOC, "));

		stream ->bufflen += 2;
		stream ->buff -= 2;
		stream ->reallen -= 2;
	}
}

static void dbg_dump_eflags(struct STREAM *stream, uint8_t flags)
{
	if (!flags)
		safe_unistrncpy(stream, _UT("none"));
	else
	{
		if (flags & EFLAG_O)
			safe_unistrncpy(stream, _UT("OF, "));
		if (flags & EFLAG_D)
			safe_unistrncpy(stream, _UT("DF, "));
		if (flags & EFLAG_I)
			safe_unistrncpy(stream, _UT("IF, "));
		if (flags & EFLAG_S)
			safe_unistrncpy(stream, _UT("SF, "));
		if (flags & EFLAG_Z)
			safe_unistrncpy(stream, _UT("ZF, "));
		if (flags & EFLAG_A)
			safe_unistrncpy(stream, _UT("AF, "));
		if (flags & EFLAG_P)
			safe_unistrncpy(stream, _UT("PF, "));
		if (flags & EFLAG_C)
			safe_unistrncpy(stream, _UT("CF, "));

		stream ->bufflen += 2;
		stream ->buff -= 2;
		stream ->reallen -= 2;
	}
}

static void dbg_dump_groups(struct STREAM *stream, struct INSTRUCTION *instr)
{
	if (!instr ->groups)
		safe_unistrncpy(stream, _UT("none"));
	else
	{
		if (instr ->groups & GRP_GEN)
			safe_unistrncpy(stream, _UT("GEN, "));
		if (instr ->groups & GRP_SSE1)
			safe_unistrncpy(stream, _UT("SSE1, "));
		if (instr ->groups & GRP_ARITH)
			safe_unistrncpy(stream, _UT("ARITH, "));
		if (instr ->groups & GRP_BINARY)
			safe_unistrncpy(stream, _UT("BINARY, "));
		if (instr ->groups & GRP_STACK)
			safe_unistrncpy(stream, _UT("STACK, "));
		if (instr ->groups & GRP_SEGREG)
			safe_unistrncpy(stream, _UT("SEGREG, "));
		if (instr ->groups & GRP_LOGICAL)
			safe_unistrncpy(stream, _UT("LOGICAL, "));
		if (instr ->groups & GRP_PREFIX)
			safe_unistrncpy(stream, _UT("PREFIX, "));
		if (instr ->groups & GRP_BRANCH)
			safe_unistrncpy(stream, _UT("BRANCH, "));
		if (instr ->groups & GRP_COND)
			safe_unistrncpy(stream, _UT("COND, "));
		if (instr ->groups & GRP_DECIMAL)
			safe_unistrncpy(stream, _UT("DECIMAL, "));
		if (instr ->groups & GRP_BREAK)
			safe_unistrncpy(stream, _UT("BREAK, "));
		if (instr ->groups & GRP_SYSTEM)
			safe_unistrncpy(stream, _UT("SYSTEM, "));
		if (instr ->groups & GRP_INOUT)
			safe_unistrncpy(stream, _UT("INOUT, "));
		if (instr ->groups & GRP_STRING)
			safe_unistrncpy(stream, _UT("STRING, "));
		if (instr ->groups & GRP_DATAMOV)
			safe_unistrncpy(stream, _UT("DATAMOV, "));
		if (instr ->groups & GRP_CONTROL)
			safe_unistrncpy(stream, _UT("CONTROL, "));
		if (instr ->groups & GRP_CONVER)
			safe_unistrncpy(stream, _UT("CONVER, "));
		if (instr ->groups & GRP_X87FPU)
			safe_unistrncpy(stream, _UT("X87FPU, "));
		if (instr ->groups & GRP_FLGCTRL)
			safe_unistrncpy(stream, _UT("FLGCTRL, "));
		if (instr ->groups & GRP_SHFTROT)
			safe_unistrncpy(stream, _UT("SHFTROT, "));
		if (instr ->groups & GRP_SIMDFP)
			safe_unistrncpy(stream, _UT("SIMDFP, "));
		if (instr ->groups & GRP_SHUNPCK)
			safe_unistrncpy(stream, _UT("SHUNPCK, "));
		if (instr ->groups & GRP_FETCH)
			safe_unistrncpy(stream, _UT("FETCH, "));
		if (instr ->groups & GRP_CACHECT)
			safe_unistrncpy(stream, _UT("CACHECT, "));
		if (instr ->groups & GRP_COMPAR)
			safe_unistrncpy(stream, _UT("COMPAR, "));
		if (instr ->groups & GRP_TRANS)
			safe_unistrncpy(stream, _UT("TRANS, "));
		if (instr ->groups & GRP_SIMDINT)
			safe_unistrncpy(stream, _UT("SIMDINT, "));
		if (instr ->groups & GRP_PCKSCLR)
			safe_unistrncpy(stream, _UT("PCKSCLR, "));
		if (instr ->groups & GRP_PCKSP)
			safe_unistrncpy(stream, _UT("PCKSP, "));
		if (instr ->groups & GRP_UNPACK)
			safe_unistrncpy(stream, _UT("UNPACK, "));
		if (instr ->groups & GRP_SHIFT)
			safe_unistrncpy(stream, _UT("SHIFT, "));
		if (instr ->groups & GRP_BIT)
			safe_unistrncpy(stream, _UT("BIT, "));
		if (instr ->groups & GRP_SM)
			safe_unistrncpy(stream, _UT("SM, "));
		if (instr ->groups & GRP_MXCSRSM)
			safe_unistrncpy(stream, _UT("MXCSRSM, "));
		if (instr ->groups & GRP_ORDER)
			safe_unistrncpy(stream, _UT("ORDER, "));
		if (instr ->groups & GRP_SSE2)
			safe_unistrncpy(stream, _UT("SSE2, "));
		if (instr ->groups & GRP_SSSE3)
			safe_unistrncpy(stream, _UT("SSSE3, "));
		if (instr ->groups & GRP_MMX)
			safe_unistrncpy(stream, _UT("MMX, "));
		if (instr ->groups & GRP_SSE3)
			safe_unistrncpy(stream, _UT("SSE3, "));
		if (instr ->groups & GRP_SMX)
			safe_unistrncpy(stream, _UT("GRP_SMX, "));
		if (instr ->groups & GRP_VMX)
			safe_unistrncpy(stream, _UT("GRP_VMX, "));
		if (instr ->groups & GRP_SSE41)
			safe_unistrncpy(stream, _UT("GRP_SSE41, "));
		if (instr ->groups & GRP_SSE42)
			safe_unistrncpy(stream, _UT("GRP_SSE42, "));
		if (instr ->groups & GRP_STRTXT)
			safe_unistrncpy(stream, _UT("GRP_STRTXT, "));

		stream ->bufflen += 2;
		stream ->buff -= 2;
		stream ->reallen -= 2;
	}
}

int medi_dbg_dump(struct INSTRUCTION *instr, uint8_t *sf_prefixes, int sf_prefixes_len, unichar_t *buff, int len)
{
	unsigned int i;
	struct STREAM stream;

	stream.buff = buff;
	stream.bufflen = len;
	stream.reallen = 0;
	stream.options = (DUMP_OPTION_DISP_UHEX | DUMP_OPTION_IMM_UHEX);

	safe_unistrncpy(&stream, _UT("Superfluous prefixes:\n\t"));
    dbg_dump_sf_prefixes(&stream, sf_prefixes, sf_prefixes_len);
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Prefixes:\n\t"));
	dbg_dump_prefixes(&stream, instr);
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Mnemonic:\n\t"));
	safe_unistrncpy(&stream, _UT("************\n\t"));
	internal_dump_mnemonic(&stream, instr);
	safe_unistrncpy(&stream, _UT("\n\t************"));
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Instruction bytes offset:\n\t"));
	itoa(&stream, instr ->opcode_offset, 0x1, 0x0, 0x10);
	safe_copy_unichar(&stream, '\n');

    if (instr ->opsize)
    {
        safe_unistrncpy(&stream, _UT("Opsize:\n\t"));
        itoa(&stream, instr ->opsize, sizeof(i), 0, 0x10);
        safe_copy_unichar(&stream, '\n');
    }

	safe_unistrncpy(&stream, _UT("Flags:\n\t"));
	dbg_dump_flags(&stream, instr);
	safe_copy_unichar(&stream, '\n');

	for (i = 0; i < 3; i++)
	{
		safe_unistrncpy(&stream, _UT("OPERAND "));
		itoa(&stream, i, sizeof(i), 0, 0x10);
		safe_unistrncpy(&stream, _UT(":\n\t"));
		if ( !(instr ->ops[i].flags & OPERAND_FLAG_PRESENT) )
		{
			safe_unistrncpy(&stream, _UT("not present"));
		}
		else
		{
			internal_dump_operand(&stream, instr, i);
			if (instr ->ops[i].flags & OPERAND_TYPE_IMM)
			{
				safe_unistrncpy(&stream, _UT("; "));
				safe_unistrncpy(&stream, _UT("Offset: "));
				itoa(&stream, instr ->ops[i].value.imm.offset, 0x1, 0x0, 0x10);
                safe_unistrncpy(&stream, _UT("; "));
                safe_unistrncpy(&stream, _UT("Size in stream: "));
                itoa(&stream, instr ->ops[i].value.imm.size, 0x1, 0x0, 0x10);
                safe_unistrncpy(&stream, _UT("; "));
                safe_unistrncpy(&stream, _UT("Size: "));
                itoa(&stream, instr ->ops[i].size, 0x1, 0x0, 0x10);
    		}
			if ( (instr ->ops[i].flags & OPERAND_TYPE_MEM) && (instr ->ops[i].value.addr.mod & ADDR_MOD_DISP) )
			{
				safe_unistrncpy(&stream, _UT("; "));
				safe_unistrncpy(&stream, _UT("Offset: "));
				itoa(&stream, instr ->disp.offset, 0x1, 0x0, 0x10);
                safe_unistrncpy(&stream, _UT("; "));
                safe_unistrncpy(&stream, _UT("Size in stream: "));
                itoa(&stream, instr ->disp.size, 0x1, 0x0, 0x10);
			}
		}
		safe_copy_unichar(&stream, '\n');
	}
	
	safe_unistrncpy(&stream, _UT("Tested flags:\n\t"));
	dbg_dump_eflags(&stream, instr ->tested_flags);
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Modified flags:\n\t"));
	dbg_dump_eflags(&stream, instr ->modified_flags);
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Set flags:\n\t"));
	dbg_dump_eflags(&stream, instr ->set_flags);
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Cleared flags:\n\t"));
	dbg_dump_eflags(&stream, instr ->cleared_flags);
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Undefined flags:\n\t"));
	dbg_dump_eflags(&stream, instr ->undefined_flags);
	safe_copy_unichar(&stream, '\n');

	safe_unistrncpy(&stream, _UT("Groups:\n\t"));
	dbg_dump_groups(&stream, instr);

	return stream.reallen;
}
#endif //MEDIANA_CTRL_DBG_DUMP
