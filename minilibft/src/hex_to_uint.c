/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:49:19 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 12:24:35 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

int	hex_to_uint(char *str, uint32_t *value)
{
	uint32_t	temp;
	uint32_t	color;

	color = 0;
	temp = ft_strlen(str);
	if ((!(temp >= 2 && temp <= 10)) || !(str[0] == '0' && str[1] == 'x'))
		return (-1);
	temp = ((temp - 2) * 4) - 4;
	str += 2;
	while (*str != 0)
	{
		if (*str >= '0' && *str <= '9')
			color |= (*str - 48) << temp;
		else if (*str >= 'a' && *str <= 'f')
			color |= (*str - 87) << temp;
		else if (*str >= 'A' && *str <= 'F')
			color |= (*str - 55) << temp;
		else
			return (-1);
		temp -= 4;
		str += 1;
	}
	if (value != NULL)
		*value = color;
	return (0);
}
