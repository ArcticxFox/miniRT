/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:50:36 by ejones            #+#    #+#             */
/*   Updated: 2026/09/11 18:56:12 by ejones           ###   ########.fr       */
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
	mlx->needs_redraw = 0;
}

void	key_released(int key, void* param)
{
	mlx_t* mlx = (mlx_t*)param;

	if (key == KEY_RIGHT)
		mlx->keys.right = false;
	if (key == KEY_LEFT)
		mlx->keys.left = false;
	if (key == KEY_DOWN)
		mlx->keys.down = false;
	if (key == KEY_UP)
		mlx->keys.up = false;
	if (key != 40)
		mlx->needs_redraw = 1;
}


void window_hook(int event, void* param)
{
	if(event == 0)
		mlx_loop_end(((mlx_t*)param)->mlx);
}
