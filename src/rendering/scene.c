/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:01:03 by ejones            #+#    #+#             */
/*   Updated: 2026/09/15 18:04:49 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	render_moving_scene(mlx_t *mlx, t_camera camera)
{
	int			x;
	int			y;
	t_ray		ray;
	mlx_color	tab_col[16] = {0};

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			ray = camera_ray(mlx, camera, x, y);
			fill_tab(mlx, &ray, tab_col);
			mlx_set_image_region(mlx->mlx, mlx->img, x, y, 4, 4, tab_col);
			x = x + 4;
		}
		y += 4;
	}
}

void	render_scene(mlx_t *mlx, t_camera camera)
{
	int			x;
	int			y;
	double		viewport_x;
	double		viewport_y;
	t_ray		ray;
	mlx_color	color;

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			viewport_x = (2.0 * (x + 0.5) / mlx->info.width - 1.0) * mlx->info.width / mlx->info.height;
			viewport_y = 1.0 - 2.0 * (y + 0.5) / mlx->info.height;
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
	mlx_t	*mlx;
	double	current_time;
	double	delta_time;

	mlx = (mlx_t *)param;
	current_time = get_time();
	delta_time = current_time - mlx->last_time;
	mlx->last_time = current_time;
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){ {0, 0, 0, 0} });
	if (!mlx->needs_redraw)
		update_camera(mlx, delta_time);
	if (!mlx->needs_redraw)
		render_moving_scene(mlx, mlx->camera);
	else
		render_scene(mlx, mlx->camera);
	mlx_put_image_to_window(
		mlx->mlx,
		mlx->win,
		mlx->img,
		0,
		0
	);
}
