/* Include guard */
#if !defined(MATH3D_H)
#define MATH3D_H

/* C Stdlib headers */
#include <math.h>   /* For trig functions */
#include <stdint.h> /* For integer types */
#include <string.h> /* For memset() */

/* Consts */
#define PI 3.141592654
#define TWO_PI 6.283185308
#define PI_OVER_180 0.017453293

/* Typedefs */
/* Unsigned integers */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
/* Signed integers */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
/* Floating point numbers */
typedef float f32;
typedef double f64;

/* The type of a colour */
typedef struct {
  u8 r, g, b, a;
} col_t;
/* The type of a 2D vector */
typedef struct {
  f32 x, y;
} vec2_t;
/* The type of a 3D vector */
typedef struct {
  f32 x, y, z;
} vec3_t;
/* The type of a 4D vector */
typedef struct {
  f32 x, y, z, w;
} vec4_t;
/* The type of a 4x4 matrix */
typedef struct {
  f32 vals[16];
} mat4_t;
/* The type of a triangle in 3D space */
typedef struct {
  vec3_t v0, v1, v2;
} tri_t;
/* The type of a triangle in 2D space */
typedef struct {
  vec2_t v0, v1, v2;
} tri2_t;
typedef struct {
  col_t c0, c1, c2;
} tri_col_t;
/* The type of a 3D mesh */
typedef struct {
  tri_t* tris;
  tri_col_t* cols;
  u64 tri_count;
  vec3_t pos;
} mesh_t;

/* Macros */
/* Convert easily from vector types with more dimensions */
#define VTOVEC2(a)  ((vec2_t){(a).x, (a).y})
#define VTOVEC3(a)  ((vec3_t){(a).x, (a).y, (a).z})
#define DEGTORAD(a) ((a) * PI_OVER_180)
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#define SWAP(a, b)  do{__typeof__((a)) tmp = (a); a = b; b = tmp;}while(0);

/* Dot product of two 2D vectors */
f32 dot_v2(vec2_t a, vec2_t b);
/* Dot product of two 3D vectors */
f32 dot_v3(vec3_t a, vec3_t b);
/* Cross product of two 2D vectors - imaginary z component */
f32 cross_v2(vec2_t a, vec2_t b);
/* Cross product of two 3D vectors */
vec3_t cross_v3(vec3_t a, vec3_t b);

/* Add two 2D vectors */
vec2_t add_v2(vec2_t a, vec2_t b);
/* Add two 3D vectors */
vec3_t add_v3(vec3_t a, vec3_t b);

/* Negate a 2D vector */
vec2_t negate_v2(vec2_t v);
/* Negate a 3D vector */
vec3_t negate_v3(vec3_t v);

/* Normalize a 2D vector */
vec2_t normalize_v2(vec2_t v);
/* Normalize a 3D vector */
vec3_t normalize_v3(vec3_t v);

/* Length of a 2D vector */
f32 length_v2(vec2_t v);
/* Length of a 3D vector */
f32 length_v3(vec3_t v);

/* Multiply two 4x4 matrices */
mat4_t mulm4(mat4_t a, mat4_t b);
/* Multiply a 4x4 matrix by a 4D vector */
vec4_t mulm4v4(mat4_t a, vec4_t b);

/* Create a perspective projection matrix */
mat4_t projection(f32 fov, f32 aspect, f32 near_z, f32 far_z);
/* Create a 4x4 3D translation matrix */
mat4_t translation(vec3_t v);
/* Create a 4x4 3D rotation matrix (euler angles: [yaw, pitch, roll]) */
mat4_t euler_rot(vec3_t angles);

#endif /* MATH3D_H */
