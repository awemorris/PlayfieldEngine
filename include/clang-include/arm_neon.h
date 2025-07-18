#ifndef _ARM_NEON_H
#define _ARM_NEON_H

#if !defined(__ARM_NEON__) && !defined(__ARM_NEON)
#error "Arm NEON not supported"
#endif

#include <stdint.h>

typedef float float32_t;
typedef __fp16 float16_t;
typedef double float64_t;

typedef uint8_t poly8_t;
typedef uint16_t poly16_t;
typedef uint64_t poly64_t;

typedef __attribute__((neon_vector_type(8)))  int8_t int8x8_t;
typedef __attribute__((neon_vector_type(16))) int8_t int8x16_t;
typedef __attribute__((neon_vector_type(4)))  int16_t int16x4_t;
typedef __attribute__((neon_vector_type(8)))  int16_t int16x8_t;
typedef __attribute__((neon_vector_type(2)))  int32_t int32x2_t;
typedef __attribute__((neon_vector_type(4)))  int32_t int32x4_t;
typedef __attribute__((neon_vector_type(1)))  int64_t int64x1_t;
typedef __attribute__((neon_vector_type(2)))  int64_t int64x2_t;
typedef __attribute__((neon_vector_type(8)))  uint8_t uint8x8_t;
typedef __attribute__((neon_vector_type(16))) uint8_t uint8x16_t;
typedef __attribute__((neon_vector_type(4)))  uint16_t uint16x4_t;
typedef __attribute__((neon_vector_type(8)))  uint16_t uint16x8_t;
typedef __attribute__((neon_vector_type(2)))  uint32_t uint32x2_t;
typedef __attribute__((neon_vector_type(4)))  uint32_t uint32x4_t;
typedef __attribute__((neon_vector_type(1)))  uint64_t uint64x1_t;
typedef __attribute__((neon_vector_type(2)))  uint64_t uint64x2_t;
typedef __attribute__((neon_vector_type(4)))  float16_t float16x4_t;
typedef __attribute__((neon_vector_type(8)))  float16_t float16x8_t;
typedef __attribute__((neon_vector_type(2)))  float32_t float32x2_t;
typedef __attribute__((neon_vector_type(4)))  float32_t float32x4_t;
typedef __attribute__((neon_vector_type(1)))  float64_t float64x1_t;
typedef __attribute__((neon_vector_type(2)))  float64_t float64x2_t;
typedef __attribute__((neon_polyvector_type(8)))  poly8_t poly8x8_t;
typedef __attribute__((neon_polyvector_type(16))) poly8_t poly8x16_t;
typedef __attribute__((neon_polyvector_type(4)))  poly16_t poly16x4_t;
typedef __attribute__((neon_polyvector_type(8)))  poly16_t poly16x8_t;
typedef __attribute__((neon_polyvector_type(1)))  poly64_t poly64x1_t;
typedef __attribute__((neon_polyvector_type(2)))  poly64_t poly64x2_t;

typedef struct int8x8x2_t {
	int8x8_t val[2];
} int8x8x2_t;

typedef struct int8x16x2_t {
	int8x16_t val[2];
} int8x16x2_t;

typedef struct int16x4x2_t {
	int16x4_t val[2];
} int16x4x2_t;

typedef struct int16x8x2_t {
	int16x8_t val[2];
} int16x8x2_t;

typedef struct int32x2x2_t {
	int32x2_t val[2];
} int32x2x2_t;

typedef struct int32x4x2_t {
	int32x4_t val[2];
} int32x4x2_t;

typedef struct int64x1x2_t {
	int64x1_t val[2];
} int64x1x2_t;

typedef struct int64x2x2_t {
	int64x2_t val[2];
} int64x2x2_t;

typedef struct uint8x8x2_t {
	uint8x8_t val[2];
} uint8x8x2_t;

typedef struct uint8x16x2_t {
	uint8x16_t val[2];
} uint8x16x2_t;

