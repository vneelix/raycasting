/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 21:26:18 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 12:24:32 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	return ((char*)ft_memcpy((void*)dest,
		(const void*)src, len < n ? len : n));
}
