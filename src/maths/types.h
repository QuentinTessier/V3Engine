#pragma once

#include <stdint.h>

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef float       f32;
typedef double      f64;

typedef int8_t      b8;
typedef int16_t     b16;
typedef int32_t     b32;
typedef int64_t     b64;

#define BITWISE(bit) (1 << (bit))

#define TO_STRING(x) #x

#define DEFINE_VECTOR2_TYPE(type)           \
    typedef struct vec_##type {             \
        type x, y;                          \
    } vec_##type;

DEFINE_VECTOR2_TYPE(i8);
DEFINE_VECTOR2_TYPE(i16);
DEFINE_VECTOR2_TYPE(i32);
DEFINE_VECTOR2_TYPE(i64);

DEFINE_VECTOR2_TYPE(u8);
DEFINE_VECTOR2_TYPE(u16);
DEFINE_VECTOR2_TYPE(u32);
DEFINE_VECTOR2_TYPE(u64);

DEFINE_VECTOR2_TYPE(f32);
DEFINE_VECTOR2_TYPE(f64);

#ifdef _DEBUG_BUILD

struct MathTypesTable {
    char name[32];
} MathTypeTable[] = {
    {TO_STRING(i8)},
    {TO_STRING(i16)},
    {TO_STRING(i32)},
    {TO_STRING(i64)},

    {TO_STRING(u8)},
    {TO_STRING(u16)},
    {TO_STRING(u32)},
    {TO_STRING(u64)},

    {TO_STRING(f32)},
    {TO_STRING(f64)},

    {TO_STRING(b8)},
    {TO_STRING(b16)},
    {TO_STRING(b32)},
    {TO_STRING(b64)},
};

#endif