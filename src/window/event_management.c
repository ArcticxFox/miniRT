/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:50:36 by ejones            #+#    #+#             */
/*   Updated: 2026/09/07 19:22:15 by ejones           ###   ########.fr       */
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

void key_hook(int key, void* param)
{
	mlx_t* mlx = (mlx_t*)param;

	printf("key = %d\n", key);
	
	switch(key)
	{
		case 19 :
			y_rotation(mlx);
		break;
		case 41 : // ESCAPE
			mlx_loop_end(mlx->mlx);
		break;
		case 79 : // RIGHT KEY
			mlx->camera.origin = add(mlx->camera.origin, mlx->camera.right);
			printf("camera x = %f\n", mlx->camera.origin.x);
		break;
		case 80 : // LEFT KEY
			mlx->camera.origin = sub(mlx->camera.origin, mlx->camera.right);
				printf("camera x = %f\n", mlx->camera.origin.x);
			break;
		case 81 : // UP KEY
			mlx->camera.origin = sub(mlx->camera.origin, mlx->camera.up);
			printf("camera y = %f\n", mlx->camera.origin.y);
		break;
		case 82 : // DOWN KEY
			mlx->camera.origin = add(mlx->camera.origin, mlx->camera.up);
			printf("camera y = %f\n", mlx->camera.origin.y);
		break;
		default : break;
	}
	mlx->needs_redraw = 1;
}

void window_hook(int event, void* param)
{
	if(event == 0)
		mlx_loop_end(((mlx_t*)param)->mlx);
}
