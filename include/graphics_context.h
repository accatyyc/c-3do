#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include "geometry.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_color;

typedef enum {
	BMP_CONTEXT_TYPE
} context_type;

struct graphics_context {
	context_type type;
	int width;
	int height;
	float *depth_buffer;
	void *_internal;
};

struct texture {
	int width;
	int height;
	void *_internal;
};

struct vertex {
	vec3 coordinate;
	rgb_color color;
	vec3 normal;
	vec2 texture_coordinate;
};

struct graphics_context *create_context(context_type type, int width, int height);
void destroy_context(struct graphics_context *context);

void draw_line(vec2 p1, vec2 p2, struct graphics_context *context, rgb_color color);
void clear(struct graphics_context *context, rgb_color color);
void bmp_context_save(struct graphics_context *context, char name[]);

rgb_color interpolate_color(rgb_color c1, rgb_color c2, float value);

/**
 Draws a 2D triangle. Uses the Z-value of the coordinates for Z-buffering,
 so the Z-value has no visual meaning, and is only used if the graphics
 context has a Z-buffer enabled.

 The shader input can be anything that the rendering program wants to
 input to its shader functions.

 The vertex shader is a function that receives a pointer to a vertex,
 which it is then allowed to transform/change colors of.
 */
void triangle(struct vertex vertices[3],
			  void *shader_input,
			  void (*vertex_shader)(struct vertex *v, void *input),
			  struct graphics_context *context);

struct texture load_texture(char *file_name);

#endif
