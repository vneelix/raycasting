/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_it_nswe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:42:30 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 17:24:45 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	remove_it_nswe_init(t_engine *engine)
{
	if (surface_load(&engine->north.sfe,
		"remove_it/north.png", SDL_PIXELFORMAT_BGRA32)
			|| surface_load(&engine->south.sfe,
				"remove_it/south.png", SDL_PIXELFORMAT_BGRA32)
				|| surface_load(&engine->west.sfe,
					"remove_it/west.png", SDL_PIXELFORMAT_BGRA32)
						|| surface_load(&engine->east.sfe,
							"remove_it/east.png", SDL_PIXELFORMAT_BGRA32))
		return (-1);
	engine->north.w = engine->north.sfe->w;
	engine->north.h = engine->north.sfe->h;
	engine->north.pixel = engine->north.sfe->pixels;
	engine->south.w = engine->south.sfe->w;
	engine->south.h = engine->south.sfe->h;
	engine->south.pixel = engine->south.sfe->pixels;
	engine->west.w = engine->west.sfe->w;
	engine->west.h = engine->west.sfe->h;
	engine->west.pixel = engine->west.sfe->pixels;
	engine->east.w = engine->east.sfe->w;
	engine->east.h = engine->east.sfe->h;
	engine->east.pixel = engine->east.sfe->pixels;
	return (0);
}

int	remove_it_nswe(t_engine *engine, t_item *item)
{
	if (dot(item->j, (t_double2){0., 1.}) == 0.)
	{
		if (dot(item->j, (t_double2){1., 0.}) >= 0.)
			item->texture = &engine->east;
		else
			item->texture = &engine->west;
		item->r_dx = 1. / (2. / item->texture->w);
		item->r_dy = 1. / (2. / item->texture->h);
		return (0);
	}
	else if (dot(item->j, (t_double2){1., 0.}) == 0.)
	{
		if (dot(item->j, (t_double2){0., 1.}) >= 0.)
			item->texture = &engine->north;
		else
			item->texture = &engine->south;
		item->r_dx = 1. / (2. / item->texture->w);
		item->r_dy = 1. / (2. / item->texture->h);
		return (0);
	}
	return (-1);
}
