/*============================================================================
This C header file is part of the SoftFloat IEC/IEEE Floating-point Arithmetic
Package, Release 2b.

Written by John R. Hauser.  This work was made possible in part by the
International Computer Science Institute, located at Suite 600, 1947 Center
Street, Berkeley, California 94704.  Funding was partially provided by the
National Science Foundation under grant MIP-9311980.  The original version
of this code was written as part of a project to build a fixed-point vector
processor in collaboration with the University of California at Berkeley,
overseen by Profs. Nelson Morgan and John Wawrzynek.  More information
is available through the Web page `http://www.cs.berkeley.edu/~jhauser/
arithmetic/SoftFloat.html'.

THIS SOFTWARE IS DISTRIBUTED AS IS, FOR FREE.  Although reasonable effort has
been made to avoid it, THIS SOFTWARE MAY CONTAIN FAULTS THAT WILL AT TIMES
RESULT IN INCORRECT BEHAVIOR.  USE OF THIS SOFTWARE IS RESTRICTED TO PERSONS
AND ORGANIZATIONS WHO CAN AND WILL TAKE FULL RESPONSIBILITY FOR ALL LOSSES,
COSTS, OR OTHER PROBLEMS THEY INCUR DUE TO THE SOFTWARE, AND WHO FURTHERMORE
EFFECTIVELY INDEMNIFY JOHN HAUSER AND THE INTERNATIONAL COMPUTER SCIENCE
INSTITUTE (possibly via similar legal warning) AGAINST ALL LOSSES, COSTS, OR
OTHER PROBLEMS INCURRED BY THEIR CUSTOMERS AND CLIENTS DUE TO THE SOFTWARE.

Derivative works are acceptable, even for commercial purposes, so long as
(1) the source code for the derivative work includes prominent notice that
the work is derivative, and (2) the source code includes prominent notice with
these four paragraphs for those parts of this code that are retained.
=============================================================================*/

/*============================================================================
 * Adapted for Bochs (x86 achitecture simulator) by
 *            Stanislav Shwartsman (gate@fidonet.org.il)
 * ==========================================================================*/ 

#include <config.h>      /* generated by configure script from config.h.in */

#ifndef SOFTFLOAT_H
#define SOFTFLOAT_H

#define FLOATX80

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point types.
*----------------------------------------------------------------------------*/
typedef Bit32u float32, Float32;
typedef Bit64u float64, Float64;

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point class.
*----------------------------------------------------------------------------*/
typedef enum {
    float_negative_zero,
    float_positive_zero,
    float_NaN,
    float_negative_inf,
    float_positive_inf,
    float_denormal,
    float_normalized
} float_class_t;

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point underflow tininess-detection mode.
*----------------------------------------------------------------------------*/
enum {
    float_tininess_after_rounding  = 0,
    float_tininess_before_rounding = 1
};

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point NaN operands handling mode.
*----------------------------------------------------------------------------*/
enum float_nan_handling_mode_t {
    float_larger_significand_nan = 0,	// this mode used by x87 FPU
    float_first_operand_nan = 1		// this mode used by SSE
};

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point rounding mode.
*----------------------------------------------------------------------------*/
enum float_round_t {
    float_round_nearest_even = 0,
    float_round_down         = 1,
    float_round_up           = 2,
    float_round_to_zero      = 3
};

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point exception flags.
*----------------------------------------------------------------------------*/
enum float_exception_flag_t {
    float_flag_invalid   = 0x01,
    float_flag_denormal  = 0x02,
    float_flag_divbyzero = 0x04,
    float_flag_overflow  = 0x08,
    float_flag_underflow = 0x10,
    float_flag_inexact   = 0x20
};

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point ordering relations
*----------------------------------------------------------------------------*/
enum {
    float_relation_less      = -1,
    float_relation_equal     =  0,
    float_relation_greater   =  1,
    float_relation_unordered =  2
};

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point status structure.
*----------------------------------------------------------------------------*/
struct float_status_t 
{
#ifdef FLOATX80
    int float_rounding_precision;	/* floatx80 only */
#endif
    int float_detect_tininess;
    int float_rounding_mode;
    int float_exception_flags;
    int float_nan_handling_mode;
    int flush_underflow_to_zero;	/* flag register */
};
typedef struct float_status_t softfloat_status_word_t;

