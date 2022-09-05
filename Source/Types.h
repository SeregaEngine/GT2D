#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

// Integer
typedef int8_t  s8;
typedef int16_t s16;
typedef int     s32; // just int instead of int32_t
typedef long    ls32;
typedef int64_t s64;

typedef uint8_t       u8;
typedef uint16_t      u16;
typedef unsigned int  u32;
typedef unsigned long lu32;
typedef uint64_t      u64;

// Float
typedef float  f32;
typedef double f64;

// Bool
typedef s32 b32;

#endif // TYPES_H_