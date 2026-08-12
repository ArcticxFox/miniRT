/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:50:36 by ejones            #+#    #+#             */
/*   Updated: 2026/08/12 19:43:37 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void key_hook(int key, void* param)
{
	mlx_t* mlx = (mlx_t*)param;
	printf("key = %d\n", key);
	switch(key)
	{
		case 41 : // ESCAPE
			mlx_loop_end(mlx->mlx);
		break;
		case 79 : // RIGHT KEY
			mlx->camera.origin.x += 1;
			printf("camera x = %f\n", mlx->camera.origin.x);
		break;
		case 80 : // LEFT KEY
			mlx->camera.origin.x -= 1;
			printf("camera x = %f\n", mlx->camera.origin.x);
		break;
		case 81 : // UP KEY
			mlx->camera.origin.y -= 1;
			printf("camera y = %f\n", mlx->camera.origin.y);
		break;
		case 82 : // DOWN KEY
			mlx->camera.origin.y += 1;
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
