/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_ptr_release.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:39:57 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 12:23:43 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

void	ft_double_ptr_release(void **ptr)
{
	void	**temp;

	if (ptr == NULL)
		return ;
	temp = ptr;
	while (*temp)
		free(*temp++);
	free((void*)ptr);
}