typedef struct uint16x4x2_t {
	uint16x4_t val[2];
} uint16x4x2_t;

typedef struct uint16x8x2_t {
	uint16x8_t val[2];
} uint16x8x2_t;

typedef struct uint32x2x2_t {
	uint32x2_t val[2];
} uint32x2x2_t;

typedef struct uint32x4x2_t {
	uint32x4_t val[2];
} uint32x4x2_t;

typedef struct uint64x1x2_t {
	uint64x1_t val[2];
} uint64x1x2_t;

typedef struct uint64x2x2_t {
	uint64x2_t val[2];
} uint64x2x2_t;

typedef struct float16x4x2_t {
	float16x4_t val[2];
} float16x4x2_t;

typedef struct float16x8x2_t {
	float16x8_t val[2];
} float16x8x2_t;

typedef struct float32x2x2_t {
	float32x2_t val[2];
} float32x2x2_t;

typedef struct float32x4x2_t {
	float32x4_t val[2];
} float32x4x2_t;

typedef struct float64x1x2_t {
	float64x1_t val[2];
} float64x1x2_t;

typedef struct float64x2x2_t {
	float64x2_t val[2];
} float64x2x2_t;

typedef struct poly8x8x2_t {
	poly8x8_t val[2];
} poly8x8x2_t;

typedef struct poly8x16x2_t {
	poly8x16_t val[2];
} poly8x16x2_t;

typedef struct poly16x4x2_t {
	poly16x4_t val[2];
} poly16x4x2_t;

typedef struct poly16x8x2_t {
	poly16x8_t val[2];
} poly16x8x2_t;

typedef struct poly64x1x2_t {
	poly64x1_t val[2];
} poly64x1x2_t;

typedef struct poly64x2x2_t {
	poly64x2_t val[2];
} poly64x2x2_t;

typedef struct int8x8x3_t {
	int8x8_t val[3];
} int8x8x3_t;

typedef struct int8x16x3_t {
	int8x16_t val[3];
} int8x16x3_t;

typedef struct int16x4x3_t {
	int16x4_t val[3];
} int16x4x3_t;

typedef struct int16x8x3_t {
	int16x8_t val[3];
} int16x8x3_t;

typedef struct int32x2x3_t {
	int32x2_t val[3];
} int32x2x3_t;

typedef struct int32x4x3_t {
	int32x4_t val[3];
} int32x4x3_t;

typedef struct int64x1x3_t {
	int64x1_t val[3];
} int64x1x3_t;

typedef struct int64x2x3_t {
	int64x2_t val[3];
} int64x2x3_t;

typedef struct uint8x8x3_t {
	uint8x8_t val[3];
} uint8x8x3_t;

typedef struct uint8x16x3_t {
	uint8x16_t val[3];
} uint8x16x3_t;

typedef struct uint16x4x3_t {
	uint16x4_t val[3];
} uint16x4x3_t;

typedef struct uint16x8x3_t {
	uint16x8_t val[3];
} uint16x8x3_t;

typedef struct uint32x2x3_t {
	uint32x2_t val[3];
} uint32x2x3_t;

typedef struct uint32x4x3_t {
	uint32x4_t val[3];
} uint32x4x3_t;

typedef struct uint64x1x3_t {
	uint64x1_t val[3];
} uint64x1x3_t;

typedef struct uint64x2x3_t {
	uint64x2_t val[3];
} uint64x2x3_t;

typedef struct float16x4x3_t {
	float16x4_t val[3];
} float16x4x3_t;

typedef struct float16x8x3_t {
	float16x8_t val[3];
} float16x8x3_t;

typedef struct float32x2x3_t {
	float32x2_t val[3];
} float32x2x3_t;

typedef struct float32x4x3_t {
	float32x4_t val[3];
} float32x4x3_t;

typedef struct float64x1x3_t {
	float64x1_t val[3];
} float64x1x3_t;

typedef struct float64x2x3_t {
	float64x2_t val[3];
} float64x2x3_t;

