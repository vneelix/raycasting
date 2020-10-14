/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 12:08:38 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/09 17:27:22 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_float2	line_line_intersect(t_float2 a, t_float2 b,
									t_float2 c, t_float2 d)
{
	float		determinant;
	t_float4	coeff_matrix;
	t_float2	local_matrix;

	coeff_matrix = (t_float4){
		b.y - a.y, a.x - b.x,
		d.y - c.y, c.x - d.x
	};
	local_matrix = (t_float2){
		coeff_matrix[0] * a.x + coeff_matrix[1] * a.y,
		coeff_matrix[2] * c.x + coeff_matrix[3] * c.y
	};
	determinant = coeff_matrix[0] * coeff_matrix[3]
					- coeff_matrix[1] * coeff_matrix[2];
	if (determinant != 0.f)
	{
		return ((t_float2){
			(coeff_matrix[3] * local_matrix[0]
				- coeff_matrix[1] * local_matrix[1]) / determinant,
			(coeff_matrix[0] * local_matrix[1]
				- coeff_matrix[2] * local_matrix[0]) / determinant});
	}
	else
		return ((t_float2){INFINITY, INFINITY});
}

t_float2	vec2f_segment_intersect(t_float2 origin, t_float2 direct,
												t_float2 a, t_float2 b)
{
	float		temp;
	t_float2	point;

	direct = normalize(direct);
	point = line_line_intersect(origin, origin + direct, a, b);
	if (point.x == INFINITY || point.y == INFINITY)
		return ((t_float2){INFINITY, INFINITY});
	if (dot(direct, normalize(point - origin)) >= 0.f)
	{
		temp = dot(point - a, b - a) / length(b - a);
		if (temp >= 0.f && temp <= length(b - a))
			return (point);
	}
	return ((t_float2){INFINITY, INFINITY});
}
