/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:50:36 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 16:51:12 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	save_object_start(t_mlx *mlx, t_data scene)
{
	t_object	*object;

	object = scene.items.objects;
	if (mlx->selected.type == OBJ_SPHERE)
	{
		mlx->object_start = object[mlx->selected.index].data.sphere.center;
		mlx->selected.r = object[mlx->selected.index].data.sphere.r;
	}
	else if (mlx->selected.type == OBJ_CYLINDER)
	{
		mlx->object_start = object[mlx->selected.index].data.cylinder.center;
		mlx->selected.r = object[mlx->selected.index].data.cylinder.r;
		mlx->selected.h = object[mlx->selected.index].data.cylinder.h;
		mlx->object_dir = &object[mlx->selected.index].data.cylinder.axis_dir;
	}
	else if (mlx->selected.type == OBJ_PLANE)
	{
		mlx->object_start = object[mlx->selected.index].data.plane.point_in_py;
		mlx->object_dir = &object[mlx->selected.index].data.plane.direction;
	}
}

void	drag_start(t_mlx *mlx, int x, int y)
{
	mlx->drag_start.x = x;
	mlx->drag_start.y = y;
	save_object_start(mlx, mlx->scene);
}

void	mouse_down(int click, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (click == 1)
	{
		mlx->keys.left_click = true;
		mlx_mouse_get_pos(mlx->mlx, &mlx->old_mouse_pos.x,
			&mlx->old_mouse_pos.y);
		if (find_objects(mlx))
			drag_start(mlx, mlx->old_mouse_pos.x, mlx->old_mouse_pos.y);
		if (mlx->mode == MODE_SCALE)
			mlx->value_start = get_distance(mlx,
					mlx->old_mouse_pos.x, mlx->old_mouse_pos.y);
		mlx->needs_redraw = 0;
	}
}

void	mouse_up(int click, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	printf("MOUSE CLICK == %d\n", click);
	if (click == 1)
	{
		mlx->keys.left_click = false;
		mlx->selected.type = OBJ_NONE;
	}
	mlx->needs_redraw = 1;
}

void	window_hook(int event, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (event == 0)
		mlx_loop_end(((t_mlx *)param)->mlx);
}
