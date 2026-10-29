/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:50:36 by ejones            #+#    #+#             */
/*   Updated: 2026/10/29 16:54:57 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool handle_mode_key(t_mlx *mlx, int key)
{
	if (key == KEY_M)
		mlx->mode = MODE_MOVE;
	else if (key == KEY_C)
	{
		mlx->mode = MODE_CAMERA;
		mlx_mouse_get_pos(mlx->mlx,
		&mlx->prev_mouse_pos.x, &mlx->prev_mouse_pos.y);
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
	if (key == 45)
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

void	save_object_start(t_mlx *mlx, t_data scene)
{
	if (mlx->selected.type == OBJ_SPHERE)
	{
		mlx->object_start = scene.sphere[mlx->selected.index].center;
		mlx->selected.r = scene.sphere[mlx->selected.index].r;
	}
	else if (mlx->selected.type == OBJ_CYLINDER)
	{
		mlx->object_start = scene.cylinder[mlx->selected.index].center;
		mlx->selected.r = scene.cylinder[mlx->selected.index].r;
		mlx->selected.h = scene.cylinder[mlx->selected.index].h;
	}
	else if (mlx->selected.type == OBJ_PLANE)
		mlx->object_start = scene.plane[mlx->selected.index].point_in_py;
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
		mlx_mouse_get_pos(mlx->mlx, &mlx->prev_mouse_pos.x,
			&mlx->prev_mouse_pos.y);
		if (find_objects(mlx))
			drag_start(mlx, mlx->prev_mouse_pos.x, mlx->prev_mouse_pos.y);
		if (mlx->mode == MODE_SCALE)
			mlx->value_start = get_distance(mlx, mlx->prev_mouse_pos.x, mlx->prev_mouse_pos.y);
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
	if (event == 0)
		mlx_loop_end(((t_mlx *)param)->mlx);
}
