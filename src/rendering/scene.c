/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:01:03 by ejones            #+#    #+#             */
/*   Updated: 2026/11/05 21:07:04 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	render_moving_scene(t_mlx *mlx, t_camera camera)
{
	int			x;
	int			y;
	t_ray		ray;
	mlx_color	tab_col[36];

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			ray = camera_ray(mlx, camera, x, y);
			fill_tab(mlx, &ray, tab_col, 36);
			mlx_set_image_region(mlx->mlx, mlx->img, x, y, 6, 6, tab_col);
			x = x + 6;
		}
		y += 6;
	}
}

int	next_tile(t_mlx *mlx, int	*tile_x, int *tile_y)
{
	int	cols;
	int	rows;

	cols = (mlx->info.width + 15) / 16;
	rows = (mlx->info.height + 15) / 16;
	while (mlx->render.diagonal <= cols + rows - 2)
	{
		*tile_x = mlx->render.diagonal - mlx->render.diagonal_y;
		*tile_y = mlx->render.diagonal_y;
		mlx->render.diagonal_y++;
		if (mlx->render.diagonal_y > mlx->render.diagonal
			|| mlx->render.diagonal_y >= rows)
		{
			mlx->render.diagonal++;
			mlx->render.diagonal_y = 0;
		}
		if (*tile_x >= 0 && *tile_x < cols && *tile_y >= 0 && *tile_y < rows)
			return (true);
	}
	return (false);
}

void	render_scene(t_mlx *mlx, t_camera camera)
{
	int			x;
	int			y;
	int			end_x;
	int			end_y;
	mlx_color	color;

	(void)camera;
	if (!next_tile(mlx, &x, &y))
		return ;
	x *= 16;
	y *= 16;
	end_x = x + 16;
	end_y = y + 16;
	if (end_y > mlx->info.height)
		end_y = mlx->info.height;
	if (end_x > mlx->info.width)
		end_x = mlx->info.width;
	while (y < end_y)
	{
		x = (mlx->render.diagonal - 1) * 0;
		while (x < end_x)
		{
			color = ssaa(mlx, x, y);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, color);
			++x;
		}
		++y;
	}
	mlx->render.x += 16;
	if (mlx->render.x > mlx->info.width)
	{
		mlx->render.x = 0;
		mlx->render.y += 16;
	}
	if (mlx->render.y > mlx->info.height)
		mlx->render.y = 0;
}

// void	render_scene(t_mlx *mlx, t_camera camera)
// {
// 	int			x;
// 	int			y;
// 	int			end_x;
// 	int			end_y;
// 	mlx_color	color;

// 	(void)camera;
// 	if (mlx->render.y > mlx->info.height)
// 		return ;
// 	end_x = mlx->render.x + 32;
// 	end_y = mlx->render.y + 32;
// 	if (end_y > mlx->info.height)
// 		end_y = mlx->info.height;
// 	if (end_x > mlx->info.width)
// 		end_x = mlx->info.width;
// 	y = mlx->render.y;
// 	while (y < end_y)
// 	{
// 		x = mlx->render.x;
// 		while (x < end_x)
// 		{
// 			color = ssaa(mlx, x, y);
// 			mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, color);
// 			++x;
// 		}
// 		++y;
// 	}
// 	mlx->render.x += 32;
// 	if (mlx->render.x > mlx->info.width)
// 	{
// 		mlx->render.x = 0;
// 		mlx->render.y += 32;
// 	}
// 	if (mlx->render.y > mlx->info.height)
// 		mlx->render.y = 0;
// }

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
	{
		render_mode(mlx, delta_time);
		render_moving_scene(mlx, mlx->scene.camera);
		mlx->render.x = 0;
		mlx->render.y = 0;
	}
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
