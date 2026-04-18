#include "irix.h"

#define IRIX_FP_SNAN        0
#define IRIX_FP_QNAN        1
#define IRIX_FP_POS_INF     2
#define IRIX_FP_NEG_INF     3
#define IRIX_FP_POS_NORM    4
#define IRIX_FP_NEG_NORM    5
#define IRIX_FP_POS_DENORM  6
#define IRIX_FP_NEG_DENORM  7
#define IRIX_FP_POS_ZERO    8
#define IRIX_FP_NEG_ZERO    9

int lib_fp_class_d(double x)
{
	int exponent;
	long long mantissa;
	union {double d; long long ll;} pkt;
	pkt.d = x;
	exponent = pkt.ll >> 52 & 0x7FF;
	mantissa = pkt.ll << 12;
	if (exponent == 0x7FF)
	{
		if (mantissa) return mantissa >= 0 ? IRIX_FP_QNAN : IRIX_FP_SNAN;
		return pkt.ll < 0 ? IRIX_FP_NEG_INF : IRIX_FP_POS_INF;
	}
	if (exponent) return pkt.ll < 0 ? IRIX_FP_NEG_NORM   : IRIX_FP_POS_NORM;
	if (mantissa) return pkt.ll < 0 ? IRIX_FP_NEG_DENORM : IRIX_FP_POS_DENORM;
	return pkt.ll < 0 ? IRIX_FP_NEG_ZERO : IRIX_FP_POS_ZERO;
}
