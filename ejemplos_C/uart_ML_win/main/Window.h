#ifndef _INC_WINDOW_H_
#define _INC_WINDOW_H_

#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "math.h"

#define abs(a) (((a) < (0)) ? (-a) : (a))


bool transform(float *x, float *dest);
void clear(void);
#endif /* _INC_WINDOW_H_ */