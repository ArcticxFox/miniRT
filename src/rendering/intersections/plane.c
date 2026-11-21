/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:44:43 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 17:21:48 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_plane(t_pl pl, t_query *query)
{
	double	denom;
	double	t;
	t_vec	oc;

	oc = sub(pl.point_in_py, query->ray.origin);
	denom = dot(query->ray.dir, pl.direction);
	if (fabs(denom) < 1e-8)
		return (false);
	t = dot(oc, pl.direction) / denom;
	if (t <= query->iv.min || query->iv.max <= t)
		return (false);
	query->hit->t = t;
	query->hit->point = ray_at(query->ray, t);
	query->hit->normal = multiply_scalar(pl.direction, 1);
	query->hit->color = pl.rgb;
	return (true);
}
