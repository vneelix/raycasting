/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:59:44 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/31 13:53:57 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				collision(t_engine *engine, t_double2 o, t_double2 d)
{
	uint32_t		i;
	t_double2		proj;
	const double	dist = 0.5;

	i = 0;
	while (i != engine->item_storage.size)
	{
		proj = point_segment_projection(o,
			((t_item*)engine->item_storage.data)[i].p0,
				((t_item*)engine->item_storage.data)[i].p1);
		if (proj.x != INFINITY
				&& proj.y != INFINITY
					&& dot(d, normalize(proj - o)) >= 0.)
		{
			if (length(proj - o) < dist)
				return (1);
		}
		i += 1;
	}
	if (length(find_nearest_point(engine, o, d, NULL) - o) < dist)
		return (1);
	return (0);
}

t_double2		point_line_projection(t_double2 p,
										t_double2 a, t_double2 b)
{
	double		determinant;
	t_double4	coeff_matrix;
	t_double2	local_matrix;

	coeff_matrix = (t_double4){
		b.y - a.y, a.x - b.x,
		a.x - b.x, a.y - b.y
	};
	local_matrix = (t_double2){
		coeff_matrix[0] * a.x + coeff_matrix[1] * a.y,
		p.x * a.x + p.y * a.y - p.x * b.x - p.y * b.y
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

t_double2		point_segment_projection(
					t_double2 p, t_double2 a, t_double2 b)
{
	double		val;
	t_double2	proj;

	proj = point_line_projection(p, a, b);
	if (proj.x == INFINITY || proj.y == INFINITY)
		return ((t_double2){INFINITY, INFINITY});
	val = prj(b - a, proj - a);
	if (val >= 0. && val <= 1.)
		return (proj);
	return ((t_double2){INFINITY, INFINITY});
}
