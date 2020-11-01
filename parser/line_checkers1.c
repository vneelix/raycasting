/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checkers1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:39:59 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 21:39:19 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_line_wnum(const char *line, char stop_symbol)
{
	const int	must_fields_in_line = 1;
	const int	must_numbers_in_line = 1;
	const char	*lexeme = "wnum";
	int			is_correct_type;
	int			is_correct_numbers_count;

	is_correct_type = is_line_correct_type(line, stop_symbol, lexeme
			, must_fields_in_line);
	is_correct_numbers_count = numbers_in_line(line, stop_symbol) ==
							must_numbers_in_line;
	return (is_correct_type && is_correct_numbers_count);
}

int	is_line_texture(const char *line, char stop_symbol)
{
	const int	must_fields_in_line = 2;
	const int	must_numbers_in_line = 1;
	const char	*lexeme = "t";
	int			is_correct_type;
	int			is_correct_numbers_count;

	is_correct_type = is_line_correct_type(line, stop_symbol, lexeme
			, must_fields_in_line);
	is_correct_numbers_count = numbers_in_line(line, stop_symbol) >=
				must_fields_in_line ? must_numbers_in_line :
				numbers_in_line(line, stop_symbol) == must_numbers_in_line;
	return (is_correct_type && is_correct_numbers_count);
}

int	is_line_texture_number(const char *line, char stop_symbol)
{
	const int	must_fields_in_line = 1;
	const int	must_numbers_in_line = 1;
	const char	*lexeme = "tnum";
	int			is_correct_type;
	int			is_correct_numbers_count;

	is_correct_numbers_count = numbers_in_line(line, stop_symbol) ==
							must_numbers_in_line;
	is_correct_type = is_line_correct_type(line, stop_symbol, lexeme
			, must_fields_in_line);
	return (is_correct_type && is_correct_numbers_count);
}

int	is_line_floor_texture(const char *line, char stop_symbol)
{
	const int	must_fields_in_line = 1;
	const int	must_numbers_in_line = 1;
	const char	*lexeme = "tflr";
	int			is_correct_type;
	int			is_correct_numbers_count;

	is_correct_type = is_line_correct_type(line, stop_symbol, lexeme,
										must_fields_in_line);
	is_correct_numbers_count = numbers_in_line(line, stop_symbol) ==
							must_numbers_in_line;
	return (is_correct_type && is_correct_numbers_count);
}

int	is_line_ceiling_texture(const char *line, char stop_symbol)
{
	const int	must_fields_in_line = 1;
	const int	must_numbers_in_line = 1;
	const char	*lexeme = "tcel";
	int			is_correct_type;
	int			is_correct_numbers_count;

	is_correct_type = is_line_correct_type(line, stop_symbol, lexeme
			, must_fields_in_line);
	is_correct_numbers_count = numbers_in_line(line, stop_symbol) ==
							must_numbers_in_line;
	return (is_correct_type && is_correct_numbers_count);
}
