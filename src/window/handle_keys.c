/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 16:50:22 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/27 16:51:18 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	handle_mode_key(t_mlx *mlx, int key)
{
	if (key == KEY_M)
		mlx->mode = MODE_MOVE;
	else if (key == KEY_C)
	{
		mlx->mode = MODE_CAMERA;
		mlx_mouse_get_pos(mlx->mlx,
			&mlx->old_mouse_pos.x, &mlx->old_mouse_pos.y);
	}
	else if (key == KEY_R)
		mlx->mode = MODE_ROTATE;
	else if (key == KEY_S)
		mlx->mode = MODE_SCALE;
	else
		return (false);
	mlx->needs_redraw = 1;
	printf("mode == %d\n", mlx->mode);
	return (true);
}

static void	set_movement_key(t_mlx *mlx, int key, bool pressed)
{
	if (key == KEY_RIGHT)
		mlx->keys.right = pressed;
	else if (key == KEY_LEFT)
		mlx->keys.left = pressed;
	else if (key == KEY_DOWN)
		mlx->keys.down = pressed;
	else if (key == KEY_UP)
		mlx->keys.up = pressed;
	else if (key == 5)
		mlx->keys.forwards = pressed;
	else if (key == 9)
		mlx->keys.backwards = pressed;
	else
		return ;
	if (mlx->mode == MODE_CAMERA)
		mlx->needs_redraw = !pressed;
}

static void	handle_camera_key(t_mlx *mlx, int key)
{
	if (key == 45 && mlx->scene.camera.fov > 0.001)
		mlx->scene.camera.fov *= 0.98f;
	else if (key == 46 && mlx->scene.camera.fov < 180)
		mlx->scene.camera.fov *= 1.05f;
	set_movement_key(mlx, key, true);
}

void	key_pressed(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	if (handle_mode_key(mlx, key))
		return ;
	if (mlx->mode == MODE_CAMERA)
		handle_camera_key(mlx, key);
}

void	key_released(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	printf("key == %d\n\n", key);
	set_movement_key(mlx, key, false);
}
