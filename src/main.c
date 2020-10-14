/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:49:31 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/14 15:39:22 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	render_prepare(t_engine *engine)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		return (-1);
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
	{
		SDL_Quit();
		return (-1);
	}
	if ((engine->win = SDL_CreateWindow("RC", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN)) == NULL)
	{
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}
	if ((engine->sfe = SDL_GetWindowSurface(engine->win)) == NULL)
	{
		SDL_DestroyWindow(engine->win);
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}
	engine->w = engine->sfe->w;
	engine->h = engine->sfe->h;
	engine->pixel = (uint32_t*)engine->sfe->pixels;
	return (0);
}

int	calculate_angle(t_engine *engine)
{
	int32_t		i;
	float		segment_length;

	i = -W / 2;
	segment_length = tanf(engine->fov / 2.f)
							* engine->distance / (W / 2);
	while (i != W / 2)
	{
		engine->angle[i + W / 2] =
			atanf(segment_length * i / engine->distance);
		i += 1;
	}
	return (0);
}

int	calculate_floor_ceil_point(t_engine *engine)
{
	int32_t		i;
	t_float2	origin;
	t_float2	direct;
	float		segment_length;

	i = -H / 2;
	segment_length = tanf(engine->floor_ceil_fov / 2.f)
							* engine->floor_ceil_distance / (H / 2);
	origin = (t_float2){0, engine->floor_ceil_distance};
	while (i != 0)
	{
		t_float2 example = (t_float2){1.0f, 0.f};
		direct = rotate(example,
			atanf(segment_length * i / engine->floor_ceil_distance));
		engine->floor_ceil_point[i + H / 2] =
			line_line_intersect(origin, origin + direct,
				(t_float2){0.f, 0.f}, (t_float2){1.f, 0.f});
		i += 1;
	}
	return (0);
}

int	engine_prepare(t_engine *engine)
{
	if (render_prepare(engine) == (-1))
		return (-1);
	engine->fov = RAD(60);
	engine->distance = 8.f;
	engine->floor_ceil_fov = RAD(60);
	engine->floor_ceil_distance = 2.f;
	calculate_angle(engine);
	calculate_floor_ceil_point(engine);
	return (0);
}

int	SDL_Loop(t_engine *engine)
{
	SDL_Event	evt;
	SDL_bool	rndr = 0;

	float		angle = 0.f;

	while (SDL_WaitEvent(&evt))
	{
		if (evt.type == SDL_QUIT
			|| (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
			return (0);
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_UP) {
			engine->floor.o += (t_float2){1, 0};
			rndr = 1;
		}
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_DOWN) {
			engine->floor.o -= (t_float2){1, 0};
			rndr = 1;
		}
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_LEFT) {
			angle += 1.f;
			engine->floor.i = normalize(rotate((t_float2){1, 0}, RAD(angle)));
			engine->floor.j = (t_float2){engine->floor.i.y, -engine->floor.i.x};
			rndr = 1;
		}
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_RIGHT) {
			angle -= 1.f;
			engine->floor.i = normalize(rotate((t_float2){1, 0}, RAD(angle)));
			engine->floor.j = (t_float2){engine->floor.i.y, -engine->floor.i.x};
			rndr = 1;
		}
		if (rndr) {
			bzero(engine->pixel, sizeof(uint32_t) * W * H);
			Renderer(engine, (t_float2){0, 0}, normalize(rotate((t_float2){1, 0}, RAD(0))));
			SDL_UpdateWindowSurface(engine->win);
			rndr = 0;
		}
	}
	return (0);
}

int	func(t_engine *engine) {
	engine->item_storage.size = 1;
	engine->item_storage.storage =
		ft_memalloc(sizeof(t_item) * engine->item_storage.size);

	txr.sfe = IMG_Load("materials/textures/brick.png");
	txr.w = txr.sfe->w;
	txr.h = txr.sfe->h;
	txr.pixel = txr.sfe->pixels;

	flr.sfe = IMG_Load("materials/textures/floor.png");
	flr.w = flr.sfe->w;
	flr.h = flr.sfe->h;
	flr.pixel = flr.sfe->pixels;

	((t_item*)engine->item_storage.storage)[0].w = 10;
	((t_item*)engine->item_storage.storage)[0].h = 0;
	((t_item*)engine->item_storage.storage)[0].i = (t_float2){0, 1};
	((t_item*)engine->item_storage.storage)[0].j = (t_float2){1, 0};
	((t_item*)engine->item_storage.storage)[0].o = (t_float2){10, 0};
	((t_item*)engine->item_storage.storage)[0].segment.xy = (t_float2){
		((t_item*)engine->item_storage.storage)[0].o
			+ ((t_item*)engine->item_storage.storage)[0].i
				* ((t_item*)engine->item_storage.storage)[0].w / 2.f};
	((t_item*)engine->item_storage.storage)[0].segment.zw = (t_float2){
		((t_item*)engine->item_storage.storage)[0].o
			- ((t_item*)engine->item_storage.storage)[0].i
				* ((t_item*)engine->item_storage.storage)[0].w / 2.f};
	((t_item*)engine->item_storage.storage)[0].texture = &txr;

	engine->floor.w = 50 * 1.f;
	engine->floor.h = 50 * 1.f;
	engine->floor.texture = &flr;
	engine->floor.o = (t_float2){0, 0};
	engine->floor.i = (t_float2){+1, 0};
	engine->floor.j = (t_float2){0, -1};
	return 0;
}

int	main(void)
{
	t_engine *engine;

	if ((engine = (t_engine*)ft_memalloc(sizeof(t_engine))) == NULL)
		return (-1);
	engine_prepare(engine);
	func(engine);
	bzero(engine->pixel, sizeof(uint32_t) * W * H);
	Renderer(engine, (t_float2){0, 0}, normalize((t_float2){1, 0}));
	SDL_UpdateWindowSurface(engine->win);
	SDL_Loop(engine);
	exit(0);
}
