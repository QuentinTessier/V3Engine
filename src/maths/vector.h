#pragma once

#include <stdio.h>
#include "types.h"

#define DEFINE_VECTOR_CONSTRUCTOR_2(type)                       \
    static inline vec_##type vec_##type##_(type x, type y)      \
    { return (vec_##type){x, y}; }

#define DEFINE_PRINT_VECTOR_INTEGER_2(type, format)             \
    static void print_vec_##type(FILE *stream, vec_##type const v)     \
    { fprintf(stream, "(%"#format", ""%"#format")", v.x, v.y); }

#define DEFINE_PRINT_VECTOR_DECIMAL_2(type, format)                                             \
    static void print_vec_##type(FILE *stream, int precision, vec_##type const v)                      \
    { fprintf(stream, "(%.*"#format", ""%.*"#format")", precision, v.x, precision, v.y); }

#define DEFINE_VECTOR_TO_STRING_INTEGER_2(type, format)                                         \
    static char *to_string_vec_##type(char *buffer, size_t max, vec_##type const v)                    \
    { snprintf(buffer, max, "(%"#format", ""%"#format")", v.x, v.y); }

#define DEFINE_VECTOR_TO_STRING_DECIMAL_2(type, format)                                         \
    static char *to_string_vec_##type(char *buffer, size_t max, int precision, vec_##type const v)     \
    { snprintf(buffer, max, "(%.*"#format", ""%.*"#format")", precision, v.x, precision, v.y); }

#define DEFINE_VECTOR_OPERATION_2(type, op, name)               \
    static vec_##type vec_##type##_##name(vec_##type a, vec_##type b)  \
    { return ((vec_##type){a.x op b.x, a.y op b.y}); }

#define DEFINE_VECTOR_FUNCTIONS_2(type)                         \
    DEFINE_VECTOR_CONSTRUCTOR_2(type);                          \
    DEFINE_VECTOR_OPERATION_2(type, +, add);                    \
    DEFINE_VECTOR_OPERATION_2(type, -, sub);                    \
    DEFINE_VECTOR_OPERATION_2(type, /, div);                    \
    DEFINE_VECTOR_OPERATION_2(type, *, mul);


DEFINE_VECTOR_FUNCTIONS_2(i8);
DEFINE_VECTOR_FUNCTIONS_2(i16);
DEFINE_VECTOR_FUNCTIONS_2(i32);
DEFINE_VECTOR_FUNCTIONS_2(i64);

DEFINE_VECTOR_FUNCTIONS_2(u8);
DEFINE_VECTOR_FUNCTIONS_2(u16);
DEFINE_VECTOR_FUNCTIONS_2(u32);
DEFINE_VECTOR_FUNCTIONS_2(u64);

DEFINE_VECTOR_FUNCTIONS_2(f32);
DEFINE_VECTOR_FUNCTIONS_2(f64);

DEFINE_PRINT_VECTOR_INTEGER_2(i8, d);
DEFINE_PRINT_VECTOR_INTEGER_2(i16, d);
DEFINE_PRINT_VECTOR_INTEGER_2(i32, d);
DEFINE_PRINT_VECTOR_INTEGER_2(i64, d);

DEFINE_PRINT_VECTOR_INTEGER_2(u8, d);
DEFINE_PRINT_VECTOR_INTEGER_2(u16, d);
DEFINE_PRINT_VECTOR_INTEGER_2(u32, d);
DEFINE_PRINT_VECTOR_INTEGER_2(u64, d);

DEFINE_VECTOR_TO_STRING_INTEGER_2(i8, d);
DEFINE_VECTOR_TO_STRING_INTEGER_2(i16, d);
DEFINE_VECTOR_TO_STRING_INTEGER_2(i32, d);
DEFINE_VECTOR_TO_STRING_INTEGER_2(i64, d);

DEFINE_VECTOR_TO_STRING_INTEGER_2(u16, d);
DEFINE_VECTOR_TO_STRING_INTEGER_2(u32, d);
DEFINE_VECTOR_TO_STRING_INTEGER_2(u8, d);
DEFINE_VECTOR_TO_STRING_INTEGER_2(u64, d);

DEFINE_PRINT_VECTOR_DECIMAL_2(f32, f);
DEFINE_PRINT_VECTOR_DECIMAL_2(f64, f);

DEFINE_VECTOR_TO_STRING_DECIMAL_2(f32, f);
DEFINE_VECTOR_TO_STRING_DECIMAL_2(f64, f);