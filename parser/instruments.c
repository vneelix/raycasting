/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:23:12 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 21:39:30 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		numbers_in_line(const char *line, char stop_symbol)
{
	int	is_current_digit;
	int	total_numbers;

	if (line == NULL || ft_strchr(line, stop_symbol) == NULL)
		return (0);
	is_current_digit = 0;
	total_numbers = 0;
	while (*line != stop_symbol)
	{
		if (ft_isdigit(*line) && !is_current_digit)
		{
			is_current_digit = 1;
			total_numbers++;
		}
		else if (!ft_isdigit(*line))
			is_current_digit = 0;
		line++;
	}
	return (total_numbers);
}

int		fields_in_line(const char *line, const char stop_symbol,
					const char field_separator)
{
	int	total_fields;

	if (line == NULL)
		return (0);
	total_fields = 0;
	while (*line != stop_symbol)
	{
		if (*line == field_separator)
			total_fields++;
		line++;
	}
	return (total_fields);
}

int		strchr_len(const char *line, char stop_symbol)
{
	const char *symbol_in_line = ft_strchr(line, stop_symbol);

	if (line == NULL || symbol_in_line == NULL)
		return (0);
	return ((int)(symbol_in_line - line));
}
