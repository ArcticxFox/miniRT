/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 16:06:19 by ejones            #+#    #+#             */
/*   Updated: 2026/11/20 16:16:28 by ejones           ###   ########.fr       */
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

static int	split_range(t_bvh *bvh, t_range r, t_aabb bounds)
{
	t_axis	axis;
	double	mid;
	int		k;

	axis = longest_axis(bounds);
	mid = 0.5 * (vec_axis(bounds.min, axis) + vec_axis(bounds.max, axis));
	k =  partition(bvh, r, axis, mid);
	if (k == mid || k == r.end)
		k = (r.start + r.end) / 2;
	return (k);
}

static t_bvh_node	*build_node(t_bvh *bvh, t_range r)
{
	t_bvh_node	*node;
	int			mid;

	node = &bvh->node[bvh->node_count++];
	node->bounds = range_bounds(bvh, r);
	if(r.end - r.start <= LEAF_MAX)
	{
		node->is_leaf = true;
		node->leaf.start = r.start;
		node->leaf.count = r.end - r.start;
		return (node);
	}
	node->is_leaf = false;
	mid = split_range(bvh, r, node->bounds);
	node->children.left = build_node(bvh, (t_range){r.start, mid});
	node->children.right = build_node(bvh, (t_range){mid, r.end});
	return (node);
}

static void	fill_ref(t_bvh *bvh, t_objects *objs)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < objs->count)
	{
		if (objs->objects[i].type != OBJ_PLANE)
		{
			bvh->objects[n].index = i;
			bvh->objects[n].type = objs->objects[i].type;
			++n;
		}
		++i;
	}
}

int	init_bvh(t_bvh *bvh, t_objects *objs)
{
	bvh->scene = objs->objects;
	bvh->object_count = objs->count - objs->pl_count;
	bvh->node_count = 0;
	bvh->root = NULL;
	if (bvh->object_count == 0)
		return (0);
	bvh->node_capacity = 2 * bvh->object_count - 1;
	bvh->objects = ft_calloc(bvh->object_count, sizeof(t_object_ref));
	bvh->node = ft_calloc(bvh->node_capacity, sizeof(t_bvh_node));
	if (!bvh->objects || !bvh->node)
	{
		free_bvh(bvh);
		return (MRT_MALLOC);
	}
	fill_ref(bvh, objs);
	bvh->root = build_node(bvh, (t_range) {0, bvh->object_count});
	return (0);
}
