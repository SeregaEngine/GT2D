#ifndef TYPES_H_
#define TYPES_H_

#include <cstdint>

// Fast integers
typedef std::int_fast8_t  s8,  n8,  i8;
typedef std::int_fast16_t s16, n16, i16;
typedef int               s32, n32, i32;    // << For compatibility
typedef std::int_fast32_t s32f, n32f, i32f; // <<
typedef std::int_fast64_t s64, n64, i64;

typedef std::uint_fast8_t  u8;
typedef std::uint_fast16_t u16;
typedef std::uint_fast32_t u32;
typedef std::uint_fast64_t u64;

// Integers of exact size
typedef std::int8_t  s8e,  n8e,  i8e;
typedef std::int16_t s16e, n16e, i16e;
typedef std::int32_t s32e, n32e, i32e;
typedef std::int64_t s64e, n64e, i64e;

typedef std::uint8_t  u8e;
typedef std::uint16_t u16e;
typedef std::uint32_t u32e;
typedef std::uint64_t u64e;

// Float
typedef float  f32, f32e, r32, r32e;
typedef double f64, f64e, r64, r64e;

// Bool
typedef s32 b32;
typedef s32f b32f;
typedef s32e b32e;

#endif // TYPES_H_