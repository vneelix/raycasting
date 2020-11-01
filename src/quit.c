/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:51:54 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/27 22:11:35 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	release_texture_storage(t_storage *storage)
{
	uint32_t	i;

	i = 0;
	if (storage->title != NULL)
		ft_double_ptr_release((void**)storage->title);
	while (i != storage->size)
		SDL_FreeSurface(((t_texture*)storage->data)[i++].sfe);
	free(storage->data);
	return (0);
}

static	int	release_item_storage(t_storage *storage)
{
	uint32_t	i;

	i = 0;
	if (storage->title != NULL)
		ft_double_ptr_release((void**)storage->title);
	free(storage->data);
	return (0);
}

static int	io_shutdown(t_engine *engine)
{
	SDL_DestroyRenderer(engine->rndr);
	SDL_FreeSurface(engine->sfe);
	SDL_DestroyWindow(engine->win);
	IMG_Quit();
	SDL_Quit();
	return (0);
}

int			release_map(t_map *map)
{
	uint32_t	i;

	i = 0;
	if (map == NULL)
		return (0);
	if (map->walls != NULL)
		free(map->walls);
	if (map->textures != NULL)
	{
		while (i != (uint32_t)map->texture_num)
			free(map->textures[i++].texture_name);
		free(map->textures);
	}
	free(map);
	return (0);
}

int			quit(t_engine *engine)
{
	if (engine == NULL)
		exit(0);
	release_texture_storage(&engine->texture_storage);
	release_item_storage(&engine->item_storage);
	release_map(engine->map);
	io_shutdown(engine);
	free(engine);
	exit(0);
}
