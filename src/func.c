/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:06:06 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/08 17:07:37 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float	clamp(float val, float lhs, float rhs)
{
	if (val < lhs)
		return (lhs);
	else if (val >= lhs && val <= rhs)
		return (val);
	else
		return (rhs);
}
