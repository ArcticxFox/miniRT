/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 16:32:45 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 15:48:09 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	update_selection(t_mlx *mlx, t_obj_type type, int index)
{
	mlx->selected.type = type;
	mlx->selected.index = index;
	mlx->selected.valid = true;
	mlx->needs_redraw = 1;
}

bool	find_objects(t_mlx *mlx)
{
	t_object	*items;
	int			i;
	t_hit		hit;
	t_query		query;

	i = 0;
	items = mlx->scene.items.objects;
	query.iv = (t_interval){0.001, INFINITY};
	mlx->selected.valid = false;
	query.ray = camera_ray(mlx, &mlx->scene.camera,
		mlx->old_mouse_pos.x, mlx->old_mouse_pos.y);
	query.hit = &hit;
	while (i < mlx->scene.items.count)
	{
		if (hit_object(&items[i], &query))
		{
			update_selection(mlx, items[i].type, i);
			query.iv.max = query.hit->t;
		}
		++i;
	}
	return (query.iv.max < INFINITY);
}
