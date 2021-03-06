/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 20:28:28 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 12:23:54 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

void	*ft_memalloc(size_t n)
{
	void	*ret;

	if ((ret = malloc(n)) == NULL)
		return (NULL);
	ft_bzero(ret, n);
	return (ret);
}
