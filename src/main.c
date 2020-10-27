/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.r>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:49:31 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/27 13:02:20 by vneelix          ###   ########.r       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/* int	render_prepare(t_engine *engine)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		return (-1);
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
	{
		SDL_Quit();
		return (-1);
	}
	if ((engine->win = SDL_CreateWindow("Raycasting engine", SDL_WINDOWPOS_CENTERED,
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
	if ((engine->rndr = SDL_CreateSoftwareRenderer(engine->sfe)) == NULL)
	{
		SDL_FreeSurface(engine->sfe);
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

int	split_segment(uint32_t length, double fov, double dist, double *angle)
{
	int32_t		i;
	double		segment_length;

	i = -((int32_t)(length / 2));
	segment_length = tanf(fov / 2.) * dist / (length / 2);
	while (i != length / 2)
	{
		angle[i + length / 2] = atanf(segment_length * i / dist);
		i += 1;
	}
	return (0);
}

int	calculate_hor_point(t_engine *engine)
{
	int32_t		i;
	t_double2	origin;
	t_double2	direct;

	i = -H / 2;
	origin = (t_double2){0, engine->ver_distance};
	while (i != 0)
	{
		t_double2 example = (t_double2){1.0f, 0.};
		direct = rotate(example, engine->ver_angle[i + H / 2]);
		engine->hor_point[i + H / 2] =
			line_line_intersect(origin, origin + direct,
				(t_double2){0., 0.}, (t_double2){1., 0.});
		i += 1;
	}
	return (0);
}

int	engine_prepare(t_engine *engine)
{
	if (render_prepare(engine) == (-1))
		return (-1);

	engine->hor_fov = RAD(60);
	engine->hor_distance = 1.;
	engine->ver_fov = RAD(60);
	engine->ver_distance = 1.;

	split_segment(W, engine->hor_fov,
		engine->hor_distance, engine->hor_angle);
	split_segment(H, engine->ver_fov,
		engine->ver_distance, engine->ver_angle);

	for (int i = 0; i != W; i += 1) {
		engine->hor_cosine[i] = cos(engine->hor_angle[i]);
		engine->hor_inv_cosine[i] = 1. / cos(engine->hor_angle[i]);
	}

	calculate_hor_point(engine);

	int ret = material_init(engine);

	return (0);
}

int	SDL_Loop(t_engine *engine)
{
	SDL_Event	evt;
	SDL_bool	rndr = 0;

	double		angle = 0.;

	while (1)
	{
		SDL_PollEvent(&evt);
		if (evt.type == SDL_QUIT
			|| (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
			return (0);
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_LEFT) {
			angle -= (M_PI / 180.) * 2.;
			rD = normalize(rotate((t_double2){1, 0}, angle));
			rndr = 1;
		}
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_RIGHT) {
			angle += (M_PI / 180.) * 2.;
			rD = normalize(rotate((t_double2){1, 0}, angle));
			rndr = 1;
		}
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_UP) {
			oD += rD * 0.5;
			rndr = 1;
		}
		if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_DOWN) {
			oD -= rD * 0.5;
			rndr = 1;
		}
		if (SDL_TRUE) {
			SDL_RenderClear(engine->rndr);
			//uint32_t before = SDL_GetTicks();
			renderer(engine, oD, rD);
			//uint32_t after = SDL_GetTicks();
			//printf("%d\n", (int)(1. / (after - before) * 1000.));
			SDL_UpdateWindowSurface(engine->win);
			rndr = 0;
		}
	}
	return (0);
}

void	item_init(t_item *item, uint32_t color,
					t_texture *txtr, t_double2 p0, t_double2 p1)
{
	item->p0 = p0;
	item->p1 = p1;
	item->w = length(p1 - p0);
	item->i = normalize(p1 - p0);
	item->o = p0 + item->i * 0.5;
	item->j = (t_double2){item->i.y, -item->i.x};
	if (txtr != NULL)
	{
		item->texture = txtr;
		item->r_dx = 1. / (2. / txtr->w);
		item->r_dy = 1. / (2. / txtr->h);
	}
	else
		item->color = color;
}

int	func(t_engine *engine) {
	txr.sfe = IMG_Load("materials/textures/txr1.png");
	txr.sfe = SDL_ConvertSurfaceFormat(txr.sfe, SDL_PIXELFORMAT_BGRA32, 0);
	txr.w = txr.sfe->w;
	txr.h = txr.sfe->h;
	txr.pixel = txr.sfe->pixels;

	engine->item_storage.size = 17;
	engine->item_storage.data =
		ft_memalloc(sizeof(t_item) * engine->item_storage.size);

	item_init((t_item*)engine->item_storage.data + 0, 0, &txr, (t_double2){-5, 5}, (t_double2){-5, -5});
	item_init((t_item*)engine->item_storage.data + 1, 0, &txr, (t_double2){-5, 5}, (t_double2){5, 5});
	item_init((t_item*)engine->item_storage.data + 2, 0, &txr, (t_double2){-5, -5}, (t_double2){5, -5});
	item_init((t_item*)engine->item_storage.data + 3, 0, &txr, (t_double2){5, 5}, (t_double2){5, 2});
	item_init((t_item*)engine->item_storage.data + 4, 0, &txr, (t_double2){5, -5}, (t_double2){5, -2});
	item_init((t_item*)engine->item_storage.data + 5, 0, &txr, (t_double2){5, 2}, (t_double2){10, 2});
	item_init((t_item*)engine->item_storage.data + 6, 0, &txr, (t_double2){5, -2}, (t_double2){10, -2});
	item_init((t_item*)engine->item_storage.data + 7, 0, &txr, (t_double2){10, 2}, (t_double2){14, 6});
	item_init((t_item*)engine->item_storage.data + 8, 0, &txr, (t_double2){10, -2}, (t_double2){14, -6});
	item_init((t_item*)engine->item_storage.data + 9, 0, &txr, (t_double2){14, 6}, (t_double2){18, 6});
	item_init((t_item*)engine->item_storage.data + 10, 0, &txr, (t_double2){14, -6}, (t_double2){18, -6});
	item_init((t_item*)engine->item_storage.data + 11, 0, &txr, (t_double2){18, 6}, (t_double2){18, 0});
	item_init((t_item*)engine->item_storage.data + 12, 0, &txr, (t_double2){18, 0}, (t_double2){18, -6});
	item_init((t_item*)engine->item_storage.data + 13, 0, &txr, (t_double2){14, -2}, (t_double2){16, -2});
	item_init((t_item*)engine->item_storage.data + 14, 0, &txr, (t_double2){14, -4}, (t_double2){16, -4});
	item_init((t_item*)engine->item_storage.data + 15, 0, &txr, (t_double2){14, -4}, (t_double2){14, -2});
	item_init((t_item*)engine->item_storage.data + 16, 0, &txr, (t_double2){16, -4}, (t_double2){16, -2});

	item_init(&engine->ceil, 0, &txr, (t_double2){0, 0}, (t_double2){0, 0});
	item_init(&engine->floor, 0, &txr, (t_double2){0, 0}, (t_double2){0, 0});

	oD = (t_double2){0, 0};
	rD = (t_double2){1, 0};
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
	renderer(engine, oD, rD);
	SDL_UpdateWindowSurface(engine->win);
	SDL_Loop(engine);
	quit(engine);
	exit(0);
} */

int	split_segment(uint32_t length, double fov,
						double dist, double *angle)
{
	int32_t		i;
	double		segment_length;

	i = -((int32_t)(length / 2));
	segment_length = tan(fov / 2.) * dist / (length / 2);
	while (i != length / 2)
	{
		angle[i + length / 2] = atan(segment_length * i / dist);
		i += 1;
	}
	return (0);
}

int	calculate_hor_point(t_engine *engine)
{
	int32_t		i;
	t_double2	origin;
	t_double2	direct;

	i = -H / 2;
	origin = (t_double2){0, engine->ver_distance};
	while (i != 0)
	{
		direct = rotate((t_double2){1.0, 0.},
							engine->ver_angle[i + H / 2]);
		engine->hor_point[i + H / 2] =
			line_line_intersect(origin, origin + direct,
				(t_double2){0., 0.}, (t_double2){1., 0.});
		i += 1;
	}
	return (0);
}

int	engine_init(t_engine *engine)
{
	uint32_t	i;

	i = 0;
	engine->hor_fov = RAD(60);
	engine->ver_fov = RAD(60);
	engine->hor_distance = 1.;
	engine->ver_distance = 1.;
	split_segment(W, engine->hor_fov,
		engine->hor_distance, engine->hor_angle);
	split_segment(H, engine->ver_fov,
		engine->ver_distance, engine->ver_angle);
	while (i != W)
	{
		engine->hor_cosine[i] = cos(engine->hor_angle[i]);
		engine->hor_inv_cosine[i] = 1. / cos(engine->hor_angle[i]);
		i += 1;
	}
	calculate_hor_point(engine);
	return (0);
}

int		main(void)
{
	t_engine *engine;

	if ((engine = ft_memalloc(sizeof(t_engine))) == NULL)
		return (-1);
	if (io_init(engine)
			|| material_init(engine))
		quit(engine);
	engine_init(engine);
	quit(engine);
}
