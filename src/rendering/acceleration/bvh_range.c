/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_range.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:17:58 by ejones            #+#    #+#             */
/*   Updated: 2026/11/20 14:18:19 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	vec_axis(t_vec v, t_axis axis)
{
	if(axis == AXIS_X)
		return (v.x);
	else if (axis == AXIS_Y)
		return (v.y);
	return (v.z);
}

int	longest_axis(t_aabb bounds)
{
	t_vec	extent;

	extent =  sub(bounds.max, bounds.min);
	if(extent.x >= extent.y && extent.x >= extent.z)
		return (AXIS_X);
	if (extent.y >= extent.z)
		return (AXIS_Y);
	return (AXIS_Z);
}

t_aabb	ref_aabb(t_bvh *bvh, int i)
{
	return (object_aabb(&bvh->scene[bvh->objects[i].index]));
}

t_aabb	range_bounds(t_bvh *bvh, t_range r)
{
	t_aabb	box;
	int		i;

	box = ref_aabb(bvh, r.start);
	i = r.start + 1;
	while (i < r.end)
	{
		box = surrounding_box(box, ref_aabb(bvh, i));
		++i;
	}
	return (box);
}

double	centroid(t_bvh *bvh, int i, t_axis axis)
{
	t_aabb	box;
	box = ref_aabb(bvh, i);
	return (0.5 * (vec_axis(box.min, axis) + vec_axis(box.max, axis)));
}
