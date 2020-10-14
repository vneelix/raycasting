/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 12:09:05 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/14 15:36:18 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"

# include <math.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# define W 800
# define H 800

# define RAD(DEG) ((DEG) * ((M_PI) / (180.f)))

typedef float	t_float2 __attribute__((ext_vector_type(2)));
typedef float	t_float4 __attribute__((ext_vector_type(4)));

typedef	struct	s_texture {
	SDL_Surface	*sfe;

	uint32_t	w;
	uint32_t	h;
	uint32_t	*pixel;
}				t_texture;

typedef struct	s_storage {
	uint32_t	size;
	char		**title;
	void		*storage;
}				t_storage;

typedef struct	s_item {
	float		w;
	float		h;

	t_float2	o;
	t_float2	i;
	t_float2	j;

	t_float4	segment;

	t_texture	*texture;
}				t_item;

typedef struct	s_engine {
	SDL_Window	*win;
	SDL_Surface	*sfe;

	uint32_t	w;
	uint32_t	h;
	uint32_t	*pixel;

	t_storage	item_storage;

	t_item		floor;

	float		fov;
	float		angle[W];
	float		distance;

	float		floor_ceil_fov;
	float		floor_ceil_distance;
	t_float2	floor_ceil_point[H / 2];
}				t_engine;

t_texture		txr;
t_texture		flr;

float			dot(t_float2 p0, t_float2 p1);
float			length(t_float2 p);
t_float2		normalize(t_float2 p);
t_float2		rotate(t_float2 p, float a);
float			vec2f_projection(t_float2 p0, t_float2 p1);

t_float2		line_line_intersect(t_float2 a, t_float2 b, t_float2 c, t_float2 d);
t_float2		vec2f_segment_intersect(
							t_float2 origin, t_float2 direct, t_float2 c, t_float2 d);

int				ft_read_directory(const char *directory,
					void *addr_double_ptr, uint32_t *number);

float			clamp(float val, float lhs, float rhs);

int				Renderer(t_engine *engine, t_float2 origin, t_float2 direct);

typedef struct	s_intersection {
	t_item		*item;
	t_float2	origin;
	t_float2	intersection;
}				t_intersection;

#endif
