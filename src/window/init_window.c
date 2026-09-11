/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:44:46 by ejones            #+#    #+#             */
/*   Updated: 2026/09/11 18:43:12 by ejones           ###   ########.fr       */
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
	mlx->win = mlx_new_window(mlx->mlx, &info);

	mlx->needs_redraw = 1;

	mlx->img = mlx_new_image(mlx->mlx, info.width, info.height);
	mlx->last_time = get_time();
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_pressed, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYUP, key_released, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, mlx);
}
