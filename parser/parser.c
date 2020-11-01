/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 19:47:23 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 21:51:33 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void			p_parse(char **map_text_ptr, t_map *map)
{
	*map_text_ptr = find_and_parse_texture_num(&map->texture_num,
											*map_text_ptr);
	ft_assert(map->texture_num >= 1, "Incorrect texture number.");
	ft_assert(map_text_ptr != NULL, "Unexpected EOF.");
	ft_assert((map->textures = malloc(sizeof(t_prsd_txr) *
		map->texture_num)) != NULL, "Cannot allocate textures.");
	*map_text_ptr = find_and_parse_textures(map, *map_text_ptr);
}

t_map				parse(char *map_text)
{
	t_map	map;
	char	*map_text_ptr;

	map_text_ptr = map_text;
	map_text_ptr = find_and_parse_player_attribs(&map.player, map_text_ptr);
	ft_assert(map_text_ptr != NULL, "Unexpected EOF.");
	p_parse(&map_text_ptr, &map);
	map_text_ptr = find_and_parse_floor_texture(&map.floor_texture,
											map_text_ptr);
	ft_assert(map_text_ptr != NULL, "Unexpected EOF.");
	map_text_ptr = find_and_parse_ceiling_texture(&map.ceiling_texture,
											map_text_ptr);
	ft_assert(map_text_ptr != NULL, "Unexpected EOF.");
	map_text_ptr = find_and_parse_wall_num(&map.wall_num, map_text_ptr);
	ft_assert(map.wall_num > 0, "Incorrect wall number.");
	ft_assert(map_text_ptr != NULL, "Unexpected EOF.");
	ft_assert((map.walls = malloc(sizeof(t_wall) * map.wall_num))
	!= NULL, "Cannot allocate walls.");
	map_text_ptr = find_and_parse_walls(&map, map_text_ptr);
	return (map);
}

t_map				*parser(char *path)
{
	t_map	*map;
	char	*map_text;

	ft_assert((map_text = ft_getfile(
		path, 0)) != NULL, "Cannot open text map");
	ft_assert((map = (t_map*)ft_memalloc(
		sizeof(t_map))) != NULL, "Cannot allocate map.");
	*map = parse((char*)map_text);
	free(map_text);
	return (map);
}
