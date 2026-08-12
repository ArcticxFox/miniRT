/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:44:46 by ejones            #+#    #+#             */
/*   Updated: 2026/08/09 16:59:28 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	init_window(mlx_t *mlx, mlx_window_create_info *info)
{
	mlx->mlx = mlx_init();

	*info = (mlx_window_create_info){0};
	info->title = "My Ray Tracer";
	info->width = 800;
	info->height = 600;
	info->is_resizable = true;

	mlx->win = mlx_new_window(mlx->mlx, info);

	mlx->img = mlx_new_image(mlx->mlx, 800, 600);

	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, key_hook, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window_hook, mlx);
}
