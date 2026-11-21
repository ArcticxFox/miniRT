/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_hit_aabb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 13:48:02 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 20:01:13 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static bool	hit_slab(double origin, double direction,
	t_interval aabb, t_interval *interval)
{
	if (direction == 0.0)
	{
		if (origin < aabb.min || origin > aabb.max)
			return (false);
		interval->max = INFINITY;
		interval->min = -INFINITY;
		return (true);
	}
	interval->max = (aabb.max - origin) / direction;
	interval->min = (aabb.min - origin) / direction;
	if (interval->min > interval->max)
		swap_double(&interval->min, &interval->max);
	return (true);
}

static bool	hit_axis(double o, double d, t_interval box, t_interval *iv)
{
	t_interval	slab;

	if (!hit_slab(o, d, box, &slab))
		return (false);
	iv->min = fmin(iv->min, slab.min);
	iv->max = fmin(iv->max, slab.max);
	return (iv->min <= iv->max);
}

bool	hit_aabb(t_ray ray, t_aabb box, t_interval interval)
{
	t_interval	b;

	b.min = box.min.x;
	b.max = box.max.x;
	if (!hit_axis(ray.origin.x, ray.dir.x, b, &interval))
		return (false);
	b.min = box.min.y;
	b.max = box.max.y;
	if (!hit_axis(ray.origin.y, ray.dir.y, b, &interval))
		return (false);
	b.min = box.min.z;
	b.max = box.max.z;
	if (!hit_axis(ray.origin.z, ray.dir.z, b, &interval))
		return (false);
	return (true);
}
