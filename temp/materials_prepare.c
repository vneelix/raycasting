/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_prepare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:08:31 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/09 13:33:13 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/* int	textures_load(t_stock *texture_stock)
{
	uint32_t	i;
	char		*path;
	SDL_Surface	*temp;

	i = 0;
	if ((texture_stock->stock = ft_memalloc(
		sizeof(t_texture) * (texture_stock->number + 1))) == NULL)
		return (-1);
	while (i != texture_stock->number)
	{
		if ((path = ft_strjoin("materials/textures/",
						texture_stock->title[i])) == NULL)
			return (-1);
		temp = IMG_Load(path);
		free((void*)path);
		if (temp != NULL)
		{
			((t_texture*)texture_stock->stock)[i].sfe =
				SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_BGRA32, 0);
			SDL_FreeSurface(temp);
		}
		if (((t_texture*)texture_stock->stock)[i++].sfe == NULL)
			return (-1);
	}
	return (0);
}

int	textures_prepare(t_engine *engine)
{
	uint32_t	i;

	if (ft_read_directory("materials/textures/",
			&engine->texture_stock.title, &engine->texture_stock.number) == -1)
		return (-1);
	if (textures_load(&engine->texture_stock) == -1)
		return (-1);
	i = 0;
	while (i != engine->texture_stock.number)
	{
		((t_texture*)engine->texture_stock.stock)[i].width =
			((t_texture*)engine->texture_stock.stock)[i].sfe->w;
		((t_texture*)engine->texture_stock.stock)[i].height =
			((t_texture*)engine->texture_stock.stock)[i].sfe->h;
		((t_texture*)engine->texture_stock.stock)[i].img =
			((t_texture*)engine->texture_stock.stock)[i].sfe->pixels;
		i += 1;
	}
	return (0);
}

int	materials_prepare(t_engine *engine)
{
	if (ft_read_directory("materials/textures/",
			&engine->texture_stock.title, &engine->texture_stock.number) == -1)
		return (-1);
	if (textures_prepare(engine) == -1)
		return (-1);
	return (0);
} */
