/* Implements math3d.h */
#include "math3d.h"

/* Dot product of two 2D vectors */
f32 dot_v2(vec2_t a, vec2_t b) {
  return (a.x * b.x + a.y * b.y);
}
/* Dot product of two 3D vectors */
f32 dot_v3(vec3_t a, vec3_t b) {
  return (a.x * b.x + a.y * b.y);
}
/* Cross product of two 2D vectors - imaginary z component */
f32 cross_v2(vec2_t a, vec2_t b) {
  return (a.x * b.y) - (a.y * b.x);
}
/* Cross product of two 3D vectors */
vec3_t cross_v3(vec3_t a, vec3_t b) {
  vec3_t res;
  res.x = (a.y * b.z) - (a.z * b.y);
  res.y = (a.z * b.x) - (a.x * b.z);
  res.z = (a.x * b.y) - (a.y * b.x);
  return res;
}

/* Add two 2D vectors */
vec2_t add_v2(vec2_t a, vec2_t b) {
  vec2_t res;
  res.x = a.x + b.x;
  res.y = a.y + b.y;
  return res;
}
/* Add two 3D vectors */
vec3_t add_v3(vec3_t a, vec3_t b) {
  vec3_t res;
  res.x = a.x + b.x;
  res.y = a.y + b.y;
  res.z = a.z + b.z;
  return res;
}

/* Negate a 2D vector */
vec2_t negate_v2(vec2_t v) {
  vec2_t res;
  res.x = -v.x;
  res.y = -v.y;
  return res;
}
/* Negate a 3D vector */
vec3_t negate_v3(vec3_t v) {
  vec3_t res;
  res.x = -v.x;
  res.y = -v.y;
  res.z = -v.z;
  return res;
}

/* Normalize a 2D vector */
vec2_t normalize_v2(vec2_t v) {
  vec2_t res;
  f32 len = sqrtf(dot_v2(v, v));
  res.x = v.x / len;
  res.y = v.y / len;
  return res;
}
/* Normalize a 3D vector */
vec3_t normalize_v3(vec3_t v) {
  vec3_t res;
  f32 len = sqrtf(dot_v3(v, v));
  res.x = v.x / len;
  res.y = v.y / len;
  res.z = v.z / len;
  return res;
}

/* Length of a 2D vector */
f32 length_v2(vec2_t v) {
  return sqrtf(dot_v2(v, v));
}
/* Length of a 3D vector */
f32 length_v3(vec3_t v) {
  return sqrtf(dot_v3(v, v));
}

