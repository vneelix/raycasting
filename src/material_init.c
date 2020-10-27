/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:08:31 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/26 19:12:39 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	texture_load(t_storage *texture_storage)
{
	uint32_t	i;
	char		*path;
	SDL_Surface	*temp;

	i = 0;
	if ((texture_storage->data = ft_memalloc(
		sizeof(t_texture) * (texture_storage->size))) == NULL)
		return (-1);
	while (i != texture_storage->size)
	{
		if ((path = ft_strjoin("materials/textures/",
						texture_storage->title[i])) == NULL)
			return (-1);
		temp = IMG_Load(path);
		free((void*)path);
		if (temp != NULL)
		{
			((t_texture*)texture_storage->data)[i].sfe =
				SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_BGRA32, 0);
			SDL_FreeSurface(temp);
		}
		if (((t_texture*)texture_storage->data)[i++].sfe == NULL)
			return (-1);
	}
	return (0);
}

int	texture_init(t_engine *engine)
{
	uint32_t	i;

	if (ft_read_directory("materials/textures/",
		&engine->texture_storage.title, &engine->texture_storage.size) == -1)
		return (-1);
	if (texture_load(&engine->texture_storage) == -1)
		return (-1);
	i = 0;
	while (i != engine->texture_storage.size)
	{
		((t_texture*)engine->texture_storage.data)[i].w =
			((t_texture*)engine->texture_storage.data)[i].sfe->w;
		((t_texture*)engine->texture_storage.data)[i].h =
			((t_texture*)engine->texture_storage.data)[i].sfe->h;
		((t_texture*)engine->texture_storage.data)[i].pixel =
			((t_texture*)engine->texture_storage.data)[i].sfe->pixels;
		i += 1;
	}
	return (0);
}

int	material_init(t_engine *engine)
{
	if (texture_init(engine) == -1)
		return (-1);
	return (0);
}
