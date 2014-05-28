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
*
* Core file of the disassembler. If you found a bug, or want to suggest a 
* feature, feel free to contact me:
*
* mika0x65@gmail.com
* mika0x65.livejournal.com
*
*******************************************************************************
*/

#include "stdafx.h"
#include <string.h>
#include "mediana.h"
#include "tables.h"
#include "tables.inc"

#define PREF_SEG_INDEX      0x0
#define PREF_OPSIZE_INDEX   0x1
#define PREF_ADDRSIZE_INDEX 0x2
#define PREF_REP_INDEX      0x3
#define PREF_LOCK_INDEX     0x4
#define PREF_REX_INDEX      0x5

#define PREFIX_COUNT        0x6

//PREF_SEG_*
#define PREF_CS_ID       0x0
#define PREF_DS_ID       0x1
#define PREF_ES_ID       0x2
#define PREF_SS_ID       0x3
#define PREF_FS_ID       0x4
#define PREF_GS_ID       0x5

//PREF_OPSIZE_*
#define PREF_OPSIZE_ID   0x6

//PREF_ADDRSIZE_*
#define PREF_ADDRSIZE_ID 0x7

//PREF_REP_*
#define PREF_REPZ_ID     0x8
#define PREF_REPNZ_ID    0x9

//PREF_LOCK_*
#define PREF_LOCK_ID     0xA

//PREF_REX_*
#define PREF_REX_ID      0xB

//Holds operand's real and intended sizes, value of sign.
struct OPERAND_SIZE
{
    uint16_t size_in_stream;
    uint16_t size;
    uint8_t sign;
};

struct INTERNAL_DATA
{
    uint8_t prefixes[PREFIX_COUNT]; //Valuable prefixes.
    uint8_t severe_err;             //Severe disassembling error.
    uint8_t err;                    //DIsassembling error.
    uint8_t is_opsize_used;         //
    uint8_t is_addrsize_used;       //Prefixes were used during disassembling.
    uint8_t is_rex_used;            //
};

