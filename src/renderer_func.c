/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:02:44 by vneelix           #+#    #+#             */
/*   Updated: 2020/10/26 18:03:01 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		calc_height(t_engine *engine, double dist)
{
	double	segment;

	segment = tan(engine->ver_fov / 2.)
		* engine->ver_distance / (H / 2.);
	return (ceil((1. / dist) / segment + 1e-4));
}

double		illu_calc(t_double2 d, t_double2 n)
{
	double temp;

	if ((temp = dot(-d, n)) < 0.)
		return (dot(-d, -n));
	return (temp);
}
