/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:00:27 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 12:23:52 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}
