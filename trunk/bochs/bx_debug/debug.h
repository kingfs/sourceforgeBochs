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
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

#ifndef BX_DEBUG_H
#define BX_DEBUG_H

// if including from C parser, need basic types etc
#include "config.h"
#include "osdep.h"

#define BX_DBG_NO_HANDLE 1000

Bit32u crc32(const Bit8u *buf, int len);

#if BX_DEBUGGER

// some strict C declarations needed by the parser/lexer
#ifdef __cplusplus
extern "C" {
#endif

extern Bit32u dbg_cpu;

void dbg_printf (const char *fmt, ...);

typedef enum {
  BX_DBG_SREG_ES,
  BX_DBG_SREG_CS,
  BX_DBG_SREG_SS,
  BX_DBG_SREG_DS,
  BX_DBG_SREG_FS,
  BX_DBG_SREG_GS
} SRegs;

#if BX_SUPPORT_X86_64
# define BX_DBG_GEN_REGISTERS 16
#else
# define BX_DBG_GEN_REGISTERS 8
#endif

typedef enum {
  BX_DBG_REG8H_AH,
  BX_DBG_REG8H_CH,
  BX_DBG_REG8H_DH,
  BX_DBG_REG8H_BH,
} Regs8H;

#if BX_SUPPORT_X86_64

typedef enum {
  BX_DBG_REG8L_AL,
  BX_DBG_REG8L_CL,
  BX_DBG_REG8L_DL,
  BX_DBG_REG8L_BL,
  BX_DBG_REG8L_SPL,
  BX_DBG_REG8L_BPL,
  BX_DBG_REG8L_SIL,
  BX_DBG_REG8L_DIL,
  BX_DBG_REG8L_R8,
  BX_DBG_REG8L_R9,
  BX_DBG_REG8L_R10,
  BX_DBG_REG8L_R11,
  BX_DBG_REG8L_R12,
  BX_DBG_REG8L_R13,
  BX_DBG_REG8L_R14,
  BX_DBG_REG8L_R15
} Regs8L;

typedef enum {
  BX_DBG_REG16_AX,
  BX_DBG_REG16_CX,
  BX_DBG_REG16_DX,
  BX_DBG_REG16_BX,
  BX_DBG_REG16_SP,
  BX_DBG_REG16_BP,
  BX_DBG_REG16_SI,
  BX_DBG_REG16_DI,
  BX_DBG_REG16_R8,
  BX_DBG_REG16_R9,
  BX_DBG_REG16_R10,
  BX_DBG_REG16_R11,
  BX_DBG_REG16_R12,
  BX_DBG_REG16_R13,
  BX_DBG_REG16_R14,
  BX_DBG_REG16_R15
} Regs16;

typedef enum {
  BX_DBG_REG32_EAX,
  BX_DBG_REG32_ECX,
  BX_DBG_REG32_EDX,
  BX_DBG_REG32_EBX,
  BX_DBG_REG32_ESP,
  BX_DBG_REG32_EBP,
  BX_DBG_REG32_ESI,
  BX_DBG_REG32_EDI,
  BX_DBG_REG32_R8,
  BX_DBG_REG32_R9,
  BX_DBG_REG32_R10,
  BX_DBG_REG32_R11,
  BX_DBG_REG32_R12,
  BX_DBG_REG32_R13,
  BX_DBG_REG32_R14,
  BX_DBG_REG32_R15
} Regs32;

typedef enum {
  BX_DBG_REG64_RAX,
  BX_DBG_REG64_RCX,
  BX_DBG_REG64_RDX,
  BX_DBG_REG64_RBX,
  BX_DBG_REG64_RSP,
  BX_DBG_REG64_RBP,
  BX_DBG_REG64_RSI,
  BX_DBG_REG64_RDI,
  BX_DBG_REG64_R8,
  BX_DBG_REG64_R9,
  BX_DBG_REG64_R10,
  BX_DBG_REG64_R11,
  BX_DBG_REG64_R12,
  BX_DBG_REG64_R13,
  BX_DBG_REG64_R14,
  BX_DBG_REG64_R15
} Regs64;

#else

typedef enum {
  BX_DBG_REG8L_AL,
  BX_DBG_REG8L_CL,
  BX_DBG_REG8L_DL,
  BX_DBG_REG8L_BL
} Regs8L;

typedef enum {
  BX_DBG_REG16_AX,
  BX_DBG_REG16_CX,
  BX_DBG_REG16_DX,
  BX_DBG_REG16_BX,
  BX_DBG_REG16_SP,
  BX_DBG_REG16_BP,
  BX_DBG_REG16_SI,
  BX_DBG_REG16_DI
} Regs16;

typedef enum {
  BX_DBG_REG32_EAX,
  BX_DBG_REG32_ECX,
  BX_DBG_REG32_EDX,
  BX_DBG_REG32_EBX,
  BX_DBG_REG32_ESP,
  BX_DBG_REG32_EBP,
  BX_DBG_REG32_ESI,
  BX_DBG_REG32_EDI
} Regs32;

#endif

typedef enum
{
  bkRegular,
  bkAtIP,
  bkStepOver
} BreakpointKind;

typedef enum _show_flags {
  Flag_call    = 0x1,
  Flag_ret     = 0x2,
  Flag_softint = 0x4,
  Flag_iret    = 0x8,
  Flag_intsig  = 0x10,
  Flag_mode    = 0x20,
} show_flags_t;

// Flex defs
extern int bxlex(void);
extern char *bxtext;  // Using the pointer option rather than array
extern int bxwrap(void);
void bx_add_lex_input(char *buf);

// Yacc defs
extern int bxparse(void);
extern void bxerror(char *s);

// register function for 'info device' command
bx_bool bx_dbg_register_debug_info(const char *devname, void *dev);

#define EMPTY_ARG (-1)

bx_bool bx_dbg_read_linear(unsigned which_cpu, bx_address laddr, unsigned len, Bit8u *buf);
Bit16u bx_dbg_get_selector_value(unsigned int seg_no);
Bit16u bx_dbg_get_ip (void);
Bit32u bx_dbg_get_eip(void);
bx_address bx_dbg_get_instruction_pointer(void);
Bit8u bx_dbg_get_reg8l_value(unsigned reg);
Bit8u bx_dbg_get_reg8h_value(unsigned reg);
Bit16u bx_dbg_get_reg16_value(unsigned reg);
Bit32u bx_dbg_get_reg32_value(unsigned reg);
Bit64u bx_dbg_get_reg64_value(unsigned reg);
void bx_dbg_set_reg8l_value(unsigned reg, Bit8u value);
void bx_dbg_set_reg8h_value(unsigned reg, Bit8u value);
void bx_dbg_set_reg16_value(unsigned reg, Bit16u value);
void bx_dbg_set_reg32_value(unsigned reg, Bit32u value);
void bx_dbg_set_reg64_value(unsigned reg, Bit64u value);
void bx_dbg_set_rip_value(bx_address value);
void bx_dbg_load_segreg(unsigned reg, unsigned value);
bx_address bx_dbg_get_laddr(Bit16u sel, bx_address ofs);
void bx_dbg_step_over_command(void);
void bx_dbg_trace_command(bx_bool enable);
void bx_dbg_trace_reg_command(bx_bool enable);
void bx_dbg_trace_mem_command(bx_bool enable);
void bx_dbg_ptime_command(void);
void bx_dbg_timebp_command(bx_bool absolute, Bit64u time);
#define MAX_CONCURRENT_BPS 5
extern int timebp_timer;
extern Bit64u timebp_queue[MAX_CONCURRENT_BPS];
extern int timebp_queue_size;
void bx_dbg_modebp_command(void);
void bx_dbg_vmexitbp_command(void);
void bx_dbg_where_command(void);
void bx_dbg_print_string_command(bx_address addr);
void bx_dbg_xlate_address(bx_lin_address address);
void bx_dbg_show_command(const char*);
void bx_dbg_print_stack_command(unsigned nwords);
void bx_dbg_print_watchpoints(void);
void bx_dbg_watchpoint_continue(bx_bool watch_continue);
void bx_dbg_watch(int type, bx_phy_address address, Bit32u len);
void bx_dbg_unwatch_all(void);
void bx_dbg_unwatch(bx_phy_address handle);
void bx_dbg_continue_command(void);
void bx_dbg_stepN_command(int cpu, Bit32u count);
void bx_dbg_set_auto_disassemble(bx_bool enable);
void bx_dbg_disassemble_switch_mode(void);
void bx_dbg_disassemble_hex_mode_switch(int mode);
void bx_dbg_set_disassemble_size(unsigned size);
void bx_dbg_del_breakpoint_command(unsigned handle);
void bx_dbg_en_dis_breakpoint_command(unsigned handle, bx_bool enable);
bx_bool bx_dbg_en_dis_pbreak(unsigned handle, bx_bool enable);
bx_bool bx_dbg_en_dis_lbreak(unsigned handle, bx_bool enable);
bx_bool bx_dbg_en_dis_vbreak(unsigned handle, bx_bool enable);
bx_bool bx_dbg_del_pbreak(unsigned handle);
bx_bool bx_dbg_del_lbreak(unsigned handle);
bx_bool bx_dbg_del_vbreak(unsigned handle);
int bx_dbg_vbreakpoint_command(BreakpointKind bk, Bit32u cs, bx_address eip);
int bx_dbg_lbreakpoint_command(BreakpointKind bk, bx_address laddress);
int bx_dbg_pbreakpoint_command(BreakpointKind bk, bx_phy_address paddress);
void bx_dbg_info_bpoints_command(void);
void bx_dbg_quit_command(void);
#define BX_INFO_GENERAL_PURPOSE_REGS 0x01 /* bitmasks - choices for bx_dbg_info_registers_command */
#define BX_INFO_FPU_REGS 0x02
#define BX_INFO_MMX_REGS 0x04
#define BX_INFO_SSE_REGS 0x08
#define BX_INFO_AVX_REGS 0x10
void bx_dbg_info_registers_command(int);
void bx_dbg_info_ivt_command(unsigned from, unsigned to);
void bx_dbg_info_idt_command(unsigned from, unsigned to);
void bx_dbg_info_gdt_command(unsigned from, unsigned to);
void bx_dbg_info_ldt_command(unsigned from, unsigned to);
void bx_dbg_info_tss_command(void);
void bx_dbg_info_debug_regs_command(void);
void bx_dbg_info_control_regs_command(void);
void bx_dbg_info_segment_regs_command(void);
void bx_dbg_info_flags(void);
void bx_dbg_info_linux_command(void);
void bx_dbg_examine_command(const char *command, const char *format, bx_bool format_passed,
                    bx_address addr, bx_bool addr_passed);
Bit32u bx_dbg_lin_indirect(bx_address addr);
Bit32u bx_dbg_phy_indirect(bx_phy_address addr);
void bx_dbg_writemem_command(const char *filename, bx_address laddr, unsigned len);
void bx_dbg_setpmem_command(bx_phy_address addr, unsigned len, Bit32u val);
void bx_dbg_query_command(const char *);
void bx_dbg_take_command(const char *, unsigned n);
void bx_dbg_disassemble_current(const char *);
void bx_dbg_disassemble_command(const char *, Bit64u from, Bit64u to);
void bx_dbg_instrument_command(const char *);
void bx_dbg_doit_command(unsigned);
void bx_dbg_crc_command(bx_phy_address addr1, bx_phy_address addr2);
void bx_dbg_linux_syscall(unsigned which_cpu);
void bx_dbg_info_device(const char *, const char *);
void bx_dbg_print_help(void);
void bx_dbg_calc_command(Bit64u value);
void bx_dbg_dump_table(void);

// callbacks from CPU
void bx_dbg_exception(unsigned cpu, Bit8u vector, Bit16u error_code);
void bx_dbg_interrupt(unsigned cpu, Bit8u vector, Bit16u error_code);
void bx_dbg_halt(unsigned cpu);

// memory trace callbacks from CPU, len=1,2,4 or 8
void bx_dbg_lin_memory_access(unsigned cpu, bx_address lin, bx_phy_address phy, unsigned len, unsigned pl, unsigned rw, Bit8u *data);
void bx_dbg_phy_memory_access(unsigned cpu, bx_phy_address phy, unsigned len, unsigned rw, unsigned attr, Bit8u *data);

// check memory access for watchpoints
void bx_dbg_check_memory_watchpoints(unsigned cpu, bx_phy_address phy, unsigned len, unsigned rw);

// commands that work with Bochs param tree
void bx_dbg_restore_command(const char *param_name, const char *path);
void bx_dbg_show_param_command(const char *param);

int bx_dbg_show_symbolic(void);
void bx_dbg_set_symbol_command(const char *symbol, bx_address val);
const char* bx_dbg_symbolic_address(Bit32u context, Bit32u eip, Bit32u base);
const char* bx_dbg_symbolic_address_16bit(Bit32u eip, Bit32u cs);
int bx_dbg_symbol_command(const char* filename, bx_bool global, Bit32u offset);
void bx_dbg_info_symbols_command(const char *Symbol);
int bx_dbg_lbreakpoint_symbol_command(const char *Symbol);
Bit32u bx_dbg_get_symbol_value(const char *Symbol);
const char* bx_dbg_disasm_symbolic_address(Bit32u eip, Bit32u base);

#ifdef __cplusplus
}
#endif

