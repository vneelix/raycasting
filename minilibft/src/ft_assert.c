/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 16:56:55 by nsena             #+#    #+#             */
/*   Updated: 2020/10/30 12:23:32 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

void	ft_assert(int condition, char *message_on_fail)
{
	if (!condition)
	{
		if (message_on_fail != NULL)
		{
			ft_putstr(message_on_fail);
			ft_putstr("\n");
		}
		else
		{
			ft_putstr("Assertion failed.\n");
		}
		exit(0);
	}
}
