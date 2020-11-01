/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruments.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:22:00 by nsena             #+#    #+#             */
/*   Updated: 2020/10/27 15:22:02 by nsena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPARSER_INSTRUMENTS_H
# define MAPPARSER_INSTRUMENTS_H

int	numbers_in_line(const char *line, char stop_symbol);
int	fields_in_line(const char *line, char stop_symbol, char field_separator);
int	strchr_len(const char *line, char stop_symbol);

#endif