// the rest for C++
#ifdef __cplusplus

typedef enum {
  STOP_NO_REASON = 0,
  STOP_TIME_BREAK_POINT,
  STOP_READ_WATCH_POINT,
  STOP_WRITE_WATCH_POINT,
  STOP_MAGIC_BREAK_POINT,
  STOP_MODE_BREAK_POINT,
  STOP_VMEXIT_BREAK_POINT,
  STOP_CPU_HALTED,
} stop_reason_t;

typedef enum {
  BREAK_POINT_MAGIC, BREAK_POINT_READ, BREAK_POINT_WRITE, BREAK_POINT_TIME
} break_point_t;

#define BX_DBG_PENDING_DMA 1
#define BX_DBG_PENDING_IRQ 2

void bx_debug_break(void);

void bx_dbg_exit(int code);
#if BX_DBG_EXTENSIONS
    int bx_dbg_extensions(char *command);
#else
#define bx_dbg_extensions(command) 0
#endif

//
// code for guards...
//

#define BX_DBG_GUARD_IADDR_VIR     0x0001
#define BX_DBG_GUARD_IADDR_LIN     0x0002
#define BX_DBG_GUARD_IADDR_PHY     0x0004
#define BX_DBG_GUARD_IADDR_ALL (BX_DBG_GUARD_IADDR_VIR | \
                                BX_DBG_GUARD_IADDR_LIN | \
                                BX_DBG_GUARD_IADDR_PHY)

