#include "minalg.h"

/* --- VECTORS --- */

const Vec *vec_T(Vec *v1, Vec *v_out) {
  vec_copy(v1, v_out);
  v_out->type ^= 1;
  return v_out;
}

const Vec *vec_copy(Vec *v1, Vec *v_out) {
  v_out->len = v1->len;
  v_out->type = v1->type;
  for (u8 i = 0; i < v_out->len; i++) {
    v_out->d[i] = v1->d[i];
  }
  return v_out;
}

const Vec *vec_add(Vec *v1, Vec *v2, Vec *v_out) {
  for (u8 i = 0; i < v_out->len; i++) {
    v_out->d[i] = v1->d[i] + v2->d[i];
  }
  return v_out;
}

const Vec *vec_sub(Vec *v1, Vec *v2, Vec *v_out) {
  for (u8 i = 0; i < v_out->len; i++) {
    v_out->d[i] = v1->d[i] - v2->d[i];
  }
  return v_out;
}

const Vec *vec_mul(Vec *v1, Vec *v2, Vec *v_out) {
  for (u8 i = 0; i < v_out->len; i++) {
    v_out->d[i] = v1->d[i] * v2->d[i];
  }
  return v_out;
}

const Vec *vec_scale(Vec *v1, f64 factor, Vec *v_out) {
  for (u8 i = 0; i < v_out->len; i++) {
    v_out->d[i] = v1->d[i] * factor;
  }
  return v_out;
}

const Vec *vec_offset(Vec *v1, f64 offset, Vec *v_out) {
  for (u8 i = 0; i < v_out->len; i++) {
    v_out->d[i] = v1->d[i] + offset;
  }
  return v_out;
}

/* --- MATRICES --- */

f64 *MatPtr(Matrix *m, u8 r, u8 c) { return &m->d[r * VEC_MAX_LEN + c]; }

const Matrix *mat_scale(Matrix *m1, f64 factor, Matrix *m_out) {
  for (u8 r = 0; r < m_out->nr; r++) {
    for (u8 c = 0; c < m_out->nc; c++) {
      *MatPtr(m_out, r, c) = *MatPtr(m1, r, c) * factor;
    }
  }
  return m_out;
}

const Matrix *mat_offset(Matrix *m1, f64 offset, Matrix *m_out) {
  for (u8 r = 0; r < m_out->nr; r++) {
    for (u8 c = 0; c < m_out->nc; c++) {
      *MatPtr(m_out, r, c) = *MatPtr(m1, r, c) + offset;
    }
  }
  return m_out;
}

const Matrix *mat_add(Matrix *m1, Matrix *m2, Matrix *m_out) {
  for (u8 r = 0; r < m_out->nr; r++) {
    for (u8 c = 0; c < m_out->nc; c++) {
      *MatPtr(m_out, r, c) = *MatPtr(m1, r, c) + *MatPtr(m2, r, c);
    }
  }
  return m_out;
}

const Matrix *mat_T(Matrix *m1, Matrix *m_out) {
  for (u8 r = 0; r < m_out->nr; r++) {
    for (u8 c = 0; c < m_out->nc; c++) {
      *MatPtr(m_out, r, c) = *MatPtr(m1, c, r);
    }
  }
  return m_out;
}

/* --- VECTOR MATRIX MULTIPLICATIONS --- */

const Matrix *vec_vec_mul(Vec *v1, Vec *v2, Matrix *m_out) {
  for (u8 r = 0; r < m_out->nr; r++) {
    for (u8 c = 0; c < m_out->nc; c++) {
      *MatPtr(m_out, r, c) = v1->d[r] * v2->d[c];
    }
  }
  return m_out;
}

const Vec *mat_vec_mul(Matrix *m1, Vec *v2, Vec *v_out) {
  vec_scale(v_out, 0.0, v_out);
  for (u8 r = 0; r < m1->nr; r++) {
    for (u8 c = 0; c < m1->nc; c++) {
      v_out->d[r] += *MatPtr(m1, r, c) * v2->d[c];
    }
  }
  return v_out;
}

const Vec *vec_mat_mul(Vec *v1, Matrix *m2, Vec *v_out) {
  vec_scale(v_out, 0.0, v_out);
  for (u8 r = 0; r < m2->nr; r++) {
    for (u8 c = 0; c < m2->nc; c++) {
      v_out->d[c] += *MatPtr(m2, r, c) * v1->d[r];
    }
  }
  return v_out;
}
