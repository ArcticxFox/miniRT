/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:01:03 by ejones            #+#    #+#             */
/*   Updated: 2026/10/30 16:34:53 by ejones           ###   ########.fr       */
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

void	render_mode(t_mlx *mlx, double	delta_time)
{
	if (mlx->mode == MODE_CAMERA)
		update_camera(mlx, delta_time);
	else if (mlx->mode == MODE_MOVE)
		move_object(mlx);
	else if (mlx->mode == MODE_ROTATE)
	{
		if (mlx->selected.type == (OBJ_SPHERE || OBJ_NONE) )
			return ;
		rotate_objects(mlx);
	}
	else if (mlx->mode == MODE_SCALE)
	{
		if (mlx->selected.type == OBJ_PLANE)
			return ;
		scale_object(mlx);
	}
}

void	render_loop(void *param)
{
	t_mlx	*mlx;
	double	current_time;
	double	delta_time;

	mlx = (t_mlx *)param;
	char	str[15];

	current_time = get_time();
	delta_time = current_time - mlx->last_time;
	mlx->last_time = current_time;
	if(delta_time > 0.05)
		delta_time = 0.05;
	if (!mlx->needs_redraw)
		render_mode(mlx, delta_time);
	if (!mlx->needs_redraw)
		render_moving_scene(mlx, mlx->scene.camera);
	else
		render_scene(mlx, mlx->scene.camera);
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){{0, 0, 0, 0}});
	mlx_put_image_to_window(
		mlx->mlx,
		mlx->win,
		mlx->img,
		0,
		0
		);
	mlx_set_font(mlx->mlx, "default");
	mlx_set_font_scale(mlx->mlx, "default", 12.f);
	sprintf(str, "%.4f", mlx->scene.camera.origin.x);
	mlx_string_put(mlx->mlx, mlx->win, 20, 20, (mlx_color){ .rgba = 0x0020FFFF }, "x:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 20, (mlx_color){ .rgba = 0x0020FFFF }, str);

	sprintf(str, "%.4f", mlx->scene.camera.origin.y);
	mlx_string_put(mlx->mlx, mlx->win, 20, 40, (mlx_color){ .rgba = 0x0020FFFF }, "y:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 40, (mlx_color){ .rgba = 0x0020FFFF }, str);

	sprintf(str, "%.4f", mlx->scene.camera.origin.z);
	mlx_string_put(mlx->mlx, mlx->win, 20, 60, (mlx_color){ .rgba = 0x0020FFFF }, "z:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 60, (mlx_color){ .rgba = 0x0020FFFF }, str);
}
