/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:03:29 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/26 18:27:53 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	clr_ceil_floor(t_engine *engine, t_double2 p)
{
	int	index;

	if (engine->ceil.texture != NULL)
	{
		index = (int)(p.x * engine->ceil.r_dx)
			+ engine->ceil.texture->w * (int)(p.y * engine->ceil.r_dy);
		engine->ceil.color = engine->ceil.texture->pixel[index];
	}
	if (engine->floor.texture != NULL)
	{
		index = (int)(p.x * engine->floor.r_dx)
			+ engine->floor.texture->w * (int)(p.y * engine->floor.r_dy);
		engine->floor.color = engine->floor.texture->pixel[index];
	}
	return (0);
}

int			rndr_ceil_floor(t_engine *engine, int x,
								t_double4 r, double height)
{
	int			y;
	int			brdr;
	t_double2	p;
	int			rndr;

	y = -H / 2;
	brdr = clamp(height, 0., H / 2.);
	rndr = engine->ceil.texture != NULL
	|| engine->floor.texture != NULL ? 1 : 0;
	while (y != -brdr)
	{
		if (rndr)
		{
			p = decomp(r.xy, r.zw, (t_double2){r.w, -r.z},
			engine->hor_point[y + H / 2] * engine->hor_inv_cosine[x + W / 2]);
			p = (t_double2){fabs(fmod(p.x, 2.)), fabs(fmod(p.y, 2.))};
			clr_ceil_floor(engine, p);
		}
		engine->pixel[(x + W / 2) + W * (y + H / 2)] = engine->ceil.color;
		engine->pixel[(x + W / 2) + W * (H / 2 - y - 1)] = engine->floor.color;
		y += 1;
	}
	return (0);
}

int			rndr_wall(t_engine *engine, int x,
					t_double4 inter, t_item *item)
{
	int			y;
	int			brdr;
	double		r_dy;
	uint32_t	color;
	int			txtr_x;

	if (item->texture != NULL)
	{
		r_dy = 1. / (2. * inter[2] / item->texture->h);
		txtr_x = fmod(length(inter.xy - item->p0), 2.) * item->r_dx;
	}
	brdr = clamp(inter[2], 0., H / 2.);
	y = -brdr;
	while (y != brdr)
	{
		if (item->texture != NULL)
			color = color_dot_f(item->texture->pixel[txtr_x
			+ item->texture->w * (int)((y + inter[2]) * r_dy)], inter[3]);
		else
			color = color_dot_f(item->color, inter[3]);
		engine->pixel[(x + W / 2) + W * (y + H / 2)] = color;
		y += 1;
	}
	return (0);
}

int			renderer(t_engine *engine, t_double2 o, t_double2 d)
{
	int			x;
	t_double2	d_;
	uint32_t	ind;
	t_double2	inter;
	int			height;

	x = -W / 2;
	while (x != W / 2)
	{
		height = 0;
		d_ = rotate(d, engine->hor_angle[x + W / 2]);
		inter = find_nearest_point(engine, o, d_, &ind);
		if (inter.x != INFINITY && inter.y != INFINITY)
		{
			height = calc_height(engine, length(inter - o)
							* engine->hor_cosine[x + W / 2]);
			rndr_wall(engine, x, (t_double4){inter.x, inter.y, height,
				illu_calc(d_, ((t_item*)engine->item_storage.data)[ind].j)},
									(t_item*)engine->item_storage.data + ind);
		}
		rndr_ceil_floor(engine, x,
			(t_double4){o.x, o.y, d_.x, d_.y}, height);
		x += 1;
	}
	return (0);
}
