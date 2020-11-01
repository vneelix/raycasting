/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:57:09 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 13:56:13 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

char	*ft_find_str(char **str_array, char *str, uint32_t *i)
{
	uint32_t	index;

	index = 0;
	if (str == NULL
		|| str_array == NULL)
		return (NULL);
	while (*str_array != NULL)
	{
		if ((ft_strcmp(str, *str_array) == 0)
			&& (ft_strlen(str) == ft_strlen(*str_array)))
		{
			if (i != NULL)
				*i = index;
			return (*str_array);
		}
		str_array += 1;
		index += 1;
	}
	return (NULL);
}
