#ifndef TYPES_H_
#define TYPES_H_

#include <cstdint>
// Integers
typedef std::int8_t  s8,  n8,  i8;
typedef std::int16_t s16, n16, i16;
typedef std::int32_t s32, n32, i32;
typedef std::int64_t s64, n64, i64;
typedef std::int_fast32_t s32f, n32f, i32f;

typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

// Float
typedef float  f32, r32;
typedef double f64, r64;

// Bool
typedef s8   b8;
typedef s32  b32;

#endif // TYPES_H_