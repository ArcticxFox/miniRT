/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 16:47:15 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 17:08:28 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	hit_leaf(t_bvh *bvh, t_bvh_node *node, t_query *q)
{
	bool	hit;
	int		i;

	hit = false;
	i = node->leaf.start;
	while (i < node->leaf.start + node->leaf.count)
	{
		if (!hit_object(&bvh->scene[bvh->objects->index], q->ray, q->hit, q->iv))
		{

		}
	}
	return
}
