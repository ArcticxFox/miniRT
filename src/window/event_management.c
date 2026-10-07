/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:50:36 by ejones            #+#    #+#             */
/*   Updated: 2026/10/07 16:08:43 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	key_pressed(int key, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *) param;
	if (key == 45 && mlx->scene.camera.fov > 0)
		mlx->scene.camera.fov -= 1;
	if (key == 46 && mlx->scene.camera.fov < 180)
		mlx->scene.camera.fov += 1;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == KEY_RIGHT)
		mlx->keys.right = true;
	if (key == KEY_LEFT)
		mlx->keys.left = true;
	if (key == KEY_DOWN)
		mlx->keys.down = true;
	if (key == KEY_UP)
		mlx->keys.up = true;
	if (key == 5)
		mlx->keys.forwards = true;
	if (key == 9)
		mlx->keys.backwards = true;
	if (key != 40 && (key == KEY_RIGHT || key == KEY_LEFT
			|| key == KEY_DOWN || key == KEY_UP || key == 5 || key == 9))
		mlx->needs_redraw = 0;
}

//b == 5 f == 9
void	key_released(int key, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	printf("key == %d\n\n", key);
	if (key != 40)
		mlx->needs_redraw = 1;
	if (key == KEY_RIGHT)
		mlx->keys.right = false;
	if (key == KEY_LEFT)
		mlx->keys.left = false;
	if (key == KEY_DOWN)
		mlx->keys.down = false;
	if (key == KEY_UP)
		mlx->keys.up = false;
	if (key == 5)
		mlx->keys.forwards = false;
	if (key == 9)
		mlx->keys.backwards = false;
}

void	mouse_down(int click, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	printf("MOUSE CLICK == %d\n", click);
	if (click == 1)
	{
		mlx->keys.left_click = true;
		mlx_mouse_get_pos(mlx->mlx,
			&mlx->prev_mouse_pos.x, &mlx->prev_mouse_pos.y);
		mlx->needs_redraw = 0;
	}
	if (click == 3)
		mlx->keys.right_click = true;

	bool		hit_anything;
	t_hit		hit_tmp;
	t_interval	range;
	t_ray ray;

	int	n = 0;
	int	type = 0;
	int	x, y;
	mlx_mouse_get_pos(mlx->mlx, &x, &y);

	ray = camera_ray(mlx, mlx->scene.camera, x, y);
	hit_anything = false;
	range.min = 0.001f;
	range.max = DBL_MAX;
	if (-1 < (n = hit_spheres(&mlx->scene, ray, &hit_tmp, range)))
	{
		hit_anything = true;
		range.max = hit_tmp.t;
		type = 1;
		mlx->scene.sphere[n].r = 4;
	}
}

void	mouse_up(int click, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	printf("MOUSE CLICK == %d\n", click);
	if (click == 1)
		mlx->keys.left_click = false;
	if (click == 3)
		mlx->keys.right_click = false;
	mlx->needs_redraw = 1;
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(((mlx_t *)param)->mlx);
}