#define BX_DBG_GUARD_ICOUNT        0x0010

typedef struct {
  unsigned guard_for;

  // instruction address breakpoints
  struct {
#if (BX_DBG_MAX_VIR_BPOINTS > 0)
    unsigned num_virtual;
    struct {
      Bit32u cs;  // only use 16 bits
      bx_address eip;
      unsigned bpoint_id;
      bx_bool enabled;
    } vir[BX_DBG_MAX_VIR_BPOINTS];
#endif

#if (BX_DBG_MAX_LIN_BPOINTS > 0)
    unsigned num_linear;
    struct {
      bx_address addr;
      unsigned bpoint_id;
      bx_bool enabled;
    } lin[BX_DBG_MAX_LIN_BPOINTS];
#endif

#if (BX_DBG_MAX_PHY_BPOINTS > 0)
    unsigned num_physical;
    struct {
      bx_phy_address addr;
      unsigned bpoint_id;
      bx_bool enabled;
    } phy[BX_DBG_MAX_PHY_BPOINTS];
#endif
  } iaddr;

  // user typed Ctrl-C, requesting simulator stop at next convinient spot
  volatile bx_bool interrupt_requested;

  // booleans to control whether simulator should report events
  // to debug controller
  struct {
    bx_bool irq;
    bx_bool a20;
    bx_bool io;
    bx_bool dma;
  } report;

  struct {
    bx_bool irq;  // should process IRQs asynchronously
    bx_bool dma;  // should process DMAs asynchronously
  } async;

#define BX_DBG_ASYNC_PENDING_A20   0x01
#define BX_DBG_ASYNC_PENDING_RESET 0x02
#define BX_DBG_ASYNC_PENDING_NMI   0x04

  // Asynchronous changes which are pending.  These are Q'd by
  // the debugger, as the master simulator is notified of a pending
  // async change.  At the simulator's next point, where it checks for
  // such events, it notifies the debugger with acknowlegement.  This
  // field contains a logically or'd list of all events which should
  // be checked, and ack'd.
  struct {
    unsigned which; // logical OR of above constants
    bx_bool a20;
    bx_bool reset;
    bx_bool nmi;
  } async_changes_pending;
} bx_guard_t;

