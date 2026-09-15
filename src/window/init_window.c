/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:44:46 by ejones            #+#    #+#             */
/*   Updated: 2026/09/15 19:24:33 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	init_window(mlx_t *mlx)
{
	mlx_window_create_info	info;

	mlx->mlx = mlx_init();

	info = (mlx_window_create_info){0};
	info.title = "My Ray Tracer";
	info.width = 1920;
	info.height = 1080;
	info.is_resizable = true;

	mlx->info = info;
	mlx->needs_redraw = 1;
	mlx->win = mlx_new_window(mlx->mlx, &info);

	mlx->keys.up = false;
	mlx->keys.down = false;
	mlx->keys.left = false;
	mlx->keys.right = false;
	mlx->keys.wheel_backwards = false;
	mlx->keys.wheel_forwards = false;

	mlx->img = mlx_new_image(mlx->mlx, info.width, info.height);
	mlx->last_time = get_time();
	// mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEWHEEL, mouse_wheel, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_pressed, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYUP, key_released, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, mlx);
}
