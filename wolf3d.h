/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 12:09:05 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 16:59:12 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "parser.h"
# include "minilibft.h"

# include <math.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# define W 1000
# define H 1000

# define RAD(DEG) ((DEG) * ((M_PI) / (180.f)))

typedef double	t_double2 __attribute__((ext_vector_type(2)));
typedef double	t_double4 __attribute__((ext_vector_type(4)));

typedef	struct	s_texture {
	SDL_Surface	*sfe;

	uint32_t	w;
	uint32_t	h;
	uint32_t	*pixel;
}				t_texture;

typedef struct	s_storage {
	uint32_t	size;
	void		*data;
	char		**title;
}				t_storage;

typedef struct	s_item {
	double		w;
	double		h;

	t_double2	o;
	t_double2	i;
	t_double2	j;

	t_double2	p0;
	t_double2	p1;

	uint32_t	color;

	double		r_dx;
	double		r_dy;
	t_texture	*texture;
}				t_item;

typedef struct	s_plr {
	t_double2	o;
	t_double2	d;
	double		delta;
}				t_plr;

typedef struct	s_engine {
	SDL_Window		*win;
	SDL_Surface		*sfe;
	SDL_Renderer	*rndr;

	uint32_t		w;
	uint32_t		h;
	uint32_t		*pixel;

	t_map			*map;

	t_storage		item_storage;
	t_storage		texture_storage;

	t_item			ceil;
	t_item			floor;

	t_plr			player;

	double			hor_fov;
	double			hor_angle[W];
	double			hor_distance;

	double			hor_cosine[W];
	double			hor_inv_cosine[W];

	double			ver_fov;
	double			ver_angle[H];
	double			ver_distance;

	t_double2		hor_point[H / 2];

	int				collision;

	int				nswe;
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
}				t_engine;

/*
** intersection.c
*/
double			prj(t_double2 a, t_double2 b);
t_double2		line_line_intersect(t_double2 a, t_double2 b,
										t_double2 c, t_double2 d);
t_double2		vec_segment_intersect(t_double2 o, t_double2 d,
										t_double2 p0, t_double2 p1);
t_double2		find_nearest_point(t_engine *engine, t_double2 o,
										t_double2 d, uint32_t *index);

/*
** intersection2.c
*/
int				collision(t_engine *engine, t_double2 o, t_double2 d);
t_double2		point_line_projection(t_double2 p,
										t_double2 a, t_double2 b);
t_double2		point_segment_projection(
						t_double2 p, t_double2 a, t_double2 b);

/*
** renderer.c
*/
int				rndr_ceil_floor(t_engine *engine, int x,
								t_double4 r, double height);
int				rndr_wall(t_engine *engine, int x,
						t_double4 inter, t_item *item);
int				renderer(t_engine *engine, t_double2 o, t_double2 d);

/*
** renderer_func.c
*/
double			calc_height(t_engine *engine, double dist);
double			illu_calc(t_double2 d, t_double2 n);

/*
** vec_op.c
*/
double			dot(t_double2 p0, t_double2 p1);
double			length(t_double2 p);
t_double2		normalize(t_double2 p);
t_double2		rotate(t_double2 p, double a);
t_double2		decomp(t_double2 o, t_double2 i,
							t_double2 j, t_double2 p);

/*
** func.c
*/
double			clamp(double val, double lhs, double rhs);
uint32_t		color_dot_f(uint32_t color, double m);

/*
** material_init.c
*/
int				surface_load(SDL_Surface **dest,
								const char *path, Uint32 format);
int				material_init(t_engine *engine);

int				io_init(t_engine *engine);
int				quit(t_engine *engine);
int				geometry_init(t_engine *engine, t_map *map);
int				release_map(t_map *map);

int				remove_it_nswe_init(t_engine *engine);
int				remove_it_nswe(t_engine *engine, t_item *item);

#endif
