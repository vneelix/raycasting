/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checkers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:56:15 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 14:56:16 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPARSER_LINE_CHECKERS_H
# define MAPPARSER_LINE_CHECKERS_H

int	is_line_correct_type(const char *line, char stop_symbol,
						const char *lexeme, int must_fields_in_line);
int	is_line_wall(const char *line, char stop_symbol);
int	is_line_player(const char *line, char stop_symbol);
int	is_line_wnum(const char *line, char stop_symbol);
int	is_line_texture(const char *line, char stop_symbol);
int	is_line_texture_number(const char *line, char stop_symbol);
int	is_line_floor_texture(const char *line, char stop_symbol);
int	is_line_ceiling_texture(const char *line, char stop_symbol);

#endif
