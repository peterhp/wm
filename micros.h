#ifndef _QPT_HEADER_SELF_DEFINED_MICROS_H_
#define _QPT_HEADER_SELF_DEFINED_MICROS_H_

#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#endif // micros.h
