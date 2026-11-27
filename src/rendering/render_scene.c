/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 16:40:43 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/27 16:44:42 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	render_moving_scene(t_mlx *mlx, t_camera *camera)
{
	int			x;
	int			y;
	t_ray		ray;
	mlx_color	tab_col[16];

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			ray = camera_ray(mlx, camera, x + 2, y + 2);
			fill_tab(mlx, &ray, tab_col, 16);
			mlx_set_image_region(mlx->mlx, mlx->img, x, y, 4, 4, tab_col);
			x = x + 4;
		}
		y += 4;
	}
}

void	render_scene(t_mlx *mlx)
{
	int				x;
	int				y;
	mlx_color		color;

	y = mlx->render.y;
	while (y < mlx->render.y + 8)
	{
		x = mlx->render.x;
		while (x < mlx->render.x + 8)
		{
			color = ssaa(mlx, x, y);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, color);
			++x;
		}
		++y;
	}
	mlx->render.x += 8;
	if (mlx->render.x >= mlx->info.width)
	{
		mlx->render.x = 0;
		mlx->render.y += 8;
	}
	if (mlx->render.y >= mlx->info.height)
		mlx->render.y = 0;
}
