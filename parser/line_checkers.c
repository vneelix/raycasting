/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:56:20 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 21:39:10 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_line_correct_type(const char *line, const char stop_symbol,
						const char *lexeme, const int must_fields_in_line)
{
	const int	line_len = strchr_len(line, stop_symbol);
	const int	must_line_type_len = ft_strlen(lexeme);

	if (line_len < must_line_type_len)
		return (0);
	if (fields_in_line(line, stop_symbol, ' ') !=
						must_fields_in_line)
		return (0);
	if (ft_strncmp(line, lexeme, must_line_type_len) != 0)
		return (0);
	return (1);
}

int	is_line_wall(const char *line, char stop_symbol)
{
	const int	must_fields_in_line = 5;
	const int	must_numbers_in_line = 5;
	const char	*lexeme = "w";
	int			is_correct_type;
	int			is_correct_numbers_count;

	is_correct_type = is_line_correct_type(line, stop_symbol, lexeme
			, must_fields_in_line);
	is_correct_numbers_count = numbers_in_line(line, stop_symbol) ==
							must_numbers_in_line;
	return (is_correct_type && is_correct_numbers_count);
}

int	is_line_player(const char *line, char stop_symbol)
{
	const int	must_fields_in_line = 4;
	const int	must_numbers_in_line = 4;
	const char	*lexeme = "p";
	int			is_correct_type;
	int			is_correct_numbers_count;

	is_correct_type = is_line_correct_type(line, stop_symbol, lexeme
			, must_fields_in_line);
	is_correct_numbers_count = numbers_in_line(line, stop_symbol) ==
							must_numbers_in_line;
	return (is_correct_type && is_correct_numbers_count);
}
