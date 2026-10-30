/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:06:55 by ejones            #+#    #+#             */
/*   Updated: 2026/10/30 16:15:14 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rotate(t_mlx *mlx, double yaw, double pitch)
{
	t_quat	q_yaw;
	t_quat	q_pitch;
	t_cy	*cy;

	cy = &mlx->scene.cylinder[mlx->selected.index];
	q_yaw = quat_from_axis_angle(mlx->scene.camera.up, yaw);
	q_pitch = quat_from_axis_angle(mlx->scene.camera.right, pitch);
	cy->axis_dir = quat_rotate_vec(q_yaw,
		cy->axis_dir);
	cy->axis_dir = quat_rotate_vec(q_pitch,
		cy->axis_dir);
	cy->axis_dir =
		normalize(cy->axis_dir);
}

void	rotation_v2(t_mlx *mlx, int mouse_x, int mouse_y)
{
	double	yaw;
	double	pitch;
	double	sensitivity;

	sensitivity = 0.005;
	yaw = (mouse_x - mlx->prev_mouse_pos.x) * sensitivity;
	pitch = (mouse_y - mlx->prev_mouse_pos.y) * sensitivity;
	if (mlx->keys.left_click)
	{
		if (mlx->selected.type == OBJ_CYLINDER)
			rotate(mlx, yaw, pitch);
		mlx->prev_mouse_pos.x = mouse_x;
		mlx->prev_mouse_pos.y = mouse_y;
	}
}

void	rotate_objects(t_mlx *mlx)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(mlx->mlx, &mouse_x, &mouse_y);
	rotation_v2(mlx, mouse_x, mouse_y);
}
