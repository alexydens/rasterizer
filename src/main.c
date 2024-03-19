/* SDL2, windowing and draw a pixel to screen */
#include <SDL2/SDL.h>

/* C Stdlib Headers */
#include <math.h>   /* sin(), cos(), tan() */
#include <stdbool.h>/* For boolean type */
#include <stdio.h>  /* Console I/O */
#include <stdlib.h> /* malloc(), free(), NULL, etc */
#include <string.h> /* memset(), memcpy(), strlen(), etc */

/* Project headers */
#include "math3d.h" /* Vector and matrix math */

/* Consts */
#define WINDOW_WIDTH  1280          /* The width of the window on startup */
#define WINDOW_HEIGHT 720           /* The height of the window on startup */
#define WINDOW_TITLE  "Rasterizer"  /* The window title on startup */
#define SCALE_DOWN    4             /* How much to scale down by */

/* Global state */
struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
  f32 delta_time;
  f32 *z_buffer;
  u64 ticks;
  i32 width, height;
  f32 aspect_ratio;
  f32 fov;
  f32 near_z;
  f32 far_z;
  mat4_t projection;
} app_state;

/* Data */
tri_t quad_tris[12] = {
    {
        .v0 = {.x = 0.5, .y = -0.5, .z = 0.5},
        .v1 = {.x = 0.5, .y = 0.5, .z = 0.5},
        .v2 = {.x = -0.5, .y = -0.5, .z = 0.5},
    },
    {
        .v0 = {.x = -0.5, .y = -0.5, .z = 0.5},
        .v1 = {.x = 0.5, .y = 0.5, .z = 0.5},
        .v2 = {.x = -0.5, .y = 0.5, .z = 0.5},
    },
    {
        .v0 = {.x = 0.5, .y = -0.5, .z = -0.5},
        .v1 = {.x = -0.5, .y = -0.5, .z = -0.5},
        .v2 = {.x = 0.5, .y = 0.5, .z = -0.5},
    },
    {
        .v0 = {.x = -0.5, .y = -0.5, .z = -0.5},
        .v1 = {.x = -0.5, .y = 0.5, .z = -0.5},
        .v2 = {.x = 0.5, .y = 0.5, .z = -0.5},
    },
    {
        .v0 = {.x = 0.5, .y = 0.5, .z = -0.5},
        .v1 = {.x = -0.5, .y = 0.5, .z = -0.5},
        .v2 = {.x = 0.5, .y = 0.5, .z = 0.5},
    },
    {
        .v0 = {.x = -0.5, .y = 0.5, .z = -0.5},
        .v1 = {.x = -0.5, .y = 0.5, .z = 0.5},
        .v2 = {.x = 0.5, .y = 0.5, .z = 0.5},
    },
    {
        .v0 = {.x = 0.5, .y = -0.5, .z = -0.5},
        .v1 = {.x = 0.5, .y = -0.5, .z = 0.5},
        .v2 = {.x = -0.5, .y = -0.5, .z = -0.5},
    },
    {
        .v0 = {.x = -0.5, .y = -0.5, .z = -0.5},
        .v1 = {.x = 0.5, .y = -0.5, .z = 0.5},
        .v2 = {.x = -0.5, .y = -0.5, .z = 0.5},
    },
    {
        .v0 = {.x = 0.5, .y = 0.5, .z = -0.5},
        .v1 = {.x = 0.5, .y = 0.5, .z = 0.5},
        .v2 = {.x = 0.5, .y = -0.5, .z = -0.5},
    },
    {
        .v0 = {.x = 0.5, .y = -0.5, .z = -0.5},
        .v1 = {.x = 0.5, .y = 0.5, .z = 0.5},
        .v2 = {.x = 0.5, .y = -0.5, .z = 0.5},
    },
    {
        .v0 = {.x = -0.5, .y = 0.5, .z = -0.5},
        .v1 = {.x = -0.5, .y = -0.5, .z = -0.5},
        .v2 = {.x = -0.5, .y = 0.5, .z = 0.5},
    },
    {
        .v0 = {.x = -0.5, .y = -0.5, .z = -0.5},
        .v1 = {.x = -0.5, .y = -0.5, .z = 0.5},
        .v2 = {.x = -0.5, .y = 0.5, .z = 0.5},
    },
};
tri_col_t quad_cols[12] = {
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
    {
        .c0 = {0xff, 0x00, 0x00, 0xff},
        .c1 = {0x00, 0xff, 0x00, 0xff},
        .c2 = {0x00, 0x00, 0xff, 0xff},
    },
};
mesh_t quad_mesh = {quad_tris, quad_cols, 12, {0.0, 0.0, 25.0}};

