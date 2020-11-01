/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:55:46 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 20:43:11 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

int	loop(t_engine *engine)
{
	SDL_Event	evt;
	const Uint8	*state;

	while (1)
	{
		if ((SDL_PollEvent(&evt) && evt.type == SDL_QUIT)
			|| ((state = SDL_GetKeyboardState(NULL)) == NULL)
									|| state[SDL_SCANCODE_ESCAPE])
			quit(engine);
		if ((state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])
			&& (collision(engine, engine->player.o,
				engine->player.d * (state[SDL_SCANCODE_UP] ? 1. : -1.)) == 0))
			engine->player.o += engine->player.d
				* (state[SDL_SCANCODE_UP] ? 0.12 : -0.12);
		if (state[SDL_SCANCODE_LEFT]
			|| state[SDL_SCANCODE_RIGHT])
		{
			engine->player.delta = fmod(engine->player.delta + RAD(1.28)
				* (state[SDL_SCANCODE_LEFT] ? -1. : 1.), 2. * M_PI);
			engine->player.d = rotate((t_double2){1, 0}, engine->player.delta);
		}
		renderer(engine, engine->player.o, engine->player.d);
		SDL_UpdateWindowSurface(engine->win);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map		*map;
	t_engine	*engine;

	ft_assert(argc == 2, "usage: wolf3d file");
	map = parser(argv[1]);
	if ((engine = ft_memalloc(sizeof(t_engine))) == NULL)
		exit(0);
	engine->map = map;
	if (io_init(engine)
			|| material_init(engine))
		quit(engine);
	engine_init(engine);
	if (geometry_init(engine, map))
		quit(engine);
	loop(engine);
	quit(engine);
}
