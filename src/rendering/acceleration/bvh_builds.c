/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 16:06:19 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 16:55:03 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_bvh_node	*build_node(t_bvh *bvh, t_range r)
{
	t_bvh_node	*node;
	int			mid;

	node = &bvh->node[bvh->node_count++];
	node->bounds = range_bounds(bvh, r);
	if (r.end - r.start <= LEAF_HIGH)
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

void	free_bvh(t_bvh *bvh)
{
	free(bvh->objects);
	free(bvh->node);
	bvh->objects = NULL;
	bvh->node = NULL;
	bvh->root = NULL;
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
	bvh->root = build_node(bvh, (t_range){0, bvh->object_count});
	bvh->stats = (t_bvh_stats){0};
	return (0);
}

void	rebuild_bvh(t_bvh *bvh, t_objects *objs)
{
	if (bvh->object_count == 0)
		return ;
	bvh->node_count = 0;
	fill_ref(bvh, objs);
	bvh->root = build_node(bvh, (t_range){0, bvh->object_count});
	bvh->stats = (t_bvh_stats){0};
}
