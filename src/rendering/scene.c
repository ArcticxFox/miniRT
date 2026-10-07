/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:01:03 by ejones            #+#    #+#             */
/*   Updated: 2026/10/07 15:59:26 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	render_moving_scene(t_mlx *mlx, t_camera camera)
{
	int			x;
	int			y;
	t_ray		ray;
	mlx_color	tab_col[25];

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			ray = camera_ray(mlx, camera, x, y);
			fill_tab(mlx, &ray, tab_col, 25);
			mlx_set_image_region(mlx->mlx, mlx->img, x, y, 5, 5, tab_col);
			x = x + 5;
		}
		y += 5;
	}
}

void	render_scene(t_mlx *mlx, t_camera camera)
{
	int			x;
	int			y;
	t_ray		ray;
	mlx_color	color;

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			ray = camera_ray(mlx, camera, x, y);
			color = ray_color(mlx, ray);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_loop(void *param)
{
	t_mlx	*mlx;
	double	current_time;
	double	delta_time;

	mlx = (t_mlx *)param;
	current_time = get_time();
	delta_time = current_time - mlx->last_time;
	mlx->last_time = current_time;
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){{0, 0, 0, 0}});
	if (!mlx->needs_redraw)
		update_camera(mlx, delta_time);
	if (!mlx->needs_redraw)
		render_moving_scene(mlx, mlx->scene.camera);
	else
		render_scene(mlx, mlx->scene.camera);
	mlx_put_image_to_window(
		mlx->mlx,
		mlx->win,
		mlx->img,
		0,
		0
		);
}
