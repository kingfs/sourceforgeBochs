/////////////////////////////////////////////////////////////////////////
// $Id$
/////////////////////////////////////////////////////////////////////////
//
//   Copyright (c) 2008-2013 Stanislav Shwartsman
//          Written by Stanislav Shwartsman [sshwarts at sourceforge net]
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
//
/////////////////////////////////////////////////////////////////////////

/* bx_define_opcode is a macro with the following fields:
 *   - Opcode name
 *   - Opcode execution function (/m form)
 *   - Opcode execution function (/r form)
 *   - x86 ISA extensions that enable this instruction
 *   - source for instruction destination register
 *   - source for instruction src1 register
 *   - source for instruction src2 register
 *   - source for instruction src3 register
 *   - special attributes (PREPARE_SSE, PREPARE_AVX and etc)
 *
 * in case of complex /m form instruction (load+op) /m form execution function
 * directly calls the /r form.
 */

/* Codes for Addressing Method:
 * ---------------------------
 * A  - Direct address. The instruction has no ModR/M byte; the address
 *      of the operand is encoded in the instruction; and no base register,
 *      index register, or scaling factor can be applied.
 * C  - The reg field of the ModR/M byte selects a control register.
 * D  - The reg field of the ModR/M byte selects a debug register.
 * E  - A ModR/M byte follows the opcode and specifies the operand. The
 *      operand is either a general-purpose register or a memory address.
 *      In case of the register operand, the R/M field of the ModR/M byte
 *      selects a general register.
 * F  - Flags Register.
 * G  - The reg field of the ModR/M byte selects a general register.
 * I  - Immediate data. The operand value is encoded in subsequent bytes of
 *      the instruction.
 * J  - The instruction contains a relative offset to be added to the
 *      instruction pointer register.
 * M  - The ModR/M byte may refer only to memory.
 * N  - The R/M field of the ModR/M byte selects a packed-quadword MMX
        technology register.
 * O  - The instruction has no ModR/M byte; the offset of the operand is
 *      coded as a word or double word (depending on address size attribute)
 *      in the instruction. No base register, index register, or scaling
 *      factor can be applied.
 * P  - The reg field of the ModR/M byte selects a packed quadword MMX
 *      technology register.
 * Q  - A ModR/M byte follows the opcode and specifies the operand. The
 *      operand is either an MMX technology register or a memory address.
 *      If it is a memory address, the address is computed from a segment
 *      register and any of the following values: a base register, an
 *      index register, a scaling factor, and a displacement.
 * R  - The mod field of the ModR/M byte may refer only to a general register.
 * S  - The reg field of the ModR/M byte selects a segment register.
 * T  - The reg field of the ModR/M byte selects a test register.
 * U  - The R/M field of the ModR/M byte selects a 128-bit XMM/256-bit YMM register.
 * V  - The reg field of the ModR/M byte selects a 128-bit XMM/256-bit YMM register.
 * W  - A ModR/M byte follows the opcode and specifies the operand. The
 *      operand is either a 128-bit XMM/256-bit YMM register or a memory address.
 *      If it is a memory address, the address is computed from a segment
 *      register and any of the following values: a base register, an
 *      index register, a scaling factor, and a displacement.
 * X  - Memory addressed by the DS:rSI register pair.
 * Y  - Memory addressed by the ES:rDI register pair.
 */

/*
 * Codes for Operand Type:
 * ----------------------
 * b  - Byte, regardless of operand-size attribute.
 * w  - Word, regardless of operand-size attribute.
 * d  - Doubleword, regardless of operand-size attribute.
 * dq - Double-quadword, regardless of operand-size attribute.
 * p  - 32-bit or 48-bit pointer, depending on operand-size attribute.
 * pd - 128-bit/256-bit packed double-precision floating-point data.
 * pi - Quadword MMX technology register (packed integer)
 * ps - 128-bit/256-bit packed single-precision floating-point data.
 * q  - Quadword, regardless of operand-size attribute.
 * s  - 6-byte or 10-byte pseudo-descriptor.
 * si - Doubleword integer register (scalar integer)
 * ss - Scalar element of a packed single-precision floating data.
 * sd - Scalar element of a packed double-precision floating data.
 * v  - Word, doubleword or quadword, depending on operand-size attribute.
 */