/* Create window */
void create_window(void);
/* Destroy window */
void destroy_window(void);
/* Clear the screen */
void clearscreen(col_t col);
/* Write one pixel to the screen */
void putpixel(u32 x, u32 y, col_t col);
/* Write a triangle to the screen */
void puttri(tri_t tri, tri_col_t cols);

/* Render a triangle */
void render_tri(tri_t tri, tri_col_t cols);
/* Render a mesh */
void render_mesh(mesh_t mesh);

/* Entry point */
int main() {
  SDL_Init(SDL_INIT_VIDEO);
  printf("INFO: Creating window...\n");
  create_window();
  app_state.fov = 60;
  app_state.near_z = 0.1;
  app_state.far_z = 999.0;
  app_state.projection = projection(
      app_state.fov,
      app_state.aspect_ratio,
      app_state.near_z, app_state.far_z
  );
  app_state.ticks = 0;
  /* Main loop */
  while (app_state.running) {
    /* DeltaTime - part 1 */
    u64 start = SDL_GetPerformanceCounter();
    /* Update ticks */
    app_state.ticks++;
    /* Poll through events */
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        app_state.running = false;
        break;
      case SDL_WINDOWEVENT: {
        if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
          app_state.width = e.window.data1 / SCALE_DOWN;
          app_state.height = e.window.data2 / SCALE_DOWN;
          app_state.aspect_ratio = (f32)app_state.height / (f32)app_state.width;
          app_state.projection = projection(
              app_state.fov,
              app_state.aspect_ratio,
              app_state.near_z, app_state.far_z
          );
          app_state.z_buffer = realloc(
              app_state.z_buffer,
              sizeof(f32) * app_state.width * app_state.height
          );
          SDL_RenderSetLogicalSize(
              app_state.renderer,
              app_state.width, app_state.height
          );
        }
      }
      default:
        break;
      }
    }
    /* Clear screen */
    clearscreen((col_t){0x00, 0x00, 0x00, 0xff});
    for (register u64 i = 0; i < (u64)app_state.width * app_state.height; i++) {
      app_state.z_buffer[i] = INFINITY;
    }

    /* Update scene */
    // mat4_t rotation = euler_rot((vec3_t){ DEGTORAD(0.5), DEGTORAD(0.3), 0.0
    // });
    mat4_t rotation = euler_rot((vec3_t){DEGTORAD(0.7), DEGTORAD(0.5), 0.0});
    for (u64 i = 0; i < quad_mesh.tri_count; i++) {
      /* Get triangle */
      tri_t tri = quad_mesh.tris[i];
      /* Create 4D vectors for matrix multiplication */
      vec4_t v0 = {tri.v0.x, tri.v0.y, tri.v0.z, 1};
      vec4_t v1 = {tri.v1.x, tri.v1.y, tri.v1.z, 1};
      vec4_t v2 = {tri.v2.x, tri.v2.y, tri.v2.z, 1};
      v0 = mulm4v4(rotation, v0);
      v1 = mulm4v4(rotation, v1);
      v2 = mulm4v4(rotation, v2);
      quad_mesh.tris[i].v0 = (vec3_t){v0.x, v0.y, v0.z};
      quad_mesh.tris[i].v1 = (vec3_t){v1.x, v1.y, v1.z};
      quad_mesh.tris[i].v2 = (vec3_t){v2.x, v2.y, v2.z};
    }
    /* Draw scene */
    render_mesh(quad_mesh);

    /* Present window */
    SDL_RenderPresent(app_state.renderer);

    /* DeltaTime - part 2 */
    if (app_state.ticks % 100 == 0) {
      char title[48] = "";
      f32 fps =
          app_state.delta_time > 0 ? 1000.0f / app_state.delta_time : 1.0f;
      sprintf(title, "FPS: %f\tDelta Time: %f", fps, app_state.delta_time);
      SDL_SetWindowTitle(app_state.window, title);
    }
    u64 end = SDL_GetPerformanceCounter();
    app_state.delta_time =
        (end - start) / (f32)SDL_GetPerformanceFrequency() * 1000.0f;
  }
  printf("INFO: Destroying window...\n");
  destroy_window();
  SDL_Quit();
  return 0;
}

