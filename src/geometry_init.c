/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:30:55 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/31 13:48:03 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char	*find_textr(t_map *map, uint32_t ind)
{
	uint32_t	i;

	i = 0;
	while (i != (uint32_t)map->texture_num)
	{
		if ((uint32_t)map->textures[i].texture_index == ind)
			return (map->textures[i].texture_name);
		i += 1;
	}
	return (NULL);
}

static int	item_configure(t_item *item)
{
	item->w = length(item->p1 - item->p0);
	item->i = normalize(item->p1 - item->p0);
	item->j = (t_double2){item->i.y, -item->i.x};
	item->o = item->p0 + item->i * 0.5;
	return (0);
}

static int	textr_init(t_engine *engine, t_map *map,
								t_item *item, uint32_t i)
{
	uint32_t	index;
	char		*temp;

	item_configure(item);
	if ((temp = find_textr(map, i)) == NULL) {
		ft_putstr("Texture not found\n");
		return (-1);
	}
	if (hex_to_uint(temp, &item->color) == 0)
		return (0);
	if (ft_find_str(engine->texture_storage.title, temp, &index) == NULL) {
		printf("%s: not found\n", temp);
		return (-1);
	}
	item->texture = (t_texture*)engine->texture_storage.data + index;
	item->r_dx = 1. / (2. / item->texture->w);
	item->r_dy = 1. / (2. / item->texture->h);
	return (0);
}

static int	item_init(t_engine *engine, t_map *map)
{
	uint32_t	i;

	i = 0;
	engine->item_storage.size =
					map->wall_num;
	if ((engine->item_storage.data =
			ft_memalloc(sizeof(t_item) * engine->item_storage.size)) == NULL)
		return (-1);
	while (i != (uint32_t)engine->item_storage.size)
	{
		((t_item*)engine->item_storage.data)[i].p0 =
			(t_double2){map->walls[i].p1x, map->walls[i].p1y};
		((t_item*)engine->item_storage.data)[i].p1 =
			(t_double2){map->walls[i].p2x, map->walls[i].p2y};
		if (textr_init(engine, map,
			(t_item*)engine->item_storage.data + i,
							map->walls[i].texture_index))
			return (-1);
		i += 1;
	}
	return (0);
}

int			geometry_init(t_engine *engine, t_map *map)
{
	if (item_init(engine, map))
		return (-1);
	if (textr_init(engine, map, &engine->ceil, map->ceiling_texture)
		|| textr_init(engine, map, &engine->floor, map->floor_texture))
		return (-1);
	engine->player.delta = RAD(fmod(map->player.angle, 360.));
	engine->player.o = (t_double2){map->player.x, map->player.y};
	engine->player.d = rotate((t_double2){1, 0}, engine->player.delta);
	return (0);
}
