/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 16:55:14 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/27 16:57:25 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	partition(t_bvh *bvh, t_range r, t_axis axis, double mid)
{
	t_object_ref	tmp;
	int				i;
	int				j;

	i = r.start;
	j = r.end - 1;
	while (i <= j)
	{
		if (centroid(bvh, i, axis) < mid)
			++i;
		else
		{
			tmp = bvh->objects[i];
			bvh->objects[i] = bvh->objects[j];
			bvh->objects[j] = tmp;
			--j;
		}
	}
	return (i);
}

int	split_range(t_bvh *bvh, t_range r, t_aabb bounds)
{
	t_axis	axis;
	double	mid;
	int		k;

	axis = longest_axis(bounds);
	mid = 0.5 * (vec_axis(bounds.min, axis) + vec_axis(bounds.max, axis));
	k = partition(bvh, r, axis, mid);
	if (k == r.start || k == r.end)
		k = (r.start + r.end) / 2;
	return (k);
}
