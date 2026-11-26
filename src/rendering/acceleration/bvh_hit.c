/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 16:47:15 by ejones            #+#    #+#             */
/*   Updated: 2026/11/26 15:40:24 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	hit_leaf(t_bvh *bvh, t_bvh_node *node, t_query *q)
{
	bool	hit_anything;
	int		i;
	t_hit	tmp;
	t_query	test;

	hit_anything = false;
	i = node->leaf.start;
	test = *q;
	test.hit = &tmp;
	test.iv = q->iv;
	while (i < node->leaf.start + node->leaf.count)
	{
		bvh->stats.object_tests++;
		if (hit_object(&bvh->scene[bvh->objects[i].index], &test))
		{
			*q->hit = tmp;
			q->iv.max = tmp.t;
			test.iv.max = tmp.t;
			hit_anything = true;
		}
		++i;
	}
	return (hit_anything);
}

static bool	hit_node(t_bvh *bvh, t_bvh_node *node, t_query *q)
{
	bool	hit_l;
	bool	hit_r;

	bvh->stats.node_visits++;
	bvh->stats.aabb_tests++;
	if (!hit_aabb(q->ray, node->bounds, q->iv))
		return (false);
	if (node->is_leaf)
		return (hit_leaf(bvh, node, q));
	hit_l = hit_node(bvh, node->children.left, q);
	hit_r = hit_node(bvh, node->children.right, q);
	return (hit_l || hit_r);
}

bool	hit_bvh(t_bvh *bvh, t_query *q)
{
	if (!bvh->root)
		return (false);
	return (hit_node(bvh, bvh->root, q));
}
