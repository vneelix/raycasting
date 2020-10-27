/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 13:32:48 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/24 16:36:04 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		dot(t_double2 p0, t_double2 p1)
{
	return (p0.x * p1.x + p0.y * p1.y);
}

double		length(t_double2 p)
{
	return (sqrt(p.x * p.x + p.y * p.y));
}

t_double2	normalize(t_double2 p)
{
	return (p / length(p));
}

t_double2	rotate(t_double2 p, double a)
{
	return (t_double2){
		p.x * cos(a) - p.y * sin(a),
		p.x * sin(a) + p.y * cos(a)};
}

t_double2	decomp(t_double2 o, t_double2 i,
						t_double2 j, t_double2 p)
{
	return (o + p.x * i + p.y * j);
}