/*----------------------------------------------------------------------------
| Returns current floating point rounding mode specified by status word
*----------------------------------------------------------------------------*/
int get_float_rounding_mode(float_status_t &status);

/*----------------------------------------------------------------------------
| Routine to raise any or all of the software IEC/IEEE floating-point
| exception flags.
*----------------------------------------------------------------------------*/
void float_raise(float_status_t &status, int exceptions);

/*----------------------------------------------------------------------------
| Software IEC/IEEE integer-to-floating-point conversion routines.
*----------------------------------------------------------------------------*/
float32 int32_to_float32(Bit32s, float_status_t &status);
float64 int32_to_float64(Bit32s);
float32 int64_to_float32(Bit64s, float_status_t &status);
float64 int64_to_float64(Bit64s, float_status_t &status);

/*----------------------------------------------------------------------------
| Software IEC/IEEE single-precision conversion routines.
*----------------------------------------------------------------------------*/
Bit32s float32_to_int32(float32, float_status_t &status);
Bit32s float32_to_int32_round_to_zero(float32, float_status_t &status);
Bit64s float32_to_int64(float32, float_status_t &status);
Bit64s float32_to_int64_round_to_zero(float32, float_status_t &status);
float64 float32_to_float64(float32, float_status_t &status);

/*----------------------------------------------------------------------------
| Software IEC/IEEE single-precision operations.
*----------------------------------------------------------------------------*/
float32 float32_round_to_int(float32, float_status_t &status);
float32 float32_add(float32, float32, float_status_t &status);
float32 float32_sub(float32, float32, float_status_t &status);
float32 float32_mul(float32, float32, float_status_t &status);
float32 float32_div(float32, float32, float_status_t &status);
float32 float32_rem(float32, float32, float_status_t &status);
float32 float32_sqrt(float32, float_status_t &status);

typedef int (*float32_compare_method)(float32, float32, float_status_t &status);
int float32_eq(float32, float32, float_status_t &status);
int float32_le(float32, float32, float_status_t &status);
int float32_lt(float32, float32, float_status_t &status);
int float32_eq_signaling(float32, float32, float_status_t &status);
int float32_le_quiet(float32, float32, float_status_t &status);
int float32_lt_quiet(float32, float32, float_status_t &status);
int float32_unordered(float32, float32, float_status_t &status);
int float32_compare(float32, float32, float_status_t &status);
int float32_compare_quiet(float32, float32, float_status_t &status);

float_class_t float32_class(float32);
int float32_is_signaling_nan(float32);

/*----------------------------------------------------------------------------
| Software IEC/IEEE double-precision conversion routines.
*----------------------------------------------------------------------------*/
Bit32s float64_to_int32(float64, float_status_t &status);
Bit32s float64_to_int32_round_to_zero(float64, float_status_t &status);
Bit64s float64_to_int64(float64, float_status_t &status);
Bit64s float64_to_int64_round_to_zero(float64, float_status_t &status);
float32 float64_to_float32(float64, float_status_t &status);

/*----------------------------------------------------------------------------
| Software IEC/IEEE double-precision operations.
*----------------------------------------------------------------------------*/
float64 float64_round_to_int(float64, float_status_t &status);
float64 float64_add(float64, float64, float_status_t &status);
float64 float64_sub(float64, float64, float_status_t &status);
float64 float64_mul(float64, float64, float_status_t &status);
float64 float64_div(float64, float64, float_status_t &status);
float64 float64_rem(float64, float64, float_status_t &status);
float64 float64_sqrt(float64, float_status_t &status);

