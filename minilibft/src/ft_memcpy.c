/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:01:04 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 12:24:02 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	uint8_t		*uint8[2];
	uint64_t	*uint64[2];

	if (!dest || !src)
		return (NULL);
	uint64[0] = (uint64_t*)src;
	uint64[1] = (uint64_t*)dest;
	while (n / 8)
	{
		*(uint64[1]++) = *(uint64[0]++);
		n -= 8;
	}
	uint8[0] = (uint8_t*)uint64[0];
	uint8[1] = (uint8_t*)uint64[1];
	while (n)
	{
		*(uint8[1]++) = *(uint8[0]++);
		n -= 1;
	}
	return (dest);
}