bx_define_opcode(BX_IA_ERROR, &BX_CPU_C::BxError, &BX_CPU_C::BxError, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
#if BX_SUPPORT_HANDLERS_CHAINING_SPEEDUPS
bx_define_opcode(BX_INSERTED_OPCODE, &BX_CPU_C::BxError, &BX_CPU_C::BxError, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
#endif

bx_define_opcode(BX_IA_AAA, NULL, &BX_CPU_C::AAA, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AAD, NULL, &BX_CPU_C::AAD, 0, OP_Ib, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AAM, NULL, &BX_CPU_C::AAM, 0, OP_Ib, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AAS, NULL, &BX_CPU_C::AAS, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DAA, NULL, &BX_CPU_C::DAA, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DAS, NULL, &BX_CPU_C::DAS, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_EbGb, &BX_CPU_C::ADC_EbGbM, &BX_CPU_C::ADC_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EbGb, &BX_CPU_C::AND_EbGbM, &BX_CPU_C::AND_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_EbGb, &BX_CPU_C::ADD_EbGbM, &BX_CPU_C::ADD_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EbGb, &BX_CPU_C::CMP_EbGbM, &BX_CPU_C::CMP_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EbGb, &BX_CPU_C::OR_EbGbM, &BX_CPU_C::OR_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EbGb, &BX_CPU_C::SBB_EbGbM, &BX_CPU_C::SBB_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EbGb, &BX_CPU_C::SUB_EbGbM, &BX_CPU_C::SUB_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EbGb, &BX_CPU_C::TEST_EbGbM, &BX_CPU_C::TEST_EbGbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EbGb, &BX_CPU_C::XOR_EbGbM, &BX_CPU_C::XOR_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_EwGw, &BX_CPU_C::ADC_EwGwM, &BX_CPU_C::ADC_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_EwGw, &BX_CPU_C::ADD_EwGwM, &BX_CPU_C::ADD_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EwGw, &BX_CPU_C::AND_EwGwM, &BX_CPU_C::AND_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EwGw, &BX_CPU_C::CMP_EwGwM, &BX_CPU_C::CMP_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EwGw, &BX_CPU_C::OR_EwGwM, &BX_CPU_C::OR_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EwGw, &BX_CPU_C::SBB_EwGwM, &BX_CPU_C::SBB_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EwGw, &BX_CPU_C::SUB_EwGwM, &BX_CPU_C::SUB_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EwGw, &BX_CPU_C::TEST_EwGwM, &BX_CPU_C::TEST_EwGwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EwGw, &BX_CPU_C::XOR_EwGwM, &BX_CPU_C::XOR_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_EdGd, &BX_CPU_C::ADC_EdGdM, &BX_CPU_C::ADC_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_EdGd, &BX_CPU_C::ADD_EdGdM, &BX_CPU_C::ADD_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EdGd, &BX_CPU_C::AND_EdGdM, &BX_CPU_C::AND_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EdGd, &BX_CPU_C::CMP_EdGdM, &BX_CPU_C::CMP_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EdGd, &BX_CPU_C::OR_EdGdM, &BX_CPU_C::OR_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EdGd, &BX_CPU_C::SBB_EdGdM, &BX_CPU_C::SBB_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EdGd, &BX_CPU_C::SUB_EdGdM, &BX_CPU_C::SUB_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EdGd, &BX_CPU_C::TEST_EdGdM, &BX_CPU_C::TEST_EdGdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EdGd, &BX_CPU_C::XOR_EdGdM, &BX_CPU_C::XOR_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_ALIb, NULL, &BX_CPU_C::ADC_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_ALIb, NULL, &BX_CPU_C::ADD_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_ALIb, NULL, &BX_CPU_C::AND_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_ALIb, NULL, &BX_CPU_C::CMP_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_ALIb, NULL, &BX_CPU_C::OR_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_ALIb, NULL, &BX_CPU_C::SBB_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_ALIb, NULL, &BX_CPU_C::SUB_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_ALIb, NULL, &BX_CPU_C::TEST_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_ALIb, NULL, &BX_CPU_C::XOR_EbIbR, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_AXIw, NULL, &BX_CPU_C::ADC_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_AXIw, NULL, &BX_CPU_C::ADD_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_AXIw, NULL, &BX_CPU_C::AND_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_AXIw, NULL, &BX_CPU_C::CMP_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_AXIw, NULL, &BX_CPU_C::OR_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_AXIw, NULL, &BX_CPU_C::SBB_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_AXIw, NULL, &BX_CPU_C::SUB_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_AXIw, NULL, &BX_CPU_C::TEST_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_AXIw, NULL, &BX_CPU_C::XOR_EwIwR, 0, OP_AXReg, OP_Iw, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_EAXId, NULL, &BX_CPU_C::ADC_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_EAXId, NULL, &BX_CPU_C::ADD_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EAXId, NULL, &BX_CPU_C::AND_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EAXId, NULL, &BX_CPU_C::CMP_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EAXId, NULL, &BX_CPU_C::OR_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EAXId, NULL, &BX_CPU_C::SBB_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EAXId, NULL, &BX_CPU_C::SUB_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EAXId, NULL, &BX_CPU_C::TEST_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EAXId, NULL, &BX_CPU_C::XOR_EdIdR, 0, OP_EAXReg, OP_Id, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADD_EbIb, &BX_CPU_C::ADD_EbIbM, &BX_CPU_C::ADD_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EbIb, &BX_CPU_C::OR_EbIbM, &BX_CPU_C::OR_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_EbIb, &BX_CPU_C::ADC_EbIbM, &BX_CPU_C::ADC_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EbIb, &BX_CPU_C::SBB_EbIbM, &BX_CPU_C::SBB_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EbIb, &BX_CPU_C::AND_EbIbM, &BX_CPU_C::AND_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EbIb, &BX_CPU_C::SUB_EbIbM, &BX_CPU_C::SUB_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EbIb, &BX_CPU_C::XOR_EbIbM, &BX_CPU_C::XOR_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EbIb, &BX_CPU_C::TEST_EbIbM, &BX_CPU_C::TEST_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EbIb, &BX_CPU_C::CMP_EbIbM, &BX_CPU_C::CMP_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADD_EwIw, &BX_CPU_C::ADD_EwIwM, &BX_CPU_C::ADD_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EwIw, &BX_CPU_C::OR_EwIwM, &BX_CPU_C::OR_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_EwIw, &BX_CPU_C::ADC_EwIwM, &BX_CPU_C::ADC_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EwIw, &BX_CPU_C::SBB_EwIwM, &BX_CPU_C::SBB_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EwIw, &BX_CPU_C::AND_EwIwM, &BX_CPU_C::AND_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EwIw, &BX_CPU_C::SUB_EwIwM, &BX_CPU_C::SUB_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EwIw, &BX_CPU_C::XOR_EwIwM, &BX_CPU_C::XOR_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EwIw, &BX_CPU_C::TEST_EwIwM, &BX_CPU_C::TEST_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EwIw, &BX_CPU_C::CMP_EwIwM, &BX_CPU_C::CMP_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADD_EdId, &BX_CPU_C::ADD_EdIdM, &BX_CPU_C::ADD_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EdId, &BX_CPU_C::OR_EdIdM, &BX_CPU_C::OR_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_EdId, &BX_CPU_C::ADC_EdIdM, &BX_CPU_C::ADC_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EdId, &BX_CPU_C::SBB_EdIdM, &BX_CPU_C::SBB_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EdId, &BX_CPU_C::AND_EdIdM, &BX_CPU_C::AND_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EdId, &BX_CPU_C::SUB_EdIdM, &BX_CPU_C::SUB_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EdId, &BX_CPU_C::XOR_EdIdM, &BX_CPU_C::XOR_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EdId, &BX_CPU_C::TEST_EdIdM, &BX_CPU_C::TEST_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EdId, &BX_CPU_C::CMP_EdIdM, &BX_CPU_C::CMP_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADD_GbEb, &BX_CPU_C::ADD_GbEbM, &BX_CPU_C::ADD_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_GbEb, &BX_CPU_C::OR_GbEbM, &BX_CPU_C::OR_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_GbEb, &BX_CPU_C::ADC_GbEbM, &BX_CPU_C::ADC_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_GbEb, &BX_CPU_C::SBB_GbEbM, &BX_CPU_C::SBB_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_GbEb, &BX_CPU_C::AND_GbEbM, &BX_CPU_C::AND_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_GbEb, &BX_CPU_C::SUB_GbEbM, &BX_CPU_C::SUB_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_GbEb, &BX_CPU_C::XOR_GbEbM, &BX_CPU_C::XOR_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_GbEb, &BX_CPU_C::CMP_GbEbM, &BX_CPU_C::CMP_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_GwEw, &BX_CPU_C::ADC_GwEwM, &BX_CPU_C::ADC_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_GwEw, &BX_CPU_C::ADD_GwEwM, &BX_CPU_C::ADD_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_GwEw, &BX_CPU_C::AND_GwEwM, &BX_CPU_C::AND_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_GwEw, &BX_CPU_C::CMP_GwEwM, &BX_CPU_C::CMP_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_GwEw, &BX_CPU_C::OR_GwEwM, &BX_CPU_C::OR_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_GwEw, &BX_CPU_C::SBB_GwEwM, &BX_CPU_C::SBB_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_GwEw, &BX_CPU_C::SUB_GwEwM, &BX_CPU_C::SUB_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_GwEw, &BX_CPU_C::XOR_GwEwM, &BX_CPU_C::XOR_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADC_GdEd, &BX_CPU_C::ADC_GdEdM, &BX_CPU_C::ADC_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADD_GdEd, &BX_CPU_C::ADD_GdEdM, &BX_CPU_C::ADD_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_GdEd, &BX_CPU_C::AND_GdEdM, &BX_CPU_C::AND_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_GdEd, &BX_CPU_C::CMP_GdEdM, &BX_CPU_C::CMP_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_GdEd, &BX_CPU_C::OR_GdEdM, &BX_CPU_C::OR_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_GdEd, &BX_CPU_C::SBB_GdEdM, &BX_CPU_C::SBB_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_GdEd, &BX_CPU_C::SUB_GdEdM, &BX_CPU_C::SUB_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_GdEd, &BX_CPU_C::XOR_GdEdM, &BX_CPU_C::XOR_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_INC_Eb, &BX_CPU_C::INC_EbM, &BX_CPU_C::INC_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_INC_Ew, &BX_CPU_C::INC_EwM, &BX_CPU_C::INC_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_INC_Ed, &BX_CPU_C::INC_EdM, &BX_CPU_C::INC_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_DEC_Eb, &BX_CPU_C::DEC_EbM, &BX_CPU_C::DEC_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DEC_Ew, &BX_CPU_C::DEC_EwM, &BX_CPU_C::DEC_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DEC_Ed, &BX_CPU_C::DEC_EdM, &BX_CPU_C::DEC_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BSF_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::BSF_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BSR_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::BSR_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BSF_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BSF_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BSR_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BSR_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BTC_EwGw, &BX_CPU_C::BTC_EwGwM, &BX_CPU_C::BTC_EwGwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTR_EwGw, &BX_CPU_C::BTR_EwGwM, &BX_CPU_C::BTR_EwGwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTS_EwGw, &BX_CPU_C::BTS_EwGwM, &BX_CPU_C::BTS_EwGwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BTC_EdGd, &BX_CPU_C::BTC_EdGdM, &BX_CPU_C::BTC_EdGdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTR_EdGd, &BX_CPU_C::BTR_EdGdM, &BX_CPU_C::BTR_EdGdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTS_EdGd, &BX_CPU_C::BTS_EdGdM, &BX_CPU_C::BTS_EdGdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BTC_EwIb, &BX_CPU_C::BTC_EwIbM, &BX_CPU_C::BTC_EwIbR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTR_EwIb, &BX_CPU_C::BTR_EwIbM, &BX_CPU_C::BTR_EwIbR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTS_EwIb, &BX_CPU_C::BTS_EwIbM, &BX_CPU_C::BTS_EwIbR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BTC_EdIb, &BX_CPU_C::BTC_EdIbM, &BX_CPU_C::BTC_EdIbR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTR_EdIb, &BX_CPU_C::BTR_EdIbM, &BX_CPU_C::BTR_EdIbR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTS_EdIb, &BX_CPU_C::BTS_EdIbM, &BX_CPU_C::BTS_EdIbR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BT_EwIb, &BX_CPU_C::BT_EwIbM, &BX_CPU_C::BT_EwIbR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BT_EdIb, &BX_CPU_C::BT_EdIbM, &BX_CPU_C::BT_EdIbR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BT_EwGw, &BX_CPU_C::BT_EwGwM, &BX_CPU_C::BT_EwGwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BT_EdGd, &BX_CPU_C::BT_EdGdM, &BX_CPU_C::BT_EdGdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BOUND_GwMa, &BX_CPU_C::BOUND_GwMa, &BX_CPU_C::BxError, 0, OP_Gw, OP_M, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BOUND_GdMa, &BX_CPU_C::BOUND_GdMa, &BX_CPU_C::BxError, 0, OP_Gd, OP_M, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ARPL_EwGw, &BX_CPU_C::ARPL_EwGw, &BX_CPU_C::ARPL_EwGw, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_CALL_Ed, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CALL_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL_Ew, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CALL_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL_Jd, NULL, &BX_CPU_C::CALL_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL_Jw, NULL, &BX_CPU_C::CALL_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL16_Ap, NULL, &BX_CPU_C::CALL16_Ap, 0, OP_Iw, OP_Iw, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL32_Ap, NULL, &BX_CPU_C::CALL32_Ap, 0, OP_Id, OP_Iw, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL16_Ep, &BX_CPU_C::CALL16_Ep, &BX_CPU_C::BxError, 0, OP_M, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL32_Ep, &BX_CPU_C::CALL32_Ep, &BX_CPU_C::BxError, 0, OP_M, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_CBW, NULL, &BX_CPU_C::CBW, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CDQ, NULL, &BX_CPU_C::CDQ, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CLC, NULL, &BX_CPU_C::CLC, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CLD, NULL, &BX_CPU_C::CLD, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CLFLUSH, &BX_CPU_C::CLFLUSH, &BX_CPU_C::BxError, BX_ISA_CLFLUSH, OP_Mb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CLI, NULL, &BX_CPU_C::CLI, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CLTS, NULL, &BX_CPU_C::CLTS, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CMC, NULL, &BX_CPU_C::CMC, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CWD, NULL, &BX_CPU_C::CWD, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CWDE, NULL, &BX_CPU_C::CWDE, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ENTER16_IwIb, NULL, &BX_CPU_C::ENTER16_IwIb, 0, OP_Iw, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ENTER32_IwIb, NULL, &BX_CPU_C::ENTER32_IwIb, 0, OP_Iw, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_HLT, NULL, &BX_CPU_C::HLT, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_IMUL_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::IMUL_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_GdEdId, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::IMUL_GdEdIdR, 0, OP_Gd, OP_Ed, OP_Id, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::IMUL_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_GwEwIw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::IMUL_GwEwIwR, 0, OP_Gw, OP_Ew, OP_Iw, OP_NONE, 0)

bx_define_opcode(BX_IA_IN_ALDX, NULL, &BX_CPU_C::IN_ALDX, 0, OP_ALReg, OP_DXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IN_ALIb, NULL, &BX_CPU_C::IN_ALIb, 0, OP_ALReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IN_AXDX, NULL, &BX_CPU_C::IN_AXDX, 0, OP_AXReg, OP_DXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IN_AXIb, NULL, &BX_CPU_C::IN_AXIb, 0, OP_AXReg, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IN_EAXDX, NULL, &BX_CPU_C::IN_EAXDX, 0, OP_EAXReg, OP_DXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IN_EAXIb, NULL, &BX_CPU_C::IN_EAXIb, 0, OP_EAXReg, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_OUT_DXAL, NULL, &BX_CPU_C::OUT_DXAL, 0, OP_DXReg, OP_ALReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OUT_DXAX, NULL, &BX_CPU_C::OUT_DXAX, 0, OP_DXReg, OP_AXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OUT_DXEAX, NULL, &BX_CPU_C::OUT_DXEAX, 0, OP_DXReg, OP_EAXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OUT_IbAL, NULL, &BX_CPU_C::OUT_IbAL, 0, OP_Ib, OP_ALReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OUT_IbAX, NULL, &BX_CPU_C::OUT_IbAX, 0, OP_Ib, OP_AXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OUT_IbEAX, NULL, &BX_CPU_C::OUT_IbEAX, 0, OP_Ib, OP_EAXReg, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_INT_Ib, NULL, &BX_CPU_C::INT_Ib, 0, OP_Ib, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_INT1, NULL, &BX_CPU_C::INT1, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_INT3, NULL, &BX_CPU_C::INT3, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_INTO, NULL, &BX_CPU_C::INTO, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_IRET16, NULL, &BX_CPU_C::IRET16, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_IRET32, NULL, &BX_CPU_C::IRET32, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_JMP_Ed, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::JMP_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP_Ew, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::JMP_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP_Jw, NULL, &BX_CPU_C::JMP_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP_Jd, NULL, &BX_CPU_C::JMP_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_JMP16_Ap, NULL, &BX_CPU_C::JMP_Ap, 0, OP_Iw, OP_Iw, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP32_Ap, NULL, &BX_CPU_C::JMP_Ap, 0, OP_Id, OP_Iw, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_JMP16_Ep, &BX_CPU_C::JMP16_Ep, &BX_CPU_C::BxError, 0, OP_M, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP32_Ep, &BX_CPU_C::JMP32_Ep, &BX_CPU_C::BxError, 0, OP_M, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_JCXZ_Jb, NULL, &BX_CPU_C::JCXZ_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JECXZ_Jb, NULL, &BX_CPU_C::JECXZ_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOP16_Jb, NULL, &BX_CPU_C::LOOP16_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOPE16_Jb, NULL, &BX_CPU_C::LOOPE16_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOPNE16_Jb, NULL, &BX_CPU_C::LOOPNE16_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOP32_Jb, NULL, &BX_CPU_C::LOOP32_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOPE32_Jb, NULL, &BX_CPU_C::LOOPE32_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOPNE32_Jb, NULL, &BX_CPU_C::LOOPNE32_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_JB_Jw, NULL, &BX_CPU_C::JB_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JBE_Jw, NULL, &BX_CPU_C::JBE_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JL_Jw, NULL, &BX_CPU_C::JL_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JLE_Jw, NULL, &BX_CPU_C::JLE_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNB_Jw, NULL, &BX_CPU_C::JNB_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNBE_Jw, NULL, &BX_CPU_C::JNBE_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNL_Jw, NULL, &BX_CPU_C::JNL_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNLE_Jw, NULL, &BX_CPU_C::JNLE_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNO_Jw, NULL, &BX_CPU_C::JNO_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNP_Jw, NULL, &BX_CPU_C::JNP_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNS_Jw, NULL, &BX_CPU_C::JNS_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNZ_Jw, NULL, &BX_CPU_C::JNZ_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JO_Jw, NULL, &BX_CPU_C::JO_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JP_Jw, NULL, &BX_CPU_C::JP_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JS_Jw, NULL, &BX_CPU_C::JS_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JZ_Jw, NULL, &BX_CPU_C::JZ_Jw, 0, OP_Jw, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_JB_Jd, NULL, &BX_CPU_C::JB_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JBE_Jd, NULL, &BX_CPU_C::JBE_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JL_Jd, NULL, &BX_CPU_C::JL_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JLE_Jd, NULL, &BX_CPU_C::JLE_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNB_Jd, NULL, &BX_CPU_C::JNB_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNBE_Jd, NULL, &BX_CPU_C::JNBE_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNL_Jd, NULL, &BX_CPU_C::JNL_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNLE_Jd, NULL, &BX_CPU_C::JNLE_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNO_Jd, NULL, &BX_CPU_C::JNO_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNP_Jd, NULL, &BX_CPU_C::JNP_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNS_Jd, NULL, &BX_CPU_C::JNS_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNZ_Jd, NULL, &BX_CPU_C::JNZ_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JO_Jd, NULL, &BX_CPU_C::JO_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JP_Jd, NULL, &BX_CPU_C::JP_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JS_Jd, NULL, &BX_CPU_C::JS_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JZ_Jd, NULL, &BX_CPU_C::JZ_Jd, 0, OP_Jd, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_SAHF, NULL, &BX_CPU_C::SAHF, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LAHF, NULL, &BX_CPU_C::LAHF, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_LDS_GdMp, &BX_CPU_C::LDS_GdMp, &BX_CPU_C::BxError, 0, OP_Gd, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LDS_GwMp, &BX_CPU_C::LDS_GwMp, &BX_CPU_C::BxError, 0, OP_Gw, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LES_GdMp, &BX_CPU_C::LES_GdMp, &BX_CPU_C::BxError, 0, OP_Gd, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LES_GwMp, &BX_CPU_C::LES_GwMp, &BX_CPU_C::BxError, 0, OP_Gw, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LFS_GdMp, &BX_CPU_C::LFS_GdMp, &BX_CPU_C::BxError, 0, OP_Gd, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LFS_GwMp, &BX_CPU_C::LFS_GwMp, &BX_CPU_C::BxError, 0, OP_Gw, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LSS_GdMp, &BX_CPU_C::LSS_GdMp, &BX_CPU_C::BxError, 0, OP_Gd, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LSS_GwMp, &BX_CPU_C::LSS_GwMp, &BX_CPU_C::BxError, 0, OP_Gw, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LGS_GdMp, &BX_CPU_C::LGS_GdMp, &BX_CPU_C::BxError, 0, OP_Gd, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LGS_GwMp, &BX_CPU_C::LGS_GwMp, &BX_CPU_C::BxError, 0, OP_Gw, OP_Mp, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_LAR_GwEw, &BX_CPU_C::LAR_GvEw, &BX_CPU_C::LAR_GvEw, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LSL_GwEw, &BX_CPU_C::LSL_GvEw, &BX_CPU_C::LSL_GvEw, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LAR_GdEw, &BX_CPU_C::LAR_GvEw, &BX_CPU_C::LAR_GvEw, 0, OP_Gd, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LSL_GdEw, &BX_CPU_C::LSL_GvEw, &BX_CPU_C::LSL_GvEw, 0, OP_Gd, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LEA_GdM, &BX_CPU_C::LEA_GdM, &BX_CPU_C::BxError, 0, OP_Gd, OP_Md, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LEA_GwM, &BX_CPU_C::LEA_GwM, &BX_CPU_C::BxError, 0, OP_Gw, OP_Mw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LEAVE16, NULL, &BX_CPU_C::LEAVE16, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LEAVE32, NULL, &BX_CPU_C::LEAVE32, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

// IDT/GDT/LDTR/TR access - keep NNN for VMX
bx_define_opcode(BX_IA_SIDT_Ms, &BX_CPU_C::SIDT_Ms, &BX_CPU_C::BxError, 0, OP_M, BX_SRC_NNN, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_LIDT_Ms, &BX_CPU_C::LIDT_Ms, &BX_CPU_C::BxError, 0, BX_SRC_NNN, OP_M, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_SGDT_Ms, &BX_CPU_C::SGDT_Ms, &BX_CPU_C::BxError, 0, OP_M, BX_SRC_NNN, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_LGDT_Ms, &BX_CPU_C::LGDT_Ms, &BX_CPU_C::BxError, 0, BX_SRC_NNN, OP_M, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_SLDT_Ew, &BX_CPU_C::SLDT_Ew, &BX_CPU_C::SLDT_Ew, 0, OP_M, BX_SRC_NNN, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_LLDT_Ew, &BX_CPU_C::LLDT_Ew, &BX_CPU_C::LLDT_Ew, 0, BX_SRC_NNN, OP_M, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_STR_Ew, &BX_CPU_C::STR_Ew, &BX_CPU_C::STR_Ew, 0, OP_M, BX_SRC_NNN, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_LTR_Ew, &BX_CPU_C::LTR_Ew, &BX_CPU_C::LTR_Ew, 0, BX_SRC_NNN, OP_M, OP_NONE, OP_NONE, 0) // FIXME disasm
// IDT/GDT/LDTR/TR access - keep NNN for VMX

bx_define_opcode(BX_IA_SMSW_Ew, &BX_CPU_C::SMSW_EwM, &BX_CPU_C::SMSW_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LMSW_Ew, &BX_CPU_C::LMSW_Ew, &BX_CPU_C::LMSW_Ew, 0, OP_NONE, OP_Ew, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_CR0Rd, NULL, &BX_CPU_C::MOV_CR0Rd, 0, OP_Cd, OP_Ed, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_CR2Rd, NULL, &BX_CPU_C::MOV_CR2Rd, 0, OP_Cd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_CR3Rd, NULL, &BX_CPU_C::MOV_CR3Rd, 0, OP_Cd, OP_Ed, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_CR4Rd, NULL, &BX_CPU_C::MOV_CR4Rd, BX_ISA_PENTIUM, OP_Cd, OP_Ed, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_RdCR0, NULL, &BX_CPU_C::MOV_RdCR0, 0, OP_Ed, OP_Cd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_RdCR2, NULL, &BX_CPU_C::MOV_RdCR2, 0, OP_Ed, OP_Cd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_RdCR3, NULL, &BX_CPU_C::MOV_RdCR3, 0, OP_Ed, OP_Cd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_RdCR4, NULL, &BX_CPU_C::MOV_RdCR4, BX_ISA_PENTIUM, OP_Ed, OP_Cd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_RdDd, NULL, &BX_CPU_C::MOV_RdDd, 0, OP_Ed, OP_Dd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_DdRd, NULL, &BX_CPU_C::MOV_DdRd, 0, OP_Dd, OP_Ed, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_MOV_EbIb, &BX_CPU_C::MOV_EbIbM, &BX_CPU_C::MOV_EbIbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EdId, &BX_CPU_C::MOV_EdIdM, &BX_CPU_C::MOV_EdIdR, 0, OP_Ed, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EwIw, &BX_CPU_C::MOV_EwIwM, &BX_CPU_C::MOV_EwIwR, 0, OP_Ew, OP_Iw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_GbEb, &BX_CPU_C::MOV_GbEbM, &BX_CPU_C::MOV_GbEbR, 0, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EbGb, &BX_CPU_C::MOV_EbGbM, &BX_CPU_C::MOV_GbEbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_GwEw, &BX_CPU_C::MOV_GwEwM, &BX_CPU_C::MOV_GwEwR, 0, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EwGw, &BX_CPU_C::MOV_EwGwM, &BX_CPU_C::MOV_GwEwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV32_GdEd, &BX_CPU_C::MOV32_GdEdM, &BX_CPU_C::MOV_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV32_EdGd, &BX_CPU_C::MOV32_EdGdM, &BX_CPU_C::MOV_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EwSw, &BX_CPU_C::MOV_EwSwM, &BX_CPU_C::MOV_EwSwR, 0, OP_Ew, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_SwEw, &BX_CPU_C::MOV_SwEw, &BX_CPU_C::MOV_SwEw, 0, OP_Sw, OP_Ew, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_MOV_ALOd, NULL, &BX_CPU_C::MOV_ALOd, 0, OP_ALReg, OP_Od, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_AXOd, NULL, &BX_CPU_C::MOV_AXOd, 0, OP_AXReg, OP_Od, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EAXOd, NULL, &BX_CPU_C::MOV_EAXOd, 0, OP_EAXReg, OP_Od, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_OdAL, NULL, &BX_CPU_C::MOV_OdAL, 0, OP_Od, OP_ALReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_OdAX, NULL, &BX_CPU_C::MOV_OdAX, 0, OP_Od, OP_AXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_OdEAX, NULL, &BX_CPU_C::MOV_OdEAX, 0, OP_Od, OP_EAXReg, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_MOVSX_GdEb, &BX_CPU_C::MOVSX_GdEbM, &BX_CPU_C::MOVSX_GdEbR, 0, OP_Gd, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVSX_GdEw, &BX_CPU_C::MOVSX_GdEwM, &BX_CPU_C::MOVSX_GdEwR, 0, OP_Gd, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVSX_GwEb, &BX_CPU_C::MOVSX_GwEbM, &BX_CPU_C::MOVSX_GwEbR, 0, OP_Gw, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVZX_GdEb, &BX_CPU_C::MOVZX_GdEbM, &BX_CPU_C::MOVZX_GdEbR, 0, OP_Gd, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVZX_GdEw, &BX_CPU_C::MOVZX_GdEwM, &BX_CPU_C::MOVZX_GdEwR, 0, OP_Gd, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVZX_GwEb, &BX_CPU_C::MOVZX_GwEbM, &BX_CPU_C::MOVZX_GwEbR, 0, OP_Gw, OP_Eb, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_NOP, &BX_CPU_C::NOP, &BX_CPU_C::NOP, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PAUSE, NULL, &BX_CPU_C::PAUSE, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_POP_Ew, &BX_CPU_C::POP_EwM, &BX_CPU_C::POP_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP_Ed, &BX_CPU_C::POP_EdM, &BX_CPU_C::POP_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_POP16_DS, NULL, &BX_CPU_C::POP16_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP16_ES, NULL, &BX_CPU_C::POP16_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP16_FS, NULL, &BX_CPU_C::POP16_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP16_GS, NULL, &BX_CPU_C::POP16_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP16_SS, NULL, &BX_CPU_C::POP16_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP32_DS, NULL, &BX_CPU_C::POP32_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP32_ES, NULL, &BX_CPU_C::POP32_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP32_FS, NULL, &BX_CPU_C::POP32_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP32_GS, NULL, &BX_CPU_C::POP32_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP32_SS, NULL, &BX_CPU_C::POP32_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POPA16, NULL, &BX_CPU_C::POPA16, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POPA32, NULL, &BX_CPU_C::POPA32, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POPF_Fd, NULL, &BX_CPU_C::POPF_Fd, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_POPF_Fw, NULL, &BX_CPU_C::POPF_Fw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_PUSH_Ew, &BX_CPU_C::PUSH_EwM, &BX_CPU_C::PUSH_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH_Ed, &BX_CPU_C::PUSH_EdM, &BX_CPU_C::PUSH_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_PUSH_Id, NULL, &BX_CPU_C::PUSH_Id, 0, OP_Id, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH_Iw, NULL, &BX_CPU_C::PUSH_Iw, 0, OP_Iw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH16_CS, NULL, &BX_CPU_C::PUSH16_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH16_DS, NULL, &BX_CPU_C::PUSH16_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH16_ES, NULL, &BX_CPU_C::PUSH16_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH16_FS, NULL, &BX_CPU_C::PUSH16_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH16_GS, NULL, &BX_CPU_C::PUSH16_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH16_SS, NULL, &BX_CPU_C::PUSH16_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH32_CS, NULL, &BX_CPU_C::PUSH32_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH32_DS, NULL, &BX_CPU_C::PUSH32_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH32_ES, NULL, &BX_CPU_C::PUSH32_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH32_FS, NULL, &BX_CPU_C::PUSH32_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH32_GS, NULL, &BX_CPU_C::PUSH32_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH32_SS, NULL, &BX_CPU_C::PUSH32_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSHA16, NULL, &BX_CPU_C::PUSHA16, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSHA32, NULL, &BX_CPU_C::PUSHA32, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSHF_Fd, NULL, &BX_CPU_C::PUSHF_Fd, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSHF_Fw, NULL, &BX_CPU_C::PUSHF_Fw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_REP_CMPSB_XbYb, NULL, &BX_CPU_C::REP_CMPSB_XbYb, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_CMPSD_XdYd, NULL, &BX_CPU_C::REP_CMPSD_XdYd, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_CMPSW_XwYw, NULL, &BX_CPU_C::REP_CMPSW_XwYw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_INSB_YbDX, NULL, &BX_CPU_C::REP_INSB_YbDX, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_INSD_YdDX, NULL, &BX_CPU_C::REP_INSD_YdDX, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_INSW_YwDX, NULL, &BX_CPU_C::REP_INSW_YwDX, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_LODSB_ALXb, NULL, &BX_CPU_C::REP_LODSB_ALXb, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_LODSD_EAXXd, NULL, &BX_CPU_C::REP_LODSD_EAXXd, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_LODSW_AXXw, NULL, &BX_CPU_C::REP_LODSW_AXXw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_MOVSB_XbYb, NULL, &BX_CPU_C::REP_MOVSB_XbYb, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_MOVSD_XdYd, NULL, &BX_CPU_C::REP_MOVSD_XdYd, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_MOVSW_XwYw, NULL, &BX_CPU_C::REP_MOVSW_XwYw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_OUTSB_DXXb, NULL, &BX_CPU_C::REP_OUTSB_DXXb, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_OUTSD_DXXd, NULL, &BX_CPU_C::REP_OUTSD_DXXd, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_OUTSW_DXXw, NULL, &BX_CPU_C::REP_OUTSW_DXXw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_SCASB_ALXb, NULL, &BX_CPU_C::REP_SCASB_ALXb, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_SCASD_EAXXd, NULL, &BX_CPU_C::REP_SCASD_EAXXd, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_SCASW_AXXw, NULL, &BX_CPU_C::REP_SCASW_AXXw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_STOSB_YbAL, NULL, &BX_CPU_C::REP_STOSB_YbAL, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_STOSD_YdEAX, NULL, &BX_CPU_C::REP_STOSD_YdEAX, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_STOSW_YwAX, NULL, &BX_CPU_C::REP_STOSW_YwAX, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm

bx_define_opcode(BX_IA_RETfar16, NULL, &BX_CPU_C::RETfar16_Iw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETfar16_Iw, NULL, &BX_CPU_C::RETfar16_Iw, 0, OP_Iw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETfar32, NULL, &BX_CPU_C::RETfar32_Iw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETfar32_Iw, NULL, &BX_CPU_C::RETfar32_Iw, 0, OP_Iw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_RETnear16, NULL, &BX_CPU_C::RETnear16, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETnear16_Iw, NULL, &BX_CPU_C::RETnear16_Iw, 0, OP_Iw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETnear32, NULL, &BX_CPU_C::RETnear32, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETnear32_Iw, NULL, &BX_CPU_C::RETnear32_Iw, 0, OP_Iw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_NOT_Eb, &BX_CPU_C::NOT_EbM, &BX_CPU_C::NOT_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_NEG_Eb, &BX_CPU_C::NEG_EbM, &BX_CPU_C::NEG_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_NOT_Ew, &BX_CPU_C::NOT_EwM, &BX_CPU_C::NOT_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_NEG_Ew, &BX_CPU_C::NEG_EwM, &BX_CPU_C::NEG_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_NOT_Ed, &BX_CPU_C::NOT_EdM, &BX_CPU_C::NOT_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_NEG_Ed, &BX_CPU_C::NEG_EdM, &BX_CPU_C::NEG_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_Eb, &BX_CPU_C::ROL_EbM, &BX_CPU_C::ROL_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_Eb, &BX_CPU_C::ROR_EbM, &BX_CPU_C::ROR_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_Eb, &BX_CPU_C::RCL_EbM, &BX_CPU_C::RCL_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_Eb, &BX_CPU_C::RCR_EbM, &BX_CPU_C::RCR_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_Eb, &BX_CPU_C::SHL_EbM, &BX_CPU_C::SHL_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_Eb, &BX_CPU_C::SHR_EbM, &BX_CPU_C::SHR_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_Eb, &BX_CPU_C::SAR_EbM, &BX_CPU_C::SAR_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_Ew, &BX_CPU_C::ROL_EwM, &BX_CPU_C::ROL_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_Ew, &BX_CPU_C::ROR_EwM, &BX_CPU_C::ROR_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_Ew, &BX_CPU_C::RCL_EwM, &BX_CPU_C::RCL_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_Ew, &BX_CPU_C::RCR_EwM, &BX_CPU_C::RCR_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_Ew, &BX_CPU_C::SHL_EwM, &BX_CPU_C::SHL_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_Ew, &BX_CPU_C::SHR_EwM, &BX_CPU_C::SHR_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_Ew, &BX_CPU_C::SAR_EwM, &BX_CPU_C::SAR_EwR, 0, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_Ed, &BX_CPU_C::ROL_EdM, &BX_CPU_C::ROL_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_Ed, &BX_CPU_C::ROR_EdM, &BX_CPU_C::ROR_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_Ed, &BX_CPU_C::RCL_EdM, &BX_CPU_C::RCL_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_Ed, &BX_CPU_C::RCR_EdM, &BX_CPU_C::RCR_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_Ed, &BX_CPU_C::SHL_EdM, &BX_CPU_C::SHL_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_Ed, &BX_CPU_C::SHR_EdM, &BX_CPU_C::SHR_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_Ed, &BX_CPU_C::SAR_EdM, &BX_CPU_C::SAR_EdR, 0, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_EbIb, &BX_CPU_C::ROL_EbM, &BX_CPU_C::ROL_EbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_EbIb, &BX_CPU_C::ROR_EbM, &BX_CPU_C::ROR_EbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_EbIb, &BX_CPU_C::RCL_EbM, &BX_CPU_C::RCL_EbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_EbIb, &BX_CPU_C::RCR_EbM, &BX_CPU_C::RCR_EbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_EbIb, &BX_CPU_C::SHL_EbM, &BX_CPU_C::SHL_EbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_EbIb, &BX_CPU_C::SHR_EbM, &BX_CPU_C::SHR_EbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_EbIb, &BX_CPU_C::SAR_EbM, &BX_CPU_C::SAR_EbR, 0, OP_Eb, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_EwIb, &BX_CPU_C::ROL_EwM, &BX_CPU_C::ROL_EwR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_EwIb, &BX_CPU_C::ROR_EwM, &BX_CPU_C::ROR_EwR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_EwIb, &BX_CPU_C::RCL_EwM, &BX_CPU_C::RCL_EwR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_EwIb, &BX_CPU_C::RCR_EwM, &BX_CPU_C::RCR_EwR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_EwIb, &BX_CPU_C::SHL_EwM, &BX_CPU_C::SHL_EwR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_EwIb, &BX_CPU_C::SHR_EwM, &BX_CPU_C::SHR_EwR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_EwIb, &BX_CPU_C::SAR_EwM, &BX_CPU_C::SAR_EwR, 0, OP_Ew, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_EdIb, &BX_CPU_C::ROL_EdM, &BX_CPU_C::ROL_EdR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_EdIb, &BX_CPU_C::ROR_EdM, &BX_CPU_C::ROR_EdR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_EdIb, &BX_CPU_C::RCL_EdM, &BX_CPU_C::RCL_EdR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_EdIb, &BX_CPU_C::RCR_EdM, &BX_CPU_C::RCR_EdR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_EdIb, &BX_CPU_C::SHL_EdM, &BX_CPU_C::SHL_EdR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_EdIb, &BX_CPU_C::SHR_EdM, &BX_CPU_C::SHR_EdR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_EdIb, &BX_CPU_C::SAR_EdM, &BX_CPU_C::SAR_EdR, 0, OP_Ed, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_SETB_Eb, &BX_CPU_C::SETB_EbM, &BX_CPU_C::SETB_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETBE_Eb, &BX_CPU_C::SETBE_EbM, &BX_CPU_C::SETBE_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETL_Eb, &BX_CPU_C::SETL_EbM, &BX_CPU_C::SETL_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETLE_Eb, &BX_CPU_C::SETLE_EbM, &BX_CPU_C::SETLE_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNB_Eb, &BX_CPU_C::SETNB_EbM, &BX_CPU_C::SETNB_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNBE_Eb, &BX_CPU_C::SETNBE_EbM, &BX_CPU_C::SETNBE_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNL_Eb, &BX_CPU_C::SETNL_EbM, &BX_CPU_C::SETNL_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNLE_Eb, &BX_CPU_C::SETNLE_EbM, &BX_CPU_C::SETNLE_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNO_Eb, &BX_CPU_C::SETNO_EbM, &BX_CPU_C::SETNO_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNP_Eb, &BX_CPU_C::SETNP_EbM, &BX_CPU_C::SETNP_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNS_Eb, &BX_CPU_C::SETNS_EbM, &BX_CPU_C::SETNS_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETNZ_Eb, &BX_CPU_C::SETNZ_EbM, &BX_CPU_C::SETNZ_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETO_Eb, &BX_CPU_C::SETO_EbM, &BX_CPU_C::SETO_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETP_Eb, &BX_CPU_C::SETP_EbM, &BX_CPU_C::SETP_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETS_Eb, &BX_CPU_C::SETS_EbM, &BX_CPU_C::SETS_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SETZ_Eb, &BX_CPU_C::SETZ_EbM, &BX_CPU_C::SETZ_EbR, 0, OP_Eb, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_SHLD_EdGd, &BX_CPU_C::SHLD_EdGdM, &BX_CPU_C::SHLD_EdGdR, 0, OP_Ed, OP_Gd, OP_CLReg, OP_NONE, 0)
bx_define_opcode(BX_IA_SHLD_EdGdIb, &BX_CPU_C::SHLD_EdGdM, &BX_CPU_C::SHLD_EdGdR, 0, OP_Ed, OP_Gd, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_SHLD_EwGw, &BX_CPU_C::SHLD_EwGwM, &BX_CPU_C::SHLD_EwGwR, 0, OP_Ew, OP_Gw, OP_CLReg, OP_NONE, 0)
bx_define_opcode(BX_IA_SHLD_EwGwIb, &BX_CPU_C::SHLD_EwGwM, &BX_CPU_C::SHLD_EwGwR, 0, OP_Ew, OP_Gw, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRD_EdGd, &BX_CPU_C::SHRD_EdGdM, &BX_CPU_C::SHRD_EdGdR, 0, OP_Ed, OP_Gd, OP_CLReg, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRD_EdGdIb, &BX_CPU_C::SHRD_EdGdM, &BX_CPU_C::SHRD_EdGdR, 0, OP_Ed, OP_Gd, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRD_EwGw, &BX_CPU_C::SHRD_EwGwM, &BX_CPU_C::SHRD_EwGwR, 0, OP_Ew, OP_Gw, OP_CLReg, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRD_EwGwIb, &BX_CPU_C::SHRD_EwGwM, &BX_CPU_C::SHRD_EwGwR, 0, OP_Ew, OP_Gw, OP_Ib, OP_NONE, 0)

bx_define_opcode(BX_IA_RSM, NULL, &BX_CPU_C::RSM, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_SALC, NULL, &BX_CPU_C::SALC, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_STC, NULL, &BX_CPU_C::STC, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_STD, NULL, &BX_CPU_C::STD, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_STI, NULL, &BX_CPU_C::STI, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_MUL_ALEb, &BX_CPU_C::LOAD_Eb, &BX_CPU_C::MUL_ALEbR, 0, OP_ALReg, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_ALEb, &BX_CPU_C::LOAD_Eb, &BX_CPU_C::IMUL_ALEbR, 0, OP_ALReg, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DIV_ALEb, &BX_CPU_C::LOAD_Eb, &BX_CPU_C::DIV_ALEbR, 0, OP_ALReg, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IDIV_ALEb, &BX_CPU_C::LOAD_Eb, &BX_CPU_C::IDIV_ALEbR, 0, OP_ALReg, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MUL_AXEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::MUL_AXEwR, 0, OP_AXReg, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_AXEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::IMUL_AXEwR, 0, OP_AXReg, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DIV_AXEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::DIV_AXEwR, 0, OP_AXReg, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IDIV_AXEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::IDIV_AXEwR, 0, OP_AXReg, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MUL_EAXEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::MUL_EAXEdR, 0, OP_EAXReg, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_EAXEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::IMUL_EAXEdR, 0, OP_EAXReg, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DIV_EAXEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::DIV_EAXEdR, 0, OP_EAXReg, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IDIV_EAXEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::IDIV_EAXEdR, 0, OP_EAXReg, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VERR_Ew, &BX_CPU_C::VERR_Ew, &BX_CPU_C::VERR_Ew, 0, OP_NONE, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VERW_Ew, &BX_CPU_C::VERW_Ew, &BX_CPU_C::VERW_Ew, 0, OP_NONE, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XCHG_EbGb, &BX_CPU_C::XCHG_EbGbM, &BX_CPU_C::XCHG_EbGbR, 0, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XCHG_EwGw, &BX_CPU_C::XCHG_EwGwM, &BX_CPU_C::XCHG_EwGwR, 0, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XCHG_EdGd, &BX_CPU_C::XCHG_EdGdM, &BX_CPU_C::XCHG_EdGdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XCHG_RXAX, NULL, &BX_CPU_C::XCHG_RXAX, 0, OP_Ew, OP_AXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XCHG_ERXEAX, NULL, &BX_CPU_C::XCHG_ERXEAX, 0, OP_Ew, OP_EAXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XLAT, NULL, &BX_CPU_C::XLAT, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_SYSENTER, NULL, &BX_CPU_C::SYSENTER, BX_ISA_SYSENTER_SYSEXIT, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_SYSEXIT, NULL, &BX_CPU_C::SYSEXIT, BX_ISA_SYSENTER_SYSEXIT, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_MONITOR, &BX_CPU_C::BxError, &BX_CPU_C::MONITOR, BX_ISA_MONITOR_MWAIT, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MWAIT, &BX_CPU_C::BxError, &BX_CPU_C::MWAIT, BX_ISA_MONITOR_MWAIT, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_FWAIT, NULL, &BX_CPU_C::FWAIT, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_FPU
bx_define_opcode(BX_IA_FLD_STi, NULL, &BX_CPU_C::FLD_STi, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FLD_SINGLE_REAL, &BX_CPU_C::FLD_SINGLE_REAL, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLD_DOUBLE_REAL, &BX_CPU_C::FLD_DOUBLE_REAL, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLD_EXTENDED_REAL, &BX_CPU_C::FLD_EXTENDED_REAL, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FILD_WORD_INTEGER, &BX_CPU_C::FILD_WORD_INTEGER, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FILD_DWORD_INTEGER, &BX_CPU_C::FILD_DWORD_INTEGER, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FILD_QWORD_INTEGER, &BX_CPU_C::FILD_QWORD_INTEGER, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FBLD_PACKED_BCD, &BX_CPU_C::FBLD_PACKED_BCD, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FST_STi, NULL, &BX_CPU_C::FST_STi, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSTP_STi, NULL, &BX_CPU_C::FST_STi, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FST_SINGLE_REAL, &BX_CPU_C::FST_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSTP_SINGLE_REAL, &BX_CPU_C::FST_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FST_DOUBLE_REAL, &BX_CPU_C::FST_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSTP_DOUBLE_REAL, &BX_CPU_C::FST_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSTP_EXTENDED_REAL, &BX_CPU_C::FSTP_EXTENDED_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIST_WORD_INTEGER, &BX_CPU_C::FIST_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISTP_WORD_INTEGER, &BX_CPU_C::FIST_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIST_DWORD_INTEGER, &BX_CPU_C::FIST_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISTP_DWORD_INTEGER, &BX_CPU_C::FIST_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISTP_QWORD_INTEGER, &BX_CPU_C::FISTP_QWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FBSTP_PACKED_BCD, &BX_CPU_C::FBSTP_PACKED_BCD, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISTTP16, &BX_CPU_C::FISTTP16, NULL, BX_ISA_SSE3, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISTTP32, &BX_CPU_C::FISTTP32, NULL, BX_ISA_SSE3, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISTTP64, &BX_CPU_C::FISTTP64, NULL, BX_ISA_SSE3, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FNINIT, NULL, &BX_CPU_C::FNINIT, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FNCLEX, NULL, &BX_CPU_C::FNCLEX, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FRSTOR, &BX_CPU_C::FRSTOR, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FNSAVE, &BX_CPU_C::FNSAVE, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDENV, &BX_CPU_C::FLDENV, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FNSTENV, &BX_CPU_C::FNSTENV, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDCW, &BX_CPU_C::FLDCW, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FNSTCW, &BX_CPU_C::FNSTCW, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FNSTSW, &BX_CPU_C::FNSTSW, NULL, BX_ISA_X87, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FNSTSW_AX, NULL, &BX_CPU_C::FNSTSW_AX, BX_ISA_X87, OP_AXReg, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLD1, NULL, &BX_CPU_C::FLD1, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDL2T, NULL, &BX_CPU_C::FLDL2T, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDL2E, NULL, &BX_CPU_C::FLDL2E, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDPI, NULL, &BX_CPU_C::FLDPI, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDLG2, NULL, &BX_CPU_C::FLDLG2, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDLN2, NULL, &BX_CPU_C::FLDLN2, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FLDZ, NULL, &BX_CPU_C::FLDZ, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FADD_ST0_STj, NULL, &BX_CPU_C::FADD_ST0_STj, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FADD_STi_ST0, NULL, &BX_CPU_C::FADD_STi_ST0, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FADD_SINGLE_REAL, &BX_CPU_C::FADD_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FADD_DOUBLE_REAL, &BX_CPU_C::FADD_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIADD_WORD_INTEGER, &BX_CPU_C::FIADD_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIADD_DWORD_INTEGER, &BX_CPU_C::FIADD_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FMUL_ST0_STj, NULL, &BX_CPU_C::FMUL_ST0_STj, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FMUL_STi_ST0, NULL, &BX_CPU_C::FMUL_STi_ST0, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FMUL_SINGLE_REAL, &BX_CPU_C::FMUL_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FMUL_DOUBLE_REAL, &BX_CPU_C::FMUL_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIMUL_WORD_INTEGER , &BX_CPU_C::FIMUL_WORD_INTEGER , NULL , BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIMUL_DWORD_INTEGER, &BX_CPU_C::FIMUL_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUB_ST0_STj, NULL, &BX_CPU_C::FSUB_ST0_STj, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUBR_ST0_STj, NULL, &BX_CPU_C::FSUBR_ST0_STj, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUB_STi_ST0, NULL, &BX_CPU_C::FSUB_STi_ST0, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUBR_STi_ST0, NULL, &BX_CPU_C::FSUBR_STi_ST0, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUB_SINGLE_REAL, &BX_CPU_C::FSUB_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUBR_SINGLE_REAL, &BX_CPU_C::FSUBR_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUB_DOUBLE_REAL, &BX_CPU_C::FSUB_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FSUBR_DOUBLE_REAL, &BX_CPU_C::FSUBR_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISUB_WORD_INTEGER, &BX_CPU_C::FISUB_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISUBR_WORD_INTEGER, &BX_CPU_C::FISUBR_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISUB_DWORD_INTEGER, &BX_CPU_C::FISUB_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FISUBR_DWORD_INTEGER, &BX_CPU_C::FISUBR_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIV_ST0_STj, NULL, &BX_CPU_C::FDIV_ST0_STj, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIVR_ST0_STj, NULL, &BX_CPU_C::FDIVR_ST0_STj, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIV_STi_ST0, NULL, &BX_CPU_C::FDIV_STi_ST0, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIVR_STi_ST0, NULL, &BX_CPU_C::FDIVR_STi_ST0, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIV_SINGLE_REAL, &BX_CPU_C::FDIV_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIVR_SINGLE_REAL, &BX_CPU_C::FDIVR_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIV_DOUBLE_REAL, &BX_CPU_C::FDIV_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FDIVR_DOUBLE_REAL, &BX_CPU_C::FDIVR_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIDIV_WORD_INTEGER, &BX_CPU_C::FIDIV_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIDIVR_WORD_INTEGER, &BX_CPU_C::FIDIVR_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIDIV_DWORD_INTEGER, &BX_CPU_C::FIDIV_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FIDIVR_DWORD_INTEGER, &BX_CPU_C::FIDIVR_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOM_STi, NULL, &BX_CPU_C::FCOM_STi, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOMP_STi, NULL, &BX_CPU_C::FCOM_STi, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FUCOM_STi, NULL, &BX_CPU_C::FUCOM_STi, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FUCOMP_STi, NULL, &BX_CPU_C::FUCOM_STi, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOMI_ST0_STj, NULL, &BX_CPU_C::FCOMI_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOMIP_ST0_STj, NULL, &BX_CPU_C::FCOMI_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FUCOMI_ST0_STj, NULL, &BX_CPU_C::FUCOMI_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FUCOMIP_ST0_STj, NULL, &BX_CPU_C::FUCOMI_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOM_SINGLE_REAL, &BX_CPU_C::FCOM_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOMP_SINGLE_REAL, &BX_CPU_C::FCOM_SINGLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOM_DOUBLE_REAL, &BX_CPU_C::FCOM_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOMP_DOUBLE_REAL, &BX_CPU_C::FCOM_DOUBLE_REAL, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FICOM_WORD_INTEGER, &BX_CPU_C::FICOM_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FICOMP_WORD_INTEGER, &BX_CPU_C::FICOM_WORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FICOM_DWORD_INTEGER, &BX_CPU_C::FICOM_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FICOMP_DWORD_INTEGER, &BX_CPU_C::FICOM_DWORD_INTEGER, NULL, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVB_ST0_STj, NULL, &BX_CPU_C::FCMOVB_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVE_ST0_STj, NULL, &BX_CPU_C::FCMOVE_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVBE_ST0_STj, NULL, &BX_CPU_C::FCMOVBE_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVU_ST0_STj, NULL, &BX_CPU_C::FCMOVU_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVNB_ST0_STj, NULL, &BX_CPU_C::FCMOVNB_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVNE_ST0_STj, NULL, &BX_CPU_C::FCMOVNE_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVNBE_ST0_STj, NULL, &BX_CPU_C::FCMOVNBE_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCMOVNU_ST0_STj, NULL, &BX_CPU_C::FCMOVNU_ST0_STj, BX_ISA_P6, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FCOMPP, NULL, &BX_CPU_C::FCOMPP, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FUCOMPP, NULL, &BX_CPU_C::FUCOMPP, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FXCH_STi, NULL, &BX_CPU_C::FXCH_STi, BX_ISA_X87, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FNOP, NULL, &BX_CPU_C::FNOP, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FPLEGACY, NULL, &BX_CPU_C::FPLEGACY, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FCHS, NULL, &BX_CPU_C::FCHS, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FABS, NULL, &BX_CPU_C::FABS, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FTST, NULL, &BX_CPU_C::FTST, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FXAM, NULL, &BX_CPU_C::FXAM, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FDECSTP, NULL, &BX_CPU_C::FDECSTP, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FINCSTP, NULL, &BX_CPU_C::FINCSTP, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FFREE_STi, NULL, &BX_CPU_C::FFREE_STi, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_FFREEP_STi, NULL, &BX_CPU_C::FFREEP_STi, BX_ISA_X87, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_F2XM1, NULL, &BX_CPU_C::F2XM1, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FYL2X, NULL, &BX_CPU_C::FYL2X, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FPTAN, NULL, &BX_CPU_C::FPTAN, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FPATAN, NULL, &BX_CPU_C::FPATAN, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FXTRACT, NULL, &BX_CPU_C::FXTRACT, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FPREM1, NULL, &BX_CPU_C::FPREM1, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FPREM, NULL, &BX_CPU_C::FPREM, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FYL2XP1, NULL, &BX_CPU_C::FYL2XP1, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FSQRT, NULL, &BX_CPU_C::FSQRT, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FSINCOS, NULL, &BX_CPU_C::FSINCOS, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FRNDINT, NULL, &BX_CPU_C::FRNDINT, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FSCALE, NULL, &BX_CPU_C::FSCALE, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FSIN, NULL, &BX_CPU_C::FSIN, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FCOS, NULL, &BX_CPU_C::FCOS, BX_ISA_X87, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
#else
bx_define_opcode(BX_IA_FPU_ESC, &BX_CPU_C::FPU_ESC, &BX_CPU_C::FPU_ESC, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
#endif

// 486 new instructions
bx_define_opcode(BX_IA_CPUID, NULL, &BX_CPU_C::CPUID, BX_ISA_486, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BSWAP_RX, NULL, &BX_CPU_C::BSWAP_RX, BX_ISA_486, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BSWAP_ERX, NULL, &BX_CPU_C::BSWAP_ERX, BX_ISA_486, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_INVD, NULL, &BX_CPU_C::INVD, BX_ISA_486, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_WBINVD, NULL, &BX_CPU_C::WBINVD, BX_ISA_486, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XADD_EbGb, &BX_CPU_C::XADD_EbGbM, &BX_CPU_C::XADD_EbGbR, BX_ISA_486, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XADD_EwGw, &BX_CPU_C::XADD_EwGwM, &BX_CPU_C::XADD_EwGwR, BX_ISA_486, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XADD_EdGd, &BX_CPU_C::XADD_EdGdM, &BX_CPU_C::XADD_EdGdR, BX_ISA_486, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMPXCHG_EbGb, &BX_CPU_C::CMPXCHG_EbGbM, &BX_CPU_C::CMPXCHG_EbGbR, BX_ISA_486, OP_Eb, OP_Gb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMPXCHG_EwGw, &BX_CPU_C::CMPXCHG_EwGwM, &BX_CPU_C::CMPXCHG_EwGwR, BX_ISA_486, OP_Ew, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMPXCHG_EdGd, &BX_CPU_C::CMPXCHG_EdGdM, &BX_CPU_C::CMPXCHG_EdGdR, BX_ISA_486, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_INVLPG, &BX_CPU_C::INVLPG, &BX_CPU_C::BxError, 0, OP_Mb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
// 486 new instructions

// Pentium new instructions
bx_define_opcode(BX_IA_CMPXCHG8B, &BX_CPU_C::CMPXCHG8B, &BX_CPU_C::BxError, BX_ISA_PENTIUM, OP_Mq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_WRMSR, NULL, &BX_CPU_C::WRMSR, BX_ISA_PENTIUM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RDMSR, NULL, &BX_CPU_C::RDMSR, BX_ISA_PENTIUM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RDTSC, NULL, &BX_CPU_C::RDTSC, BX_ISA_PENTIUM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
// Pentium new instructions

// MMX
bx_define_opcode(BX_IA_PUNPCKLBW_PqQd, &BX_CPU_C::PUNPCKLBW_PqQd, &BX_CPU_C::PUNPCKLBW_PqQd, BX_ISA_MMX, OP_Pq, OP_Qd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUNPCKLWD_PqQd, &BX_CPU_C::PUNPCKLWD_PqQd, &BX_CPU_C::PUNPCKLWD_PqQd, BX_ISA_MMX, OP_Pq, OP_Qd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUNPCKLDQ_PqQd, &BX_CPU_C::PUNPCKLDQ_PqQd, &BX_CPU_C::PUNPCKLDQ_PqQd, BX_ISA_MMX, OP_Pq, OP_Qd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PACKSSWB_PqQq, &BX_CPU_C::PACKSSWB_PqQq, &BX_CPU_C::PACKSSWB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PCMPGTB_PqQq, &BX_CPU_C::PCMPGTB_PqQq, &BX_CPU_C::PCMPGTB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PCMPGTW_PqQq, &BX_CPU_C::PCMPGTW_PqQq, &BX_CPU_C::PCMPGTW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PCMPGTD_PqQq, &BX_CPU_C::PCMPGTD_PqQq, &BX_CPU_C::PCMPGTD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PACKUSWB_PqQq, &BX_CPU_C::PACKUSWB_PqQq, &BX_CPU_C::PACKUSWB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUNPCKHBW_PqQq, &BX_CPU_C::PUNPCKHBW_PqQq, &BX_CPU_C::PUNPCKHBW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUNPCKHWD_PqQq, &BX_CPU_C::PUNPCKHWD_PqQq, &BX_CPU_C::PUNPCKHWD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUNPCKHDQ_PqQq, &BX_CPU_C::PUNPCKHDQ_PqQq, &BX_CPU_C::PUNPCKHDQ_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PACKSSDW_PqQq, &BX_CPU_C::PACKSSDW_PqQq, &BX_CPU_C::PACKSSDW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVD_PqEd, &BX_CPU_C::MOVD_PqEdM, &BX_CPU_C::MOVD_PqEdR, BX_ISA_MMX, OP_Pq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVQ_PqQq, &BX_CPU_C::MOVQ_PqQqM, &BX_CPU_C::MOVQ_PqQqR, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PCMPEQB_PqQq, &BX_CPU_C::PCMPEQB_PqQq, &BX_CPU_C::PCMPEQB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PCMPEQW_PqQq, &BX_CPU_C::PCMPEQW_PqQq, &BX_CPU_C::PCMPEQW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PCMPEQD_PqQq, &BX_CPU_C::PCMPEQD_PqQq, &BX_CPU_C::PCMPEQD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_EMMS, NULL, &BX_CPU_C::EMMS, BX_ISA_MMX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVD_EdPd, &BX_CPU_C::MOVD_EdPdM, &BX_CPU_C::MOVD_EdPdR, BX_ISA_MMX, OP_Ed, OP_Pd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVQ_QqPq, &BX_CPU_C::MOVQ_QqPqM, &BX_CPU_C::MOVQ_PqQqR, BX_ISA_MMX, OP_Qq, OP_Pq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRLW_PqQq, &BX_CPU_C::PSRLW_PqQq, &BX_CPU_C::PSRLW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRLD_PqQq, &BX_CPU_C::PSRLD_PqQq, &BX_CPU_C::PSRLD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRLQ_PqQq, &BX_CPU_C::PSRLQ_PqQq, &BX_CPU_C::PSRLQ_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMULLW_PqQq, &BX_CPU_C::PMULLW_PqQq, &BX_CPU_C::PMULLW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBUSB_PqQq, &BX_CPU_C::PSUBUSB_PqQq, &BX_CPU_C::PSUBUSB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBUSW_PqQq, &BX_CPU_C::PSUBUSW_PqQq, &BX_CPU_C::PSUBUSW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PAND_PqQq, &BX_CPU_C::PAND_PqQq, &BX_CPU_C::PAND_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDUSB_PqQq, &BX_CPU_C::PADDUSB_PqQq, &BX_CPU_C::PADDUSB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDUSW_PqQq, &BX_CPU_C::PADDUSW_PqQq, &BX_CPU_C::PADDUSW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PANDN_PqQq, &BX_CPU_C::PANDN_PqQq, &BX_CPU_C::PANDN_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRAW_PqQq, &BX_CPU_C::PSRAW_PqQq, &BX_CPU_C::PSRAW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRAD_PqQq, &BX_CPU_C::PSRAD_PqQq, &BX_CPU_C::PSRAD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMULHW_PqQq, &BX_CPU_C::PMULHW_PqQq, &BX_CPU_C::PMULHW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBSB_PqQq, &BX_CPU_C::PSUBSB_PqQq, &BX_CPU_C::PSUBSB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBSW_PqQq, &BX_CPU_C::PSUBSW_PqQq, &BX_CPU_C::PSUBSW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POR_PqQq, &BX_CPU_C::POR_PqQq, &BX_CPU_C::POR_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDSB_PqQq, &BX_CPU_C::PADDSB_PqQq, &BX_CPU_C::PADDSB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDSW_PqQq, &BX_CPU_C::PADDSW_PqQq, &BX_CPU_C::PADDSW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PXOR_PqQq, &BX_CPU_C::PXOR_PqQq, &BX_CPU_C::PXOR_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSLLW_PqQq, &BX_CPU_C::PSLLW_PqQq, &BX_CPU_C::PSLLW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSLLD_PqQq, &BX_CPU_C::PSLLD_PqQq, &BX_CPU_C::PSLLD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSLLQ_PqQq, &BX_CPU_C::PSLLQ_PqQq, &BX_CPU_C::PSLLQ_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMADDWD_PqQq, &BX_CPU_C::PMADDWD_PqQq, &BX_CPU_C::PMADDWD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBB_PqQq, &BX_CPU_C::PSUBB_PqQq, &BX_CPU_C::PSUBB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBW_PqQq, &BX_CPU_C::PSUBW_PqQq, &BX_CPU_C::PSUBW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBD_PqQq, &BX_CPU_C::PSUBD_PqQq, &BX_CPU_C::PSUBD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDB_PqQq, &BX_CPU_C::PADDB_PqQq, &BX_CPU_C::PADDB_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDW_PqQq, &BX_CPU_C::PADDW_PqQq, &BX_CPU_C::PADDW_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDD_PqQq, &BX_CPU_C::PADDD_PqQq, &BX_CPU_C::PADDD_PqQq, BX_ISA_MMX, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRLW_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRLW_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRAW_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRAW_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSLLW_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSLLW_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRLD_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRLD_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRAD_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRAD_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSLLD_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSLLD_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSRLQ_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRLQ_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSLLQ_NqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSLLQ_NqIb, BX_ISA_MMX, OP_Nq, OP_Ib, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_MOVQ_EqPq, &BX_CPU_C::MOVQ_QqPqM, &BX_CPU_C::MOVQ_EqPqR, 0, OP_Eq, OP_Pq, OP_NONE, OP_NONE, 0)
#endif
// MMX

bx_define_opcode(BX_IA_FEMMS, NULL, &BX_CPU_C::EMMS, BX_ISA_3DNOW, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_3DNOW
bx_define_opcode(BX_IA_PF2ID_PqQq, &BX_CPU_C::PF2ID_PqQq, &BX_CPU_C::PF2ID_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PF2IW_PqQq, &BX_CPU_C::PF2IW_PqQq, &BX_CPU_C::PF2IW_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFACC_PqQq, &BX_CPU_C::PFACC_PqQq, &BX_CPU_C::PFACC_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFADD_PqQq, &BX_CPU_C::PFADD_PqQq, &BX_CPU_C::PFADD_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFCMPEQ_PqQq, &BX_CPU_C::PFCMPEQ_PqQq, &BX_CPU_C::PFCMPEQ_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFCMPGE_PqQq, &BX_CPU_C::PFCMPGE_PqQq, &BX_CPU_C::PFCMPGE_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFCMPGT_PqQq, &BX_CPU_C::PFCMPGT_PqQq, &BX_CPU_C::PFCMPGT_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFMAX_PqQq, &BX_CPU_C::PFMAX_PqQq, &BX_CPU_C::PFMAX_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFMIN_PqQq, &BX_CPU_C::PFMIN_PqQq, &BX_CPU_C::PFMIN_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFMUL_PqQq, &BX_CPU_C::PFMUL_PqQq, &BX_CPU_C::PFMUL_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFNACC_PqQq, &BX_CPU_C::PFNACC_PqQq, &BX_CPU_C::PFNACC_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFPNACC_PqQq, &BX_CPU_C::PFPNACC_PqQq, &BX_CPU_C::PFPNACC_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFRCP_PqQq, &BX_CPU_C::PFRCP_PqQq, &BX_CPU_C::PFRCP_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFRCPIT1_PqQq, &BX_CPU_C::PFRCPIT1_PqQq, &BX_CPU_C::PFRCPIT1_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFRCPIT2_PqQq, &BX_CPU_C::PFRCPIT2_PqQq, &BX_CPU_C::PFRCPIT2_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFRSQIT1_PqQq, &BX_CPU_C::PFRSQIT1_PqQq, &BX_CPU_C::PFRSQIT1_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFRSQRT_PqQq, &BX_CPU_C::PFRSQRT_PqQq, &BX_CPU_C::PFRSQRT_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFSUB_PqQq, &BX_CPU_C::PFSUB_PqQq, &BX_CPU_C::PFSUB_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PFSUBR_PqQq, &BX_CPU_C::PFSUBR_PqQq, &BX_CPU_C::PFSUBR_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PI2FD_PqQq, &BX_CPU_C::PI2FD_PqQq, &BX_CPU_C::PI2FD_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PI2FW_PqQq, &BX_CPU_C::PI2FW_PqQq, &BX_CPU_C::PI2FW_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMULHRW_PqQq, &BX_CPU_C::PMULHRW_PqQq, &BX_CPU_C::PMULHRW_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSWAPD_PqQq, &BX_CPU_C::PSWAPD_PqQq, &BX_CPU_C::PSWAPD_PqQq, BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
#endif
bx_define_opcode(BX_IA_PREFETCHW, &BX_CPU_C::NOP, &BX_CPU_C::NOP, 0, OP_Mb, OP_NONE, OP_NONE, OP_NONE, 0) // NOP even when no 3DNow!

bx_define_opcode(BX_IA_SYSCALL_LEGACY, NULL, &BX_CPU_C::SYSCALL, BX_ISA_SYSCALL_SYSRET_LEGACY, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_SYSRET_LEGACY, NULL, &BX_CPU_C::SYSRET, BX_ISA_SYSCALL_SYSRET_LEGACY, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

// P6 new instructions
bx_define_opcode(BX_IA_CMOVB_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVB_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVBE_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVBE_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVL_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVL_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVLE_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVLE_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNB_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNB_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNBE_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNBE_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNL_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNL_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNLE_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNLE_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNO_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNO_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNP_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNP_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNS_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNS_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNZ_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVNZ_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVO_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVO_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVP_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVP_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVS_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVS_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVZ_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CMOVZ_GwEwR, BX_ISA_P6, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_CMOVB_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVB_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVBE_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVBE_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVL_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVL_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVLE_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVLE_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNB_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNB_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNBE_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNBE_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNL_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNL_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNLE_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNLE_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNO_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNO_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNP_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNP_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNS_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNS_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNZ_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVNZ_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVO_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVO_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVP_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVP_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVS_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVS_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVZ_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CMOVZ_GdEdR, BX_ISA_P6, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_RDPMC, NULL, &BX_CPU_C::RDPMC, BX_ISA_P6, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_UD2A, &BX_CPU_C::UndefinedOpcode, &BX_CPU_C::UndefinedOpcode, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_UD2B, &BX_CPU_C::UndefinedOpcode, &BX_CPU_C::UndefinedOpcode, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
// P6 new instructions

// FXSAVE
bx_define_opcode(BX_IA_FXSAVE, &BX_CPU_C::FXSAVE, &BX_CPU_C::BxError, BX_ISA_SSE, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_FXRSTOR, &BX_CPU_C::FXRSTOR, &BX_CPU_C::BxError, BX_ISA_SSE, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
// FXSAVE

// SSE
bx_define_opcode(BX_IA_LDMXCSR, &BX_CPU_C::LDMXCSR, &BX_CPU_C::BxError, BX_ISA_SSE, OP_Md, OP_NONE, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_STMXCSR, &BX_CPU_C::STMXCSR, &BX_CPU_C::BxError, BX_ISA_SSE, OP_Md, OP_NONE, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PREFETCH, &BX_CPU_C::PREFETCH, &BX_CPU_C::NOP, BX_ISA_SSE, OP_Mb, BX_SRC_NNN, OP_NONE, OP_NONE, 0)
// SSE

// SSE and SSE2
bx_define_opcode(BX_IA_ANDPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ANDPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ORPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ORPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_XORPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::XORPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ANDNPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ANDNPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_MOVUPS_VpsWps, &BX_CPU_C::MOVUPS_VpsWpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVUPS_WpsVps, &BX_CPU_C::MOVUPS_WpsVpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE, OP_Wps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVSS_VssWss, &BX_CPU_C::MOVSS_VssWssM, &BX_CPU_C::MOVSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVSS_WssVss, &BX_CPU_C::MOVSS_WssVssM, &BX_CPU_C::MOVSS_VssWssR, BX_ISA_SSE, OP_Wss, OP_Vss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVLPS_VpsMq, &BX_CPU_C::MOVLPS_VpsMq, &BX_CPU_C::MOVHLPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Mq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVLPS_MqVps, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::BxError, BX_ISA_SSE, OP_Mq, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVHPS_VpsMq, &BX_CPU_C::MOVHPS_VpsMq, &BX_CPU_C::MOVLHPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Mq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVHPS_MqVps, &BX_CPU_C::MOVHPS_MqVps, &BX_CPU_C::BxError, BX_ISA_SSE, OP_Mq, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVAPS_VpsWps, &BX_CPU_C::MOVAPS_VpsWpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVAPS_WpsVps, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE, OP_Wps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVNTPS_MpsVps, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_SSE, OP_Mps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTPI2PS_VpsQq, &BX_CPU_C::CVTPI2PS_VpsQqM, &BX_CPU_C::CVTPI2PS_VpsQqR, BX_ISA_SSE, OP_Vps, OP_Qq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSI2SS_VssEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CVTSI2SS_VssEdR, BX_ISA_SSE, OP_Vss, OP_Ed, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTPS2PI_PqWps, &BX_CPU_C::CVTTPS2PI_PqWps, &BX_CPU_C::CVTTPS2PI_PqWps, BX_ISA_SSE, OP_Pq, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTPS2PI_PqWps, &BX_CPU_C::CVTPS2PI_PqWps, &BX_CPU_C::CVTPS2PI_PqWps, BX_ISA_SSE, OP_Pq, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTSS2SI_GdWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTTSS2SI_GdWssR, BX_ISA_SSE, OP_Gd, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSS2SI_GdWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTSS2SI_GdWssR, BX_ISA_SSE, OP_Gd, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_UCOMISS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::UCOMISS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_COMISS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::COMISS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVMSKPS_GdUps, &BX_CPU_C::BxError, &BX_CPU_C::MOVMSKPS_GdUps, BX_ISA_SSE, OP_Gd, OP_Ups, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_RSQRTPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::RSQRTPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_RSQRTSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::RSQRTSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_RCPPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::RCPPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_RCPSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::RCPSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSHUFW_PqQqIb, &BX_CPU_C::PSHUFW_PqQqIb, &BX_CPU_C::PSHUFW_PqQqIb, BX_ISA_SSE | BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_PSHUFLW_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSHUFLW_VdqWdqIbR, BX_ISA_SSE, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PINSRW_PqEwIb, &BX_CPU_C::PINSRW_PqEwIb, &BX_CPU_C::PINSRW_PqEwIb, BX_ISA_SSE | BX_ISA_3DNOW, OP_Pq, OP_Ew, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_PEXTRW_GdNqIb, &BX_CPU_C::BxError, &BX_CPU_C::PEXTRW_GdNqIb, BX_ISA_SSE | BX_ISA_3DNOW, OP_Gd, OP_Nq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHUFPS_VpsWpsIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::SHUFPS_VpsWpsIbR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVMSKB_GdNq, &BX_CPU_C::BxError, &BX_CPU_C::PMOVMSKB_GdNq, BX_ISA_SSE | BX_ISA_3DNOW, OP_Gd, OP_Nq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMINUB_PqQq, &BX_CPU_C::PMINUB_PqQq, &BX_CPU_C::PMINUB_PqQq, BX_ISA_SSE | BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMAXUB_PqQq, &BX_CPU_C::PMAXUB_PqQq, &BX_CPU_C::PMAXUB_PqQq, BX_ISA_SSE | BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PAVGB_PqQq, &BX_CPU_C::PAVGB_PqQq, &BX_CPU_C::PAVGB_PqQq, BX_ISA_SSE, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PAVGW_PqQq, &BX_CPU_C::PAVGW_PqQq, &BX_CPU_C::PAVGW_PqQq, BX_ISA_SSE, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMULHUW_PqQq, &BX_CPU_C::PMULHUW_PqQq, &BX_CPU_C::PMULHUW_PqQq, BX_ISA_SSE | BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVNTQ_MqPq, &BX_CPU_C::MOVQ_QqPqM, &BX_CPU_C::BxError, BX_ISA_SSE | BX_ISA_3DNOW, OP_Mq, OP_Pq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMINSW_PqQq, &BX_CPU_C::PMINSW_PqQq, &BX_CPU_C::PMINSW_PqQq, BX_ISA_SSE | BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMAXSW_PqQq, &BX_CPU_C::PMAXSW_PqQq, &BX_CPU_C::PMAXSW_PqQq, BX_ISA_SSE, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSADBW_PqQq, &BX_CPU_C::PSADBW_PqQq, &BX_CPU_C::PSADBW_PqQq, BX_ISA_SSE | BX_ISA_3DNOW, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MASKMOVQ_PqNq, &BX_CPU_C::BxError, &BX_CPU_C::MASKMOVQ_PqNq, BX_ISA_SSE | BX_ISA_3DNOW, OP_NONE, OP_Pq, OP_Nq, OP_NONE, 0)

// SSE alias
bx_define_opcode(BX_IA_ADDPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ADDPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ADDPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ADDPD_VpdWpdR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ADDSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::ADDSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ADDSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::ADDSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_MULPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MULPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MULPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MULPD_VpdWpdR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MULSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::MULSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MULSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::MULSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_SUBPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::SUBPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SUBPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::SUBPD_VpdWpdR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SUBSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::SUBSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SUBSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::SUBSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_MINPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MINPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MINPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MINPD_VpdWpdR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MINSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::MINSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MINSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::MINSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_DIVPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::DIVPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_DIVPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::DIVPD_VpdWpdR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_DIVSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::DIVSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_DIVSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::DIVSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_MAXPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MAXPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MAXPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MAXPD_VpdWpdR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MAXSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::MAXSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MAXSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::MAXSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_SQRTPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::SQRTPS_VpsWpsR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SQRTPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::SQRTPD_VpdWpdR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SQRTSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::SQRTSS_VssWssR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SQRTSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::SQRTSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_CMPPS_VpsWpsIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CMPPS_VpsWpsIbR, BX_ISA_SSE, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CMPPD_VpdWpdIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CMPPD_VpdWpdIbR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CMPSS_VssWssIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CMPSS_VssWssIbR, BX_ISA_SSE, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CMPSD_VsdWsdIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CMPSD_VsdWsdIbR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_CVTPS2PD_VpdWps, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTPS2PD_VpdWpsR, BX_ISA_SSE2, OP_Vpd, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTPD2PS_VpsWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CVTPD2PS_VpsWpdR, BX_ISA_SSE2, OP_Vps, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSS2SD_VsdWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTSS2SD_VsdWssR, BX_ISA_SSE2, OP_Vsd, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSD2SS_VssWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTSD2SS_VssWsdR, BX_ISA_SSE2, OP_Vss, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
// SSE alias

bx_define_opcode(BX_IA_MOVSD_VsdWsd, &BX_CPU_C::MOVQ_VqWqM, &BX_CPU_C::MOVSD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVSD_WsdVsd, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::MOVSD_VsdWsdR, BX_ISA_SSE2, OP_Wsd, OP_Vsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTPI2PD_VpdQq, &BX_CPU_C::CVTPI2PD_VpdQqM, &BX_CPU_C::CVTPI2PD_VpdQqR, BX_ISA_SSE2, OP_Vpd, OP_Qq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSI2SD_VsdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CVTSI2SD_VsdEdR, BX_ISA_SSE2, OP_Vsd, OP_Ed, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTPD2PI_PqWpd, &BX_CPU_C::CVTTPD2PI_PqWpd, &BX_CPU_C::CVTTPD2PI_PqWpd, BX_ISA_SSE2, OP_Pq, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTSD2SI_GdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTTSD2SI_GdWsdR, BX_ISA_SSE2, OP_Gd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTPD2PI_PqWpd, &BX_CPU_C::CVTPD2PI_PqWpd, &BX_CPU_C::CVTPD2PI_PqWpd, BX_ISA_SSE2, OP_Pq, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSD2SI_GdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTSD2SI_GdWsdR, BX_ISA_SSE2, OP_Gd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_UCOMISD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::UCOMISD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_COMISD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::COMISD_VsdWsdR, BX_ISA_SSE2, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVMSKPD_GdUpd, &BX_CPU_C::BxError, &BX_CPU_C::MOVMSKPD_GdUpd, BX_ISA_SSE2, OP_Gd, OP_Upd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTDQ2PS_VpsWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CVTDQ2PS_VpsWdqR, BX_ISA_SSE2, OP_Vps, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTPS2DQ_VdqWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CVTPS2DQ_VdqWpsR, BX_ISA_SSE2, OP_Vdq, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTPS2DQ_VdqWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CVTTPS2DQ_VdqWpsR, BX_ISA_SSE2, OP_Vdq, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_UNPCKHPD_VpdWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKHQDQ_VdqWdqR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_UNPCKLPD_VpdWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKLQDQ_VdqWdqR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKHDQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::UNPCKHPS_VpsWpsR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKLDQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::UNPCKLPS_VpsWpsR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVAPD_VpdWpd, &BX_CPU_C::MOVAPS_VpsWpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVAPD_WpdVpd, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Wpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVDQA_VdqWdq, &BX_CPU_C::MOVAPS_VpsWpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVDQA_WdqVdq, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Wdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVDQU_VdqWdq, &BX_CPU_C::MOVUPS_VpsWpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVDQU_WdqVdq, &BX_CPU_C::MOVUPS_WpsVpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Wdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVHPD_MqVsd, &BX_CPU_C::MOVHPS_MqVps, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Mq, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVHPD_VsdMq, &BX_CPU_C::MOVHPS_VpsMq, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Vsd, OP_Mq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVLPD_MqVsd, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Mq, OP_Vsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVLPD_VsdMq, &BX_CPU_C::MOVLPS_VpsMq, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Vps, OP_Mq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVNTDQ_MdqVdq, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Mdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVNTPD_MpdVpd, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Mpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVUPD_VpdWpd, &BX_CPU_C::MOVUPS_VpsWpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVUPD_WpdVpd, &BX_CPU_C::MOVUPS_WpsVpsM, &BX_CPU_C::MOVAPS_VpsWpsR, BX_ISA_SSE2, OP_Wpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ANDNPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ANDNPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ANDPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ANDPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ORPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ORPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_XORPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::XORPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PAND_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ANDPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PANDN_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ANDNPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_POR_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ORPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PXOR_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::XORPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKLBW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKLBW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKLWD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKLWD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_UNPCKLPS_VpsWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::UNPCKLPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PACKSSWB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PACKSSWB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPGTB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPGTB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPGTW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPGTW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPGTD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPGTD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PACKUSWB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PACKUSWB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKHBW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKHBW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKHWD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKHWD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_UNPCKHPS_VpsWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::UNPCKHPS_VpsWpsR, BX_ISA_SSE2, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PACKSSDW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PACKSSDW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKLQDQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKLQDQ_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PUNPCKHQDQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PUNPCKHQDQ_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVD_VdqEd, &BX_CPU_C::MOVSS_VssWssM, &BX_CPU_C::MOVD_VdqEdR, BX_ISA_SSE2, OP_Vdq, OP_Ed, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSHUFD_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSHUFD_VdqWdqIbR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSHUFHW_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSHUFHW_VdqWdqIbR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPEQB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPEQB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPEQW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPEQW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPEQD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPEQD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVD_EdVd, &BX_CPU_C::MOVSS_WssVssM, &BX_CPU_C::MOVD_EdVdR, BX_ISA_SSE2, OP_Ed, OP_Vd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVQ_VqWq, &BX_CPU_C::MOVQ_VqWqM, &BX_CPU_C::MOVQ_VqWqR, BX_ISA_SSE2, OP_Vq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVNTI32_MdGd, &BX_CPU_C::MOV32_EdGdM, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Md, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PINSRW_VdqEwIb, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::PINSRW_VdqHdqEwIbR, BX_ISA_SSE2, OP_Vdq, OP_Vdq, OP_Ew, OP_Ib, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PEXTRW_GdUdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PEXTRW_GdUdqIb, BX_ISA_SSE2, OP_Gd, OP_Udq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SHUFPD_VpdWpdIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::SHUFPD_VpdWpdIbR, BX_ISA_SSE2, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRLW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSRLW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRLD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSRLD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRLQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSRLQ_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDQ_PqQq, &BX_CPU_C::PADDQ_PqQq, &BX_CPU_C::PADDQ_PqQq, BX_ISA_SSE2, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PADDQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDQ_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMULLW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMULLW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVQ_WqVq, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::MOVQ_VqWqR, BX_ISA_SSE2, OP_Wq, OP_Vq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVDQ2Q_PqVRq, &BX_CPU_C::BxError, &BX_CPU_C::MOVDQ2Q_PqVRq, BX_ISA_SSE2, OP_Pq, OP_Udq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVQ2DQ_VdqQq, &BX_CPU_C::BxError, &BX_CPU_C::MOVQ2DQ_VdqQq, BX_ISA_SSE2, OP_Vdq, OP_Qq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVMSKB_GdUdq, &BX_CPU_C::BxError, &BX_CPU_C::PMOVMSKB_GdUdq, BX_ISA_SSE2, OP_Gd, OP_Udq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBUSB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBUSB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBUSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBUSW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMINUB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMINUB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDUSB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDUSB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDUSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDUSW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMAXUB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMAXUB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PAVGB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PAVGB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRAW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSRAW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRAD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSRAD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PAVGW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PAVGW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMULHUW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMULHUW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMULHW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMULHW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTPD2DQ_VqWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CVTTPD2DQ_VqWpdR, BX_ISA_SSE2, OP_Vq, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTPD2DQ_VqWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::CVTPD2DQ_VqWpdR, BX_ISA_SSE2, OP_Vq, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTDQ2PD_VpdWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTDQ2PD_VpdWqR, BX_ISA_SSE2, OP_Vpd, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBSB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBSB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBSW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMINSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMINSW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDSB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDSB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDSW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMAXSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMAXSW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSLLW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSLLW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSLLD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSLLD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSLLQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSLLQ_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMULUDQ_PqQq, &BX_CPU_C::PMULUDQ_PqQq, &BX_CPU_C::PMULUDQ_PqQq, BX_ISA_SSE2, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMULUDQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMULUDQ_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMADDWD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMADDWD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSADBW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSADBW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MASKMOVDQU_VdqUdq, &BX_CPU_C::BxError, &BX_CPU_C::MASKMOVDQU_VdqUdq, BX_ISA_SSE2, OP_NONE, OP_Vdq, OP_Udq, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSUBQ_PqQq, &BX_CPU_C::PSUBQ_PqQq, &BX_CPU_C::PSUBQ_PqQq, BX_ISA_SSE2, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSUBQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSUBQ_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDB_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDW_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PADDD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PADDD_VdqWdqR, BX_ISA_SSE2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRLW_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRLW_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRAW_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRAW_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSLLW_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSLLW_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRLD_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRLD_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRAD_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRAD_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSLLD_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSLLD_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRLQ_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRLQ_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSRLDQ_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSRLDQ_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSLLQ_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSLLQ_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSLLDQ_UdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PSLLDQ_UdqIb, BX_ISA_SSE2, OP_Udq, OP_Ib, OP_NONE, OP_NONE, BX_PREPARE_SSE)

bx_define_opcode(BX_IA_LFENCE, &BX_CPU_C::BxError, &BX_CPU_C::NOP, BX_ISA_SSE2, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SFENCE, &BX_CPU_C::BxError, &BX_CPU_C::NOP, BX_ISA_SSE, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MFENCE, &BX_CPU_C::BxError, &BX_CPU_C::NOP, BX_ISA_SSE2, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
// SSE and SSE2

// SSE3
bx_define_opcode(BX_IA_MOVDDUP_VpdWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::MOVDDUP_VpdWqR, BX_ISA_SSE3, OP_Vpd, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVSLDUP_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MOVSLDUP_VpsWpsR, BX_ISA_SSE3, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVSHDUP_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MOVSHDUP_VpsWpsR, BX_ISA_SSE3, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_HADDPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::HADDPD_VpdWpdR, BX_ISA_SSE3, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_HADDPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::HADDPS_VpsWpsR, BX_ISA_SSE3, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_HSUBPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::HSUBPD_VpdWpdR, BX_ISA_SSE3, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_HSUBPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::HSUBPS_VpsWpsR, BX_ISA_SSE3, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ADDSUBPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ADDSUBPD_VpdWpdR, BX_ISA_SSE3, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ADDSUBPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ADDSUBPS_VpsWpsR, BX_ISA_SSE3, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_LDDQU_VdqMdq, &BX_CPU_C::MOVUPS_VpsWpsM, &BX_CPU_C::BxError, BX_ISA_SSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
// SSE3

#if BX_CPU_LEVEL >= 6
// SSSE3
bx_define_opcode(BX_IA_PSHUFB_PqQq, &BX_CPU_C::PSHUFB_PqQq, &BX_CPU_C::PSHUFB_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PHADDW_PqQq, &BX_CPU_C::PHADDW_PqQq, &BX_CPU_C::PHADDW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PHADDD_PqQq, &BX_CPU_C::PHADDD_PqQq, &BX_CPU_C::PHADDD_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PHADDSW_PqQq, &BX_CPU_C::PHADDSW_PqQq, &BX_CPU_C::PHADDSW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMADDUBSW_PqQq, &BX_CPU_C::PMADDUBSW_PqQq, &BX_CPU_C::PMADDUBSW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PHSUBSW_PqQq, &BX_CPU_C::PHSUBSW_PqQq, &BX_CPU_C::PHSUBSW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PHSUBW_PqQq, &BX_CPU_C::PHSUBW_PqQq, &BX_CPU_C::PHSUBW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PHSUBD_PqQq, &BX_CPU_C::PHSUBD_PqQq, &BX_CPU_C::PHSUBD_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSIGNB_PqQq, &BX_CPU_C::PSIGNB_PqQq, &BX_CPU_C::PSIGNB_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSIGNW_PqQq, &BX_CPU_C::PSIGNW_PqQq, &BX_CPU_C::PSIGNW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PSIGND_PqQq, &BX_CPU_C::PSIGND_PqQq, &BX_CPU_C::PSIGND_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PMULHRSW_PqQq, &BX_CPU_C::PMULHRSW_PqQq, &BX_CPU_C::PMULHRSW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PABSB_PqQq, &BX_CPU_C::PABSB_PqQq, &BX_CPU_C::PABSB_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PABSW_PqQq, &BX_CPU_C::PABSW_PqQq, &BX_CPU_C::PABSW_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PABSD_PqQq, &BX_CPU_C::PABSD_PqQq, &BX_CPU_C::PABSD_PqQq, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PALIGNR_PqQqIb, &BX_CPU_C::PALIGNR_PqQqIb, &BX_CPU_C::PALIGNR_PqQqIb, BX_ISA_SSSE3, OP_Pq, OP_Qq, OP_Ib, OP_NONE, 0)

bx_define_opcode(BX_IA_PSHUFB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSHUFB_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PHADDW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PHADDW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PHADDD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PHADDD_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PHADDSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PHADDSW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMADDUBSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMADDUBSW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PHSUBSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PHSUBSW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PHSUBW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PHSUBW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PHSUBD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PHSUBD_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSIGNB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSIGNB_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSIGNW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSIGNW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PSIGND_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PSIGND_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMULHRSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMULHRSW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PABSB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PABSB_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PABSW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PABSW_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PABSD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PABSD_VdqWdqR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PALIGNR_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PALIGNR_VdqWdqIbR, BX_ISA_SSSE3, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
// SSSE3

// SSE4.1
bx_define_opcode(BX_IA_PBLENDVB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PBLENDVB_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_BLENDVPS_VpsWps, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::BLENDVPS_VpsWpsR, BX_ISA_SSE4_1, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_BLENDVPD_VpdWpd, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::BLENDVPD_VpdWpdR, BX_ISA_SSE4_1, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVSXBW_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVSXBW_VdqWqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVSXBD_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVSXBD_VdqWdR, BX_ISA_SSE4_1, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVSXBQ_VdqWw, &BX_CPU_C::LOAD_Ww, &BX_CPU_C::PMOVSXBQ_VdqWwR, BX_ISA_SSE4_1, OP_Vdq, OP_Ww, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVSXWD_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVSXWD_VdqWqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVSXWQ_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVSXWQ_VdqWdR, BX_ISA_SSE4_1, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVSXDQ_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVSXDQ_VdqWqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVZXBW_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVZXBW_VdqWqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVZXBD_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVZXBD_VdqWdR, BX_ISA_SSE4_1, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVZXBQ_VdqWw, &BX_CPU_C::LOAD_Ww, &BX_CPU_C::PMOVZXBQ_VdqWwR, BX_ISA_SSE4_1, OP_Vdq, OP_Ww, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVZXWD_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVZXWD_VdqWqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVZXWQ_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVZXWQ_VdqWdR, BX_ISA_SSE4_1, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMOVZXDQ_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVZXDQ_VdqWqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PTEST_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PTEST_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMULDQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMULDQ_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPEQQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPEQQ_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PACKUSDW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PACKUSDW_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMINSB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMINSB_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMINSD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMINSD_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMINUW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMINUW_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMINUD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMINUD_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMAXSB_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMAXSB_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMAXSD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMAXSD_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMAXUW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMAXUW_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMAXUD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMAXUD_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PMULLD_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PMULLD_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PHMINPOSUW_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PHMINPOSUW_VdqWdqR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ROUNDPS_VpsWpsIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ROUNDPS_VpsWpsIbR, BX_ISA_SSE4_1, OP_Vps, OP_Wps, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ROUNDPD_VpdWpdIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::ROUNDPD_VpdWpdIbR, BX_ISA_SSE4_1, OP_Vpd, OP_Wpd, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ROUNDSS_VssWssIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::ROUNDSS_VssWssIbR, BX_ISA_SSE4_1, OP_Vss, OP_Wss, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_ROUNDSD_VsdWsdIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::ROUNDSD_VsdWsdIbR, BX_ISA_SSE4_1, OP_Vsd, OP_Wsd, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_BLENDPS_VpsWpsIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::BLENDPS_VpsWpsIbR, BX_ISA_SSE4_1, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_BLENDPD_VpdWpdIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::BLENDPD_VpdWpdIbR, BX_ISA_SSE4_1, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PBLENDW_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PBLENDW_VdqWdqIbR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PEXTRB_EbdVdqIb, &BX_CPU_C::PEXTRB_EbdVdqIbM, &BX_CPU_C::PEXTRB_EbdVdqIbR, BX_ISA_SSE4_1, OP_Ebd, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PEXTRW_EwdVdqIb, &BX_CPU_C::PEXTRW_EwdVdqIbM, &BX_CPU_C::PEXTRW_EwdVdqIbR, BX_ISA_SSE4_1, OP_Ewd, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PEXTRD_EdVdqIb, &BX_CPU_C::PEXTRD_EdVdqIbM, &BX_CPU_C::PEXTRD_EdVdqIbR, BX_ISA_SSE4_1, OP_Ed, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_EXTRACTPS_EdVpsIb, &BX_CPU_C::EXTRACTPS_EdVpsIbM, &BX_CPU_C::EXTRACTPS_EdVpsIbR, BX_ISA_SSE4_1, OP_Ed, OP_Vps, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PINSRB_VdqEbIb, &BX_CPU_C::PINSRB_VdqHdqEbIbM, &BX_CPU_C::PINSRB_VdqHdqEbIbR, BX_ISA_SSE4_1, OP_Vdq, OP_Vdq, OP_Eb, OP_Ib, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_INSERTPS_VpsWssIb, &BX_CPU_C::INSERTPS_VpsHpsWssIb, &BX_CPU_C::INSERTPS_VpsHpsWssIb, BX_ISA_SSE4_1, OP_Vps, OP_Vps, OP_Wss, OP_Ib, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PINSRD_VdqEdIb, &BX_CPU_C::PINSRD_VdqHdqEdIbM, &BX_CPU_C::PINSRD_VdqHdqEdIbR, BX_ISA_SSE4_1, OP_Vdq, OP_Vdq, OP_Ed, OP_Ib, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_DPPS_VpsWpsIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::DPPS_VpsWpsIbR, BX_ISA_SSE4_1, OP_Vps, OP_Wps, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_DPPD_VpdWpdIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::DPPD_VpdHpdWpdIbR, BX_ISA_SSE4_1, OP_Vpd, OP_Vpd, OP_Wpd, OP_Ib, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MPSADBW_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::MPSADBW_VdqWdqIbR, BX_ISA_SSE4_1, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVNTDQA_VdqMdq, &BX_CPU_C::MOVAPS_VpsWpsM, &BX_CPU_C::BxError, BX_ISA_SSE4_1, OP_Vdq, OP_Mdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
// SSE4.1

// SSE4.2
bx_define_opcode(BX_IA_CRC32_GdEb, &BX_CPU_C::LOAD_Eb, &BX_CPU_C::CRC32_GdEbR, BX_ISA_SSE4_2, OP_Gb, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CRC32_GdEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::CRC32_GdEwR, BX_ISA_SSE4_2, OP_Gd, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CRC32_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::CRC32_GdEdR, BX_ISA_SSE4_2, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_CRC32_GdEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CRC32_GdEqR, BX_ISA_SSE4_2, OP_Gd, OP_Eq, OP_NONE, OP_NONE, 0)
#endif
bx_define_opcode(BX_IA_PCMPGTQ_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCMPGTQ_VdqWdqR, BX_ISA_SSE4_2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPESTRM_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPESTRM_VdqWdqIbR, BX_ISA_SSE4_2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPESTRI_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPESTRI_VdqWdqIbR, BX_ISA_SSE4_2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPISTRM_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPISTRM_VdqWdqIbR, BX_ISA_SSE4_2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCMPISTRI_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPISTRI_VdqWdqIbR, BX_ISA_SSE4_2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
// SSE4.2

// MOVBE instruction
bx_define_opcode(BX_IA_MOVBE_GwMw, &BX_CPU_C::MOVBE_GwMw, &BX_CPU_C::BxError, BX_ISA_MOVBE, OP_Gw, OP_Mw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVBE_GdMd, &BX_CPU_C::MOVBE_GdMd, &BX_CPU_C::BxError, BX_ISA_MOVBE, OP_Gd, OP_Md, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_MOVBE_GqMq, &BX_CPU_C::MOVBE_GqMq, &BX_CPU_C::BxError, BX_ISA_MOVBE, OP_Gq, OP_Mq, OP_NONE, OP_NONE, 0)
#endif
bx_define_opcode(BX_IA_MOVBE_MwGw, &BX_CPU_C::MOVBE_MwGw, &BX_CPU_C::BxError, BX_ISA_MOVBE, OP_Mw, OP_Gw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVBE_MdGd, &BX_CPU_C::MOVBE_MdGd, &BX_CPU_C::BxError, BX_ISA_MOVBE, OP_Md, OP_Gd, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_MOVBE_MqGq, &BX_CPU_C::MOVBE_MqGq, &BX_CPU_C::BxError, BX_ISA_MOVBE, OP_Mq, OP_Gq, OP_NONE, OP_NONE, 0)
#endif
// MOVBE instruction

#endif // BX_CPU_LEVEL >= 6

// POPCNT instruction
bx_define_opcode(BX_IA_POPCNT_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::POPCNT_GdEdR, BX_ISA_SSE4_2, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POPCNT_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::POPCNT_GwEwR, BX_ISA_SSE4_2, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_POPCNT_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::POPCNT_GqEqR, BX_ISA_SSE4_2, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
#endif
// POPCNT instruction

// XSAVE extensions
bx_define_opcode(BX_IA_XRSTOR, &BX_CPU_C::XRSTOR, &BX_CPU_C::BxError, BX_ISA_XSAVE, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XSAVE, &BX_CPU_C::XSAVE, &BX_CPU_C::BxError, BX_ISA_XSAVE, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XSETBV, &BX_CPU_C::BxError, &BX_CPU_C::XSETBV, BX_ISA_XSAVE, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_XGETBV, &BX_CPU_C::BxError, &BX_CPU_C::XGETBV, BX_ISA_XSAVE, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XSAVEOPT, &BX_CPU_C::XSAVE, &BX_CPU_C::BxError, BX_ISA_XSAVEOPT, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)

#if BX_CPU_LEVEL >= 6

// AES instructions
bx_define_opcode(BX_IA_AESIMC_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::AESIMC_VdqWdqR, BX_ISA_AES_PCLMULQDQ, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_AESENC_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::AESENC_VdqHdqWdqR, BX_ISA_AES_PCLMULQDQ, OP_Vdq, OP_Vdq, OP_Wdq, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_AESENCLAST_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::AESENCLAST_VdqHdqWdqR, BX_ISA_AES_PCLMULQDQ, OP_Vdq, OP_Vdq, OP_Wdq, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_AESDEC_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::AESDEC_VdqHdqWdqR, BX_ISA_AES_PCLMULQDQ, OP_Vdq, OP_Vdq, OP_Wdq, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_AESDECLAST_VdqWdq, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::AESDECLAST_VdqHdqWdqR, BX_ISA_AES_PCLMULQDQ, OP_Vdq, OP_Vdq, OP_Wdq, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_AESKEYGENASSIST_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::AESKEYGENASSIST_VdqWdqIbR, BX_ISA_AES_PCLMULQDQ, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_PCLMULQDQ_VdqWdqIb, &BX_CPU_C::LOAD_Wdq, &BX_CPU_C::PCLMULQDQ_VdqHdqWdqIbR, BX_ISA_AES_PCLMULQDQ, OP_Vdq, OP_Vdq, OP_Wdq, OP_Ib, BX_PREPARE_SSE)

// SHA instructions
bx_define_opcode(BX_IA_SHA1NEXTE_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::SHA1NEXTE_VdqWdqR, BX_ISA_SHA, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SHA1MSG1_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::SHA1MSG1_VdqWdqR, BX_ISA_SHA, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SHA1MSG2_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::SHA1MSG2_VdqWdqR, BX_ISA_SHA, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SHA256RNDS2_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::SHA256RNDS2_VdqWdqR, BX_ISA_SHA, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SHA256MSG1_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::SHA256MSG1_VdqWdqR, BX_ISA_SHA, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SHA256MSG2_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::SHA256MSG2_VdqWdqR, BX_ISA_SHA, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_SHA1RNDS4_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::SHA1RNDS4_VdqWdqIbR, BX_ISA_SHA, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_SSE)

#endif

#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_LM_LAHF, NULL, &BX_CPU_C::LAHF, BX_ISA_LM_LAHF_SAHF, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LM_SAHF, NULL, &BX_CPU_C::SAHF, BX_ISA_LM_LAHF_SAHF, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_SYSCALL, NULL, &BX_CPU_C::SYSCALL, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_SYSRET, NULL, &BX_CPU_C::SYSRET, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_ADD_GqEq, &BX_CPU_C::ADD_GqEqM, &BX_CPU_C::ADD_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_GqEq, &BX_CPU_C::OR_GqEqM, &BX_CPU_C::OR_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_GqEq, &BX_CPU_C::ADC_GqEqM, &BX_CPU_C::ADC_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_GqEq, &BX_CPU_C::SBB_GqEqM, &BX_CPU_C::SBB_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_GqEq, &BX_CPU_C::AND_GqEqM, &BX_CPU_C::AND_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_GqEq, &BX_CPU_C::SUB_GqEqM, &BX_CPU_C::SUB_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_GqEq, &BX_CPU_C::XOR_GqEqM, &BX_CPU_C::XOR_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_GqEq, &BX_CPU_C::CMP_GqEqM, &BX_CPU_C::CMP_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADD_EqGq, &BX_CPU_C::ADD_EqGqM, &BX_CPU_C::ADD_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EqGq, &BX_CPU_C::OR_EqGqM, &BX_CPU_C::OR_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_EqGq, &BX_CPU_C::ADC_EqGqM, &BX_CPU_C::ADC_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EqGq, &BX_CPU_C::SBB_EqGqM, &BX_CPU_C::SBB_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EqGq, &BX_CPU_C::AND_EqGqM, &BX_CPU_C::AND_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EqGq, &BX_CPU_C::SUB_EqGqM, &BX_CPU_C::SUB_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EqGq, &BX_CPU_C::XOR_EqGqM, &BX_CPU_C::XOR_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EqGq, &BX_CPU_C::TEST_EqGqM, &BX_CPU_C::TEST_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EqGq, &BX_CPU_C::CMP_EqGqM, &BX_CPU_C::CMP_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADD_RAXId, NULL, &BX_CPU_C::ADD_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_RAXId, NULL, &BX_CPU_C::OR_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_RAXId, NULL, &BX_CPU_C::ADC_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_RAXId, NULL, &BX_CPU_C::SBB_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_RAXId, NULL, &BX_CPU_C::AND_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_RAXId, NULL, &BX_CPU_C::SUB_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_RAXId, NULL, &BX_CPU_C::XOR_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_RAXId, NULL, &BX_CPU_C::TEST_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_RAXId, NULL, &BX_CPU_C::CMP_EqIdR, 0, OP_RAXReg, OP_Id, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ADD_EqId, &BX_CPU_C::ADD_EqIdM, &BX_CPU_C::ADD_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_OR_EqId, &BX_CPU_C::OR_EqIdM, &BX_CPU_C::OR_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADC_EqId, &BX_CPU_C::ADC_EqIdM, &BX_CPU_C::ADC_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SBB_EqId, &BX_CPU_C::SBB_EqIdM, &BX_CPU_C::SBB_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_AND_EqId, &BX_CPU_C::AND_EqIdM, &BX_CPU_C::AND_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SUB_EqId, &BX_CPU_C::SUB_EqIdM, &BX_CPU_C::SUB_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XOR_EqId, &BX_CPU_C::XOR_EqIdM, &BX_CPU_C::XOR_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TEST_EqId, &BX_CPU_C::TEST_EqIdM, &BX_CPU_C::TEST_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMP_EqId, &BX_CPU_C::CMP_EqIdM, &BX_CPU_C::CMP_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_XCHG_EqGq, &BX_CPU_C::XCHG_EqGqM, &BX_CPU_C::XCHG_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LEA_GqM, &BX_CPU_C::LEA_GqM, &BX_CPU_C::BxError, 0, OP_Gq, OP_Mq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV64_GdEd, &BX_CPU_C::MOV64_GdEdM, &BX_CPU_C::MOV_GdEdR, 0, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV64_EdGd, &BX_CPU_C::MOV64_EdGdM, &BX_CPU_C::MOV_GdEdR, 0, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_GqEq, &BX_CPU_C::MOV_GqEqM, &BX_CPU_C::MOV_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EqGq, &BX_CPU_C::MOV_EqGqM, &BX_CPU_C::MOV_GqEqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EqId, &BX_CPU_C::MOV_EqIdM, &BX_CPU_C::MOV_EqIdR, 0, OP_Eq, OP_Id, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_MOV_RAXOq, NULL, &BX_CPU_C::MOV_RAXOq, 0, OP_RAXReg, OP_Oq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_OqRAX, NULL, &BX_CPU_C::MOV_OqRAX, 0, OP_Oq, OP_RAXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_EAXOq, NULL, &BX_CPU_C::MOV_EAXOq, 0, OP_EAXReg, OP_Oq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_OqEAX, NULL, &BX_CPU_C::MOV_OqEAX, 0, OP_Oq, OP_EAXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_AXOq, NULL, &BX_CPU_C::MOV_AXOq, 0, OP_AXReg, OP_Oq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_OqAX, NULL, &BX_CPU_C::MOV_OqAX, 0, OP_Oq, OP_AXReg, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_ALOq, NULL, &BX_CPU_C::MOV_ALOq, 0, OP_ALReg, OP_Oq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_OqAL, NULL, &BX_CPU_C::MOV_OqAL, 0, OP_Oq, OP_ALReg, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_REP_MOVSQ_XqYq, NULL, &BX_CPU_C::REP_MOVSQ_XqYq, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_CMPSQ_XqYq, NULL, &BX_CPU_C::REP_CMPSQ_XqYq, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_STOSQ_YqRAX, NULL, &BX_CPU_C::REP_STOSQ_YqRAX, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_LODSQ_RAXXq, NULL, &BX_CPU_C::REP_LODSQ_RAXXq, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_REP_SCASQ_RAXXq, NULL, &BX_CPU_C::REP_SCASQ_RAXXq, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm

bx_define_opcode(BX_IA_CALL_Jq, NULL, &BX_CPU_C::CALL_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP_Jq, NULL, &BX_CPU_C::JMP_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_JO_Jq, NULL, &BX_CPU_C::JO_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNO_Jq, NULL, &BX_CPU_C::JNO_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JB_Jq, NULL, &BX_CPU_C::JB_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNB_Jq, NULL, &BX_CPU_C::JNB_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JZ_Jq, NULL, &BX_CPU_C::JZ_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNZ_Jq, NULL, &BX_CPU_C::JNZ_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JBE_Jq, NULL, &BX_CPU_C::JBE_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNBE_Jq, NULL, &BX_CPU_C::JNBE_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JS_Jq, NULL, &BX_CPU_C::JS_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNS_Jq, NULL, &BX_CPU_C::JNS_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JP_Jq, NULL, &BX_CPU_C::JP_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNP_Jq, NULL, &BX_CPU_C::JNP_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JL_Jq, NULL, &BX_CPU_C::JL_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNL_Jq, NULL, &BX_CPU_C::JNL_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JLE_Jq, NULL, &BX_CPU_C::JLE_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_JNLE_Jq, NULL, &BX_CPU_C::JNLE_Jq, 0, OP_Jq, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ENTER64_IwIb, NULL, &BX_CPU_C::ENTER64_IwIb, 0, OP_Iw, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LEAVE64, NULL, &BX_CPU_C::LEAVE64, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IRET64, NULL, &BX_CPU_C::IRET64, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_SHLD_EqGq, &BX_CPU_C::SHLD_EqGqM, &BX_CPU_C::SHLD_EqGqR, 0, OP_Eq, OP_Gq, OP_CLReg, OP_NONE, 0)
bx_define_opcode(BX_IA_SHLD_EqGqIb, &BX_CPU_C::SHLD_EqGqM, &BX_CPU_C::SHLD_EqGqR, 0, OP_Eq, OP_Gq, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRD_EqGq, &BX_CPU_C::SHRD_EqGqM, &BX_CPU_C::SHRD_EqGqR, 0, OP_Eq, OP_Gq, OP_CLReg, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRD_EqGqIb, &BX_CPU_C::SHRD_EqGqM, &BX_CPU_C::SHRD_EqGqR, 0, OP_Eq, OP_Gq, OP_Ib, OP_NONE, 0)

bx_define_opcode(BX_IA_IMUL_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::IMUL_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_GqEqId, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::IMUL_GqEqIdR, 0, OP_Gq, OP_Eq, OP_Id, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVZX_GqEb, &BX_CPU_C::MOVZX_GqEbM, &BX_CPU_C::MOVZX_GqEbR, 0, OP_Gq, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVZX_GqEw, &BX_CPU_C::MOVZX_GqEwM, &BX_CPU_C::MOVZX_GqEwR, 0, OP_Gq, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVSX_GqEb, &BX_CPU_C::MOVSX_GqEbM, &BX_CPU_C::MOVSX_GqEbR, 0, OP_Gq, OP_Eb, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVSX_GqEw, &BX_CPU_C::MOVSX_GqEwM, &BX_CPU_C::MOVSX_GqEwR, 0, OP_Gq, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVSX_GqEd, &BX_CPU_C::MOVSX_GqEdM, &BX_CPU_C::MOVSX_GqEdR, 0, OP_Gq, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BSWAP_RRX, NULL, &BX_CPU_C::BSWAP_RRX, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BSF_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BSF_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BSR_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BSR_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BT_EqGq, &BX_CPU_C::BT_EqGqM, &BX_CPU_C::BT_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTS_EqGq, &BX_CPU_C::BTS_EqGqM, &BX_CPU_C::BTS_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTR_EqGq, &BX_CPU_C::BTR_EqGqM, &BX_CPU_C::BTR_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTC_EqGq, &BX_CPU_C::BTC_EqGqM, &BX_CPU_C::BTC_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BT_EqIb, &BX_CPU_C::BT_EqIbM, &BX_CPU_C::BT_EqIbR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTS_EqIb, &BX_CPU_C::BTS_EqIbM, &BX_CPU_C::BTS_EqIbR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTR_EqIb, &BX_CPU_C::BTR_EqIbM, &BX_CPU_C::BTR_EqIbR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BTC_EqIb, &BX_CPU_C::BTC_EqIbM, &BX_CPU_C::BTC_EqIbR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_NOT_Eq, &BX_CPU_C::NOT_EqM, &BX_CPU_C::NOT_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_NEG_Eq, &BX_CPU_C::NEG_EqM, &BX_CPU_C::NEG_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_Eq, &BX_CPU_C::ROL_EqM, &BX_CPU_C::ROL_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_Eq, &BX_CPU_C::ROR_EqM, &BX_CPU_C::ROR_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_Eq, &BX_CPU_C::RCL_EqM, &BX_CPU_C::RCL_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_Eq, &BX_CPU_C::RCR_EqM, &BX_CPU_C::RCR_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_Eq, &BX_CPU_C::SHL_EqM, &BX_CPU_C::SHL_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_Eq, &BX_CPU_C::SHR_EqM, &BX_CPU_C::SHR_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_Eq, &BX_CPU_C::SAR_EqM, &BX_CPU_C::SAR_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_ROL_EqIb, &BX_CPU_C::ROL_EqM, &BX_CPU_C::ROL_EqR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ROR_EqIb, &BX_CPU_C::ROR_EqM, &BX_CPU_C::ROR_EqR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCL_EqIb, &BX_CPU_C::RCL_EqM, &BX_CPU_C::RCL_EqR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RCR_EqIb, &BX_CPU_C::RCR_EqM, &BX_CPU_C::RCR_EqR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHL_EqIb, &BX_CPU_C::SHL_EqM, &BX_CPU_C::SHL_EqR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SHR_EqIb, &BX_CPU_C::SHR_EqM, &BX_CPU_C::SHR_EqR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SAR_EqIb, &BX_CPU_C::SAR_EqM, &BX_CPU_C::SAR_EqR, 0, OP_Eq, OP_Ib, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_MUL_RAXEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::MUL_RAXEqR, 0, OP_RAXReg, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IMUL_RAXEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::IMUL_RAXEqR, 0, OP_RAXReg, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DIV_RAXEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::DIV_RAXEqR, 0, OP_RAXReg, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_IDIV_RAXEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::IDIV_RAXEqR, 0, OP_RAXReg, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_INC_Eq, &BX_CPU_C::INC_EqM, &BX_CPU_C::INC_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_DEC_Eq, &BX_CPU_C::DEC_EqM, &BX_CPU_C::DEC_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_CALL_Eq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CALL_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CALL64_Ep, &BX_CPU_C::CALL64_Ep, &BX_CPU_C::BxError, 0, OP_M, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP_Eq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::JMP_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JMP64_Ep, &BX_CPU_C::JMP64_Ep, &BX_CPU_C::BxError, 0, OP_M, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_PUSHF_Fq, NULL, &BX_CPU_C::PUSHF_Fq, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POPF_Fq, NULL, &BX_CPU_C::POPF_Fq, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_CMPXCHG_EqGq, &BX_CPU_C::CMPXCHG_EqGqM, &BX_CPU_C::CMPXCHG_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CDQE, NULL, &BX_CPU_C::CDQE, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CQO, NULL, &BX_CPU_C::CQO, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XADD_EqGq, &BX_CPU_C::XADD_EqGqM, &BX_CPU_C::XADD_EqGqR, 0, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_RETnear64_Iw, NULL, &BX_CPU_C::RETnear64_Iw, 0, OP_Iw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETnear64, NULL, &BX_CPU_C::RETnear64, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETfar64_Iw, NULL, &BX_CPU_C::RETfar64_Iw, 0, OP_Iw, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_RETfar64, NULL, &BX_CPU_C::RETfar64_Iw, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_CMOVO_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVO_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNO_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNO_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVB_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVB_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNB_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNB_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVZ_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVZ_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNZ_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNZ_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVBE_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVBE_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNBE_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNBE_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVS_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVS_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNS_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNS_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVP_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVP_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNP_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNP_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVL_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVL_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNL_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNL_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVLE_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVLE_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMOVNLE_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CMOVNLE_GqEqR, 0, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_PUSH_Eq, &BX_CPU_C::PUSH_EqM, &BX_CPU_C::PUSH_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP_Eq, &BX_CPU_C::POP_EqM, &BX_CPU_C::POP_EqR, 0, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH64_Id, NULL, &BX_CPU_C::PUSH64_Id, 0, OP_Id, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH64_FS, NULL, &BX_CPU_C::PUSH64_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP64_FS, NULL, &BX_CPU_C::POP64_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_PUSH64_GS, NULL, &BX_CPU_C::PUSH64_Sw, 0, OP_NONE, OP_Sw, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_POP64_GS, NULL, &BX_CPU_C::POP64_Sw, 0, OP_Sw, OP_NONE, OP_NONE, OP_NONE, 0)

// IDT/GDT/LDTR/TR access - keep NNN for VMX
bx_define_opcode(BX_IA_SGDT64_Ms, &BX_CPU_C::SGDT64_Ms, &BX_CPU_C::BxError, 0, OP_M, BX_SRC_NNN, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_SIDT64_Ms, &BX_CPU_C::SIDT64_Ms, &BX_CPU_C::BxError, 0, OP_M, BX_SRC_NNN, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_LGDT64_Ms, &BX_CPU_C::LGDT64_Ms, &BX_CPU_C::BxError, 0, BX_SRC_NNN, OP_M, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_LIDT64_Ms, &BX_CPU_C::LIDT64_Ms, &BX_CPU_C::BxError, 0, BX_SRC_NNN, OP_M, OP_NONE, OP_NONE, 0) // FIXME disasm
// IDT/GDT/LDTR/TR access - keep NNN for VMX

bx_define_opcode(BX_IA_MOV_RRXIq, NULL, &BX_CPU_C::MOV_RRXIq, 0, OP_Eq, OP_Iq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_XCHG_RRXRAX, NULL, &BX_CPU_C::XCHG_RRXRAX, 0, OP_Eq, OP_RAXReg, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_LSS_GqMp, &BX_CPU_C::LSS_GqMp, &BX_CPU_C::BxError, 0, OP_Gq, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LFS_GqMp, &BX_CPU_C::LFS_GqMp, &BX_CPU_C::BxError, 0, OP_Gq, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LGS_GqMp, &BX_CPU_C::LGS_GqMp, &BX_CPU_C::BxError, 0, OP_Gq, OP_Mp, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CMPXCHG16B, &BX_CPU_C::CMPXCHG16B, &BX_CPU_C::BxError, BX_ISA_CMPXCHG16B, OP_Mdq, OP_NONE, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_LOOPNE64_Jb, NULL, &BX_CPU_C::LOOPNE64_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOPE64_Jb, NULL, &BX_CPU_C::LOOPE64_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_LOOP64_Jb, NULL, &BX_CPU_C::LOOP64_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_JRCXZ_Jb, NULL, &BX_CPU_C::JRCXZ_Jb, 0, OP_Jb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

bx_define_opcode(BX_IA_MOVQ_EqVq, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::MOVQ_EqVqR, 0, OP_Eq, OP_Vq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVQ_PqEq, &BX_CPU_C::MOVQ_PqQqM, &BX_CPU_C::MOVQ_PqEqR, 0, OP_Pq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVQ_VdqEq, &BX_CPU_C::MOVQ_VqWqM, &BX_CPU_C::MOVQ_VdqEqR, 0, OP_Vdq, OP_Eq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSI2SS_VssEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CVTSI2SS_VssEqR, 0, OP_Vss, OP_Eq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSI2SD_VsdEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::CVTSI2SD_VsdEqR, 0, OP_Vsd, OP_Eq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTSS2SI_GqWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTTSS2SI_GqWssR, 0, OP_Gq, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTTSD2SI_GqWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTTSD2SI_GqWsdR, 0, OP_Gq, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSS2SI_GqWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTSS2SI_GqWssR, 0, OP_Gq, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_CVTSD2SI_GqWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTSD2SI_GqWsdR, 0, OP_Gq, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVNTI64_MdGd, &BX_CPU_C::MOV64_EdGdM, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Md, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOVNTI_MqGq, &BX_CPU_C::MOV_EqGqM, &BX_CPU_C::BxError, BX_ISA_SSE2, OP_Mq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_CR0Rq, NULL, &BX_CPU_C::MOV_CR0Rq, 0, OP_Cq, OP_Eq, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_CR2Rq, NULL, &BX_CPU_C::MOV_CR2Rq, 0, OP_Cq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_CR3Rq, NULL, &BX_CPU_C::MOV_CR3Rq, 0, OP_Cq, OP_Eq, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_CR4Rq, NULL, &BX_CPU_C::MOV_CR4Rq, 0, OP_Cq, OP_Eq, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_RqCR0, NULL, &BX_CPU_C::MOV_RqCR0, 0, OP_Eq, OP_Cq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_RqCR2, NULL, &BX_CPU_C::MOV_RqCR2, 0, OP_Eq, OP_Cq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_RqCR3, NULL, &BX_CPU_C::MOV_RqCR3, 0, OP_Eq, OP_Cq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_RqCR4, NULL, &BX_CPU_C::MOV_RqCR4, 0, OP_Eq, OP_Cq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_MOV_DqRq, NULL, &BX_CPU_C::MOV_DqRq, 0, OP_Dq, OP_Eq, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_MOV_RqDq, NULL, &BX_CPU_C::MOV_RqDq, 0, OP_Eq, OP_Dq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SWAPGS, &BX_CPU_C::BxError, &BX_CPU_C::SWAPGS, 0, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RDFSBASE, &BX_CPU_C::BxError, &BX_CPU_C::RDFSBASE, BX_ISA_FSGSBASE, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_RDGSBASE, &BX_CPU_C::BxError, &BX_CPU_C::RDGSBASE, BX_ISA_FSGSBASE, BX_SRC_RM, OP_NONE, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_WRFSBASE, &BX_CPU_C::BxError, &BX_CPU_C::WRFSBASE, BX_ISA_FSGSBASE, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
bx_define_opcode(BX_IA_WRGSBASE, &BX_CPU_C::BxError, &BX_CPU_C::WRGSBASE, BX_ISA_FSGSBASE, OP_NONE, BX_SRC_RM, OP_NONE, OP_NONE, 0) // FIXME disasm
#endif

bx_define_opcode(BX_IA_RDTSCP, &BX_CPU_C::BxError, &BX_CPU_C::RDTSCP, BX_ISA_RDTSCP, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)

// VMX
bx_define_opcode(BX_IA_VMXON_Mq, &BX_CPU_C::VMXON, &BX_CPU_C::BxError, BX_ISA_VMX, OP_Mq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VMXOFF, &BX_CPU_C::BxError, &BX_CPU_C::VMXOFF, BX_ISA_VMX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_VMCALL, &BX_CPU_C::BxError, &BX_CPU_C::VMCALL, BX_ISA_VMX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_VMLAUNCH, &BX_CPU_C::BxError, &BX_CPU_C::VMLAUNCH, BX_ISA_VMX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_VMRESUME, &BX_CPU_C::BxError, &BX_CPU_C::VMLAUNCH, BX_ISA_VMX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_VMCLEAR_Mq, &BX_CPU_C::VMCLEAR, &BX_CPU_C::BxError, BX_ISA_VMX, OP_Mq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VMPTRLD_Mq, &BX_CPU_C::VMPTRLD, &BX_CPU_C::BxError, BX_ISA_VMX, OP_Mq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VMPTRST_Mq, &BX_CPU_C::VMPTRST, &BX_CPU_C::BxError, BX_ISA_VMX, OP_Mq, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VMREAD_EdGd, &BX_CPU_C::VMREAD_EdGd, &BX_CPU_C::VMREAD_EdGd, BX_ISA_VMX, OP_Ed, OP_Gd, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VMWRITE_GdEd, &BX_CPU_C::VMWRITE_GdEd, &BX_CPU_C::VMWRITE_GdEd, BX_ISA_VMX, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_VMREAD_EqGq, &BX_CPU_C::VMREAD_EqGq, &BX_CPU_C::VMREAD_EqGq, BX_ISA_VMX, OP_Eq, OP_Gq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VMWRITE_GqEq, &BX_CPU_C::VMWRITE_GqEq, &BX_CPU_C::VMWRITE_GqEq, BX_ISA_VMX, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
#endif
#if BX_CPU_LEVEL >= 6
bx_define_opcode(BX_IA_INVEPT, &BX_CPU_C::INVEPT, &BX_CPU_C::BxError, BX_ISA_VMX, BX_SRC_NNN, BX_SRC_RM, OP_NONE, OP_NONE, BX_TRACE_END) // FIXME disasm
bx_define_opcode(BX_IA_INVVPID, &BX_CPU_C::INVVPID, &BX_CPU_C::BxError, BX_ISA_VMX, BX_SRC_NNN, BX_SRC_RM, OP_NONE, OP_NONE, BX_TRACE_END) // FIXME disasm
#endif
bx_define_opcode(BX_IA_VMFUNC, &BX_CPU_C::BxError, &BX_CPU_C::VMFUNC, BX_ISA_VMX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
// VMX

// SMX
bx_define_opcode(BX_IA_GETSEC, &BX_CPU_C::GETSEC, &BX_CPU_C::GETSEC, BX_ISA_SMX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
// SMX

// SVM
bx_define_opcode(BX_IA_VMRUN, &BX_CPU_C::BxError, &BX_CPU_C::VMRUN, BX_ISA_SVM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_VMMCALL, &BX_CPU_C::BxError, &BX_CPU_C::VMMCALL, BX_ISA_SVM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_VMLOAD, &BX_CPU_C::BxError, &BX_CPU_C::VMLOAD, BX_ISA_SVM, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_VMSAVE, &BX_CPU_C::BxError, &BX_CPU_C::VMSAVE, BX_ISA_SVM, OP_M, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_STGI, &BX_CPU_C::BxError, &BX_CPU_C::STGI, BX_ISA_SVM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CLGI, &BX_CPU_C::BxError, &BX_CPU_C::CLGI, BX_ISA_SVM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_SKINIT, &BX_CPU_C::BxError, &BX_CPU_C::SKINIT, BX_ISA_SVM, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
bx_define_opcode(BX_IA_INVLPGA, &BX_CPU_C::BxError, &BX_CPU_C::INVLPGA, BX_ISA_SVM, OP_Mb, OP_NONE, OP_NONE, OP_NONE, BX_TRACE_END)
// SVM

#if BX_CPU_LEVEL >= 6
bx_define_opcode(BX_IA_INVPCID, &BX_CPU_C::INVPCID, &BX_CPU_C::BxError, BX_ISA_INVPCID, BX_SRC_NNN, BX_SRC_RM, OP_NONE, OP_NONE, BX_TRACE_END) // FIXME disasm
#endif

#if BX_SUPPORT_AVX && BX_CPU_LEVEL >= 6
// AVX1/AVX2
bx_define_opcode(BX_IA_VZEROUPPER, NULL, &BX_CPU_C::VZEROUPPER, BX_ISA_AVX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VZEROALL, NULL, &BX_CPU_C::VZEROALL, BX_ISA_AVX, OP_NONE, OP_NONE, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VLDMXCSR, &BX_CPU_C::LDMXCSR, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Md, OP_NONE, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSTMXCSR, &BX_CPU_C::STMXCSR, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Md, OP_NONE, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVAPS_VpsWps, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVAPS_VpsWps, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVAPS_WpsVps, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVAPS_WpsVps, &BX_CPU_C::VMOVAPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVAPD_VpdWpd, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVAPD_VpdWpd, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVAPD_WpdVpd, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVAPD_WpdVpd, &BX_CPU_C::VMOVAPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVUPS_VpsWps, &BX_CPU_C::VMOVUPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVUPS_VpsWps, &BX_CPU_C::VMOVUPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVUPS_WpsVps, &BX_CPU_C::MOVUPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVUPS_WpsVps, &BX_CPU_C::VMOVUPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVUPD_VpdWpd, &BX_CPU_C::VMOVUPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVUPD_VpdWpd, &BX_CPU_C::VMOVUPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVUPD_WpdVpd, &BX_CPU_C::MOVUPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVUPD_WpdVpd, &BX_CPU_C::VMOVUPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVDQA_VdqWdq, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVDQA_VdqWdq, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVDQA_WdqVdq, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVDQA_WdqVdq, &BX_CPU_C::VMOVAPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVDQU_VdqWdq, &BX_CPU_C::VMOVUPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVDQU_VdqWdq, &BX_CPU_C::VMOVUPS_VpsWpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVDQU_WdqVdq, &BX_CPU_C::MOVUPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVDQU_WdqVdq, &BX_CPU_C::VMOVUPS_WpsVpsM, &BX_CPU_C::VMOVAPS_VpsWpsR, BX_ISA_AVX, OP_Wdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVSD_VsdHpdWsd, &BX_CPU_C::MOVQ_VqWqM, &BX_CPU_C::VMOVSD_VsdHpdWsdR, BX_ISA_AVX, BX_SRC_NNN, BX_SRC_RM, BX_SRC_MEM_NO_VVV, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVSS_VssHpsWss, &BX_CPU_C::MOVSS_VssWssM, &BX_CPU_C::VMOVSS_VssHpsWssR, BX_ISA_AVX, BX_SRC_NNN, BX_SRC_RM, BX_SRC_MEM_NO_VVV, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVSD_WsdHpdVsd, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::VMOVSD_VsdHpdWsdR, BX_ISA_AVX, BX_SRC_RM, BX_SRC_NNN, BX_SRC_MEM_NO_VVV, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVSS_WssHpsVss, &BX_CPU_C::MOVSS_WssVssM, &BX_CPU_C::VMOVSS_VssHpsWssR, BX_ISA_AVX, BX_SRC_RM, BX_SRC_NNN, BX_SRC_MEM_NO_VVV, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVLPS_VpsHpsMq, &BX_CPU_C::VMOVLPD_VpdHpdMq, &BX_CPU_C::VMOVHLPS_VpsHpsWps, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Mq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVHPS_VpsHpsMq, &BX_CPU_C::VMOVHPD_VpdHpdMq, &BX_CPU_C::VMOVLHPS_VpsHpsWps, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Mq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVLPS_MqVps, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mq, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVHPS_MqVps, &BX_CPU_C::MOVHPS_MqVps, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mq, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVLPD_MqVsd, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mq, OP_Vsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVHPD_MqVsd, &BX_CPU_C::MOVHPS_MqVps, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mq, OP_Vsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVLPD_VpdHpdMq, &BX_CPU_C::VMOVLPD_VpdHpdMq, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Mq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVHPD_VpdHpdMq, &BX_CPU_C::VMOVHPD_VpdHpdMq, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Mq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVDDUP_VpdWpd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMOVDDUP_VpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVDDUP_VpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMOVDDUP_VpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VMOVSLDUP_VpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMOVSLDUP_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMOVSHDUP_VpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMOVSHDUP_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VLDDQU_VdqMdq, &BX_CPU_C::VMOVUPS_VpsWpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVNTDQA_VdqMdq, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Vdq, OP_Mdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVNTDQA_VdqMdq, &BX_CPU_C::VMOVAPS_VpsWpsM, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vdq, OP_Mdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVNTPS_MpsVps, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVNTPS_MpsVps, &BX_CPU_C::VMOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mps, OP_Vps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVNTPD_MpdVpd, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVNTPD_MpdVpd, &BX_CPU_C::VMOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mpd, OP_Vpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVNTDQ_MdqVdq, &BX_CPU_C::MOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMOVNTDQ_MdqVdq, &BX_CPU_C::VMOVAPS_WpsVpsM, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VUCOMISS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::UCOMISS_VssWssR, BX_ISA_AVX, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCOMISS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::COMISS_VssWssR, BX_ISA_AVX, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VUCOMISD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::UCOMISD_VsdWsdR, BX_ISA_AVX, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCOMISD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::COMISD_VsdWsdR, BX_ISA_AVX, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VRSQRTSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VRSQRTSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VRSQRTPS_VpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VRSQRTPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VRCPSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VRCPSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VRCPPS_VpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VRCPPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VANDPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VANDPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VANDPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VANDPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VANDNPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VANDNPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VANDNPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VANDNPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VORPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VORPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VORPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VORPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VXORPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VXORPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VXORPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VXORPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPSHUFD_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPERMILPS_VpsWpsIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSHUFD_VdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMILPS_VpsWpsIbR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSHUFHW_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHUFHW_VdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSHUFHW_VdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSHUFHW_VdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSHUFLW_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHUFLW_VdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSHUFLW_VdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSHUFLW_VdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VHADDPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VHADDPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VHADDPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VHADDPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VHSUBPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VHSUBPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VHSUBPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VHSUBPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSHUFPS_VpsHpsWpsIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VSHUFPS_VpsHpsWpsIbR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSHUFPD_VpdHpdWpdIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VSHUFPD_VpdHpdWpdIbR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VADDSUBPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VADDSUBPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VADDSUBPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VADDSUBPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VROUNDPS_VpsWpsIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VROUNDPS_VpsWpsIbR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VROUNDPD_VpdWpdIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VROUNDPD_VpdWpdIbR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VROUNDSD_VsdHpdWsdIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VROUNDSD_VsdHpdWsdIbR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VROUNDSS_VssHpsWssIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VROUNDSS_VssHpsWssIbR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VDPPS_VpsHpsWpsIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VDPPS_VpsHpsWpsIbR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VDPPD_VpdHpdWpdIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::DPPD_VpdHpdWpdIbR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_Ib, BX_PREPARE_AVX)

// SSE alias
bx_define_opcode(BX_IA_VADDPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VADDPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VADDPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VADDPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VADDSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VADDSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VADDSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VADDSD_VsdHpdWsdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VMULPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMULPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMULPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMULPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMULSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMULSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMULSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMULSD_VsdHpdWsdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VSUBPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VSUBPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSUBPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VSUBPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSUBSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VSUBSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSUBSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VSUBSD_VsdHpdWsdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VDIVPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VDIVPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VDIVPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VDIVPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VDIVSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VDIVSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VDIVSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VDIVSD_VsdHpdWsdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VMAXPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMAXPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMAXPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMAXPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMAXSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMAXSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMAXSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMAXSD_VsdHpdWsdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VMINPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMINPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMINPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMINPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMINSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMINSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMINSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMINSD_VsdHpdWsdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VSQRTPS_VpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VSQRTPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSQRTPD_VpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VSQRTPD_VpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSQRTSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VSQRTSS_VssHpsWssR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VSQRTSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VSQRTSD_VsdHpdWsdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VCMPPS_VpsHpsWpsIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCMPPS_VpsHpsWpsIbR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCMPPD_VpdHpdWpdIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCMPPD_VpdHpdWpdIbR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCMPSS_VssHpsWssIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VCMPSS_VssHpsWssIbR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Wss, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCMPSD_VsdHpdWsdIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VCMPSD_VsdHpdWsdIbR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Wsd, OP_Ib, BX_PREPARE_AVX)
// SSE alias

bx_define_opcode(BX_IA_V128_VPSRLW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRLW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRLW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRLD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRLD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRLD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRLQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRLQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRLQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRAW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRAW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRAW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRAW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRAD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRAD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRAD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRAD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSLLW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSLLW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSLLW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSLLD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSLLD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSLLD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSLLQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSLLQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSLLQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPSRLW_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRLW_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRLW_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLW_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRAW_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRAW_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRAW_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRAW_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSLLW_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSLLW_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSLLW_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLW_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRLD_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRLD_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRLD_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLD_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRAD_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRAD_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRAD_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRAD_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSLLD_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSLLD_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSLLD_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLD_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRLQ_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRLQ_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRLQ_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLQ_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSLLQ_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSLLQ_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSLLQ_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLQ_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSRLDQ_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSRLDQ_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSRLDQ_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLDQ_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSLLDQ_UdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSLLDQ_UdqIb, BX_ISA_AVX, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSLLDQ_UdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLDQ_UdqIb, BX_ISA_AVX2, OP_Hdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPMOVMSKB_GdUdq, &BX_CPU_C::BxError, &BX_CPU_C::VPMOVMSKB_GdUdq, BX_ISA_AVX, OP_Gd, OP_Udq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMOVMSKB_GdUdq, &BX_CPU_C::BxError, &BX_CPU_C::VPMOVMSKB_GdUdq, BX_ISA_AVX2, OP_Gd, OP_Udq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VMOVMSKPS_GdUps, &BX_CPU_C::BxError, &BX_CPU_C::VMOVMSKPS_GdUps, BX_ISA_AVX, OP_Gd, OP_Ups, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMOVMSKPD_GdUpd, &BX_CPU_C::BxError, &BX_CPU_C::VMOVMSKPD_GdUpd, BX_ISA_AVX, OP_Gd, OP_Upd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VUNPCKLPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKLPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VUNPCKHPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKHPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VUNPCKLPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKLPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VUNPCKHPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKHPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPUNPCKHDQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VUNPCKHPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKHDQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKHPS_VpsHpsWpsR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPUNPCKLDQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VUNPCKLPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKLDQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKLPS_VpsHpsWpsR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPUNPCKLBW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPUNPCKLBW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKLBW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPUNPCKLBW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPUNPCKLWD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPUNPCKLWD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKLWD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPUNPCKLWD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPUNPCKHBW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPUNPCKHBW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKHBW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPUNPCKHBW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPUNPCKHWD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPUNPCKHWD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKHWD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPUNPCKHWD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPUNPCKLQDQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VUNPCKLPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKLQDQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKLPD_VpdHpdWpdR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPUNPCKHQDQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VUNPCKHPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPUNPCKHQDQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VUNPCKHPD_VpdHpdWpdR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPCMPEQB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPEQB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPEQB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPEQB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPEQW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPEQW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPEQW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPEQW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPEQD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPEQD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPEQD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPEQD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPEQQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPEQQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPEQQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPEQQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPGTB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPGTB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPGTB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPGTB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPGTW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPGTW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPGTW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPGTW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPGTD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPGTD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPGTD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPGTD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPGTQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCMPGTQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPCMPGTQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMPGTQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPSUBSB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBSB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBSB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBSB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSUBSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDSB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDSB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDSB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDSB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSUBUSB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBUSB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBUSB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBUSB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSUBUSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBUSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBUSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBUSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDUSB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDUSB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDUSB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDUSB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDUSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDUSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDUSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDUSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPAVGB_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPAVGB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPAVGB_VdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPAVGB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPAVGW_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPAVGW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPAVGW_VdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPAVGW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPANDN_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VANDNPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPANDN_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VANDNPS_VpsHpsWpsR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPAND_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VANDPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPAND_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VANDPS_VpsHpsWpsR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPOR_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VORPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPOR_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VORPS_VpsHpsWpsR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPXOR_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VXORPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPXOR_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VXORPS_VpsHpsWpsR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPMULHRSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMULHRSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMULHRSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMULHRSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMULDQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMULDQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMULDQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMULDQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMULUDQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMULUDQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMULUDQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMULUDQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMULLD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMULLD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMULLD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMULLD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMULLW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMULLW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMULLW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMULLW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMULHW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMULHW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMULHW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMULHW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMULHUW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMULHUW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMULHUW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMULHUW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPSADBW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSADBW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSADBW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSADBW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMASKMOVDQU_VdqUdq, &BX_CPU_C::BxError, &BX_CPU_C::MASKMOVDQU_VdqUdq, BX_ISA_AVX, OP_NONE, OP_Vdq, OP_Udq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPSUBB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSUBW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSUBD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSUBQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSUBQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSUBQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSUBQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPADDQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPADDQ_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPADDQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPADDQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPSHUFB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHUFB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSHUFB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSHUFB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPHADDW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPHADDW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPHADDW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPHADDD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPHADDD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPHADDD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPHSUBW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHSUBW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPHSUBW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPHSUBW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPHSUBD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHSUBD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPHSUBD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPHSUBD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPHADDSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPHADDSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPHADDSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPHSUBSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHSUBSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPHSUBSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPHSUBSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPMADDWD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMADDWD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMADDWD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMADDWD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMADDUBSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMADDUBSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMADDUBSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMADDUBSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPSIGNB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSIGNB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSIGNB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSIGNB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSIGNW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSIGNW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSIGNW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSIGNW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPSIGND_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSIGND_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPSIGND_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSIGND_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VTESTPS_VpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VTESTPS_VpsWpsR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VTESTPD_VpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VTESTPD_VpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPTEST_VdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPTEST_VdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VBROADCASTSS_VpsMss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VPBROADCASTD_VdqWd, BX_ISA_AVX, OP_Vps, OP_Mss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VBROADCASTSD_VpdMsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VPBROADCASTQ_VdqWq, BX_ISA_AVX, OP_Vpd, OP_Msd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VBROADCASTF128_VdqMdq, &BX_CPU_C::VBROADCASTF128_VdqMdq, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Vdq, OP_Mdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPABSB_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPABSB_VdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPABSB_VdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPABSB_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPABSW_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPABSW_VdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPABSW_VdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPABSW_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPABSD_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPABSD_VdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPABSD_VdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPABSD_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPACKSSWB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPACKSSWB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPACKSSWB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPACKSSWB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPACKUSWB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPACKUSWB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPACKUSWB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPACKUSWB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPACKUSDW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPACKUSDW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPACKUSDW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPACKUSDW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPACKSSDW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPACKSSDW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPACKSSDW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPACKSSDW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VMASKMOVPS_VpsHpsMps, &BX_CPU_C::VMASKMOVPS_VpsHpsMps, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Mps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMASKMOVPD_VpdHpdMpd, &BX_CPU_C::VMASKMOVPD_VpdHpdMpd, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Mpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMASKMOVPS_MpsHpsVps, &BX_CPU_C::VMASKMOVPS_MpsHpsVps, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mps, OP_Hps, OP_Vps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMASKMOVPD_MpdHpdVpd, &BX_CPU_C::VMASKMOVPD_MpdHpdVpd, &BX_CPU_C::BxError, BX_ISA_AVX, OP_Mpd, OP_Hpd, OP_Vpd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VPMOVSXBW_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVSXBW_VdqWqR, BX_ISA_AVX, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXBD_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVSXBD_VdqWdR, BX_ISA_AVX, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXBQ_VdqWw, &BX_CPU_C::LOAD_Ww, &BX_CPU_C::PMOVSXBQ_VdqWwR, BX_ISA_AVX, OP_Vdq, OP_Ww, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXWD_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVSXWD_VdqWqR, BX_ISA_AVX, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXWQ_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVSXWQ_VdqWdR, BX_ISA_AVX, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXDQ_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVSXDQ_VdqWqR, BX_ISA_AVX, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXBW_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVZXBW_VdqWqR, BX_ISA_AVX, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXBD_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVZXBD_VdqWdR, BX_ISA_AVX, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXBQ_VdqWw, &BX_CPU_C::LOAD_Ww, &BX_CPU_C::PMOVZXBQ_VdqWwR, BX_ISA_AVX, OP_Vdq, OP_Ww, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXWD_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVZXWD_VdqWqR, BX_ISA_AVX, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXWQ_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::PMOVZXWQ_VdqWdR, BX_ISA_AVX, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXDQ_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::PMOVZXDQ_VdqWqR, BX_ISA_AVX, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPMINSB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMINSB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMINSB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMINSB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMINSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMINSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMINSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMINSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMINSD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMINSD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMINSD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMINSD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMINUB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMINUB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMINUB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMINUB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMINUW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMINUW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMINUW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMINUW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMINUD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMINUD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMINUD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMINUD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMAXSB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMAXSB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMAXSB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMAXSB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMAXSW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMAXSW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMAXSW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMAXSW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMAXSD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMAXSD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMAXSD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMAXSD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMAXUB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMAXUB_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMAXUB_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMAXUB_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMAXUW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMAXUW_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMAXUW_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMAXUW_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPMAXUD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMAXUD_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPMAXUD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPMAXUD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPHMINPOSUW_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PHMINPOSUW_VdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VPERMILPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMILPS_VpsHpsWpsR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPERMILPD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMILPD_VpdHpdWpdR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPERMILPS_VpsWpsIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMILPS_VpsWpsIbR, BX_ISA_AVX, OP_Vps, OP_Wps, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPERMILPD_VpdWpdIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMILPD_VpdWpdIbR, BX_ISA_AVX, OP_Vpd, OP_Wpd, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VBLENDPS_VpsHpsWpsIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VBLENDPS_VpsHpsWpsIbR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VBLENDPD_VpdHpdWpdIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VBLENDPD_VpdHpdWpdIbR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_Ib, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPBLENDW_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPBLENDW_VdqHdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPBLENDW_VdqHdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPBLENDW_VdqHdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPALIGNR_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPALIGNR_VdqHdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPALIGNR_VdqHdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPALIGNR_VdqHdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VINSERTPS_VpsWssIb, &BX_CPU_C::INSERTPS_VpsHpsWssIb, &BX_CPU_C::INSERTPS_VpsHpsWssIb, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wss, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VEXTRACTPS_EdVpsIb, &BX_CPU_C::EXTRACTPS_EdVpsIbM, &BX_CPU_C::EXTRACTPS_EdVpsIbR, BX_ISA_AVX, OP_Ed, OP_Vps, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPERM2F128_VdqHdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERM2F128_VdqHdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VINSERTF128_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VINSERTF128_VdqHdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VEXTRACTF128_WdqVdqIb, &BX_CPU_C::VEXTRACTF128_WdqVdqIbM, &BX_CPU_C::VEXTRACTF128_WdqVdqIbR, BX_ISA_AVX, OP_Wdq, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VBLENDVPS_VpsHpsWpsIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VBLENDVPS_VpsHpsWpsIbR, BX_ISA_AVX, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VBLENDVPD_VpdHpdWpdIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VBLENDVPD_VpdHpdWpdIbR, BX_ISA_AVX, OP_Vpd, OP_Hpd, OP_Wpd, OP_VIb, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPBLENDVB_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPBLENDVB_VdqHdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPBLENDVB_VdqHdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPBLENDVB_VdqHdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMPSADBW_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VMPSADBW_VdqHdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VMPSADBW_VdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VMPSADBW_VdqHdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPCMPESTRM_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPESTRM_VdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPESTRI_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPESTRI_VdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPISTRM_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPISTRM_VdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCMPISTRI_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCMPISTRI_VdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VAESIMC_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::AESIMC_VdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VAESENC_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::AESENC_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VAESENCLAST_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::AESENCLAST_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VAESDEC_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::AESDEC_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VAESDECLAST_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::AESDECLAST_VdqHdqWdqR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VAESKEYGENASSIST_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::AESKEYGENASSIST_VdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPCLMULQDQ_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::PCLMULQDQ_VdqHdqWdqIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VMOVD_VdqEd, &BX_CPU_C::MOVSS_VssWssM, &BX_CPU_C::MOVD_VdqEdR, BX_ISA_AVX, OP_Vdq, OP_Ed, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVD_EdVd, &BX_CPU_C::MOVSS_WssVssM, &BX_CPU_C::MOVD_EdVdR, BX_ISA_AVX, OP_Ed, OP_Vd, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V128_VPINSRB_VdqEbIb, &BX_CPU_C::PINSRB_VdqHdqEbIbM, &BX_CPU_C::PINSRB_VdqHdqEbIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Eb, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPINSRW_VdqEwIb, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::PINSRW_VdqHdqEwIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Ew, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPINSRD_VdqEdIb, &BX_CPU_C::PINSRD_VdqHdqEdIbM, &BX_CPU_C::PINSRD_VdqHdqEdIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Ed, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPINSRQ_VdqEqIb, &BX_CPU_C::PINSRD_VdqHdqEdIbM, &BX_CPU_C::PINSRD_VdqHdqEdIbR, BX_ISA_AVX, OP_Vdq, OP_Hdq, OP_Eq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPEXTRW_GdUdqIb, &BX_CPU_C::BxError, &BX_CPU_C::PEXTRW_GdUdqIb, BX_ISA_AVX, OP_Gd, OP_Udq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPEXTRB_EbdVdqIb, &BX_CPU_C::PEXTRB_EbdVdqIbM, &BX_CPU_C::PEXTRB_EbdVdqIbR, BX_ISA_AVX, OP_Ebd, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPEXTRW_EwdVdqIb, &BX_CPU_C::PEXTRW_EwdVdqIbM, &BX_CPU_C::PEXTRW_EwdVdqIbR, BX_ISA_AVX, OP_Ewd, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPEXTRD_EdVdqIb, &BX_CPU_C::PEXTRD_EdVdqIbM, &BX_CPU_C::PEXTRD_EdVdqIbR, BX_ISA_AVX, OP_Ed, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VPEXTRQ_EqVdqIb, &BX_CPU_C::PEXTRQ_EqVdqIbM, &BX_CPU_C::PEXTRQ_EqVdqIbR, BX_ISA_AVX, OP_Eq, OP_Vdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VCVTPS2PD_VpdWps, &BX_CPU_C::LOAD_Half_Vector, &BX_CPU_C::VCVTPS2PD_VpdWpsR, BX_ISA_AVX, OP_Vpd, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTTPD2DQ_VqWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCVTTPD2DQ_VqWpdR, BX_ISA_AVX, OP_Vq, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTPD2DQ_VqWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCVTPD2DQ_VqWpdR, BX_ISA_AVX, OP_Vq, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTDQ2PD_VpdWq, &BX_CPU_C::LOAD_Half_Vector, &BX_CPU_C::VCVTDQ2PD_VpdWqR, BX_ISA_AVX, OP_Vpd, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTPD2PS_VpsWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCVTPD2PS_VpsWpdR, BX_ISA_AVX, OP_Vps, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSD2SS_VssWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VCVTSD2SS_VssWsdR, BX_ISA_AVX, OP_Vss, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSS2SD_VsdWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VCVTSS2SD_VsdWssR, BX_ISA_AVX, OP_Vsd, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTDQ2PS_VpsWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCVTDQ2PS_VpsWdqR, BX_ISA_AVX, OP_Vps, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTPS2DQ_VdqWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCVTPS2DQ_VdqWpsR, BX_ISA_AVX, OP_Vdq, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTTPS2DQ_VdqWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VCVTTPS2DQ_VdqWpsR, BX_ISA_AVX, OP_Vdq, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSI2SD_VsdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::VCVTSI2SD_VsdEdR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Ed, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSI2SS_VssEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::VCVTSI2SS_VssEdR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Ed, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSD2SI_GdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTSD2SI_GdWsdR, BX_ISA_AVX, OP_Gd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSS2SI_GdWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTSS2SI_GdWssR, BX_ISA_AVX, OP_Gd, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTTSD2SI_GdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTTSD2SI_GdWsdR, BX_ISA_AVX, OP_Gd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTTSS2SI_GdWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTTSS2SI_GdWssR, BX_ISA_AVX, OP_Gd, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSI2SD_VsdEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::VCVTSI2SD_VsdEqR, BX_ISA_AVX, OP_Vsd, OP_Hpd, OP_Eq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSI2SS_VssEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::VCVTSI2SS_VssEqR, BX_ISA_AVX, OP_Vss, OP_Hps, OP_Eq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTTSD2SI_GqWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTTSD2SI_GqWsdR, BX_ISA_AVX, OP_Gq, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTTSS2SI_GqWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTTSS2SI_GqWssR, BX_ISA_AVX, OP_Gq, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSD2SI_GqWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::CVTSD2SI_GqWsdR, BX_ISA_AVX, OP_Gq, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTSS2SI_GqWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::CVTSS2SI_GqWssR, BX_ISA_AVX, OP_Gq, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VMOVQ_WqVq, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::MOVQ_VqWqR, BX_ISA_AVX, OP_Wq, OP_Vq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMOVQ_VqWq, &BX_CPU_C::MOVQ_VqWqM, &BX_CPU_C::MOVQ_VqWqR, BX_ISA_AVX, OP_Vq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVQ_VdqEq, &BX_CPU_C::MOVQ_VqWqM, &BX_CPU_C::MOVQ_VdqEqR, BX_ISA_AVX, OP_Vdq, OP_Eq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V128_VMOVQ_EqVq, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::MOVQ_EqVqR, BX_ISA_AVX, OP_Eq, OP_Vq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VCVTPH2PS_VpsWps, &BX_CPU_C::LOAD_Half_Vector, &BX_CPU_C::VCVTPH2PS_VpsWpsR, BX_ISA_AVX_F16C, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VCVTPS2PH_WpsVpsIb, &BX_CPU_C::VCVTPS2PH_WpsVpsIb, &BX_CPU_C::VCVTPS2PH_WpsVpsIb, BX_ISA_AVX_F16C, OP_Wps, OP_Vps, OP_Ib, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VPMOVSXBW256_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMOVSXBW256_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXBD256_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VPMOVSXBD256_VdqWqR, BX_ISA_AVX2, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXBQ256_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VPMOVSXBQ256_VdqWdR, BX_ISA_AVX2, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXWD256_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMOVSXWD256_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXWQ256_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VPMOVSXWQ256_VdqWqR, BX_ISA_AVX2, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVSXDQ256_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMOVSXDQ256_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXBW256_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMOVZXBW256_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXBD256_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VPMOVZXBD256_VdqWqR, BX_ISA_AVX2, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXBQ256_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VPMOVZXBQ256_VdqWdR, BX_ISA_AVX2, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXWD256_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMOVZXWD256_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXWQ256_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VPMOVZXWQ256_VdqWqR, BX_ISA_AVX2, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMOVZXDQ256_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMOVZXDQ256_VdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_V256_VPERM2I128_VdqHdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERM2F128_VdqHdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VINSERTI128_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VINSERTF128_VdqHdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VEXTRACTI128_WdqVdqIb, &BX_CPU_C::VEXTRACTF128_WdqVdqIbM, &BX_CPU_C::VEXTRACTF128_WdqVdqIbR, BX_ISA_AVX2, OP_Wdq, OP_Vdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VBROADCASTI128_VdqMdq, &BX_CPU_C::VBROADCASTF128_VdqMdq, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vdq, OP_Mdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPBROADCASTB_VdqWb, &BX_CPU_C::LOAD_Wb, &BX_CPU_C::VPBROADCASTB_VdqWb, BX_ISA_AVX2, OP_Vdq, OP_Wb, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPBROADCASTW_VdqWw, &BX_CPU_C::LOAD_Ww, &BX_CPU_C::VPBROADCASTW_VdqWw, BX_ISA_AVX2, OP_Vdq, OP_Ww, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPBROADCASTD_VdqWd, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VPBROADCASTD_VdqWd, BX_ISA_AVX2, OP_Vdq, OP_Wd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPBROADCASTQ_VdqWq, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VPBROADCASTQ_VdqWq, BX_ISA_AVX2, OP_Vdq, OP_Wq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VBROADCASTSS_VpsWss, &BX_CPU_C::BxError, &BX_CPU_C::VPBROADCASTD_VdqWd, BX_ISA_AVX2, OP_Vdq, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VBROADCASTSD_VpdWsd, &BX_CPU_C::BxError, &BX_CPU_C::VPBROADCASTQ_VdqWq, BX_ISA_AVX2, OP_Vpd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPBLENDD_VdqHdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VBLENDPS_VpsHpsWpsIbR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)

// VexW aliased
bx_define_opcode(BX_IA_VMASKMOVD_VdqHdqMdq, &BX_CPU_C::VMASKMOVPS_VpsHpsMps, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vps, OP_Hps, OP_Mps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMASKMOVQ_VdqHdqMdq, &BX_CPU_C::VMASKMOVPD_VpdHpdMpd, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vpd, OP_Hpd, OP_Mpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMASKMOVD_MdqHdqVdq, &BX_CPU_C::VMASKMOVPS_MpsHpsVps, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Mps, OP_Hps, OP_Vps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VMASKMOVQ_MdqHdqVdq, &BX_CPU_C::VMASKMOVPD_MpdHpdVpd, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Mpd, OP_Hpd, OP_Vpd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VGATHERDPS_VpsHps, &BX_CPU_C::VGATHERDPS_VpsHps, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vps, OP_VSib, OP_Hps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VGATHERDPD_VpdHpd, &BX_CPU_C::VGATHERDPD_VpdHpd, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vpd, OP_VSib, OP_Hpd, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VGATHERQPS_VpsHps, &BX_CPU_C::VGATHERQPS_VpsHps, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vps, OP_VSib, OP_Hps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VGATHERQPD_VpdHpd, &BX_CPU_C::VGATHERQPD_VpdHpd, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vpd, OP_VSib, OP_Hpd, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VGATHERDD_VdqHdq, &BX_CPU_C::VGATHERDPS_VpsHps, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vdq, OP_VSib, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VGATHERDQ_VdqHdq, &BX_CPU_C::VGATHERDPD_VpdHpd, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vdq, OP_VSib, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VGATHERQD_VdqHdq, &BX_CPU_C::VGATHERQPS_VpsHps, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vdq, OP_VSib, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VGATHERQQ_VdqHdq, &BX_CPU_C::VGATHERQPD_VpdHpd, &BX_CPU_C::BxError, BX_ISA_AVX2, OP_Vdq, OP_VSib, OP_Hdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VPSRLVD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLVD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSRLVQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRLVQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSLLVD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLVD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSLLVQ_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSLLVQ_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
// VexW aliased

bx_define_opcode(BX_IA_V256_VPERMQ_VdqWdqIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMQ_VdqWdqIbR, BX_ISA_AVX2, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPERMD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPERMPS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_V256_VPERMPD_VpdWpdIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMQ_VdqWdqIbR, BX_ISA_AVX2, OP_Vps, OP_Wps, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSRAVD_VdqHdqWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPSRAVD_VdqHdqWdqR, BX_ISA_AVX2, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
// AVX1/AVX2

// AVX2 FMA - VexW aliased
bx_define_opcode(BX_IA_VFMADD132PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wps, OP_Hps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD132PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wpd, OP_Hpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD213PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Vps, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD213PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Vpd, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD231PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Wps, OP_Vps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD231PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Wpd, OP_Vpd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFMADD132SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMADDSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wss, OP_Hss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD132SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMADDSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wsd, OP_Hsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD213SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMADDSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hss, OP_Vss, OP_Wss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD213SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMADDSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hsd, OP_Vsd, OP_Wsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD231SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMADDSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hss, OP_Wss, OP_Vss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADD231SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMADDSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hsd, OP_Wsd, OP_Vsd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFMADDSUB132PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wps, OP_Hps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUB132PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wpd, OP_Hpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUB213PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Vps, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUB213PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Vpd, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUB231PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Wps, OP_Vps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUB231PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Wpd, OP_Vpd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFMSUBADD132PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wps, OP_Hps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADD132PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wpd, OP_Hpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADD213PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Vps, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADD213PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Vpd, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADD231PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Wps, OP_Vps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADD231PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Wpd, OP_Vpd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFMSUB132PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wps, OP_Hps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB132PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wpd, OP_Hpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB213PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Vps, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB213PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Vpd, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB231PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Wps, OP_Vps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB231PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Wpd, OP_Vpd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFMSUB132SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMSUBSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wss, OP_Hss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB132SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMSUBSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wsd, OP_Hsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB213SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMSUBSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hss, OP_Vss, OP_Wss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB213SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMSUBSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hsd, OP_Vsd, OP_Wsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB231SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMSUBSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hss, OP_Wss, OP_Vss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUB231SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMSUBSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hsd, OP_Wsd, OP_Vsd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFNMADD132PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wps, OP_Hps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD132PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wpd, OP_Hpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD213PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Vps, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD213PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Vpd, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD231PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Wps, OP_Vps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD231PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Wpd, OP_Vpd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFNMADD132SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMADDSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wss, OP_Hss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD132SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMADDSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wsd, OP_Hsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD213SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMADDSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hss, OP_Vss, OP_Wss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD213SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMADDSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hsd, OP_Vsd, OP_Wsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD231SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMADDSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hss, OP_Wss, OP_Vss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADD231SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMADDSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hsd, OP_Wsd, OP_Vsd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFNMSUB132PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wps, OP_Hps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB132PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wpd, OP_Hpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB213PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Vps, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB213PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Vpd, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB231PS_VpsHpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPS_VpsHpsWpsR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Wps, OP_Vps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB231PD_VpdHpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPD_VpdHpdWpdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Wpd, OP_Vpd, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VFNMSUB132SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMSUBSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Vps, OP_Wps, OP_Hps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB132SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMSUBSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Vpd, OP_Wpd, OP_Hpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB213SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMSUBSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Vps, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB213SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMSUBSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Vpd, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB231SS_VpsHssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMSUBSS_VpsHssWssR, BX_ISA_AVX_FMA, OP_Vps, OP_Hps, OP_Wps, OP_Vps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUB231SD_VpdHsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMSUBSD_VpdHsdWsdR, BX_ISA_AVX_FMA, OP_Vpd, OP_Hpd, OP_Wpd, OP_Vpd, BX_PREPARE_AVX)
// AVX2 FMA - VexW aliased

// BMI1
bx_define_opcode(BX_IA_ANDN_GdBdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::ANDN_GdBdEdR, BX_ISA_BMI1, OP_Gd, OP_Bd, OP_Ed, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSI_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLSI_BdEdR, BX_ISA_BMI1, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSMSK_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLSMSK_BdEdR, BX_ISA_BMI1, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSR_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLSR_BdEdR, BX_ISA_BMI1, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BEXTR_GdEdBd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BEXTR_GdEdBdR, BX_ISA_BMI1, OP_Gd, OP_Ed, OP_Bd, OP_NONE, 0)

bx_define_opcode(BX_IA_ANDN_GqBqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::ANDN_GqBqEqR, BX_ISA_BMI1, OP_Gq, OP_Bq, OP_Eq, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSI_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLSI_BqEqR, BX_ISA_BMI1, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSMSK_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLSMSK_BqEqR, BX_ISA_BMI1, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSR_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLSR_BqEqR, BX_ISA_BMI1, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BEXTR_GqEqBq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BEXTR_GqEqBqR, BX_ISA_BMI1, OP_Gq, OP_Eq, OP_Bq, OP_NONE, 0)
// BMI1

// BMI2
bx_define_opcode(BX_IA_MULX_GdBdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::MULX_GdBdEdR, BX_ISA_BMI2, OP_Gd, OP_Bd, OP_Ed, OP_NONE, 0)
bx_define_opcode(BX_IA_RORX_GdEdIb, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::RORX_GdEdIbR, BX_ISA_BMI2, OP_Gd, OP_Ed, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_SHLX_GdEdBd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::SHLX_GdEdBdR, BX_ISA_BMI2, OP_Gd, OP_Ed, OP_Bd, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRX_GdEdBd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::SHRX_GdEdBdR, BX_ISA_BMI2, OP_Gd, OP_Ed, OP_Bd, OP_NONE, 0)
bx_define_opcode(BX_IA_SARX_GdEdBd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::SARX_GdEdBdR, BX_ISA_BMI2, OP_Gd, OP_Ed, OP_Bd, OP_NONE, 0)
bx_define_opcode(BX_IA_BZHI_GdBdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BZHI_GdBdEdR, BX_ISA_BMI2, OP_Gd, OP_Bd, OP_Ed, OP_NONE, 0)
bx_define_opcode(BX_IA_PEXT_GdBdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::PEXT_GdBdEdR, BX_ISA_BMI2, OP_Gd, OP_Bd, OP_Ed, OP_NONE, 0)
bx_define_opcode(BX_IA_PDEP_GdBdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::PDEP_GdBdEdR, BX_ISA_BMI2, OP_Gd, OP_Bd, OP_Ed, OP_NONE, 0)

bx_define_opcode(BX_IA_MULX_GqBqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::MULX_GqBqEqR, BX_ISA_BMI2, OP_Gq, OP_Bq, OP_Ed, OP_NONE, 0)
bx_define_opcode(BX_IA_RORX_GqEqIb, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::RORX_GqEqIbR, BX_ISA_BMI2, OP_Gq, OP_Eq, OP_Ib, OP_NONE, 0)
bx_define_opcode(BX_IA_SHLX_GqEqBq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::SHLX_GqEqBqR, BX_ISA_BMI2, OP_Gq, OP_Eq, OP_Bq, OP_NONE, 0)
bx_define_opcode(BX_IA_SHRX_GqEqBq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::SHRX_GqEqBqR, BX_ISA_BMI2, OP_Gq, OP_Eq, OP_Bq, OP_NONE, 0)
bx_define_opcode(BX_IA_SARX_GqEqBq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::SARX_GqEqBqR, BX_ISA_BMI2, OP_Gq, OP_Eq, OP_Bq, OP_NONE, 0)
bx_define_opcode(BX_IA_BZHI_GqBqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BZHI_GqBqEqR, BX_ISA_BMI2, OP_Gq, OP_Bq, OP_Eq, OP_NONE, 0)
bx_define_opcode(BX_IA_PEXT_GqBqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::PEXT_GqBqEqR, BX_ISA_BMI2, OP_Gq, OP_Bq, OP_Eq, OP_NONE, 0)
bx_define_opcode(BX_IA_PDEP_GqBqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::PDEP_GqBqEqR, BX_ISA_BMI2, OP_Gq, OP_Bq, OP_Eq, OP_NONE, 0)
// BMI2

// FMA4 (AMD) - VexW aliased
bx_define_opcode(BX_IA_VFMADDSUBPS_VpsHpsVIbWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUBPS_VpsHpsWpsVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUBPD_VpdHpdVIbWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_VIb, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSUBPD_VpdHpdWpdVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDSUBPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_Wpd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADDPS_VpsHpsVIbWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADDPS_VpsHpsWpsVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADDPD_VpdHpdVIbWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_VIb, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBADDPD_VpdHpdWpdVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBADDPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_Wpd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDPS_VpsHpsVIbWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDPS_VpsHpsWpsVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDPD_VpdHpdVIbWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_VIb, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDPD_VpdHpdWpdVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMADDPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_Wpd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSS_VssHssVIbWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMADDSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_VIb, OP_Wss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSS_VssHssWssVIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMADDSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_Wss, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSD_VsdHsdVIbWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMADDSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_VIb, OP_Wsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMADDSD_VsdHsdWsdVIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMADDSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_Wsd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBPS_VpsHpsVIbWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBPS_VpsHpsWpsVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBPD_VpdHpdVIbWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_VIb, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBPD_VpdHpdWpdVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFMSUBPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_Wpd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBSS_VssHssVIbWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMSUBSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_VIb, OP_Wss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBSS_VssHssWssVIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFMSUBSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_Wss, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBSD_VsdHsdVIbWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMSUBSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_VIb, OP_Wsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFMSUBSD_VsdHsdWsdVIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFMSUBSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_Wsd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDPS_VpsHpsVIbWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDPS_VpsHpsWpsVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDPD_VpdHpdVIbWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_VIb, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDPD_VpdHpdWpdVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMADDPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_Wpd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDSS_VssHssVIbWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMADDSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_VIb, OP_Wss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDSS_VssHssWssVIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMADDSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_Wss, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDSD_VsdHsdVIbWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMADDSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_VIb, OP_Wsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMADDSD_VsdHsdWsdVIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMADDSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_Wsd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBPS_VpsHpsVIbWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBPS_VpsHpsWpsVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPS_VpsHpsWpsR, BX_ISA_FMA4, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBPD_VpdHpdVIbWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_VIb, OP_Wpd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBPD_VpdHpdWpdVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFNMSUBPD_VpdHpdWpdR, BX_ISA_FMA4, OP_Vpd, OP_Hpd, OP_Wpd, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBSS_VssHssVIbWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMSUBSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_VIb, OP_Wss, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBSS_VssHssWssVIb, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFNMSUBSS_VssHssWssVIbR, BX_ISA_FMA4, OP_Vss, OP_Hss, OP_Wss, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBSD_VsdHsdVIbWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMSUBSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_VIb, OP_Wsd, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFNMSUBSD_VsdHsdWsdVIb, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFNMSUBSD_VsdHsdWsdVIbR, BX_ISA_FMA4, OP_Vsd, OP_Hsd, OP_Wsd, OP_VIb, BX_PREPARE_AVX)
// FMA4 (AMD) - VexW aliased

// XOP (AMD) - VexW aliased
bx_define_opcode(BX_IA_VPCMOV_VdqHdqVIbWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMOV_VdqHdqWdqVIb, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_VIb, OP_Wdq, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCMOV_VdqHdqWdqVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPCMOV_VdqHdqWdqVIb, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPPERM_VdqHdqVIbWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPPERM_VdqHdqWdqVIb, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_VIb, OP_Wdq, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPPERM_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPPERM_VdqHdqWdqVIb, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPERMIL2PS_VdqHdqVIbWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMIL2PS_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPERMIL2PS_VdqHdqWdqVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMIL2PS_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPERMIL2PD_VdqHdqVIbWdq, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMIL2PD_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vps, OP_Hps, OP_VIb, OP_Wps, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPERMIL2PD_VdqHdqWdqVIb, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VPERMIL2PD_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vps, OP_Hps, OP_Wps, OP_VIb, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VPSHAB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAB_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHAB_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAB_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHAW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAW_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHAW_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAW_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHAD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAD_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHAD_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAD_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHAQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAQ_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHAQ_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHAQ_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTB_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTB_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTB_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTW_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTW_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTW_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTD_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTD_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTD_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTQ_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTQ_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTQ_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLB_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLB_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLB_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLB_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLW_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLW_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLW_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLW_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLD_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLD_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLD_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLD_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLQ_VdqHdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLQ_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPSHLQ_VdqWdqHdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPSHLQ_VdqWdqHdq, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Hdq, OP_NONE, BX_PREPARE_AVX)

bx_define_opcode(BX_IA_VPMACSSWW_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSSWW_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSSWD_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSSWD_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSSDQL_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSSDQL_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSSDD_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSSDD_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSSDQH_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSSDQH_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSWW_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSWW_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSWD_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSWD_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSDQL_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSDQL_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSDD_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSDD_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMACSDQH_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMACSDQH_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMADCSSWD_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMADCSSWD_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPMADCSWD_VdqHdqWdqVIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPMADCSWD_VdqHdqWdqVIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_VIb, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTB_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTB_VdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTW_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTW_VdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTD_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTD_VdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPROTQ_VdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPROTQ_VdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_Ib, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMB_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMB_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMW_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMW_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMD_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMD_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMQ_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMQ_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMUB_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMUB_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMUW_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMUW_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMUD_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMUD_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPCOMUQ_VdqHdqWdqIb, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPCOMUQ_VdqHdqWdqIbR, BX_ISA_XOP, OP_Vdq, OP_Hdq, OP_Wdq, OP_Ib, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFRCZPS_VpsWps, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFRCZPS_VpsWpsR, BX_ISA_XOP, OP_Vps, OP_Wps, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFRCZPD_VpdWpd, &BX_CPU_C::LOAD_Vector, &BX_CPU_C::VFRCZPD_VpdWpdR, BX_ISA_XOP, OP_Vpd, OP_Wpd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFRCZSS_VssWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VFRCZSS_VssWssR, BX_ISA_XOP, OP_Vss, OP_Wss, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VFRCZSD_VsdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VFRCZSD_VsdWsdR, BX_ISA_XOP, OP_Vsd, OP_Wsd, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDBW_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDBW_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDBD_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDBD_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDBQ_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDBQ_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDWD_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDWD_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDWQ_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDWQ_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDDQ_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDDQ_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDUBW_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDUBW_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDUBD_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDUBD_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDUBQ_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDUBQ_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDUWD_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDUWD_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDUWQ_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDUWQ_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHADDUDQ_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHADDUDQ_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHSUBBW_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHSUBBW_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHSUBWD_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHSUBWD_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_VPHSUBDQ_VdqWdq, &BX_CPU_C::LOADU_Wdq, &BX_CPU_C::VPHSUBDQ_VdqWdqR, BX_ISA_XOP, OP_Vdq, OP_Wdq, OP_NONE, OP_NONE, BX_PREPARE_AVX)
// XOP (AMD) - VexW aliased

// TBM (AMD)
bx_define_opcode(BX_IA_BEXTR_GdEdId, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BEXTR_GdEdIdR, BX_ISA_TBM, OP_Gd, OP_Ed, OP_Id, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCFILL_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLCFILL_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCI_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLCI_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCIC_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLCIC_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCMSK_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLCMSK_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCS_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLCS_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSFILL_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLSFILL_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSIC_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::BLSIC_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_T1MSKC_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::T1MSKC_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TZMSK_BdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::TZMSK_BdEdR, BX_ISA_TBM, OP_Bd, OP_Ed, OP_NONE, OP_NONE, 0)

bx_define_opcode(BX_IA_BEXTR_GqEqId, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BEXTR_GqEqIdR, BX_ISA_TBM, OP_Gq, OP_Eq, OP_Id, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCFILL_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLCFILL_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCI_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLCI_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCIC_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLCIC_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCMSK_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLCMSK_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLCS_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLCS_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSFILL_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLSFILL_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_BLSIC_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::BLSIC_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_T1MSKC_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::T1MSKC_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TZMSK_BqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::TZMSK_BqEqR, BX_ISA_TBM, OP_Bq, OP_Eq, OP_NONE, OP_NONE, 0)
// TBM (AMD)

#endif /* BX_SUPPORT_AVX */

bx_define_opcode(BX_IA_TZCNT_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::TZCNT_GwEwR, BX_ISA_BMI1, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_TZCNT_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::TZCNT_GdEdR, BX_ISA_BMI1, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_TZCNT_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::TZCNT_GqEqR, BX_ISA_BMI1, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
#endif

bx_define_opcode(BX_IA_LZCNT_GwEw, &BX_CPU_C::LOAD_Ew, &BX_CPU_C::LZCNT_GwEwR, BX_ISA_LZCNT, OP_Gw, OP_Ew, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_LZCNT_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::LZCNT_GdEdR, BX_ISA_LZCNT, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_LZCNT_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::LZCNT_GqEqR, BX_ISA_LZCNT, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
#endif

// SSE4A
bx_define_opcode(BX_IA_MOVNTSS_MssVss, &BX_CPU_C::MOVSS_WssVssM, &BX_CPU_C::BxError, BX_ISA_SSE4A, OP_Mss, OP_Vss, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_MOVNTSD_MsdVsd, &BX_CPU_C::MOVSD_WsdVsdM, &BX_CPU_C::BxError, BX_ISA_SSE4A, OP_Msd, OP_Vsd, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_EXTRQ_UdqIbIb, &BX_CPU_C::BxError, &BX_CPU_C::EXTRQ_UdqIbIb, BX_ISA_SSE4A, OP_Udq, OP_Ib, OP_Ib, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_EXTRQ_VdqUq, &BX_CPU_C::BxError, &BX_CPU_C::EXTRQ_VdqUq, BX_ISA_SSE4A, OP_Vdq, OP_Uq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_INSERTQ_VdqUqIbIb, &BX_CPU_C::BxError, &BX_CPU_C::INSERTQ_VdqUqIbIb, BX_ISA_SSE4A, OP_Vdq, OP_Uq, OP_Ib, OP_Ib, BX_PREPARE_SSE)
bx_define_opcode(BX_IA_INSERTQ_VdqUdq, &BX_CPU_C::BxError, &BX_CPU_C::INSERTQ_VdqUdq, BX_ISA_SSE4A, OP_Vdq, OP_Udq, OP_NONE, OP_NONE, BX_PREPARE_SSE)
// SSE4A

// ADCX/ADOX
bx_define_opcode(BX_IA_ADCX_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::ADCX_GdEdR, BX_ISA_ADX, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADOX_GdEd, &BX_CPU_C::LOAD_Ed, &BX_CPU_C::ADOX_GdEdR, BX_ISA_ADX, OP_Gd, OP_Ed, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_ADCX_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::ADCX_GqEqR, BX_ISA_ADX, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_ADOX_GqEq, &BX_CPU_C::LOAD_Eq, &BX_CPU_C::ADOX_GqEqR, BX_ISA_ADX, OP_Gq, OP_Eq, OP_NONE, OP_NONE, 0)
#endif

// SMAP
bx_define_opcode(BX_IA_STAC, NULL, &BX_CPU_C::STAC, BX_ISA_SMAP, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_CLAC, NULL, &BX_CPU_C::CLAC, BX_ISA_SMAP, OP_NONE, OP_NONE, OP_NONE, OP_NONE, 0)

// RDRAND
bx_define_opcode(BX_IA_RDRAND_Ew, NULL, &BX_CPU_C::RDRAND_Ew, BX_ISA_RDRAND, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RDRAND_Ed, NULL, &BX_CPU_C::RDRAND_Ew, BX_ISA_RDRAND, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_RDRAND_Eq, NULL, &BX_CPU_C::RDRAND_Ew, BX_ISA_RDRAND, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
#endif

// RDSEED
bx_define_opcode(BX_IA_RDSEED_Ew, NULL, &BX_CPU_C::RDSEED_Ew, BX_ISA_RDSEED, OP_Ew, OP_NONE, OP_NONE, OP_NONE, 0)
bx_define_opcode(BX_IA_RDSEED_Ed, NULL, &BX_CPU_C::RDSEED_Ew, BX_ISA_RDSEED, OP_Ed, OP_NONE, OP_NONE, OP_NONE, 0)
#if BX_SUPPORT_X86_64
bx_define_opcode(BX_IA_RDSEED_Eq, NULL, &BX_CPU_C::RDSEED_Ew, BX_ISA_RDSEED, OP_Eq, OP_NONE, OP_NONE, OP_NONE, 0)
#endif

#if BX_SUPPORT_AVX
bx_define_opcode(BX_IA_KANDW_KGwKHwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KANDW_KGwKHwKEwR, BX_ISA_AVX512, OP_KGw, OP_KHw, OP_KEw, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KANDNW_KGwKHwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KANDNW_KGwKHwKEwR, BX_ISA_AVX512, OP_KGw, OP_KHw, OP_KEw, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KMOVW_KGwKEw, &BX_CPU_C::KMOVW_KGwKEwM, &BX_CPU_C::KMOVW_KGwKEwR, BX_ISA_AVX512, OP_KGw, OP_KEw, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KMOVW_KEwKGw, &BX_CPU_C::KMOVW_KEwKGwM, &BX_CPU_C::BxError, BX_ISA_AVX512, OP_KEw, OP_KGw, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KMOVW_KGwEw, &BX_CPU_C::BxError, &BX_CPU_C::KMOVW_KGwEwR, BX_ISA_AVX512, OP_KGw, OP_KEw, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KMOVW_GdKEw, &BX_CPU_C::BxError, &BX_CPU_C::KMOVW_GdKEwR, BX_ISA_AVX512, OP_KGw, OP_KEw, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KUNPCKBW_KGwKHwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KUNPCKBW_KGwKHwKEwR, BX_ISA_AVX512, OP_KGw, OP_KHw, OP_KEw, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KNOTW_KGwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KNOTW_KGwKEwR, BX_ISA_AVX512, OP_KGw, OP_KEw, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KORW_KGwKHwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KORW_KGwKHwKEwR, BX_ISA_AVX512, OP_KGw, OP_KHw, OP_KEw, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KORTESTW_KGwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KORTESTW_KGwKEw, BX_ISA_AVX512, OP_NONE, OP_KGw, OP_KEw, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KSHIFTLW_KGwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KSHIFTLW_KGwKEw, BX_ISA_AVX512, OP_KGw, OP_KEw, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KSHIFTRW_KGwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KSHIFTRW_KGwKEw, BX_ISA_AVX512, OP_KGw, OP_KEw, OP_NONE, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KXNORW_KGwKHwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KXNORW_KGwKHwKEw, BX_ISA_AVX512, OP_KGw, OP_KHw, OP_KEw, OP_NONE, BX_PREPARE_AVX)
bx_define_opcode(BX_IA_KXORW_KGwKHwKEw, &BX_CPU_C::BxError, &BX_CPU_C::KXORW_KGwKHwKEw, BX_ISA_AVX512, OP_KGw, OP_KHw, OP_KEw, OP_NONE, BX_PREPARE_AVX)
#endif

#if BX_SUPPORT_EVEX
// SSE alias
bx_define_opcode(BX_IA_V512_VADDPS_VpsHpsWps, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VADDPS_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VADDPD_VpdHpdWpd, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VADDPD_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VADDSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VADDSS_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VADDSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VADDSD_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VADDPS_VpsHpsWps_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VADDPS_MASK_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VADDPD_VpdHpdWpd_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VADDPD_MASK_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VADDSS_VssHpsWss_MASK, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VADDSS_MASK_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VADDSD_VsdHpdWsd_MASK, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VADDSD_MASK_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VSUBPS_VpsHpsWps, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VSUBPS_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VSUBPD_VpdHpdWpd, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VSUBPD_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VSUBSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VSUBSS_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VSUBSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VSUBSD_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VSUBPS_VpsHpsWps_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VSUBPS_MASK_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VSUBPD_VpdHpdWpd_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VSUBPD_MASK_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VSUBSS_VssHpsWss_MASK, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VSUBSS_MASK_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VSUBSD_VsdHpdWsd_MASK, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VSUBSD_MASK_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VMULPS_VpsHpsWps, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VMULPS_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMULPD_VpdHpdWpd, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VMULPD_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMULSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMULSS_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMULSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMULSD_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VMULPS_VpsHpsWps_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VMULPS_MASK_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMULPD_VpdHpdWpd_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VMULPD_MASK_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMULSS_VssHpsWss_MASK, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMULSS_MASK_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMULSD_VsdHpdWsd_MASK, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMULSD_MASK_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VDIVPS_VpsHpsWps, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VDIVPS_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VDIVPD_VpdHpdWpd, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VDIVPD_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VDIVSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VDIVSS_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VDIVSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VDIVSD_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VDIVPS_VpsHpsWps_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VDIVPS_MASK_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VDIVPD_VpdHpdWpd_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VDIVPD_MASK_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VDIVSS_VssHpsWss_MASK, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VDIVSS_MASK_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VDIVSD_VsdHpdWsd_MASK, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VDIVSD_MASK_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VMINPS_VpsHpsWps, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VMINPS_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMINPD_VpdHpdWpd, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VMINPD_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMINSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMINSS_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMINSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMINSD_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VMINPS_VpsHpsWps_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VMINPS_MASK_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMINPD_VpdHpdWpd_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VMINPD_MASK_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMINSS_VssHpsWss_MASK, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMINSS_MASK_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMINSD_VsdHpdWsd_MASK, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMINSD_MASK_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VMAXPS_VpsHpsWps, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VMAXPS_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMAXPD_VpdHpdWpd, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VMAXPD_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMAXSS_VssHpsWss, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMAXSS_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMAXSD_VsdHpdWsd, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMAXSD_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)

bx_define_opcode(BX_IA_V512_VMAXPS_VpsHpsWps_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorD, &BX_CPU_C::VMAXPS_MASK_VpsHpsWpsR, BX_ISA_AVX512, OP_Vps, OP_Hps, OP_Wps, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMAXPD_VpdHpdWpd_MASK, &BX_CPU_C::LOAD_BROADCAST_VectorQ, &BX_CPU_C::VMAXPD_MASK_VpdHpdWpdR, BX_ISA_AVX512, OP_Vpd, OP_Hpd, OP_Wpd, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMAXSS_VssHpsWss_MASK, &BX_CPU_C::LOAD_Wss, &BX_CPU_C::VMAXSS_MASK_VssHpsWssR, BX_ISA_AVX512, OP_Vss, OP_Hps, OP_Wss, OP_NONE, BX_PREPARE_EVEX)
bx_define_opcode(BX_IA_V512_VMAXSD_VsdHpdWsd_MASK, &BX_CPU_C::LOAD_Wsd, &BX_CPU_C::VMAXSD_MASK_VsdHpdWsdR, BX_ISA_AVX512, OP_Vsd, OP_Hpd, OP_Wsd, OP_NONE, BX_PREPARE_EVEX)
// SSE alias
#endif
