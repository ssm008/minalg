#ifndef MINALG_H
#define MINALG_H

#include <assert.h>
#include <math.h>
#include <sys/types.h>

#define VEC_MAX_LEN 4

typedef u_int8_t u8;
typedef int8_t s8;
typedef u_int16_t u16;
typedef int16_t s16;
typedef u_int32_t u32;
typedef int32_t s32;
typedef u_int64_t u64;
typedef int64_t s64;
typedef float f32; // Don't worry, will almost always be 32-bit
typedef double f64;

enum vectortype { ROW_VECTOR = 0, COL_VECTOR = 1 };

typedef struct vector {
  s32 len;
  s32 type;
  f64 *d;
} Vec;

typedef struct matrix {
  s32 nr;
  s32 nc;
  f64 *d;
} Matrix;

#define VEC(len_, name_)                                                       \
  f64 name_##_d[VEC_MAX_LEN];                                                  \
  Vec name_ = {len_, ROW_VECTOR, name_##_d};

#define MATRIX(nr_, nc_, name_)                                                \
  f64 name_##_d[VEC_MAX_LEN][VEC_MAX_LEN];                                     \
  Matrix name_ = {nr_, nc_, &name_##_d[0][0]};

const Vec *vec_T(Vec *v1, Vec *v_out);
const Vec *vec_copy(Vec *v1, Vec *v_out);
const Vec *vec_add(Vec *v1, Vec *v2, Vec *v_out);
const Vec *vec_sub(Vec *v1, Vec *v2, Vec *v_out);
const Vec *vec_mul(Vec *v1, Vec *v2, Vec *v_out);
const Vec *vec_scale(Vec *v1, f64 factor, Vec *v_out);
const Vec *vec_offset(Vec *v1, f64 offset, Vec *v_out);

const Matrix *mat_scale(Matrix *m1, f64 factor, Matrix *m_out);
const Matrix *mat_offset(Matrix *m1, f64 offset, Matrix *m_out);
const Matrix *mat_T(Matrix *m1, Matrix *m_out);
const Matrix *mat_add(Matrix *m1, Matrix *m2, Matrix *m_out);

const Matrix *vec_vec_mul(Vec *v1, Vec *v2, Matrix *m_out);
const Vec *mat_vec_mul(Matrix *m1, Vec *v2, Vec *v_out);
const Vec *vec_mat_mul(Vec *v1, Matrix *m2, Vec *v_out);

f64 *MatPtr(Matrix *m, u8 r, u8 c);
#endif
