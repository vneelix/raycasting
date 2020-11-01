/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:37:01 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 21:41:03 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*find_and_parse_floor_texture(int *floor_texture,
													char *map_text)
{
	while (1)
	{
		if (*map_text == '\0')
			return (NULL);
		if (is_line_floor_texture(map_text, '\n'))
		{
			map_text = ft_strchr(map_text, ' ') + 1;
			*floor_texture = ft_atoi(map_text);
			map_text = ft_strchr(map_text, '\n');
			if (map_text != NULL)
				map_text++;
			break ;
		}
		map_text = ft_strchr(map_text, '\n');
		if (map_text == NULL)
			return (NULL);
		map_text++;
	}
	return (map_text);
}

t_wall		p_parse_wall_attribs(char *line)
{
	t_wall	wall;

	line = ft_strchr(line, ' ') + 1;
	wall.p1x = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	wall.p1y = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	wall.p2x = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	wall.p2y = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	wall.texture_index = ft_atoi(line);
	return (wall);
}

char		*find_and_parse_walls(t_map *map, char *map_text)
{
	int	total_walls_red;

	total_walls_red = 0;
	while (1)
	{
		if (total_walls_red == map->wall_num)
			break ;
		if (*map_text == '\0')
			ft_assert(0, "Unexpected EOF.");
		if (is_line_wall(map_text, '\n'))
		{
			map->walls[total_walls_red] = p_parse_wall_attribs(map_text);
			total_walls_red++;
		}
		map_text = ft_strchr(map_text, '\n');
		if (map_text == NULL)
			ft_assert(0, "Unexpected EOF.");
		map_text++;
	}
	return (map_text);
}

t_prsd_txr	p_parse_texture_attribs(char *line)
{
	t_prsd_txr	texture;
	const char	*line_end = ft_strchr(line, '\n');
	int			str_part_len;

	line = ft_strchr(line, ' ') + 1;
	ft_assert(ft_isdigit(*line), "Texture argument seq error.");
	texture.texture_index = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	str_part_len = (int)(line_end - line);
	texture.texture_name = malloc(sizeof(char) * (str_part_len + 1));
	ft_strncpy(texture.texture_name, line, str_part_len);
	texture.texture_name[str_part_len] = '\0';
	return (texture);
}

char		*find_and_parse_textures(t_map *map, char *map_text)
{
	int	total_textures_red;
	int	was_texture_block_found;

	total_textures_red = 0;
	was_texture_block_found = 0;
	while (1)
	{
		if (total_textures_red == map->texture_num)
			break ;
		ft_assert(*map_text != '\0', "Unexpected EOF.");
		if (is_line_texture(map_text, '\n'))
		{
			map->textures[total_textures_red] =
					p_parse_texture_attribs(map_text);
			total_textures_red++;
			was_texture_block_found = 1;
		}
		else if (was_texture_block_found)
			ft_assert(total_textures_red != map->texture_num,
					"Unexpected texture block end.");
		map_text = ft_strchr(map_text, '\n');
		ft_assert(map_text != NULL, "Unexpected EOF.");
		map_text++;
	}
	return (map_text);
}
