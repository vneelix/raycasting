/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:06:06 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/26 15:30:23 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		clamp(double val, double lhs, double rhs)
{
	if (val < lhs)
		return (lhs);
	else if (val >= lhs && val <= rhs)
		return (val);
	else
		return (rhs);
}

uint32_t	color_dot_f(uint32_t color, double m)
{
	return
	(uint32_t)((color & 255) * m) |
	((uint32_t)(((color & (255 << 8)) >> 8) * m) << 8) |
	((uint32_t)(((color & (255 << 16)) >> 16) * m) << 16);
}
