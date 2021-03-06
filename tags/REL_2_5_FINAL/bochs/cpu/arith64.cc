/////////////////////////////////////////////////////////////////////////
// $Id$
/////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2001-2011  The Bochs Project
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA B 02110-1301 USA
/////////////////////////////////////////////////////////////////////////

#define NEED_CPU_REG_SHORTCUTS 1
#include "bochs.h"
#include "cpu.h"
#define LOG_THIS BX_CPU_THIS_PTR

#if BX_SUPPORT_X86_64

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADD_EqGqM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = BX_READ_64BIT_REG(i->nnn());
  sum_64 = op1_64 + op2_64;
  write_RMW_virtual_qword(sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADD_GqEqR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  op1_64 = BX_READ_64BIT_REG(i->nnn());
  op2_64 = BX_READ_64BIT_REG(i->rm());
  sum_64 = op1_64 + op2_64;
  BX_WRITE_64BIT_REG(i->nnn(), sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADD_RAXId(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  op1_64 = RAX;
  op2_64 = (Bit32s) i->Id();
  sum_64 = op1_64 + op2_64;

  /* now write sum back to destination */
  RAX = sum_64;

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADC_EqGqM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = BX_READ_64BIT_REG(i->nnn());
  sum_64 = op1_64 + op2_64 + getB_CF();
  write_RMW_virtual_qword(sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADC_GqEqR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  op1_64 = BX_READ_64BIT_REG(i->nnn());
  op2_64 = BX_READ_64BIT_REG(i->rm());
  sum_64 = op1_64 + op2_64 + getB_CF();

  /* now write sum back to destination */
  BX_WRITE_64BIT_REG(i->nnn(), sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADC_RAXId(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  op1_64 = RAX;
  op2_64 = (Bit32s) i->Id();
  sum_64 = op1_64 + op2_64 + getB_CF();

  /* now write sum back to destination */
  RAX = sum_64;

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SBB_EqGqM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = BX_READ_64BIT_REG(i->nnn());
  diff_64 = op1_64 - (op2_64 + getB_CF());
  write_RMW_virtual_qword(diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SBB_GqEqR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = BX_READ_64BIT_REG(i->nnn());
  op2_64 = BX_READ_64BIT_REG(i->rm());
  diff_64 = op1_64 - (op2_64 + getB_CF());

  /* now write diff back to destination */
  BX_WRITE_64BIT_REG(i->nnn(), diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SBB_RAXId(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = RAX;
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - (op2_64 + getB_CF());

  /* now write diff back to destination */
  RAX = diff_64;

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SBB_EqIdM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - (op2_64 + getB_CF());
  write_RMW_virtual_qword(diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SBB_EqIdR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = BX_READ_64BIT_REG(i->rm());
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - (op2_64 + getB_CF());
  BX_WRITE_64BIT_REG(i->rm(), diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SUB_EqGqM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = BX_READ_64BIT_REG(i->nnn());
  diff_64 = op1_64 - op2_64;
  write_RMW_virtual_qword(diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SUB_GqEqR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = BX_READ_64BIT_REG(i->nnn());
  op2_64 = BX_READ_64BIT_REG(i->rm());
  diff_64 = op1_64 - op2_64;

  /* now write diff back to destination */
  BX_WRITE_64BIT_REG(i->nnn(), diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SUB_RAXId(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = RAX;
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - op2_64;

  /* now write diff back to destination */
  RAX = diff_64;

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMP_EqGqM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  op1_64 = read_virtual_qword_64(i->seg(), eaddr);
  op2_64 = BX_READ_64BIT_REG(i->nnn());
  diff_64 = op1_64 - op2_64;

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMP_GqEqR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = BX_READ_64BIT_REG(i->nnn());
  op2_64 = BX_READ_64BIT_REG(i->rm());
  diff_64 = op1_64 - op2_64;

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMP_RAXId(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = RAX;
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - op2_64;

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CDQE(bxInstruction_c *i)
{
  /* CWDE: no flags are affected */
  RAX = (Bit32s) EAX;

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CQO(bxInstruction_c *i)
{
  /* CQO: no flags are affected */

  if (RAX & BX_CONST64(0x8000000000000000))
      RDX = BX_CONST64(0xffffffffffffffff);
  else
      RDX = 0;

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::XADD_EqGqM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  /* XADD dst(r/m), src(r)
   * temp <-- src + dst         | sum = op2 + op1
   * src  <-- dst               | op2 = op1
   * dst  <-- tmp               | op1 = sum
   */

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = BX_READ_64BIT_REG(i->nnn());
  sum_64 = op1_64 + op2_64;
  write_RMW_virtual_qword(sum_64);

  /* and write destination into source */
  BX_WRITE_64BIT_REG(i->nnn(), op1_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::XADD_EqGqR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  /* XADD dst(r/m), src(r)
   * temp <-- src + dst         | sum = op2 + op1
   * src  <-- dst               | op2 = op1
   * dst  <-- tmp               | op1 = sum
   */

  op1_64 = BX_READ_64BIT_REG(i->rm());
  op2_64 = BX_READ_64BIT_REG(i->nnn());
  sum_64 = op1_64 + op2_64;

  // and write destination into source
  // Note: if both op1 & op2 are registers, the last one written
  //       should be the sum, as op1 & op2 may be the same register.
  //       For example:  XADD AL, AL
  BX_WRITE_64BIT_REG(i->nnn(), op1_64);
  BX_WRITE_64BIT_REG(i->rm(), sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADD_EqIdM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = (Bit32s) i->Id();
  sum_64 = op1_64 + op2_64;
  write_RMW_virtual_qword(sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADD_EqIdR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  op1_64 = BX_READ_64BIT_REG(i->rm());
  op2_64 = (Bit32s) i->Id();
  sum_64 = op1_64 + op2_64;
  BX_WRITE_64BIT_REG(i->rm(), sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADC_EqIdM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = (Bit32s) i->Id();
  sum_64 = op1_64 + op2_64 + getB_CF();
  write_RMW_virtual_qword(sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::ADC_EqIdR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, sum_64;

  op1_64 = BX_READ_64BIT_REG(i->rm());
  op2_64 = (Bit32s) i->Id();
  sum_64 = op1_64 + op2_64 + getB_CF();
  BX_WRITE_64BIT_REG(i->rm(), sum_64);

  SET_FLAGS_OSZAPC_ADD_64(op1_64, op2_64, sum_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SUB_EqIdM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  /* pointer, segment address pair */
  op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - op2_64;
  write_RMW_virtual_qword(diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::SUB_EqIdR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = BX_READ_64BIT_REG(i->rm());
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - op2_64;
  BX_WRITE_64BIT_REG(i->rm(), diff_64);

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMP_EqIdM(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  op1_64 = read_virtual_qword_64(i->seg(), eaddr);
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - op2_64;

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMP_EqIdR(bxInstruction_c *i)
{
  Bit64u op1_64, op2_64, diff_64;

  op1_64 = BX_READ_64BIT_REG(i->rm());
  op2_64 = (Bit32s) i->Id();
  diff_64 = op1_64 - op2_64;

  SET_FLAGS_OSZAPC_SUB_64(op1_64, op2_64, diff_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::NEG_EqM(bxInstruction_c *i)
{
  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  Bit64u op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op1_64 = - (Bit64s)(op1_64);
  write_RMW_virtual_qword(op1_64);

  SET_FLAGS_OSZAPC_SUB_64(0, -op1_64, op1_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::NEG_EqR(bxInstruction_c *i)
{
  Bit64u op1_64 = BX_READ_64BIT_REG(i->rm());
  op1_64 = - (Bit64s)(op1_64);
  BX_WRITE_64BIT_REG(i->rm(), op1_64);

  SET_FLAGS_OSZAPC_SUB_64(0, -op1_64, op1_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::INC_EqM(bxInstruction_c *i)
{
  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  Bit64u op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op1_64++;
  write_RMW_virtual_qword(op1_64);

  SET_FLAGS_OSZAP_ADD_64(op1_64 - 1, 0, op1_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::INC_EqR(bxInstruction_c *i)
{
  Bit64u rrx = ++BX_READ_64BIT_REG(i->rm());
  SET_FLAGS_OSZAP_ADD_64(rrx - 1, 0, rrx);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::DEC_EqM(bxInstruction_c *i)
{
  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  Bit64u op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op1_64--;
  write_RMW_virtual_qword(op1_64);

  SET_FLAGS_OSZAP_SUB_64(op1_64 + 1, 0, op1_64);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::DEC_EqR(bxInstruction_c *i)
{
  Bit64u rrx = --BX_READ_64BIT_REG(i->rm());
  SET_FLAGS_OSZAP_SUB_64(rrx + 1, 0, rrx);

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMPXCHG_EqGqM(bxInstruction_c *i)
{
  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  Bit64u op1_64 = read_RMW_virtual_qword_64(i->seg(), eaddr);
  Bit64u diff_64 = RAX - op1_64;
  SET_FLAGS_OSZAPC_SUB_64(RAX, op1_64, diff_64);

  if (diff_64 == 0) {  // if accumulator == dest
    // dest <-- src
    write_RMW_virtual_qword(BX_READ_64BIT_REG(i->nnn()));
  }
  else {
    // accumulator <-- dest
    RAX = op1_64;
  }

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMPXCHG_EqGqR(bxInstruction_c *i)
{
  Bit64u op1_64 = BX_READ_64BIT_REG(i->rm());
  Bit64u diff_64 = RAX - op1_64;
  SET_FLAGS_OSZAPC_SUB_64(RAX, op1_64, diff_64);

  if (diff_64 == 0) {  // if accumulator == dest
    // dest <-- src
    BX_WRITE_64BIT_REG(i->rm(), BX_READ_64BIT_REG(i->nnn()));
  }
  else {
    // accumulator <-- dest
    RAX = op1_64;
  }

  BX_NEXT_INSTR(i);
}

BX_INSF_TYPE BX_CPP_AttrRegparmN(1) BX_CPU_C::CMPXCHG16B(bxInstruction_c *i)
{
  Bit64u op1_64_lo, op1_64_hi, diff;

  bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

  bx_address laddr = get_laddr64(i->seg(), eaddr);

  if (laddr & 0xf) {
    BX_ERROR(("CMPXCHG16B: not aligned memory location (#GP)"));
    exception(BX_GP_EXCEPTION, 0);
  }

  // check write permission for following write
  op1_64_lo = read_RMW_virtual_qword_64(i->seg(), eaddr);
  op1_64_hi = read_RMW_virtual_qword_64(i->seg(), (eaddr + 8) & i->asize_mask());

  diff  = RAX - op1_64_lo;
  diff |= RDX - op1_64_hi;

  if (diff == 0) {  // if accumulator == dest
    // dest <-- src (RCX:RBX)
    write_RMW_virtual_qword(RCX);
    // write permissions already checked by read_RMW_virtual_qword_64
    write_virtual_qword_64(i->seg(), eaddr, RBX);
    assert_ZF();
  }
  else {
    clear_ZF();
    // accumulator <-- dest
    RAX = op1_64_lo;
    RDX = op1_64_hi;
  }

  BX_NEXT_INSTR(i);
}

#endif /* if BX_SUPPORT_X86_64 */
