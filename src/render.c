/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:15:39 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/14 14:07:57 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_float2	FindNearestPoint(t_engine *engine, t_float2 origin,
								t_float2 direct, uint32_t *index)
{
	uint32_t	i;
	t_float2	min;
	t_float2	point;
	float		distance;

	i = 0;
	min = (t_float2){INFINITY, INFINITY};
	while (i != engine->item_storage.size)
	{
		point = vec2f_segment_intersect(origin, direct,
			((t_item*)engine->item_storage.storage)[i].segment.xy,
				((t_item*)engine->item_storage.storage)[i].segment.zw);
		if (length(point - origin) < length(min - origin))
		{
			if (index != NULL)
				*index = i;
			min = point;
		}
		i += 1;
	}
	return (min);
}

uint32_t	TextureSampling(t_engine *engine,
				int h, int y, t_intersection inter)
{
	float		dx;
	float		dy;
	uint32_t	texture_x;
	uint32_t	texture_y;

	dx = inter.item->w / (float)inter.item->texture->w;
	dy = h / (float)inter.item->texture->h;
	texture_x = length(inter.intersection - inter.item->segment.xy) / dx;
	texture_y = y / dy;
	
	return (inter.item->texture->pixel[
		texture_x + inter.item->texture->w * texture_y]);
}

int			RenderFunction(t_engine *engine, int x, t_intersection inter)
{
	uint32_t	y;
	int			height;
	float		distance;
	uint32_t	vertical_size;

	distance = length(inter.intersection - inter.origin)
		* cosf(engine->angle[x]) + (float)1e-4;
	height = (H / distance) * engine->distance;
	vertical_size = clamp(height, 0, H);
	y = 0;
	while (y != vertical_size)
	{
		float offset = clamp((height - H) / 2.f, 0, INFINITY);
		engine->pixel[x + W * (y + (H - vertical_size) / 2)] =
			TextureSampling(engine, height, y + offset, inter);
		y += 1;
	}
	return (0);
}

int			RenderFloor(t_engine *engine, int x, t_item *floor,
									t_float2 origin, t_float2 direct)
{
	uint32_t	y;
	float		coeff;
	uint32_t	index;
	t_float2	point;

	float dx = engine->floor.w / engine->floor.texture->w;
	float dy = engine->floor.h / engine->floor.texture->h;

	y = 0;
	coeff = 1.f / cosf(engine->angle[x]);
	while (y != H / 2)
	{
		index = H / 2 - 1 - y;
		point = direct * engine->floor_ceil_point[index].x * coeff
			+ (t_float2){direct.y, -direct.x} * engine->floor_ceil_point[index].y * coeff + origin;
		float _x = vec2f_projection(point - floor->o, floor->i);
		float _y = vec2f_projection(point - floor->o, floor->j);
		if (fabs(_x) < floor->w / 2.f && fabs(_y) < floor->h / 2.f)
		{
			_x = (_x + engine->floor.w / 2.f) / dx;
			_y = (_y + engine->floor.h / 2.f) / dy;
			engine->pixel[x + engine->w * (y + H / 2)] =
				engine->floor.texture->pixel[(uint32_t)_x
					+ (uint32_t)engine->floor.texture->w * (uint32_t)_y];
		}
		y += 1;
	}
	return (0);
}

/* int			RenderFloor(t_engine *engine, int x,
				t_item *floor, t_float2 o, t_float2 d)
{
	int			y;
	float		mul;
	t_float2	point;
	t_float2	delta;
	t_float2	vec2f_projection;

	y = H / 2;
	delta = (t_float2){
		floor->w / floor->texture->w, floor->h / floor->texture->h};
	mul = 1.f / cosf(engine->angle[x]);
	while (y != H)
	{
		point = engine->floor_ceil_point[H - y - 1] * mul;
		point = d * point.x + (t_float2){d.y, -d.x} * point.y + o;
		vec2f_projection = (t_float2){vec2f_vec2f_projection(point - floor->o, floor->i),
			vec2f_vec2f_projection(point - floor->o, floor->j)};
		if (fabs(vec2f_projection.x) < floor->w / 2.f
			&& fabs(vec2f_projection.y) < floor->h / 2.f)
		{
			engine->pixel[x + engine->w * y] =
				floor->texture->pixel[(int)((
					vec2f_projection.x + floor.w / 2.f) / delta.x)
						+ floor->texture->w * (int)((
							vec2f_projection.y + floor->h / 2.f) / delta.y)];
		}
		y += 1;
	}
	return (0);
} */

int			Renderer(t_engine *engine, t_float2 origin, t_float2 direct)
{
	int			x;
	t_float2	dir;
	t_float2	point;
	uint32_t	index;

	x = -W / 2;
	while (x != W / 2)
	{
		dir = normalize(rotate(
			direct, engine->angle[x + W / 2]));
		RenderFloor(engine, x + W / 2, &engine->floor, origin, dir);
		/* point = FindNearestPoint(engine, origin, dir, &index);
		if (point.x != INFINITY && point.y != INFINITY)
			RenderFunction(engine, x + W / 2, (t_intersection){
				(t_item*)engine->item_storage.storage + index, origin, point}); */
		x += 1;
	}
	return (0);
}
