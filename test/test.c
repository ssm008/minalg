#include "minalg.h"
#include <float.h>
#include <stdio.h>

// Used for comparing floats.
static f64 epsilon = DBL_EPSILON;

u8 equal(f64 a, f64 b);
u8 test_vec_add(void);
u8 test_vec_sub(void);
u8 test_mat_add(void);
u8 test_vec_vec_mul(void);
u8 test_mat_vec_mul(void);
u8 test_vec_mat_mul(void);

#define RUN_TEST(testname)                                                     \
  printf("Running %s()\n", #testname);                                         \
  testname();

int main(void) {
  RUN_TEST(test_vec_add);
  RUN_TEST(test_vec_sub);
  RUN_TEST(test_mat_add);
  RUN_TEST(test_vec_vec_mul);
  RUN_TEST(test_mat_vec_mul);
  RUN_TEST(test_vec_mat_mul);

  return 0;
}

u8 equal(f64 a, f64 b) {
  a = fabs(a);
  b = fabs(b);
  f64 diff = fabs(a - b);

  if (a == b) {
    return 1;
  } else if (a == 0.0 || b == 0.0 || a + b < DBL_MIN) {
    return diff < (epsilon * DBL_MIN);
  } else {
    return diff / fmin(a + b, DBL_MAX) < epsilon;
  }
}

u8 test_vec_add(void) {
  VEC(2, v1)
  VEC(2, v2)
  VEC(2, v_out)
  const Vec *result;
  result = vec_add(&v1, &v2, &v_out);
  assert(result == &v_out);
  assert(equal(v_out.d[0], v1.d[0] + v2.d[0]));

  return 0;
}

u8 test_vec_sub(void) {
  VEC(2, v1)
  VEC(2, v2)
  VEC(2, v_out)
  const Vec *result;
  v1.d[0] = 1;
  v1.d[1] = 2;
  v2.d[0] = 3;
  v2.d[1] = 4;
  result = vec_sub(&v1, &v2, &v_out);
  assert(result == &v_out);
  assert(equal(v_out.d[0], v1.d[0] - v2.d[0]));
  assert(equal(v_out.d[0], v1.d[0] - v2.d[0]));

  return 0;
}

u8 test_mat_add(void) {
  MATRIX(2, 2, m1)
  MATRIX(2, 2, m2)
  MATRIX(2, 2, m_out)
  const Matrix *result;

  mat_scale(&m1, 0.0, &m1);
  mat_scale(&m2, 0.0, &m2);
  *MatPtr(&m1, 0, 0) = 1;
  *MatPtr(&m1, 0, 1) = 2;
  *MatPtr(&m2, 1, 0) = 3;
  *MatPtr(&m2, 1, 1) = 4;

  result = mat_add(&m1, &m2, &m_out);
  assert(result == &m_out);
  assert(equal(*MatPtr(&m_out, 0, 0), *MatPtr(&m1, 0, 0) + *MatPtr(&m2, 0, 0)));
  assert(equal(*MatPtr(&m_out, 0, 1), *MatPtr(&m1, 0, 1) + *MatPtr(&m2, 0, 1)));
  assert(equal(*MatPtr(&m_out, 1, 0), *MatPtr(&m1, 1, 0) + *MatPtr(&m2, 1, 0)));
  assert(equal(*MatPtr(&m_out, 1, 1), *MatPtr(&m1, 1, 1) + *MatPtr(&m2, 1, 1)));
  return 0;
}

u8 test_vec_vec_mul() {
  VEC(2, v1)
  VEC(2, v2)
  MATRIX(2, 2, m_out)
  const Matrix *result;

  v1.d[0] = 1;
  v1.d[1] = 2;
  v2.d[0] = 5;
  v2.d[1] = 6;

  result = vec_vec_mul(&v1, &v2, &m_out);
  assert(result == &m_out);
  assert(equal(*MatPtr(&m_out, 0, 0), v1.d[0] * v2.d[0]));
  assert(equal(*MatPtr(&m_out, 0, 1), v1.d[0] * v2.d[1]));
  assert(equal(*MatPtr(&m_out, 1, 0), v1.d[1] * v2.d[0]));
  assert(equal(*MatPtr(&m_out, 1, 1), v1.d[1] * v2.d[1]));
  return 0;
}

u8 test_mat_vec_mul(void) {
  MATRIX(2, 2, m1)
  VEC(2, v2)
  VEC(2, v_out)

  *MatPtr(&m1, 0, 0) = 1;
  *MatPtr(&m1, 0, 1) = 2;
  *MatPtr(&m1, 1, 0) = 3;
  *MatPtr(&m1, 1, 1) = 4;
  v2.d[0] = 10;
  v2.d[1] = 11;

  const Vec *result = mat_vec_mul(&m1, &v2, &v_out);
  assert(result == &v_out);
  assert(equal(v_out.d[0],
               *MatPtr(&m1, 0, 0) * v2.d[0] + *MatPtr(&m1, 0, 1) * v2.d[1]));
  assert(equal(v_out.d[1],
               *MatPtr(&m1, 1, 0) * v2.d[0] + *MatPtr(&m1, 1, 1) * v2.d[1]));

  return 0;
}

u8 test_vec_mat_mul(void) {
  VEC(2, v1)
  MATRIX(2, 2, m2)
  VEC(2, v_out)
  const Vec *result;

  *MatPtr(&m2, 0, 0) = 1;
  *MatPtr(&m2, 0, 1) = 2;
  *MatPtr(&m2, 1, 0) = 3;
  *MatPtr(&m2, 1, 1) = 4;
  v1.d[0] = 10;
  v1.d[1] = 11;

  result = vec_mat_mul(&v1, &m2, &v_out);
  assert(result == &v_out);
  assert(equal(v_out.d[0],
               *MatPtr(&m2, 0, 0) * v1.d[0] + *MatPtr(&m2, 1, 0) * v1.d[1]));
  assert(equal(v_out.d[1],
               *MatPtr(&m2, 0, 1) * v1.d[0] + *MatPtr(&m2, 1, 1) * v1.d[1]));
  return 0;
}