/******************************************************
* Operand's type qualifers (TQ_*) handlers' prototypes.
*******************************************************
*/
static uint32_t tq_1(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_3(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_A(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_C(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_D(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_E(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_G(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_H(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_I(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_J(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_M(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_N(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_O(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_P(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_Q(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_R(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_S(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_T(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_U(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_V(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_W(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_X(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_Y(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_Z(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rAX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rCX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rDX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rBX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rSP(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rBP(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rSI(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_rDI(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_fST0(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_fES(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_fEST(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_CS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_DS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_SS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_ES(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_FS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t tq_GS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_CS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_DS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_SS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_ES_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_FS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_GS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_OPSIZE_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_ADDRSIZE_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_REPZ_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_REPNZ_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t pref_LOCK_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);

//Array of type qualifiers' handlers.
static uint32_t (*tq_handlers[])(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode) = 
{
    tq_1,
    tq_3,
    tq_A,
    tq_C,
    tq_D,
    tq_E,
    tq_G,
    tq_H,
    tq_I,
    tq_J,
    tq_M,
    tq_N,
    tq_O,
    tq_P,
    tq_Q,
    tq_R,
    tq_S,
    tq_T,
    tq_U,
    tq_V,
    tq_W,
    tq_X,
    tq_Y,
    tq_Z,
    tq_rAX,
    tq_rCX,
    tq_rDX,
    tq_rBX,
    tq_rSP,
    tq_rBP,
    tq_rSI,
    tq_rDI,
    tq_fES,
    tq_fEST,
    tq_fST0,
    tq_CS,
    tq_DS,
    tq_ES,
    tq_SS,
    tq_FS,
    tq_GS,    
    pref_CS_set,
    pref_DS_set,
    pref_ES_set,
    pref_SS_set,
    pref_FS_set,
    pref_GS_set,
    pref_OPSIZE_set,
    pref_ADDRSIZE_set,
    pref_REPZ_set,
    pref_REPNZ_set,
    pref_LOCK_set
};

/*******************************************************
* Operand's size qualifiers (SQ_*) handlers' prototypes.
********************************************************
*/
static void sq_a(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_b(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_bcd(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_bdqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_bs(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_bss(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_d(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_ddq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_di(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_dq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_dq64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_dqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_dr(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_ds(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_e(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_er(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_p(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_pd(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_pi(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_ps(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_psq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_ptp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_q(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_qdq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_qi(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_s(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_sd(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_sr(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_ss(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_st(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_stx(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_v(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_v67q64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_vd64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_vds(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_vq64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_vqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_vs(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_w(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_wdq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_wdqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_wi(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_wv(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static void sq_wvqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);

//Array of size qualifiers' handlers.
static void (*sq_handlers[])(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode) = 
{
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
    sq_wvqp
};

/***************************************
* Postprocessing functions's prototypes.
****************************************
*/
static uint32_t post_proc_arpl_movsxd(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t post_proc_nop_pause(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t post_proc_multinop(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t post_proc_cmpxchg8b(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);

//Array of potsprocessing handlers.
static uint32_t (*postprocs[])(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode) = 
{
    post_proc_arpl_movsxd,
    post_proc_nop_pause,
    post_proc_multinop,
    post_proc_cmpxchg8b
};


typedef struct {
	int seg;
	int mod;
	int base;
	int index;
	int scale;
}ADDR;

//Table for bulding 16bit addresses in my representation.
ADDR addrs_16bit[] =
{
      //seg         mod                                           base         index        scale
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_IDX,                 REG_CODE_BX, REG_CODE_SI, 0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_IDX,                 REG_CODE_BX, REG_CODE_DI, 0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_IDX,                 REG_CODE_BP, REG_CODE_SI, 0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_IDX,                 REG_CODE_BP, REG_CODE_DI, 0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE,                                REG_CODE_SI, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE,                                REG_CODE_DI, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_DISP,                                0x0,         0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE,                                REG_CODE_BX, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BX, REG_CODE_SI, 0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BX, REG_CODE_DI, 0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BP, REG_CODE_SI, 0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BP, REG_CODE_DI, 0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_SI, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_DI, 0x0,         0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_BP, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_BX, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BX, REG_CODE_SI, 0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BX, REG_CODE_DI, 0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BP, REG_CODE_SI, 0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP, REG_CODE_BP, REG_CODE_DI, 0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_SI, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_DI, 0x0,         0x1 },
    { SREG_CODE_SS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_BP, 0x0,         0x1 },
    { SREG_CODE_DS, ADDR_MOD_BASE | ADDR_MOD_DISP,                REG_CODE_BX, 0x0,         0x1 }
};


static uint8_t sregs[] =
{
    SREG_CODE_CS,
    SREG_CODE_DS,
    SREG_CODE_ES,
    SREG_CODE_SS,
    SREG_CODE_FS,
    SREG_CODE_GS
};

static uint8_t pref_opcodes[] =
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

static uint16_t pref_bits[] = 
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
    INSTR_PREFIX_REX
};

/**********************************
* Some usorted internal prototypes.
***********************************
*/
static void create_reg_operand(struct INSTRUCTION *instr, int op_index, uint8_t type, uint8_t code, uint16_t size);
static void create_xmmreg_operand(struct INSTRUCTION *instr, int op_index, uint8_t code, uint16_t size, uint8_t rex, struct INTERNAL_DATA *idata, uint8_t mode);
static void create_genreg_operand(struct INSTRUCTION *instr, int op_index, uint8_t code, uint16_t size, uint8_t rex, struct INTERNAL_DATA *idata, uint8_t mode);
static void get_seg(struct INSTRUCTION *instr, int op_index, uint8_t prefixes[], uint8_t mode);
static uint8_t get_operand_size(struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode);
static uint8_t get_operand_size_16_32(struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t parse_mem_operand(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static uint32_t parse_rm_operand(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode);
static void movsx(void *value, unsigned int size1, unsigned int size2);

/********************************************
* Operand's type qualifiers' (TQ_*) handlers.
*********************************************
*/
static uint32_t tq_1(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    instr ->ops[op_index].flags |= OPERAND_TYPE_IMM;
    instr ->ops[op_index].size = OPERAND_SIZE_8;
    instr ->ops[op_index].value.imm.imm8 = 0x1;

    return 0x0;
}

static uint32_t tq_3(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    instr ->ops[op_index].flags |= OPERAND_TYPE_IMM;
    instr ->ops[op_index].size = OPERAND_SIZE_8;
    instr ->ops[op_index].value.imm.imm8 = 0x3;

    return 0;
}

static uint32_t tq_A(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    instr ->ops[op_index].flags |= OPERAND_TYPE_DIR;
    instr ->ops[op_index].size = opsize ->size;
    instr ->ops[op_index].value.far_addr.offset = (uint8_t)(offset - origin_offset);
    memcpy(&(instr ->ops[op_index].value.far_addr), offset, instr ->ops[op_index].size);

    return instr ->ops[op_index].size;
}

static uint32_t tq_C(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_CR, (instr ->modrm >> 0x3) & 0x7, instr ->ops[op_index].size);

    return 0x0;
}

static uint32_t tq_D(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_DBG, (instr ->modrm >> 0x3) & 0x7, instr ->ops[op_index].size);

    return 0x0;
}

static uint32_t tq_E(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return parse_rm_operand(origin_offset, offset, instr, op_index, opsize, idata, mode);
}


static uint32_t tq_G(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, (instr ->modrm >> 3) & 0x7, opsize ->size, PREFIX_REX_R, idata, mode);

    return 0x0;
}

static uint32_t tq_H(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, instr ->modrm & 0x7, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_I(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    instr ->ops[op_index].flags |= OPERAND_TYPE_IMM;
    instr ->ops[op_index].size = opsize ->size;
    instr ->ops[op_index].value.imm.size = (uint8_t)opsize ->size_in_stream;
    instr ->ops[op_index].value.imm.offset = (uint8_t)(offset - origin_offset);
    memcpy(&(instr ->ops[op_index].value.imm.imm8), offset, opsize ->size_in_stream);
    movsx(&(instr ->ops[op_index].value.imm.imm8), opsize ->size_in_stream, 0x8);

    return (uint8_t)opsize ->size_in_stream;
}

static uint32_t tq_J(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    instr ->ops[op_index].flags |= OPERAND_FLAG_REL;
    return tq_I(origin_offset, offset, instr, op_index, opsize, idata, mode);
}

static uint32_t tq_M(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res = parse_rm_operand(origin_offset, offset, instr, op_index, opsize, idata, mode);
    if ((instr ->modrm & 0xC0) == 0xC0)
    {
        idata ->err = ERR_RM_REG;//error: rm encodes memory.
    }
    return res;
}

static uint32_t tq_N(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_MMX, instr ->modrm & 0x7, opsize ->size);

    return 0x0;
}

static uint32_t tq_O(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res;

    res = instr ->addrsize;
    instr ->ops[op_index].flags |= OPERAND_TYPE_MEM;
    instr ->ops[op_index].size = opsize ->size;
    instr ->ops[op_index].value.addr.mod = ADDR_MOD_DISP;
    memcpy(&(instr ->disp.value), offset, instr ->addrsize);
    get_seg(instr, op_index, idata ->prefixes, mode);

    return res;
}

static uint32_t tq_P(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_MMX, (instr ->modrm >> 0x3) & 0x7, opsize ->size);

    return 0x0;
}

static uint32_t tq_Q(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res;

    res = 0x0;
    if ((instr ->modrm & 0xC0) == 0xC0)
    {
        create_reg_operand(instr, op_index, REG_TYPE_MMX, instr ->modrm & 0x7, opsize ->size);
    }
    else
    {
        res = parse_mem_operand(origin_offset, offset, instr, op_index, opsize, idata, mode);
    }

    return res;
}

static uint32_t tq_R(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res = parse_rm_operand(origin_offset, offset, instr, op_index, opsize, idata, mode);
    if ((instr ->modrm & 0xC0) != 0xC0)
    {
        idata ->err = ERR_RM_MEM;//error: rm encodes memory.
    }
    return res;
}

static uint32_t tq_S(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_SEG, (instr ->modrm >> 3) & 0x7, OPERAND_SIZE_16);

    return 0x0;
}

static uint32_t tq_T(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_TR, (instr ->modrm >> 0x3) & 0x7, opsize ->size);

    return 0x0;
}

static uint32_t tq_U(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_xmmreg_operand(instr, op_index, instr ->modrm & 0x7, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_V(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_xmmreg_operand(instr, op_index, (instr ->modrm >> 0x3) & 0x7, opsize ->size, PREFIX_REX_R, idata, mode);

    return 0;
}

static uint32_t tq_W(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res;

    if ((instr ->modrm & 0xC0) == 0xC0)
    {
        create_xmmreg_operand(instr, op_index, instr ->modrm & 0x7, opsize ->size, PREFIX_REX_B, idata, mode);
        res = 0;
    }
    else
    {
        res = parse_mem_operand(origin_offset, offset, instr, op_index, opsize, idata, mode);
    }

    return res;
}

static uint32_t tq_X(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res;

    res = 0;
    instr ->ops[op_index].flags |= OPERAND_TYPE_MEM;
    instr ->ops[op_index].size = opsize ->size;
    instr ->ops[op_index].value.addr.mod = ADDR_MOD_BASE;
    instr ->ops[op_index].value.addr.base = REG_CODE_SI;
    get_seg(instr, op_index, idata ->prefixes, mode);

    return 0x0;
}

static uint32_t tq_Y(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    instr ->ops[op_index].flags |= OPERAND_TYPE_MEM;
    instr ->ops[op_index].size = opsize ->size;
    if (mode == DISASSEMBLE_MODE_64)
        instr ->ops[op_index].value.addr.seg = SREG_CODE_CS;
    else
        instr ->ops[op_index].value.addr.seg = SREG_CODE_ES;
    instr ->ops[op_index].value.addr.mod = ADDR_MOD_BASE;
    instr ->ops[op_index].value.addr.base = REG_CODE_DI;

    return 0x0;
}

static uint32_t tq_Z(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    //We already consumed opcode, hence we need to look backward.
    create_genreg_operand(instr, op_index, offset[-1] & 0x7, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rAX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_AX, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rCX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_CX, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rDX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_DX, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rBX(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_BX, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rSP(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_SP, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rBP(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_BP, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rSI(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_SI, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_rDI(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_genreg_operand(instr, op_index, REG_CODE_DI, opsize ->size, PREFIX_REX_B, idata, mode);

    return 0x0;
}

static uint32_t tq_fES(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res;

    if ((instr ->modrm & 0xC0) == 0xC0)
        res = tq_fEST(origin_offset, offset, instr, op_index, opsize, idata, mode);
    else
        res = tq_M(origin_offset, offset, instr, op_index, opsize, idata, mode);

    return res;
}

static uint32_t tq_fEST(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_FPU, instr ->modrm & 0x7, opsize ->size);

    return 0;
}

static uint32_t tq_fST0(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_FPU, FREG_CODE_ST0, opsize ->size);

    return 0;
}

static uint32_t tq_CS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_SEG, SREG_CODE_CS, opsize ->size);

    return 0;
}

static uint32_t tq_DS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_SEG, SREG_CODE_DS, opsize ->size);

    return 0;
}

static uint32_t tq_ES(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_SEG, SREG_CODE_ES, opsize ->size);

    return 0;
}

static uint32_t tq_SS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_SEG, SREG_CODE_SS, opsize ->size);

    return 0;
}

static uint32_t tq_FS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_SEG, SREG_CODE_FS, opsize ->size);

    return 0;
}

static uint32_t tq_GS(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    create_reg_operand(instr, op_index, REG_TYPE_SEG, SREG_CODE_GS, opsize ->size);

    return 0;
}

static uint32_t pref_CS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_SEG_INDEX << 8 | PREF_CS_ID;
}

static uint32_t pref_DS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_SEG_INDEX  << 8 | PREF_DS_ID;
}

static uint32_t pref_ES_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_SEG_INDEX  << 8 | PREF_ES_ID;
}

static uint32_t pref_SS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_SEG_INDEX  << 8 | PREF_SS_ID;
}

static uint32_t pref_FS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_SEG_INDEX  << 8 | PREF_FS_ID;
}
    
static uint32_t pref_GS_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_SEG_INDEX  << 8 | PREF_GS_ID;
}

static uint32_t pref_OPSIZE_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_OPSIZE_INDEX << 8 | PREF_OPSIZE_ID;
}

static uint32_t pref_ADDRSIZE_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_ADDRSIZE_INDEX << 8 | PREF_ADDRSIZE_ID;
}

static uint32_t pref_REPZ_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_REP_INDEX << 8 | PREF_REPZ_ID;
}

static uint32_t pref_REPNZ_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_REP_INDEX << 8 | PREF_REPNZ_ID;
}

static uint32_t pref_LOCK_set(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    return PREF_LOCK_INDEX << 8 | PREF_LOCK_ID;
}

/********************************************
* Operand's size qualifiers' (SQ_*) handlers.
*********************************************
*/
static void sq_a(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
}

static void sq_b(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_8;
	opsize->size = OPERAND_SIZE_8;
	opsize->sign = 0;
}

static void sq_bcd(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_er(opsize, instr, idata, mode);
}

static void sq_bdqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if ((instr->modrm & 0xC0) == 0xC0)
	{
		sq_dqp(opsize, instr, idata, mode);
	}
	else
	{
		sq_b(opsize, instr, idata, mode);
	}
}

static void sq_bs(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_8;
	switch (mode)
	{
	case DISASSEMBLE_MODE_16:
		opsize->size = OPERAND_SIZE_16;
		break;
	case DISASSEMBLE_MODE_32:
		opsize->size = OPERAND_SIZE_32;
		break;
	case DISASSEMBLE_MODE_64:
		opsize->size = OPERAND_SIZE_64;
		break;
	}
	opsize->sign = 1;
}

static void sq_bss(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_bs(opsize, instr, idata, mode);
}

static void sq_d(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_32;
	opsize->size = OPERAND_SIZE_32;
	opsize->sign = 0;
}

static void sq_ddq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if ((instr->modrm & 0xC0) == 0xC0)
	{
		sq_dq(opsize, instr, idata, mode);
	}
	else
	{
		sq_d(opsize, instr, idata, mode);
	}
}

static void sq_di(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_32;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_dq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_128;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_dq64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode != DISASSEMBLE_MODE_64)
	{
		sq_d(opsize, instr, idata, mode);
	}
	else
	{
		sq_q(opsize, instr, idata, mode);
	}
}

static void sq_dqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode == DISASSEMBLE_MODE_64)
	{
		opsize->size_in_stream = get_operand_size(instr, idata, mode);
		opsize->size = opsize->size_in_stream;
		opsize->sign = 0;
	}
	else
	{
		sq_d(opsize, instr, idata, mode);
	}
}

static void sq_dr(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_64;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_ds(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_d(opsize, instr, idata, mode);
	opsize->sign = 1;
}

static void sq_e(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (get_operand_size_16_32(idata, mode) == OPERAND_SIZE_16)
	{
		opsize->size_in_stream = OPERAND_SIZE_14;
	}
	else
	{
		opsize->size_in_stream = OPERAND_SIZE_28;
	}

	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_er(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_80;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_p(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = get_operand_size_16_32(idata, mode) + OPERAND_SIZE_16;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_pd(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_dq(opsize, instr, idata, mode);
}

static void sq_pi(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_q(opsize, instr, idata, mode);
}

static void sq_ps(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_128;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_psq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_q(opsize, instr, idata, mode);
}

static void sq_ptp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode == DISASSEMBLE_MODE_64)
	{
		opsize->size_in_stream = get_operand_size(instr, idata, mode) + OPERAND_SIZE_16;
		opsize->size = opsize->size_in_stream;
		opsize->sign = 0;
	}
	else
	{
		sq_p(opsize, instr, idata, mode);
	}
}

static void sq_q(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_64;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_qdq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if ((instr->modrm & 0xC0) == 0xC0)
	{
		sq_dq(opsize, instr, idata, mode);
	}
	else
	{
		sq_q(opsize, instr, idata, mode);
	}
}

static void sq_qi(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_64;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_s(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_48;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_sd(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_dq(opsize, instr, idata, mode);
}

static void sq_sr(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_32;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_ss(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	sq_dq(opsize, instr, idata, mode);
}

static void sq_st(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (get_operand_size_16_32(idata, mode) == OPERAND_SIZE_16)
	{
		opsize->size_in_stream = OPERAND_SIZE_94;
	}
	else
	{
		opsize->size_in_stream = OPERAND_SIZE_108;
	}

	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_stx(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_512;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_v(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = get_operand_size_16_32(idata, mode);
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_v67q64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode == DISASSEMBLE_MODE_64)
	{
		sq_q(opsize, instr, idata, mode);
	}
	else
	{
		if (idata->prefixes[PREF_ADDRSIZE_INDEX] != 0xFF)
		{
			mode ^= (DISASSEMBLE_MODE_16 | DISASSEMBLE_MODE_32);
			idata->is_addrsize_used = 1;
		}

		if (mode == DISASSEMBLE_MODE_16)
		{
			sq_w(opsize, instr, idata, mode);
		}
		else
		{
			sq_d(opsize, instr, idata, mode);
		}
	}
}

static void sq_vd64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode != DISASSEMBLE_MODE_64)
	{
		sq_v(opsize, instr, idata, mode);
	}
	else
	{
		if (idata->prefixes[PREF_OPSIZE_INDEX] != 0xFF)
		{
			idata->is_opsize_used = 1;
			sq_w(opsize, instr, idata, mode);
		}
		else
		{
			sq_q(opsize, instr, idata, mode);
		}
	}
}

static void sq_vds(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode == DISASSEMBLE_MODE_64)
	{
		opsize->size_in_stream = OPERAND_SIZE_32;
		opsize->size = OPERAND_SIZE_64;
		opsize->sign = 1;
	}
	else
	{
		sq_v(opsize, instr, idata, mode);
	}
}

static void sq_vq64(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode == DISASSEMBLE_MODE_64)
	{
		sq_q(opsize, instr, idata, mode);
	}
	else
	{
		sq_v(opsize, instr, idata, mode);
	}
}

static void sq_vqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode == DISASSEMBLE_MODE_64)
	{
		opsize->size_in_stream = get_operand_size(instr, idata, mode);
		opsize->size = opsize->size_in_stream;
		opsize->sign = 0;
	}
	else
	{
		sq_v(opsize, instr, idata, mode);
	}
}

static void sq_vs(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if (mode != DISASSEMBLE_MODE_64)
	{
		sq_v(opsize, instr, idata, mode);
	}
	else
	{
		opsize->size_in_stream = get_operand_size_16_32(idata, mode);
		if (idata->prefixes[PREF_OPSIZE_INDEX] != 0xFF)
		{
			opsize->size = OPERAND_SIZE_16;
		}
		else
		{
			opsize->size = OPERAND_SIZE_64;
		}
	}
}

static void sq_w(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_16;
	opsize->size = OPERAND_SIZE_16;
	opsize->sign = 0;
}

static void sq_wdq(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if ((instr->modrm & 0xC0) == 0xC0)
	{
		sq_dq(opsize, instr, idata, mode);
	}
	else
	{
		sq_w(opsize, instr, idata, mode);
	}
}

static void sq_wdqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if ((instr->modrm & 0xC0) == 0xC0)
	{
		sq_dqp(opsize, instr, idata, mode);
	}
	else
	{
		sq_w(opsize, instr, idata, mode);
	}
}

static void sq_wi(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	opsize->size_in_stream = OPERAND_SIZE_16;
	opsize->size = opsize->size_in_stream;
	opsize->sign = 0;
}

static void sq_wv(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if ((instr->modrm & 0xC0) == 0xC0)
	{
		sq_v(opsize, instr, idata, mode);
	}
	else
	{
		sq_w(opsize, instr, idata, mode);
	}
}

static void sq_wvqp(struct OPERAND_SIZE *opsize, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
	if ((instr->modrm & 0xC0) == 0xC0)
	{
		sq_vqp(opsize, instr, idata, mode);
	}
	else
	{
		sq_w(opsize, instr, idata, mode);
	}
}

/*************************
* Postprocessing routines.
**************************
*/
static uint32_t post_proc_arpl_movsxd(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res;

    res = 0;
    if (mode == DISASSEMBLE_MODE_64)
    {
        struct OPERAND_SIZE opsize;

        instr ->id = ID_MOVSXD;
        instr ->groups = GRP_GEN | GRP_CONVER;
        instr ->tested_flags = 0;
        instr ->modified_flags = 0;
        instr ->set_flags = 0;
        instr ->cleared_flags = 0;
        instr ->flags &= (INSTR_FLAG_MODRM | INSTR_FLAG_SIB);

        unistrcpy(instr ->mnemonic, _UT("movsxd"));
        res = instr ->opcode_offset + 1;
        offset += res;

        if (instr ->flags & INSTR_FLAG_MODRM)
        {
            res++;
            offset++;
        }
        if (instr ->flags & INSTR_FLAG_SIB)
        {
            res++;
            offset++;
        }
        memset(instr ->ops, 0x0, sizeof(instr ->ops));
        memset(instr ->ops + 1, 0x0, sizeof(instr ->ops + 1));
        instr ->ops[0].flags = OPERAND_FLAG_PRESENT;
        instr ->ops[1].flags = OPERAND_FLAG_PRESENT;

        sq_dqp(&opsize, instr, idata, mode);
        res += tq_G(origin_offset, offset, instr, 0, &opsize, idata, mode);
        sq_d(&opsize, instr, idata, mode);
        res += tq_E(origin_offset, offset, instr, 1, &opsize, idata, mode);
    }

    return res;
}

static uint32_t post_proc_nop_pause(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
    if (idata ->prefixes[PREF_REP_INDEX] == PREF_REPNZ_ID)
    {
        instr ->id = ID_PAUSE;
        instr ->groups = GRP_CACHECT | GRP_SSE2;
        idata ->prefixes[PREF_REP_INDEX] = 0xFF;
        unistrcpy(instr ->mnemonic, _UT("pause"));
    }

    return 0;
}

static uint32_t post_proc_multinop(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
    instr ->ops[0].flags &= ~OPERAND_FLAG_PRESENT;
    instr ->ops[1].flags &= ~OPERAND_FLAG_PRESENT;
    instr ->ops[2].flags &= ~OPERAND_FLAG_PRESENT;

    return 0;
}

static uint32_t post_proc_cmpxchg8b(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
    if (idata ->prefixes[PREF_REX_INDEX] != 0xFF && instr ->rex & PREFIX_REX_W)
    {
        idata ->is_rex_used = 1;
        unistrcpy(instr ->mnemonic, _UT("cmpxchg16b"));
        instr ->ops[0].size = OPERAND_SIZE_128;
    }

    return 0;
}

/*******************************
* Some internal common routines.
********************************
*/
static void movsx(void *value, unsigned int size1, unsigned int size2)
{
    uint8_t msb;

    if (size1 < size2)
    {
        msb = *((uint8_t *)((uint8_t *)value + size1 - 1));
        if (msb & 0x80)
            memset((uint8_t *)value + size1, 0xFF, size2 - size1);
        else
            memset((uint8_t *)value + size1, 0x0, size2 - size1);
    }
}

static uint8_t bsr(uint32_t src)
{
    uint8_t res;

    for(res = 0; src; src >>= 0x1)
    {
        if (src & 0x1)
            break;
        res++;
    }

    return res;
}

//Creates OPERAND_TYPE_REG operand of given type.
static void create_reg_operand(struct INSTRUCTION *instr, int op_index, uint8_t type, uint8_t code, uint16_t size)
{
    instr ->ops[op_index].flags |= OPERAND_TYPE_REG;
    instr ->ops[op_index].value.reg.type = type;
    instr ->ops[op_index].value.reg.code = code;
    instr ->ops[op_index].size = (uint8_t)size;
}

static void create_genreg_operand(struct INSTRUCTION *instr, int op_index, uint8_t code, uint16_t size, uint8_t rex, struct INTERNAL_DATA *idata, uint8_t mode)
{
    if (mode == DISASSEMBLE_MODE_64 && idata ->prefixes[PREF_REX_INDEX] != 0xFF)
    {
        if (code > REG_CODE_BX && size == OPERAND_SIZE_8)
        {
            code |= REG_CODE_64;
            code += 0x4;
            idata ->is_rex_used = 1;
        }
        if (instr ->rex & rex)
        {
            code |= REG_CODE_64;
            idata ->is_rex_used = 1;
        }
    }
    create_reg_operand(instr, op_index, REG_TYPE_GEN, code, size);
}

static void create_xmmreg_operand(struct INSTRUCTION *instr, int op_index, uint8_t code, uint16_t size, uint8_t rex, struct INTERNAL_DATA *idata, uint8_t mode)
{
    if (mode == DISASSEMBLE_MODE_64 && idata ->prefixes[PREF_REX_INDEX] != 0xFF)
    {
        if (instr ->rex & rex)
        {
            code |= REG_CODE_64;
            idata ->is_rex_used = 1;
        }
    }
    create_reg_operand(instr, op_index, REG_TYPE_XMM, code, size);
}

//Returns size accordingly to disassemble mode and opsize prefix.
static uint8_t get_operand_size_16_32(struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint8_t res;

    if (mode == DISASSEMBLE_MODE_64)
        mode = DISASSEMBLE_MODE_32;

    if (idata ->prefixes[PREF_OPSIZE_INDEX] != 0xFF)
    {
        mode ^= (DISASSEMBLE_MODE_16 | DISASSEMBLE_MODE_32);
        idata ->is_opsize_used = 1;
    }

    if (mode == DISASSEMBLE_MODE_16)
        res = OPERAND_SIZE_16;
    else
        res = OPERAND_SIZE_32;

    return res;
}

//Returns size accordingly to disassemble mode, size override and REX.W prefixes.
static uint8_t get_operand_size(struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint8_t res;

    if (mode == DISASSEMBLE_MODE_64)
    {
        if (idata ->prefixes[PREF_REX_INDEX] != 0xFF && instr ->rex & PREFIX_REX_W)
        {
            res = OPERAND_SIZE_64;
            idata ->is_rex_used = 1;
        }
        else
        {
            res = get_operand_size_16_32(idata, mode);
        }
    }
    else
    {
        res = get_operand_size_16_32(idata, mode);
    }

    return res;
}

//Returns address size. Address size is common for all operands.
static void get_address_size(struct INSTRUCTION *instr, uint8_t prefixes[], uint8_t mode)
{
    if (mode == DISASSEMBLE_MODE_64)
    {
        if (prefixes[PREF_ADDRSIZE_INDEX] != 0xFF)
            instr ->addrsize = ADDR_SIZE_32;
        else
            instr ->addrsize = ADDR_SIZE_64;
    }
    else
    {
        if (prefixes[PREF_ADDRSIZE_INDEX] != 0xFF)
            mode ^= (DISASSEMBLE_MODE_16 | DISASSEMBLE_MODE_32);

        if (mode == DISASSEMBLE_MODE_16)
            instr ->addrsize = ADDR_SIZE_16;
        else
            instr ->addrsize = ADDR_SIZE_32;
    }
}

//Calculates segment for memory addressing operands accordingly to
//mode, segment override prefixes and address base register.
static void get_seg(struct INSTRUCTION *instr, int op_index, uint8_t prefixes[], uint8_t mode)
{
    if (prefixes[PREF_SEG_INDEX] == 0xFF)
    {
        if (mode == DISASSEMBLE_MODE_64)
        {
            instr ->ops[op_index].value.addr.seg = SREG_CODE_CS;
        }
        else
        {
            if ( !(instr ->ops[op_index].value.addr.mod & ADDR_MOD_BASE) )
            {
                instr ->ops[op_index].value.addr.seg = SREG_CODE_DS;
            }
            else
            {
                if ((instr ->ops[op_index].value.addr.base != REG_CODE_BP) && (instr ->ops[op_index].value.addr.base != REG_CODE_SP))
                {
                    instr ->ops[op_index].value.addr.seg = SREG_CODE_DS;
                }
                else
                {
                    instr ->ops[op_index].value.addr.seg = SREG_CODE_SS;
                }
            }
        }
    }
    else
    {
        if (mode != DISASSEMBLE_MODE_64)
        {
            instr ->ops[op_index].value.addr.seg = sregs[prefixes[PREF_SEG_INDEX]];
        }
        else
        {
            if (prefixes[PREF_SEG_INDEX] == PREF_FS_ID || prefixes[PREF_SEG_INDEX] == PREF_GS_ID)
            {
                instr ->ops[op_index].value.addr.seg = sregs[prefixes[PREF_SEG_INDEX]];
            }
            else
            {
                instr ->ops[op_index].value.addr.seg = SREG_CODE_CS;
            }
        }
    }
}

//Builds ADDR.mod field from instruction's MODRM byte.
static void get_mod_type_modrm(struct INSTRUCTION *instr, int op_index)
{
    if (instr ->ops[op_index].value.addr.mod != 0x0)
    {
        instr ->ops[op_index].value.addr.mod = ADDR_MOD_BASE | ADDR_MOD_DISP;
    }
    else
    {
        if ((instr ->ops[op_index].value.addr.base == REG_CODE_BP) || (instr ->ops[op_index].value.addr.base == REG_CODE_R13))
        {
            instr ->ops[op_index].value.addr.mod = ADDR_MOD_DISP;
        }
        else
        {
            instr ->ops[op_index].value.addr.mod = ADDR_MOD_BASE;
        }
    }
}

//Builds ADDR.mod field from instruction's SIB byte.
static void get_mod_type_sib(struct INSTRUCTION *instr, int op_index)
{
    if (instr ->ops[op_index].value.addr.index == REG_CODE_SP)
    {
        get_mod_type_modrm(instr, op_index);
    }
    else
    {
        if (instr ->ops[op_index].value.addr.mod == 0)
        {
            if ( (instr ->ops[op_index].value.addr.base == REG_CODE_BP) || (instr ->ops[op_index].value.addr.base == REG_CODE_R13) )
            {
                instr ->ops[op_index].value.addr.mod = ADDR_MOD_IDX | ADDR_MOD_DISP;
            }
            else
            {
                instr ->ops[op_index].value.addr.mod = ADDR_MOD_BASE | ADDR_MOD_IDX;
            }
        }
        else
        {
            instr ->ops[op_index].value.addr.mod = ADDR_MOD_BASE | ADDR_MOD_IDX | ADDR_MOD_DISP;
        }
    }
}

//Calculates displacement's size and copies it to struct DISPLACEMENT.
static uint8_t get_disp(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, uint8_t mode)
{
    uint8_t len;

    switch(instr ->ops[op_index].value.addr.mod)
    {
    case 0x0:
        if (instr ->ops[op_index].value.addr.base == REG_CODE_BP)
            len = instr ->addrsize;
        else
            len = 0x0;
        break;
    case 0x1:
        len = 0x1;
        break;
    case 0x2:
        len = instr ->addrsize;
        break;
    }

    if (len == 8)
        len = 4;

    instr ->disp.size = len;
    if (len)
    {
        memcpy(&(instr ->disp.value), offset, len);
        movsx(&(instr ->disp.value), len, 0x8);
        instr ->disp.offset = (uint8_t)(offset - origin_offset);
    }

    return len;
}

//Parses 16bit memory address operand.
static uint32_t parse_mem_operand_16(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, uint8_t mode)
{
    uint8_t len;
    unsigned int index;

    instr ->ops[op_index].value.addr.mod = instr ->modrm >> 0x6;
    len = get_disp(origin_offset, offset, instr, op_index, mode);
    index = (instr ->modrm >> 0x3 & 0x18) | (instr ->modrm & 0x7);
    instr ->ops[op_index].value.addr.seg = addrs_16bit[index].seg;
    instr ->ops[op_index].value.addr.mod = addrs_16bit[index].mod;
    instr ->ops[op_index].value.addr.base = addrs_16bit[index].base;
    instr ->ops[op_index].value.addr.index = addrs_16bit[index].index;
    instr ->ops[op_index].value.addr.scale = addrs_16bit[index].scale;

    return len;
}

//Parses 32/64bit memory address operand.
static uint32_t parse_mem_operand_32_64(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t len = 0;

    if (instr ->flags & INSTR_FLAG_SIB)
    {
        instr ->ops[op_index].value.addr.mod = instr ->modrm >> 0x6;
        instr ->ops[op_index].value.addr.base = instr ->sib & 0x7;
        instr ->ops[op_index].value.addr.index = (instr ->sib >> 3) & 0x7;
        instr ->ops[op_index].value.addr.scale = 1 << (instr ->sib >> 0x6);

        if (mode == DISASSEMBLE_MODE_64 && idata ->prefixes[PREF_REX_INDEX] != 0xFF)
        {
            if (instr ->rex & PREFIX_REX_B)
            {
                instr ->ops[op_index].value.addr.base |= REG_CODE_64;
                idata ->is_rex_used = 1;
            }
            if (instr ->rex & PREFIX_REX_X)
            {
                instr ->ops[op_index].value.addr.index |= REG_CODE_64;
                idata ->is_rex_used = 1;
            }
        }
        len = get_disp(origin_offset, offset, instr, op_index, mode);
        get_mod_type_sib(instr, op_index);
    }
    else
    {
        instr ->ops[op_index].value.addr.mod = instr ->modrm >> 0x6;
        instr ->ops[op_index].value.addr.base = instr ->modrm & 0x7;

        if (mode == DISASSEMBLE_MODE_64)
        {
            if (idata ->prefixes[PREF_REX_INDEX] != 0xFF && instr ->rex & PREFIX_REX_B)
            {
                instr ->ops[op_index].value.addr.base |= REG_CODE_64;
                idata ->is_rex_used = 1;
            }

            if ( (instr ->ops[op_index].value.addr.mod == 0x0) &&
                 ((instr ->ops[op_index].value.addr.base == REG_CODE_BP) ||
                  (instr ->ops[op_index].value.addr.base == REG_CODE_R13)) )
            {
                instr ->ops[op_index].value.addr.base = REG_CODE_IP;
            }
        }
        len = get_disp(origin_offset, offset, instr, op_index, mode);
        get_mod_type_modrm(instr, op_index);
    }
    get_seg(instr, op_index, idata ->prefixes, mode);

    return len;
}

//Parses memory address operand.
static uint32_t parse_mem_operand(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t len;

    instr ->ops[op_index].flags |= OPERAND_TYPE_MEM;
    instr ->ops[op_index].size = opsize ->size;
    if (instr ->addrsize == ADDR_SIZE_16)
    {
        len = parse_mem_operand_16(origin_offset, offset, instr, op_index, mode);
    }
    else
    {
        len = parse_mem_operand_32_64(origin_offset, offset, instr, op_index, idata, mode);
    }
    idata ->is_addrsize_used = 1;

    return len;
}

//Parses operand accordingly to MODRM value.
static uint32_t parse_rm_operand(uint8_t *origin_offset, uint8_t *offset, struct INSTRUCTION *instr, int op_index, struct OPERAND_SIZE *opsize, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t len = 0;

    if ((instr ->modrm & 0xC0) == 0xC0)
    {
        create_genreg_operand(instr, op_index, instr ->modrm & 0x7, opsize ->size, PREFIX_REX_B, idata, mode);
    }
    else
    {
        len = parse_mem_operand(origin_offset, offset, instr, op_index, opsize, idata, mode);
    }

    return len;
}

static uint32_t parse_operand(uint8_t *origin_offset, uint8_t *offset, struct INTERNAL_OPERAND *iop, struct INSTRUCTION *instr, int op_index, struct INTERNAL_DATA *idata, uint8_t mode)
{
    uint32_t res = 0;
    struct OPERAND_SIZE opsize;

    if (iop ->type != TQ_NULL)
    {
        instr ->ops[op_index].flags |= OPERAND_FLAG_PRESENT;
        if (iop ->size >= sizeof(sq_handlers) / sizeof(sq_handlers[0]))
        {
            idata ->severe_err = ERR_INTERNAL;
        }
        else
        {
            sq_handlers[iop ->size](&opsize, instr, idata, mode);
        }

        if (iop ->size >= sizeof(tq_handlers) / sizeof(tq_handlers[0]))
        {
            idata ->severe_err = ERR_INTERNAL;
        }
        else
        {
            res = tq_handlers[iop ->type](origin_offset, offset, instr, op_index, &opsize, idata, mode);
        }
    }

    return res;
}

//Applies disassembling options.
static void apply_disasm_options(struct INSTRUCTION *instr, uint32_t len, struct DISASM_INOUT_PARAMS *params)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (params ->options & DISASM_OPTION_APPLY_REL)
        {
            if (instr ->ops[i].flags & OPERAND_FLAG_REL)
            {
                instr ->ops[i].value.imm.imm64 += len + params ->base;
            }
        }

        if (params ->options & DISASM_OPTION_OPTIMIZE_DISP)
        {
            if ((instr ->ops[i].flags & OPERAND_TYPE_MEM) && (instr ->ops[i].value.addr.mod != ADDR_MOD_DISP))
            {
                if (instr ->disp.value.d64 == 0x0)
                    instr ->ops[i].value.addr.mod &= ~ADDR_MOD_DISP;
            }
        }
    }
}

//Copies instruction's flags from struct OPCODE_DESCRIPTOR to struct INSTRUCTION.
static void copy_instr_flags(struct INSTRUCTION *instr, struct OPCODE_DESCRIPTOR *opcode)
{
    if (opcode ->props & PROP_IOPL)
        instr ->flags |= INSTR_FLAG_IOPL;
    if (opcode ->props & PROP_RING0)
        instr ->flags |= INSTR_FLAG_RING0;
    if (opcode ->props & PROP_SERIAL)
        instr ->flags |= INSTR_FLAG_SERIAL;
    if (opcode ->props & PROP_UNDOC)
        instr ->flags |= INSTR_FLAG_UNDOC;
}

//Copies instruction's tested, modified, set, cleared and underfined
//eflags values from struct OPCODE_DESCRIPTOR to struct INSTRUCTION.
static void copy_eflags(struct INSTRUCTION *instr, struct OPCODE_DESCRIPTOR *opcode)
{
    instr ->tested_flags = opcode ->tested_flags;
    instr ->modified_flags = opcode ->modified_flags;
    instr ->set_flags = opcode ->set_flags;
    instr ->cleared_flags = opcode ->cleared_flags;
    instr ->undefined_flags = opcode ->undefined_flags;
}

//Copies MODRM and SIB bytes to struct INSTRUCTION.
static uint8_t parse_modrm_sib(uint8_t *offset, struct INSTRUCTION *instr, struct OPCODE_DESCRIPTOR *opcode)
{
    uint8_t len = 0;

    if (opcode ->props & PROP_MODRM)
    {
        len++;
        instr ->flags |= INSTR_FLAG_MODRM;
        instr ->modrm = *offset;
        if (instr ->addrsize != ADDR_SIZE_16)
        {
            if ((instr ->modrm & 0x7) == 0x4 && (instr ->modrm & 0xC0) != 0xC0)
            {
                len++;
                instr ->flags |= INSTR_FLAG_SIB;
                instr ->sib = offset[1];
            }
        }
    }

    return len;
}

//Converts prefixes from internal to external representation.
static void convert_prefixes(struct INSTRUCTION *instr, uint8_t prefixes[])
{
    int i;

    for (i = 0; i < PREFIX_COUNT; i++)
    {
        if (prefixes[i] != 0xFF)
            instr ->prefixes |= pref_bits[prefixes[i]];
    }
}

//If DISASM_INOUT_PARAMS.sf_prefixes != NULL, copies superfluous prefix's value to the array.
static void add_sf_prefix_value(uint8_t prefixes[], int index, uint8_t value, struct INSTRUCTION *instr, struct DISASM_INOUT_PARAMS *params)
{
    instr ->flags |= INSTR_FLAG_SF_PREFIXES;

    if (params ->sf_prefixes)
        params ->sf_prefixes[params ->sf_prefixes_len++] = value;
    prefixes[index] = 0xFF;    
}

//Gets superfluous prefix's value by its index and call to function above :).
static void add_sf_prefix(uint8_t prefixes[], uint32_t index, struct INSTRUCTION *instr, struct DISASM_INOUT_PARAMS *params)
{
    add_sf_prefix_value(prefixes, index, pref_opcodes[prefixes[index]], instr, params);
}

//Checks if segment override prefix is superfluous.
static void check_seg_sf_prefixes(struct INSTRUCTION *instr, uint8_t prefixes[], struct DISASM_INOUT_PARAMS *params)
{
    unsigned int i;
    int mem_op_found;

    mem_op_found = 0;
    if (prefixes[PREF_SEG_INDEX] != 0xFF)
    {
        for (i = 0; i < 3; i++)
        {
            if (instr ->ops[i].flags & OPERAND_TYPE_MEM)
            {
                if (params ->mode == DISASSEMBLE_MODE_64)
                {
                    if ( !((prefixes[PREF_SEG_INDEX] == PREF_FS_ID) || (prefixes[PREF_SEG_INDEX] == PREF_GS_ID)) )
                    {
                        add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, params);
                    }
                }
                else
                {
                    if ( !(instr ->ops[i].value.addr.mod & ADDR_MOD_BASE) )
                    {
                        if (instr ->ops[i].value.addr.seg == SREG_CODE_DS)
                            add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, params);
                    }
                    else
                    {
                        if ((instr ->ops[i].value.addr.base == REG_CODE_BP) || (instr ->ops[i].value.addr.base == REG_CODE_SP))
                        {
                            if (instr ->ops[i].value.addr.seg == SREG_CODE_SS)
                                add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, params);
                        }
                        else
                        {
                            if (instr ->ops[i].value.addr.seg == SREG_CODE_DS)
                                add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, params);
                        }
                    }
                }

                mem_op_found = 1;
            }
        }

        if (!mem_op_found)
            add_sf_prefix(prefixes, PREF_SEG_INDEX, instr, params);
    }
}

//Checks opcode-extension prefixes (repz, repnz, opsize) are superfluous.
static void check_ext_sf_prefixes(uint8_t prefixes[], struct INSTRUCTION *instr, struct DISASM_INOUT_PARAMS *params)
{
    if (prefixes[PREF_OPSIZE_INDEX] != 0xFF)
        add_sf_prefix(prefixes, PREF_OPSIZE_INDEX, instr, params);
    if (prefixes[PREF_REP_INDEX] != 0xFF)
        add_sf_prefix(prefixes, PREF_OPSIZE_INDEX, instr, params);
}

//Get instruction's size. Well, really this is size of implicit operand
// that influences on instruction's mnemonic.
static void get_instruction_opsize(struct MULTI_MNEMONIC *multi_mnemonic, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
    struct OPERAND_SIZE opsize;

    if (multi_mnemonic ->size >= sizeof(sq_handlers) / sizeof(sq_handlers[0]))
    {
        idata ->severe_err = ERR_INTERNAL;
    }
    else
    {
        sq_handlers[multi_mnemonic ->size](&opsize, instr, idata, mode);
    }

    instr ->opsize = (uint8_t)opsize.size; //Possible sizes are 2/4/8.
}

//Parses instruction's mnemonic. If mnemonic is simple, it is just copied to
// struct INSTRUCTION. If mnemonic contains has multi mnemonic indicator (MM_INDICATOR)
// at first character then it depends on implicit operand's size. In this case the function
// calls get_instruction_opsize and builds choses mnemonic basing on result.
static void parse_mnemonic(struct OPCODE_DESCRIPTOR *opcode, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t mode)
{
    if (opcode ->mnemonic.value[0] != MM_INDICATOR)
    {
        unistrcpy(instr ->mnemonic, opcode ->mnemonic.value);
    }
    else
    {
        get_instruction_opsize(opcode ->mnemonic.multi_mnemonic, instr, idata, mode);
        unistrcpy(instr ->mnemonic,opcode ->mnemonic.multi_mnemonic ->values[bsr(instr ->opsize) - 1]);
    }
}

//Main function for parsing prefixes. Reads input stream until meets non-prefix byte
// or maximum instruction length is exceeded. The function checks if a prefix of the same group
// was already met and if so, replaces old prefix with a new one.
// Old prefix is added to superfluous prefixes array.
 // The function also checks if a prefix is opcode-extension.
static uint32_t parse_prefixes(uint8_t *offset, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, uint8_t *ext_table_index, uint8_t *ext_pref_index, struct DISASM_INOUT_PARAMS *params)
{
    uint8_t pref_code;
    uint8_t rex_found;
    uint8_t pref_id;
    uint8_t pref_index;
    uint32_t res;
    uint32_t tmp;
    struct OPCODE_DESCRIPTOR *ptr;

    res = 0;
    rex_found = 0;

    while(1)
    {
        pref_code = *offset;
        if (res > MAX_INSTRUCTION_LEN)
        {
            idata ->severe_err = ERR_TOO_LONG;//error: instruction too long.
            break;
        }

        ptr = &(tables[IDX_1BYTE].opcodes[pref_code]);
        if ( !( (ptr ->groups & GRP_PREFIX) ||
                (params ->mode == DISASSEMBLE_MODE_64 && pref_code >= 0x40 && pref_code <= 0x4F && !rex_found) ) )
        {
            break;
        }
        else
        {
            if (rex_found)
            {
                idata ->severe_err = ERR_REX_NOOPCD;//error: an opcode should follow after rex.
                break;
            }

            if (!rex_found && params ->mode == DISASSEMBLE_MODE_64)
            {
                if ( (pref_code >= 0x40) && (pref_code <= 0x4F) )
                {
                    idata ->prefixes[PREF_REX_INDEX] = PREF_REX_ID;
                    instr ->rex = pref_code;
                    rex_found = 1;

                    res++;
                    offset++;
                    continue;
                }
            }

            tmp = tq_handlers[ptr ->ops[0].type](NULL, NULL, instr, 0, NULL, NULL, params ->mode);
            pref_index = (uint8_t)(tmp >> 8);
            pref_id = tmp & 0xFF;
            if (idata ->prefixes[pref_index] != 0xFF)
            {
                add_sf_prefix(idata ->prefixes, pref_index, instr, params);
            }
            idata ->prefixes[pref_index] = pref_id;

            //Used later for prefix table switch.
            if (ptr ->id == ID_66 || ptr ->id == ID_REPZ || ptr ->id == ID_REPNZ)
            {
                *ext_table_index = ptr ->props & 0xFF;
                *ext_pref_index = pref_index;
            }

            res++;
            offset++;
        }
    }

    return res;
}

//Reads input stream and iterates through tables looking up appropriate struct OPCODE_DESCRIPTOR.
// Byte value at [offset] is used as index, the function checks tables limits and max instruction's length.
static uint32_t lookup_opcode(uint8_t *offset, uint8_t table, struct OPCODE_DESCRIPTOR **opcode_descr, struct INTERNAL_DATA *idata)
{
    uint8_t max;
    uint8_t opcode;
    uint32_t res;

    res = 0;
    *opcode_descr = NULL;
    do
    {
        opcode = *offset;
        opcode >>= tables[table].shift;
        opcode &= tables[table].mask;
        opcode -= tables[table].min;
        //It looks strange, but I want that table descriptors contain
        // "real" values.
        max = tables[table].max - tables[table].min;
        if (opcode > max)
        {
            idata ->severe_err = ERR_BADCODE;
            break;
        }

        if (res > MAX_INSTRUCTION_LEN)
        {
            idata ->severe_err = ERR_TOO_LONG;
            break;
        }

        if ( !(tables[table].props & TBL_PROP_MODRM) )
        {
            res++;
            offset++;
        }

        if (tables[table].opcodes[opcode].groups & GRP_SWITCH)
        {
            table = tables[table].opcodes[opcode].props & 0xFF;
            continue;
        }
        break;
    }
    while(1);

    if ( !(idata ->severe_err) )
        *opcode_descr = &(tables[table].opcodes[opcode]);

    return res;
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
static uint32_t parse_opcode(uint8_t *offset, struct OPCODE_DESCRIPTOR **opcode_descr, struct INSTRUCTION *instr, struct INTERNAL_DATA *idata, struct DISASM_INOUT_PARAMS *params)
{
    uint8_t ext_table_index;
    uint8_t ext_prefix_index;
    uint32_t res;
    uint32_t tmp;

    ext_table_index = 0xFF;
    res = parse_prefixes(offset, instr, idata, &ext_table_index, &ext_prefix_index, params);
    if (!idata ->severe_err)
    {
        instr ->opcode_offset = (uint8_t)res;
        offset += res;

        if (ext_table_index != 0xFF && *offset == 0xF)
        {
            tmp = lookup_opcode(offset, ext_table_index, opcode_descr, idata);
            if (!idata ->severe_err && (*opcode_descr) ->id != ID_NULL)
            {
                idata ->prefixes[ext_prefix_index] = 0xFF;
                check_ext_sf_prefixes(idata ->prefixes, instr, params);
                res += tmp;
            }
            else
            {
                idata ->severe_err = 0;
                res += lookup_opcode(offset, IDX_1BYTE, opcode_descr, idata);
            }
        }
        else
        {
            res += lookup_opcode(offset, IDX_1BYTE, opcode_descr, idata);
        }

        if (!idata ->severe_err && (*opcode_descr) ->id == ID_NULL)
        {
            idata ->severe_err = ERR_BADCODE;//error: invalid opcode.
        }
    }

    return res;
}

//Disassembler's entry point. So long because does everything :).
unsigned int medi_disassemble(uint8_t *offset, struct INSTRUCTION *instr, struct DISASM_INOUT_PARAMS *params)
{
	uint32_t len;
	uint32_t res;
	struct OPCODE_DESCRIPTOR *opcode;
	struct INTERNAL_DATA idata;

    //Setup everything.
    memset(instr, 0x0, sizeof(*instr));
    memset(&idata, 0x0, sizeof(idata));
    memset(idata.prefixes, 0xFF, sizeof(idata.prefixes));
    params ->sf_prefixes_len = 0;
    params ->errcode = 0;
    len = res = 0;

    //Lookup opcode.
    res = parse_opcode(offset, &opcode, instr, &idata, params);
    if (idata.severe_err)
    {
        params ->errcode = idata.severe_err;
        return 0;
    }
    len += res;
    if (len > MAX_INSTRUCTION_LEN)
    {
        params ->errcode = ERR_TOO_LONG;
        return 0;
    }

    get_address_size(instr, idata.prefixes, params ->mode);

    //Parse MODRM and SIB bytes.
    len += parse_modrm_sib(offset + len, instr, opcode);
    if (len > MAX_INSTRUCTION_LEN)
    {
        params ->errcode = ERR_TOO_LONG;
        return 0;
    }

    //Copy flags, eflags, id, groups.
    copy_eflags(instr, opcode);
    copy_instr_flags(instr, opcode);
    instr ->id = opcode ->id;
    instr ->groups = opcode ->groups;

    //Parse mnemonic.
    parse_mnemonic(opcode, instr, &idata, params ->mode);
    if (idata.severe_err)
    {
        params ->errcode = idata.severe_err;
        return 0;
    }

    //Deal with operands.
    res = parse_operand(offset, offset + len, opcode ->ops, instr, 0, &idata, params ->mode);
    if (idata.severe_err)
    {
        params ->errcode = idata.severe_err;
        return 0;
    }
    len += res;
    if (len > MAX_INSTRUCTION_LEN)
    {
        params ->errcode = ERR_TOO_LONG;
        return 0;
    }

    res = parse_operand(offset, offset + len, opcode ->ops + 1, instr, 1, &idata, params ->mode);
    if (idata.severe_err)
    {
        params ->errcode = idata.severe_err;
        return 0;
    }
    len += res;
    if (len > MAX_INSTRUCTION_LEN)
    {
        params ->errcode = ERR_TOO_LONG;
        return 0;
    }

    res = parse_operand(offset, offset + len, opcode ->ops + 2, instr, 2, &idata, params ->mode);
    if (idata.severe_err)
    {
        params ->errcode = idata.severe_err;
        return 0;
    }
    len += res;
    if (len > MAX_INSTRUCTION_LEN)
    {
        params ->errcode = ERR_TOO_LONG;
        return 0;
    }

    //Do postprocessing if necessary.
    if (opcode ->props & PROP_POST_PROC)
    {
        res = postprocs[opcode ->props >> POST_PROC_SHIFT](offset, offset, instr, &idata, params ->mode);
        if (idata.severe_err)
        {
            params ->errcode = idata.severe_err;
            return 0;
        }
        if (res)
        {
            len = res;
            if (len > MAX_INSTRUCTION_LEN)
            {
                params ->errcode = ERR_TOO_LONG;
                return 0;
            }
        }
    }

    //Check if REX is superfluous.
    if (params ->mode == DISASSEMBLE_MODE_64 && !idata.is_rex_used)
        add_sf_prefix_value(idata.prefixes, PREF_REX_INDEX, instr ->rex, instr, params);
    //Check if segment prefix is superfluous.
    check_seg_sf_prefixes(instr, idata.prefixes, params);
    //Check if opsize is superfluous. 
    if (!idata.is_opsize_used && idata.prefixes[PREF_OPSIZE_INDEX] != 0xFF)
        add_sf_prefix(idata.prefixes, PREF_OPSIZE_INDEX, instr, params);
    //Check if addrsize is superfluous. 
    if (!idata.is_addrsize_used && idata.prefixes[PREF_ADDRSIZE_INDEX] != 0xFF)
        add_sf_prefix(idata.prefixes, PREF_ADDRSIZE_INDEX, instr, params);

    //Convert prefixes to output representation.
    convert_prefixes(instr, idata.prefixes);

    //Copy error if exists.
    params ->errcode = idata.err;

    //And post checks.
    if (!(params ->arch & opcode ->arch))
        params ->errcode = ERR_ANOT_ARCH;//error: another architecture.
    else if ( (instr ->prefixes & INSTR_PREFIX_LOCK) && !(opcode ->props & PROP_LOCK) )
        params ->errcode = ERR_NON_LOCKABLE;//error: prefix lock non-lockable instruction.
    else if ((opcode ->props & PROP_I64) && (params ->mode == DISASSEMBLE_MODE_64))
        params ->errcode = ERR_16_32_ONLY;//error: instruction is 16/32bit mode only.
    else if (opcode ->props & PROP_O64 && params ->mode != DISASSEMBLE_MODE_64)
        params ->errcode = ERR_64_ONLY;//error: instruction is 64bit mode only.

    apply_disasm_options(instr, len, params);

    return len;
}