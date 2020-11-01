/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:41:14 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 13:56:34 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

char	*ft_strchr(const char *str, int ch)
{
	if (str == NULL)
		return (NULL);
	while (*str != ch)
	{
		if (*str == '\0' && ch != '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}
