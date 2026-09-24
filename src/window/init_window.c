/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:44:46 by ejones            #+#    #+#             */
/*   Updated: 2026/09/21 17:36:32 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	init_mlx_events(mlx_t *mlx)
{
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEDOWN, mouse_down, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEUP, mouse_up, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_pressed, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYUP, key_released, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, mlx);
}

void	init_keys(t_keys *keys)
{
	keys->up = false;
	keys->down = false;
	keys->left = false;
	keys->right = false;
	keys->backwards = false;
	keys->forwards = false;
	keys->left_click = false;
	keys->right_click = false;
}

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
	mlx->img = mlx_new_image(mlx->mlx, info.width, info.height);
	mlx->last_time = get_time();
	init_keys(&mlx->keys);
	mlx->prev_mouse_pos.x = 0;
	mlx->prev_mouse_pos.y = 0;
	init_mlx_events(mlx);
}
