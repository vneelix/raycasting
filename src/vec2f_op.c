/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 13:32:48 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/14 13:30:49 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float		dot(t_float2 p0, t_float2 p1)
{
	return (p0.x * p1.x + p0.y * p1.y);
}

float		length(t_float2 p)
{
	return (sqrtf(p.x * p.x + p.y * p.y));
}

t_float2	normalize(t_float2 p)
{
	return (p / length(p));
}

t_float2	rotate(t_float2 p, float a)
{
	return (t_float2){
		p.x * cosf(a) - p.y * sinf(a),
		p.x * sinf(a) + p.y * cosf(a)};
}

float		vec2f_projection(t_float2 p0, t_float2 p1)
{
	return (dot(p0, p1) / length(p1));
}
