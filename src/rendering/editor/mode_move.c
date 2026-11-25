/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:43:42 by ejones            #+#    #+#             */
/*   Updated: 2026/11/17 20:06:28 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	move_position(t_mlx *mlx, int mouse_x, int mouse_y)
{
	int	dx;
	int	dy;
	double	depth;
	double	world_unit_pixel;
	t_vec	offset;
	t_vec	new_pos;

	if (mlx->keys.left_click)
	{
		depth = dot(sub(mlx->object_start, mlx->scene.camera.origin),
			mlx->scene.camera.forward);
		world_unit_pixel = 2 * depth *
			tan(mlx->scene.camera.fov * 0.5 * M_PI / 180) / mlx->info.height;
			dx = mouse_x - mlx->drag_start.x;
			dy = mouse_y - mlx->drag_start.y;
		offset = add(
			multiply_scalar(mlx->scene.camera.right, dx * world_unit_pixel),
			multiply_scalar(mlx->scene.camera.up, -dy * world_unit_pixel));
		new_pos = add(mlx->object_start, offset);
		return (new_pos);
	}
	return (mlx->object_start);
}

void	move_object(t_mlx *mlx)
{
	int		mouse_x;
	int		mouse_y;
	int		i;
	t_object	*obj;

	i = mlx->selected.index;
	obj = mlx->scene.items.objects;
	mlx_mouse_get_pos(mlx->mlx, &mouse_x, &mouse_y);
	if (mlx->selected.type == OBJ_SPHERE)
		obj[i].data.sphere.center = move_position(mlx, mouse_x, mouse_y);
	if (mlx->selected.type == OBJ_CYLINDER)
		obj[i].data.cylinder.center = move_position(mlx, mouse_x, mouse_y);
	if (mlx->selected.type == OBJ_PLANE)
		obj[i].data.plane.point_in_py = move_position(mlx, mouse_x, mouse_y);
}