/* Create window */
void create_window(void) {
  app_state.window = SDL_CreateWindow(WINDOW_TITLE, 0, 0, WINDOW_WIDTH,
                                      WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  app_state.renderer =
      SDL_CreateRenderer(app_state.window, -1,
                         SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  SDL_RenderSetLogicalSize(app_state.renderer, WINDOW_WIDTH / SCALE_DOWN,
                           WINDOW_HEIGHT / SCALE_DOWN);
  app_state.width = WINDOW_WIDTH / SCALE_DOWN;
  app_state.height = WINDOW_HEIGHT / SCALE_DOWN;
  app_state.z_buffer = malloc(sizeof(f32) * app_state.width * app_state.height);
  app_state.aspect_ratio = (f32)app_state.height / (f32)app_state.width;
  app_state.running = true;
}
/* Destroy window */
void destroy_window(void) {
  SDL_DestroyRenderer(app_state.renderer);
  SDL_DestroyWindow(app_state.window);
}
/* Clear the screen */
void clearscreen(col_t col) {
  SDL_SetRenderDrawColor(app_state.renderer, col.r, col.g, col.b, col.a);
  SDL_RenderClear(app_state.renderer);
}
/* Write one pixel to the screen */
void putpixel(u32 x, u32 y, col_t col) {
  SDL_SetRenderDrawColor(app_state.renderer, col.r, col.g, col.b, col.a);
  SDL_RenderDrawPoint(app_state.renderer, x, y);
}
/* Write a triangle to the screen */
typedef struct {
  i32 x, y;
} vec2_int_t;
/* Helper */
inline i32 helper_puttri(vec2_int_t a, vec2_int_t b, vec2_int_t p) {
  vec2_int_t ab = (vec2_int_t){b.x - a.x, b.y - a.y};
  vec2_int_t ap = (vec2_int_t){p.x - a.x, p.y - a.y};
  return (ab.x * ap.y) - (ab.y * ap.x);
}
void puttri(tri_t tri, tri_col_t cols) {
  vec2_int_t v0 = (vec2_int_t){tri.v0.x, tri.v0.y};
  vec2_int_t v1 = (vec2_int_t){tri.v1.x, tri.v1.y};
  vec2_int_t v2 = (vec2_int_t){tri.v2.x, tri.v2.y};
  f32 z0 = tri.v0.z;
  f32 z1 = tri.v1.z;
  f32 z2 = tri.v2.z;
  /* Get bounding box of triangle */
  u32 maxX = MAX(MAX(v0.x, v1.x), v2.x);
  u32 maxY = MAX(MAX(v0.y, v1.y), v2.y);
  u32 minX = MIN(MIN(v0.x, v1.x), v2.x);
  u32 minY = MIN(MIN(v0.y, v1.y), v2.y);

  /* Ensure correct winding order */
  if (helper_puttri(v0, v1, v2) < 0) {
    SWAP(v1, v0);
    SWAP(z1, z0);
  }

  /* Compute 'area' */
  f32 area = helper_puttri(v0, v1, v2);

  /* Loop over bounding box */
  for (u32 y = minY; y < maxY; y++) {
    for (u32 x = minX; x < maxX; x++) {
      vec2_int_t point = (vec2_int_t){x, y};

      /* Find barycentric coordinates - part 1 */
      f32 w0 = helper_puttri(v1, v2, point);
      f32 w1 = helper_puttri(v2, v0, point);
      f32 w2 = helper_puttri(v0, v1, point);

      /* Is it a point in the triangle? */
      bool inTri = w0 >= 0 && w1 >= 0 && w2 >= 0;
      if (inTri) {
        /* Find barycentric coordinates - part 2 */
        f32 alpha = w0 / area;
        f32 beta = w1 / area;
        f32 gamma = w2 / area;

        /* Interpolation - z */
        f32 z = alpha * z0 + beta * z1 + gamma * z2;

        /* Draw pixel */
        if (z<app_state.z_buffer[(y * app_state.width)+(x%app_state.width)]) {
          /* Interpolation - col */
          col_t col;
          col.r = alpha * cols.c0.r + beta * cols.c1.r + gamma * cols.c2.r;
          col.g = alpha * cols.c0.g + beta * cols.c1.g + gamma * cols.c2.g;
          col.b = alpha * cols.c0.b + beta * cols.c1.b + gamma * cols.c2.b;
          /* Draw pixel to screen */
          putpixel(x, y, col);
          /* Update z buffer */
          app_state.z_buffer[(y * app_state.width)+(x%app_state.width)] = z;
        }
      }
    }
  }
}

/* Render a triangle */
void render_tri(tri_t tri, tri_col_t cols) {
  /* Create 4D vectors for matrix multiplication */
  vec4_t v0 = {tri.v0.x, tri.v0.y, tri.v0.z, 1};
  vec4_t v1 = {tri.v1.x, tri.v1.y, tri.v1.z, 1};
  vec4_t v2 = {tri.v2.x, tri.v2.y, tri.v2.z, 1};

  /* Carry out matrix multiplication */
  v0 = mulm4v4(app_state.projection, v0);
  v1 = mulm4v4(app_state.projection, v1);
  v2 = mulm4v4(app_state.projection, v2);
  if (v0.w != 0) {
    v0.x /= v0.w;
    v0.y /= v0.w;
    v0.z /= v0.w;
  }
  if (v1.w != 0) {
    v1.x /= v1.w;
    v1.y /= v1.w;
    v1.z /= v1.w;
  }
  if (v2.w != 0) {
    v2.x /= v2.w;
    v2.y /= v2.w;
    v2.z /= v2.w;
  }

  /* Scale into view */
  v0.x += 1.0;
  v0.x *= 0.5 * app_state.width;
  v1.x += 1.0;
  v1.x *= 0.5 * app_state.width;
  v2.x += 1.0;
  v2.x *= 0.5 * app_state.width;
  v0.y += 1.0;
  v0.y *= 0.5 * app_state.height;
  v1.y += 1.0;
  v1.y *= 0.5 * app_state.height;
  v2.y += 1.0;
  v2.y *= 0.5 * app_state.height;

  SDL_SetRenderDrawColor(app_state.renderer, 0x7f, 0x7f, 0x7f, 0xff);
  SDL_RenderDrawLine(app_state.renderer, v0.x, v0.y, v1.x, v1.y);
  SDL_RenderDrawLine(app_state.renderer, v2.x, v2.y, v1.x, v1.y);
  SDL_RenderDrawLine(app_state.renderer, v2.x, v2.y, v0.x, v0.y);
  putpixel(v0.x, v0.y, (col_t){0xff, 0xff, 0xff, 0xff});
  putpixel(v1.x, v1.y, (col_t){0xff, 0xff, 0xff, 0xff});
  putpixel(v2.x, v2.y, (col_t){0xff, 0xff, 0xff, 0xff});
  tri_t render_tri = {
      VTOVEC3(v0),
      VTOVEC3(v1),
      VTOVEC3(v2),
  };
  puttri(render_tri, cols);
}
/* Render a mesh */
void render_mesh(mesh_t mesh) {
  for (u64 i = 0; i < mesh.tri_count; i++) {
    /* Get triangle from mesh */
    tri_t tri = mesh.tris[i];
    vec3_t line1 = add_v3(tri.v1, negate_v3(tri.v0));
    vec3_t line2 = add_v3(tri.v2, negate_v3(tri.v0));
    vec3_t normal = normalize_v3(cross_v3(line1, line2));
    if (normal.z > 0)
      continue;
    /* Create 4D vectors for matrix multiplication */
    vec4_t v0 = {tri.v0.x, tri.v0.y, tri.v0.z, 1};
    vec4_t v1 = {tri.v1.x, tri.v1.y, tri.v1.z, 1};
    vec4_t v2 = {tri.v2.x, tri.v2.y, tri.v2.z, 1};
    /* Translate into world space */
    mat4_t trans = translation(mesh.pos);
    v0 = mulm4v4(trans, v0);
    v1 = mulm4v4(trans, v1);
    v2 = mulm4v4(trans, v2);
    /* Put back in triangle */
    tri.v0 = VTOVEC3(v0);
    tri.v1 = VTOVEC3(v1);
    tri.v2 = VTOVEC3(v2);
    render_tri(tri, mesh.cols[i]);
  }
}
