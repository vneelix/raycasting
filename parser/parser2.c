/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:36:56 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 21:41:06 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			p_parse_player_attribs(t_player *player, char *line)
{
	line = ft_strchr(line, ' ') + 1;
	player->x = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	player->y = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	player->z = ft_atoi(line);
	line = ft_strchr(line, ' ') + 1;
	player->angle = ft_atoi(line);
}

char			*find_and_parse_player_attribs(t_player *player,
													char *map_text)
{
	while (1)
	{
		if (*map_text == '\0')
			return (NULL);
		if (is_line_player(map_text, '\n'))
		{
			p_parse_player_attribs(player, map_text);
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

char			*find_and_parse_texture_num(int *texture_num,
												char *map_text)
{
	while (1)
	{
		if (*map_text == '\0')
			return (NULL);
		if (is_line_texture_number(map_text, '\n'))
		{
			map_text = ft_strchr(map_text, ' ') + 1;
			*texture_num = ft_atoi(map_text);
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

char			*find_and_parse_wall_num(int *wall_num, char *map_text)
{
	while (1)
	{
		if (*map_text == '\0')
			return (NULL);
		if (is_line_wnum(map_text, '\n'))
		{
			map_text = ft_strchr(map_text, ' ') + 1;
			*wall_num = ft_atoi(map_text);
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

char			*find_and_parse_ceiling_texture(int *ceiling_texture,
													char *map_text)
{
	while (1)
	{
		if (*map_text == '\0')
			return (NULL);
		if (is_line_ceiling_texture(map_text, '\n'))
		{
			map_text = ft_strchr(map_text, ' ') + 1;
			*ceiling_texture = ft_atoi(map_text);
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
