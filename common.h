/* *
 * common.h
 * * * *
 * made 10/28/26
 * * * * * * *
 * 1-)	#includes
 * 2-)	funky macros
 * 3-)	conventions
 * 4-)	misc.
 * */
////
///
//
#ifndef COMMON_H_
#define COMMON_H_
//
/* 	 includes
 * * * * * * * * *
 * uncomment /   *
 * comment	     *
 *   v 		  v  */

#include <stdbool.h>
#include <stdint.h>
//#include <stddef.h>
//include <math.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
////
///
//
///* communal status message names, helpful maybe?!?!? */
//
typedef enum
{
	STATUS_COMPLETE = 0,
	STATUS_READY,
	STATUS_NOT_READY,
	STATUS_ALREADY_DONE,
	STATUS_ERROR,
	STATUS_BUSY,
	STATUS_TIMEOUT,
	STATUS_BAD_ARG,
	STATUS_LIMIT_HIT,
	STATUS_COMM_FAIL
} status_t;
///
//
///* float types in typedef form*/
//
typedef float flt32_t;
//
typedef double flt64_t;
//
/* macro defines - good for integer operations
 * * * * * * * * *
 * Uncomment or  *
 * comment		 *
 *     v v v     */
#define DEG_TO_RAD(x)			  ((x) * 0.01745329252)//prob can drop some digits
//
#define PRCNT_OF(prcnt,total)  	  ( ((total) * (prcnt)) / 100 )
//
#define AS_PRCNT(val,total)		  ( ((val) * 100) / (total) )
//
#define MIN(a,b) 				  ( ((a) < (b)) ? (a) : (b) )
//
#define MAX(a,b) 				  ( ((a) > (b)) ? (a) : (b) )
//
#define WITHIN_LIMITS(x,hi,lo)	  ( ((x) >= (lo)) && ((x) <= (hi)) )
//
#define ABS(x) 					  ( ((x) < 0)? -(x) : (x) )
//
#define WITHIN_TOL(x,trgt,toL)    ( ABS((x) - (trgt)) <= (toL) )//true/false
//
#define DEADZONE(x,zone) 		  ( (ABS(x) < (zone)) ? 0 : (x) )
//
#define RETURN_IF(cond)           do { if (cond) { return; } } while (0)
//
#define RETURN_VAL_IF(cond, val)  do { if (cond) { return (val); } } while (0)
///
/* declares you know 'x' exists, but tells the compiler to ignore it.*/
#define UNUSED(x) 				  ( (void)(x) )
/*returns error if you attempt to use*/
//
#define ARRAY_LEN(ar)			  ( sizeof(ar) / sizeof((ar)[0]) )
//
/* naming conventions
 * * * * * * * * * * * *
 *
 *
 *
 *
 * global variables:
 *  -) gVarName
 *
 * pointers:
 *  -) pVarName
 *
 * structures:
 *
 *
 */
//
/* misc...
 * * * * * *
 *
 */
//
//
static inline flt32_t Clamp_flt32(flt32_t value, flt32_t min, flt32_t max)
{
	if (value < min)
	{
		return min;
	}
	//
	else if (value > max)
	{
		return max;
	}
	//
	return value;
}
//

static inline flt32_t Abs_flt32_t(flt32_t value)
{
	return ((value) < (0.0f))? -(value) : (value);
}
//
static inline bool WithinLimits_flt32(flt32_t value, flt32_t min, flt32_t max)
{
	return (value >= min) && (value <= max);
}
//
static inline bool util_WithinTol_flt32(flt32_t value, flt32_t target,
		flt32_t tolerance)
{
	flt32_t error = value - target;
	//
	if (error < 0.0)
	{
		error = -error;
	}

	return error <= tolerance;
}
//
static inline flt32_t util_Deadzone_flt32(flt32_t value, flt32_t zone)
{
	flt32_t magnitude = (value < 0.0f) ? -value : value;

	if (magnitude < zone)
	{
		return 0.0f;
	}

	return value;
}
//
static inline int32_t util_Rescale_int32(int32_t value, int32_t inMin,
		int32_t inMax, int32_t outMin, int32_t outMax)
{
	if (inMax == inMin)
	{
		return outMin;
	}

	int64_t scaled = (int64_t) (value - inMin) * (outMax - outMin)
			/ (inMax - inMin) + outMin;
	int32_t lo = (outMin < outMax) ? outMin : outMax;
	int32_t hi = (outMin < outMax) ? outMax : outMin;
	return (int32_t) ((scaled < lo) ? lo : ((scaled > hi) ? hi : scaled));
}
//
static inline flt32_t util_RampTo_flt32(flt32_t current, flt32_t target,
		flt32_t step)
{
	if (step < 0.0f)
	{
		step = -step;
	}

	if (current < target)
	{
		return ((target - current) <= step) ? target : current + step;
	}

	if (current > target)
	{
		return ((current - target) <= step) ? target : current - step;
	}

	return current;
}

#endif /* COMMON_H_ */
