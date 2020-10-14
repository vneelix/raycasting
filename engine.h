#ifndef ENGINE_H
#define ENGINE_H

#include <math.h>

#include <time.h>

#include <stdlib.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define W 1280
#define H 1280

SDL_Window	*win;
SDL_Surface	*sfe;
uint32_t	*pxl;

SDL_Surface *txr;
uint32_t	*img;

SDL_Surface *txr2;
uint32_t	*img2;

typedef struct {
	float x, y;
} float2;

typedef struct {
	float x, y, z;
} float3;

typedef struct {
	float2 p0, p1;
} segment;

#define offsetX 12
#define offsetY 0

segment map[] = {
	(segment){
		(float2){1, 4},
		(float2){7, 4}
	},
	(segment){
		(float2){7, 4},
		(float2){7, 8}
	},
	(segment){
		(float2){7, 8},
		(float2){1, 8}
	},
	(segment){
		(float2){1, 8},
		(float2){1, 4}
	},
	(segment){
		(float2){1 + offsetX, 4 + offsetY},
		(float2){7 + offsetX, 4 + offsetY}
	},
	(segment){
		(float2){7 + offsetX, 4 + offsetY},
		(float2){7 + offsetX, 8 + offsetY}
	},
	(segment){
		(float2){7 + offsetX, 8 + offsetY},
		(float2){1 + offsetX, 8 + offsetY}
	},
	(segment){
		(float2){1 + offsetX, 8 + offsetY},
		(float2){1 + offsetX, 4 + offsetY}
	},
	(segment){
		(float2){1 - offsetX, 4 + offsetY},
		(float2){7 - offsetX, 4 + offsetY}
	},
	(segment){
		(float2){7 - offsetX, 4 + offsetY},
		(float2){7 - offsetX, 8 + offsetY}
	},
	(segment){
		(float2){7 - offsetX, 8 + offsetY},
		(float2){1 - offsetX, 8 + offsetY}
	},
	(segment){
		(float2){1 - offsetX, 8 + offsetY},
		(float2){1 - offsetX, 4 + offsetY}
	},
	(segment){
		(float2){1 - 2 * offsetX, 4 + offsetY},
		(float2){7 - 2 * offsetX, 4 + offsetY}
	},
	(segment){
		(float2){7 - 2 * offsetX, 4 + offsetY},
		(float2){7 - 2 * offsetX, 8 + offsetY}
	},
	(segment){
		(float2){7 - 2 * offsetX, 8 + offsetY},
		(float2){1 - 2 * offsetX, 8 + offsetY}
	},
	(segment){
		(float2){1 - 2 * offsetX, 8 + offsetY},
		(float2){1 - 2 * offsetX, 4 + offsetY}
	},
};

float2 direct = (float2){1, 0};
float2 normalDirect = (float2){0, 1};
float2 origin = (float2){0, 0};

float angle = 0;

float fov = M_PI / 3.f;

float step = (float)0.5f;

float distPlane = 3.f;

segment *activeSegment = NULL;

float2 *array = NULL;
uint32_t aSize = 0;

#endif