typedef struct poly8x8x3_t {
	poly8x8_t val[3];
} poly8x8x3_t;

typedef struct poly8x16x3_t {
	poly8x16_t val[3];
} poly8x16x3_t;

typedef struct poly16x4x3_t {
	poly16x4_t val[3];
} poly16x4x3_t;

typedef struct poly16x8x3_t {
	poly16x8_t val[3];
} poly16x8x3_t;

typedef struct poly64x1x3_t {
	poly64x1_t val[3];
} poly64x1x3_t;

typedef struct poly64x2x3_t {
	poly64x2_t val[3];
} poly64x2x3_t;

typedef struct int8x8x4_t {
	int8x8_t val[4];
} int8x8x4_t;

typedef struct int8x16x4_t {
	int8x16_t val[4];
} int8x16x4_t;

typedef struct int16x4x4_t {
	int16x4_t val[4];
} int16x4x4_t;

typedef struct int16x8x4_t {
	int16x8_t val[4];
} int16x8x4_t;

typedef struct int32x2x4_t {
	int32x2_t val[4];
} int32x2x4_t;

typedef struct int32x4x4_t {
	int32x4_t val[4];
} int32x4x4_t;

typedef struct int64x1x4_t {
	int64x1_t val[4];
} int64x1x4_t;

typedef struct int64x2x4_t {
	int64x2_t val[4];
} int64x2x4_t;

typedef struct uint8x8x4_t {
	uint8x8_t val[4];
} uint8x8x4_t;

typedef struct uint8x16x4_t {
	uint8x16_t val[4];
} uint8x16x4_t;

typedef struct uint16x4x4_t {
	uint16x4_t val[4];
} uint16x4x4_t;

typedef struct uint16x8x4_t {
	uint16x8_t val[4];
} uint16x8x4_t;

typedef struct uint32x2x4_t {
	uint32x2_t val[4];
} uint32x2x4_t;

typedef struct uint32x4x4_t {
	uint32x4_t val[4];
} uint32x4x4_t;

typedef struct uint64x1x4_t {
	uint64x1_t val[4];
} uint64x1x4_t;

typedef struct uint64x2x4_t {
	uint64x2_t val[4];
} uint64x2x4_t;

typedef struct float16x4x4_t {
	float16x4_t val[4];
} float16x4x4_t;

typedef struct float16x8x4_t {
	float16x8_t val[4];
} float16x8x4_t;

typedef struct float32x2x4_t {
	float32x2_t val[4];
} float32x2x4_t;

typedef struct float32x4x4_t {
	float32x4_t val[4];
} float32x4x4_t;

typedef struct float64x1x4_t {
	float64x1_t val[4];
} float64x1x4_t;

typedef struct float64x2x4_t {
	float64x2_t val[4];
} float64x2x4_t;

typedef struct poly8x8x4_t {
	poly8x8_t val[4];
} poly8x8x4_t;

typedef struct poly8x16x4_t {
	poly8x16_t val[4];
} poly8x16x4_t;

typedef struct poly16x4x4_t {
	poly16x4_t val[4];
} poly16x4x4_t;

typedef struct poly16x8x4_t {
	poly16x8_t val[4];
} poly16x8x4_t;

typedef struct poly64x1x4_t {
	poly64x1_t val[4];
} poly64x1x4_t;

typedef struct poly64x2x4_t {
	poly64x2_t val[4];
} poly64x2x4_t;

#define vst1q_u8(__a, b) __extension__ ({			\
        uint8x16_t __b = (b);					\
        __builtin_neon_vst1q_v(__a, (int8x16_t)__b, 48);	\
})

#define vld1q_u8_x2(__a) __extension__ ({			\
        uint8x16x2_t r;						\
        __builtin_neon_vld1q_x2_v(&r, __a, 48);			\
        r;							\
})

#define vld1q_u8(__a) __extension__ ({				\
        (uint8x16_t)__builtin_neon_vld1q_v(__a, 48);		\
})

#endif /* __ARM_NEON_H */
