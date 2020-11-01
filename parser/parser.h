/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 19:47:17 by nsena             #+#    #+#             */
/*   Updated: 2020/10/30 13:55:54 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPARSER_PARSER_H
# define MAPPARSER_PARSER_H

# include "minilibft.h"
# include "instruments.h"
# include "line_checkers.h"

typedef struct	s_player
{
	int	x;
	int	y;
	int	z;
	int	angle;
}				t_player;

typedef struct	s_wall
{
	int	p1x;
	int	p1y;
	int	p2x;
	int	p2y;
	int	texture_index;
}				t_wall;

typedef struct	s_prsd_txr
{
	int		texture_index;
	char	*texture_name;
}				t_prsd_txr;

typedef struct	s_map
{
	t_player	player;
	int			wall_num;
	t_wall		*walls;
	int			texture_num;
	t_prsd_txr	*textures;
	int			floor_texture;
	int			ceiling_texture;
}				t_map;

t_map			*parser(char *path);
t_map			parse(char *map_text);
char			*find_and_parse_floor_texture(int *floor_texture,
									char *map_text);
t_wall			p_parse_wall_attribs(char *line);
char			*find_and_parse_walls(t_map *map, char *map_text);
t_prsd_txr		p_parse_texture_attribs(char *line);
char			*find_and_parse_textures(t_map *map, char *map_text);
void			p_parse_player_attribs(t_player *player, char *line);
char			*find_and_parse_player_attribs(t_player *player,
											char *map_text);
char			*find_and_parse_texture_num(int *texture_num,
											char *map_text);
char			*find_and_parse_wall_num(int *wall_num, char *map_text);
char			*find_and_parse_ceiling_texture(int *ceiling_texture,
												char *map_text);

#endif