typedef int (*float64_compare_method)(float64, float64, float_status_t &status);
int float64_eq(float64, float64, float_status_t &status);
int float64_le(float64, float64, float_status_t &status);
int float64_lt(float64, float64, float_status_t &status);
int float64_eq_signaling(float64, float64, float_status_t &status);
int float64_le_quiet(float64, float64, float_status_t &status);
int float64_lt_quiet(float64, float64, float_status_t &status);
int float64_unordered(float64, float64, float_status_t &status);
int float64_compare(float64, float64, float_status_t &status);
int float64_compare_quiet(float64, float64, float_status_t &status);

float_class_t float64_class(float64);
int float64_is_signaling_nan(float64);

#ifdef FLOATX80

/*----------------------------------------------------------------------------
| Software IEC/IEEE floating-point types.
*----------------------------------------------------------------------------*/
#ifdef BX_BIG_ENDIAN
struct floatx80 {	// do not allow 16-byte extension of the structure
    Bit16u exp;
    Bit64u fraction;
} GCC_ATTRIBUTE((aligned(1), packed));
#else
struct floatx80 {	// do not allow 16-byte extension of the structure
    Bit64u fraction;
    Bit16u exp;
} GCC_ATTRIBUTE((aligned(1), packed));
#endif

/*----------------------------------------------------------------------------
| Software IEC/IEEE integer-to-floating-point conversion routines.
*----------------------------------------------------------------------------*/
floatx80 int32_to_floatx80(Bit32s);
floatx80 int64_to_floatx80(Bit64s);

/*----------------------------------------------------------------------------
| Software IEC/IEEE single-precision conversion routines.
*----------------------------------------------------------------------------*/
floatx80 float32_to_floatx80(float32, float_status_t &status);

/*----------------------------------------------------------------------------
| Software IEC/IEEE double-precision conversion routines.
*----------------------------------------------------------------------------*/
floatx80 float64_to_floatx80(float64, float_status_t &status);

/*----------------------------------------------------------------------------
| Software IEC/IEEE extended double-precision conversion routines.
*----------------------------------------------------------------------------*/
Bit32s floatx80_to_int32(floatx80, float_status_t &status);
Bit32s floatx80_to_int32_round_to_zero(floatx80, float_status_t &status);
Bit64s floatx80_to_int64(floatx80, float_status_t &status);
Bit64s floatx80_to_int64_round_to_zero(floatx80, float_status_t &status);

float32 floatx80_to_float32(floatx80, float_status_t &status);
float64 floatx80_to_float64(floatx80, float_status_t &status);

/*----------------------------------------------------------------------------
| Software IEC/IEEE extended double-precision operations.
*----------------------------------------------------------------------------*/
floatx80 floatx80_round_to_int(floatx80, float_status_t &status);
floatx80 floatx80_add(floatx80, floatx80, float_status_t &status);
floatx80 floatx80_sub(floatx80, floatx80, float_status_t &status);
floatx80 floatx80_mul(floatx80, floatx80, float_status_t &status);
floatx80 floatx80_div(floatx80, floatx80, float_status_t &status);
floatx80 floatx80_rem(floatx80, floatx80, float_status_t &status);
floatx80 floatx80_sqrt(floatx80, float_status_t &status);
int floatx80_eq(floatx80, floatx80, float_status_t &status);
int floatx80_le(floatx80, floatx80, float_status_t &status);
int floatx80_lt(floatx80, floatx80, float_status_t &status);
int floatx80_eq_signaling(floatx80, floatx80, float_status_t &status);
int floatx80_le_quiet(floatx80, floatx80, float_status_t &status);
int floatx80_lt_quiet(floatx80, floatx80, float_status_t &status);
int floatx80_compare(floatx80, floatx80, float_status_t &status);
int floatx80_compare_quiet(floatx80, floatx80, float_status_t &status);

float_class_t floatx80_class(floatx80);
int floatx80_is_signaling_nan(floatx80);
#endif

#endif
