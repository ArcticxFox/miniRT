/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:01:03 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 16:41:24 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	edit_object(t_mlx *mlx)
{
	if (mlx->mode == MODE_MOVE)
		move_object(mlx);
	else if (mlx->mode == MODE_ROTATE)
	{
		if (mlx->selected.type == (OBJ_SPHERE || OBJ_NONE))
			return ;
		rotate_objects(mlx);
	}
	else if (mlx->mode == MODE_SCALE)
	{
		if (mlx->selected.type == OBJ_PLANE)
			return ;
		scale_object(mlx);
	}
	if (mlx->selected.type != OBJ_PLANE && mlx->selected.type != OBJ_NONE)
		rebuild_bvh(&mlx->scene.items.bvh, &mlx->scene.items);
}

void	render_mode(t_mlx *mlx, double delta_time)
{
	if (mlx->mode == MODE_CAMERA)
		update_camera(mlx, delta_time);
	else
		edit_object(mlx);
}

void	print_camera_coords(t_mlx *mlx)
{
	char	str[15];

	mlx_set_font(mlx->mlx, "default");
	mlx_set_font_scale(mlx->mlx, "default", 12.f);
	sprintf(str, "%.4f", mlx->scene.camera.origin.x);
	mlx_string_put(mlx->mlx, mlx->win, 20, 20,
		(mlx_color){.rgba = 0x0020FFFF}, "x:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 20,
		(mlx_color){.rgba = 0x0020FFFF}, str);
	sprintf(str, "%.4f", mlx->scene.camera.origin.y);
	mlx_string_put(mlx->mlx, mlx->win, 20, 40,
		(mlx_color){.rgba = 0x0020FFFF}, "y:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 40,
		(mlx_color){.rgba = 0x0020FFFF}, str);
	sprintf(str, "%.4f", mlx->scene.camera.origin.z);
	mlx_string_put(mlx->mlx, mlx->win, 20, 60,
		(mlx_color){.rgba = 0x0020FFFF}, "z:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 60,
		(mlx_color){.rgba = 0x0020FFFF}, str);
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
	if (delta_time > 0.05)
		delta_time = 0.05;
	if (!mlx->needs_redraw)
	{
		camera_init(&mlx->scene.camera, mlx->info.width, mlx->info.height);
		render_mode(mlx, delta_time);
		render_moving_scene(mlx, &mlx->scene.camera);
		mlx->render.x = 0;
		mlx->render.y = 0;
	}
	else
		render_scene(mlx);
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){{0, 0, 0, 0}});
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	print_camera_coords(mlx);
}
