/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:08:31 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/29 23:49:27 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			surface_load(SDL_Surface **dest, const char *path, Uint32 format)
{
	SDL_Surface *temp;

	if ((temp = IMG_Load(path)) == NULL)
		return (-1);
	*dest = SDL_ConvertSurfaceFormat(temp, format, 0);
	SDL_FreeSurface(temp);
	if (*dest == NULL)
		return (-1);
	return (0);
}

static int	texture_load(t_storage *texture_storage)
{
	uint32_t	i;
	char		*path;

	i = 0;
	if ((texture_storage->data = ft_memalloc(
		sizeof(t_texture) * (texture_storage->size))) == NULL)
		return (-1);
	while (i != texture_storage->size)
	{
		if ((path = ft_strjoin("materials/textures/",
						texture_storage->title[i])) == NULL)
			return (-1);
		if (surface_load(&((t_texture*)texture_storage->data)[i].sfe,
											path, SDL_PIXELFORMAT_BGRA32))
		{
			free(path);
			return (-1);
		}
		free(path);
		i += 1;
	}
	return (0);
}

static int	texture_init(t_engine *engine)
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

int			material_init(t_engine *engine)
{
	if (texture_init(engine) == -1)
		return (-1);
	if (engine->nswe)
		if (remove_it_nswe_init(engine))
			return (-1);
	return (0);
}
