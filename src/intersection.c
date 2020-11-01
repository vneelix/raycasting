/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:29:26 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/30 15:04:53 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_double2		line_line_intersect(t_double2 a, t_double2 b,
										t_double2 c, t_double2 d)
{
	double		determinant;
	t_double4	coeff_matrix;
	t_double2	local_matrix;

	coeff_matrix = (t_double4){
		b.y - a.y, a.x - b.x,
		d.y - c.y, c.x - d.x
	};
	local_matrix = (t_double2){
		coeff_matrix[0] * a.x + coeff_matrix[1] * a.y,
		coeff_matrix[2] * c.x + coeff_matrix[3] * c.y
	};
	determinant = 1. / (coeff_matrix[0] * coeff_matrix[3]
							- coeff_matrix[1] * coeff_matrix[2]);
	if (determinant != 0.)
	{
		return ((t_double2){
			(coeff_matrix[3] * local_matrix[0]
				- coeff_matrix[1] * local_matrix[1]) * determinant,
			(coeff_matrix[0] * local_matrix[1]
				- coeff_matrix[2] * local_matrix[0]) * determinant});
	}
	else
		return ((t_double2){INFINITY, INFINITY});
}

double			prj(t_double2 a, t_double2 b)
{
	if (a.x != 0.)
		return (b.x / a.x);
	else
		return (b.y / a.y);
}

t_double2		vec_segment_intersect(
	t_double2 o, t_double2 d, t_double2 p0, t_double2 p1)
{
	double		a;
	t_double2	p;

	p = line_line_intersect(o, o + d, p0, p1);
	if (p.x == INFINITY || p.y == INFINITY)
		return ((t_double2){INFINITY, INFINITY});
	if (prj(d, p - o) >= 0.)
	{
		a = prj(p1 - p0, p - p0);
		if (a >= 0. && a <= 1.)
			return (p);
	}
	return ((t_double2){INFINITY, INFINITY});
}

t_double2		find_nearest_point(t_engine *engine,
					t_double2 o, t_double2 d, uint32_t *index)
{
	uint32_t	i;
	t_double2	p;
	t_double2	min;

	i = 0;
	min = (t_double2){INFINITY, INFINITY};
	while (i != engine->item_storage.size)
	{
		p = vec_segment_intersect(o, d,
			((t_item*)engine->item_storage.data)[i].p0,
				((t_item*)engine->item_storage.data)[i].p1);
		if (dot(p - o, p - o) < dot(min - o, min - o))
		{
			if (index != NULL)
				*index = i;
			min = p;
		}
		i += 1;
	}
	return (min);
}
