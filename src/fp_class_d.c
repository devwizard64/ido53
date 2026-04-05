#include "app.h"

#define FP_SNAN         0
#define FP_QNAN         1
#define FP_POS_INF      2
#define FP_NEG_INF      3
#define FP_POS_NORM     4
#define FP_NEG_NORM     5
#define FP_POS_DENORM   6
#define FP_NEG_DENORM   7
#define FP_POS_ZERO     8
#define FP_NEG_ZERO     9

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
		if (mantissa) return mantissa >= 0 ? FP_QNAN : FP_SNAN;
		return pkt.ll < 0 ? FP_NEG_INF : FP_POS_INF;
	}
	if (exponent) return pkt.ll < 0 ? FP_NEG_NORM   : FP_POS_NORM;
	if (mantissa) return pkt.ll < 0 ? FP_NEG_DENORM : FP_POS_DENORM;
	return pkt.ll < 0 ? FP_NEG_ZERO : FP_POS_ZERO;
}