/* Multiply two 4x4 matrices */
mat4_t mulm4(mat4_t a, mat4_t b) {
  mat4_t res;
  res.vals[0] =
    a.vals[0] * b.vals[0]
    + a.vals[1] * b.vals[4]
    + a.vals[2] * b.vals[8]
    + a.vals[3] * b.vals[12];
  res.vals[1] =
    a.vals[0] * b.vals[1]
    + a.vals[1] * b.vals[5]
    + a.vals[2] * b.vals[9]
    + a.vals[3] * b.vals[13];
  res.vals[2] =
    a.vals[0] * b.vals[2]
    + a.vals[1] * b.vals[6]
    + a.vals[2] * b.vals[10]
    + a.vals[3] * b.vals[14];
  res.vals[3] =
    a.vals[0] * b.vals[3]
    + a.vals[1] * b.vals[7]
    + a.vals[2] * b.vals[11]
    + a.vals[3] * b.vals[15];

  res.vals[4] =
    a.vals[4] * b.vals[0]
    + a.vals[5] * b.vals[4]
    + a.vals[6] * b.vals[8]
    + a.vals[7] * b.vals[12];
  res.vals[5] =
    a.vals[4] * b.vals[1]
    + a.vals[5] * b.vals[5]
    + a.vals[6] * b.vals[9]
    + a.vals[7] * b.vals[13];
  res.vals[6] =
    a.vals[4] * b.vals[2]
    + a.vals[5] * b.vals[6]
    + a.vals[6] * b.vals[10]
    + a.vals[7] * b.vals[14];
  res.vals[7] =
    a.vals[4] * b.vals[3]
    + a.vals[5] * b.vals[7]
    + a.vals[6] * b.vals[11]
    + a.vals[7] * b.vals[15];

  res.vals[8] =
    a.vals[8] * b.vals[0]
    + a.vals[9] * b.vals[4]
    + a.vals[10] * b.vals[8]
    + a.vals[11] * b.vals[12];
  res.vals[9] =
    a.vals[8] * b.vals[1]
    + a.vals[9] * b.vals[5]
    + a.vals[10] * b.vals[9]
    + a.vals[11] * b.vals[13];
  res.vals[10] =
    a.vals[8] * b.vals[2]
    + a.vals[9] * b.vals[6]
    + a.vals[10] * b.vals[10]
    + a.vals[11] * b.vals[14];
  res.vals[11] =
    a.vals[8] * b.vals[3]
    + a.vals[9] * b.vals[7]
    + a.vals[10] * b.vals[11]
    + a.vals[11] * b.vals[15];

  res.vals[12] =
    a.vals[12] * b.vals[0]
    + a.vals[13] * b.vals[4]
    + a.vals[14] * b.vals[8]
    + a.vals[15] * b.vals[12];
  res.vals[13] =
    a.vals[12] * b.vals[1]
    + a.vals[13] * b.vals[5]
    + a.vals[14] * b.vals[9]
    + a.vals[15] * b.vals[13];
  res.vals[14] =
    a.vals[12] * b.vals[2]
    + a.vals[13] * b.vals[6]
    + a.vals[14] * b.vals[10]
    + a.vals[15] * b.vals[14];
  res.vals[15] =
    a.vals[12] * b.vals[3]
    + a.vals[13] * b.vals[7]
    + a.vals[14] * b.vals[11]
    + a.vals[15] * b.vals[15];

  return res;
}
/* Multiply a 4x4 matrix by a 4D vector */
vec4_t mulm4v4(mat4_t a, vec4_t b) {
  vec4_t res;
  res.x =
    a.vals[0] * b.x
    + a.vals[1] * b.y
    + a.vals[2] * b.z
    + a.vals[3] * b.w;
  res.y =
    a.vals[4] * b.x
    + a.vals[5] * b.y
    + a.vals[6] * b.z
    + a.vals[7] * b.w;
  res.z =
    a.vals[8] * b.x
    + a.vals[9] * b.y
    + a.vals[10] * b.z
    + a.vals[11] * b.w;
  res.w =
    a.vals[12] * b.x
    + a.vals[13] * b.y
    + a.vals[14] * b.z
    + a.vals[15] * b.w;
  return res;
}

/* Create a perspective projection matrix */
mat4_t projection(f32 fov, f32 aspect, f32 near_z, f32 far_z) {
  mat4_t res;
  memset(&res, 0, sizeof(res));
  f32 projection_a = 1.0 / tan(DEGTORAD(fov)/2);
  f32 projection_b = far_z / (far_z-near_z);
  res.vals[0] = aspect * projection_a;
  res.vals[5] = projection_a;
  res.vals[10] = projection_b;
  res.vals[11] = 1.0;
  res.vals[14] = projection_b * (-near_z);
  res.vals[15] = 0.0;
  return res;
}
/* Create a 4x4 3D translation matrix */
mat4_t translation(vec3_t v) {
  mat4_t res;
  memset(&res, 0, sizeof(res));
  res.vals[3] = v.x;
  res.vals[7] = v.y;
  res.vals[11] = v.z;
  res.vals[0] = 1.0;
  res.vals[5] = 1.0;
  res.vals[10] = 1.0;
  res.vals[15] = 1.0;
  return res;
}
/* Create a 4x4 3D rotation matrix (euler angles: [yaw, pitch, roll]) */
mat4_t euler_rot(vec3_t angles) {
  mat4_t res;
  memset(&res, 0, sizeof(res));
  f32 sin_alpha = sinf(angles.x);
  f32 cos_alpha = cosf(angles.x);
  f32 sin_beta = sinf(angles.y);
  f32 cos_beta = cosf(angles.y);
  f32 sin_gamma = sinf(angles.z);
  f32 cos_gamma = cosf(angles.z);
  res.vals[0] = cos_beta * cos_gamma;
  res.vals[1] = sin_alpha * sin_beta * cos_gamma - cos_alpha * sin_gamma;
  res.vals[2] = cos_alpha * sin_beta * cos_gamma + sin_alpha * sin_gamma;
  res.vals[4] = cos_beta * sin_gamma;
  res.vals[5] = sin_alpha * sin_beta * sin_gamma + cos_alpha * cos_gamma;
  res.vals[6] = cos_alpha * sin_beta * sin_gamma - sin_alpha * cos_gamma;
  res.vals[8] = -sin_beta;
  res.vals[9] = sin_alpha * cos_beta;
  res.vals[10] = cos_alpha * cos_beta;
  res.vals[15] = 1.0;
  return res;
}