// working information for each simulator to update when a guard
// is reached (found)
typedef struct bx_guard_found_t {
  unsigned guard_found;
  Bit64u icount_max; // stop after completing this many instructions
  unsigned iaddr_index;
  Bit32u cs; // cs:eip and linear addr of instruction at guard point
  bx_address eip;
  bx_address laddr;
  // 00 - 16 bit, 01 - 32 bit, 10 - 64-bit, 11 - illegal
  unsigned code_32_64; // CS seg size at guard point
} bx_guard_found_t;

struct bx_watchpoint {
  bx_phy_address addr;
  Bit32u len;
};

extern unsigned num_write_watchpoints;
extern unsigned num_read_watchpoints;
extern bx_watchpoint write_watchpoint[BX_DBG_MAX_WATCHPONTS];
extern bx_watchpoint read_watchpoint[BX_DBG_MAX_WATCHPONTS];
extern bx_guard_t bx_guard;

#define IS_CODE_32(code_32_64) ((code_32_64 & 1) != 0)
#define IS_CODE_64(code_32_64) ((code_32_64 & 2) != 0)

void bx_dbg_init_infile(void);
int  bx_dbg_set_rcfile(const char *rcfile);
int  bx_dbg_main(void);
void bx_dbg_user_input_loop(void);
void bx_dbg_interpret_line(char *cmd);

typedef struct {
  Bit16u sel;
  Bit32u des_l, des_h, valid;
#if BX_SUPPORT_X86_64
  Bit32u dword3;
#endif
} bx_dbg_sreg_t;

typedef struct {
  bx_address base;
  Bit16u limit;
} bx_dbg_global_sreg_t;

void bx_dbg_dma_report(bx_phy_address addr, unsigned len, unsigned what, Bit32u val);
void bx_dbg_iac_report(unsigned vector, unsigned irq);
void bx_dbg_a20_report(unsigned val);
void bx_dbg_io_report(Bit32u port, unsigned size, unsigned op, Bit32u val);
void bx_dbg_disassemble_current(int which_cpu, int print_time);

#endif // #ifdef __cplusplus

#endif // #if BX_DEBUGGER

#endif
