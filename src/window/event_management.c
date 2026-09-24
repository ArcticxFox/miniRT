/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:50:36 by ejones            #+#    #+#             */
/*   Updated: 2026/09/21 17:46:17 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	y_rotation(mlx_t *mlx)
{
	t_camera	camera;
	t_vec		new_forward;
	t_vec		new_rigt;
	double		angle;

	camera = mlx->camera;
	angle = 1.0 * M_PI / 180.0;

	new_forward.x = camera.forward.x  * cos(angle) + camera.forward.z * sin(angle);
	new_forward.y = camera.forward.y;
	new_forward.z = -camera.forward.x * sin(angle) + camera.forward.z * cos(angle);

	new_rigt.x = camera.right.x  * cos(angle) + camera.right.z * sin(angle);
	new_rigt.y = camera.right.y;
	new_rigt.z = -camera.right.x * sin(angle) + camera.right.z * cos(angle);

	mlx->camera.forward = new_forward;
	printf("forward x: %f, y: %f, z: %f\n", new_forward.x, new_forward.y, new_forward.z);
	mlx->camera.right = new_rigt;
}
void	key_pressed(int key, void* param)
{
	mlx_t* mlx = (mlx_t*)param;

	if (key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == KEY_RIGHT)
		mlx->keys.right = true;
	if (key == KEY_LEFT)
		mlx->keys.left = true;
	if (key == KEY_DOWN)
		mlx->keys.down = true;
	if (key == KEY_UP)
		mlx->keys.up = true;
	if (key == 5)
		mlx->keys.forwards = true;
	if (key == 9)
		mlx->keys.backwards = true;
	if (key != 40 && (key == KEY_RIGHT || key == KEY_LEFT
		|| key == KEY_DOWN || key == KEY_UP || key == 5 || key == 9))
		mlx->needs_redraw = 0;
}
//b == 5 f == 9
void	key_released(int key, void* param)
{
	mlx_t* mlx = (mlx_t*)param;

	printf("key == %d\n\n", key);
	if (key != 40)
		mlx->needs_redraw = 1;
	if (key == KEY_RIGHT)
		mlx->keys.right = false;
	if (key == KEY_LEFT)
		mlx->keys.left = false;
	if (key == KEY_DOWN)
		mlx->keys.down = false;
	if (key == KEY_UP)
		mlx->keys.up = false;
	if (key == 5)
		mlx->keys.forwards = false;
	if (key == 9)
		mlx->keys.backwards = false;
}

void	mouse_down(int click, void *param)
{
	mlx_t* mlx = (mlx_t*)param;
	(void)mlx;
	printf("wheel move == %d\n", click);
	if (click == 1)
	{
		mlx->keys.left_click = true;
		mlx_mouse_get_pos(mlx->mlx,
			&mlx->prev_mouse_pos.x, &mlx->prev_mouse_pos.y);
		mlx->needs_redraw = 0;
	}
	if (click == 3)
		mlx->keys.right_click = true;
}

void	mouse_up(int click, void *param)
{
	mlx_t* mlx = (mlx_t*)param;
	(void)mlx;
	printf("wheel move == %d\n", click);
	if (click == 1)
		mlx->keys.left_click = false;
	if (click == 3)
		mlx->keys.right_click = false;
	mlx->needs_redraw = 1;
}

void	window_hook(int event, void* param)
{
	if(event == 0)
		mlx_loop_end(((mlx_t*)param)->mlx);
}
