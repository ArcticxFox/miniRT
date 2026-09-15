/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:02:20 by ejones            #+#    #+#             */
/*   Updated: 2026/09/15 19:39:26 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_object(mlx_t *mlx, t_ray ray, t_hit *hit)
{
	bool	hit_anything;
	double	closest_so_far;
	t_hit	hit_tmp;

	hit_anything = false;
	closest_so_far = DBL_MAX;
	if (hit_sphere(mlx->sp, ray, &hit_tmp, 0.001f, closest_so_far))
	{
		hit_anything = true;
		closest_so_far = hit_tmp.t;
		*hit = hit_tmp;
	}
	if (hit_cylinder(mlx->cy, ray, &hit_tmp, 0.001f, closest_so_far))
	{
		hit_anything = true;
		closest_so_far = hit_tmp.t;
		*hit = hit_tmp;
	}
	if (hit_plane(mlx->pl, ray, &hit_tmp, 0.001f, closest_so_far))
	{
		hit_anything = true;
		closest_so_far = hit_tmp.t;
		*hit = hit_tmp;
	}
	return (hit_anything);
}

void	fill_tab(mlx_t *mlx, t_ray *ray, mlx_color	*tab_col)
{
	mlx_color	color;
	int	i;

	color = ray_color(mlx, *ray);
	i = 0;
	while (i < 16)
	{
		tab_col[i] = color;
		++i;
	}
}

mlx_color	ray_color(mlx_t *mlx, t_ray ray)
{
	double	a;
	t_hit	hit;
	t_vec	unit_direction;

	if (hit_object(mlx, ray, &hit))
	{
		return (hit.color);
	}
	unit_direction = normalize(ray.dir);
	a = 0.5 * (unit_direction.y + 1.0);
	return ((mlx_color){
		.r = (uint8_t)((1.0-a) * 255 + a * 127),
		.g = (uint8_t)((1.0-a) * 255 + a * 178),
		.b = (uint8_t)((1.0-a) * 255 + a * 255),
		.a = 255
	});
}

t_ray	camera_ray(mlx_t *mlx, t_camera camera, int x, int y)
{
	t_ray	ray;
	double	viewport_x;
	double	viewport_y;
	double	ratio_aspect;

	ratio_aspect = mlx->info.width / mlx->info.height;
	viewport_x = (2.0 * (x + 0.5) / mlx->info.width - 1.0) * ratio_aspect;
	viewport_y = 1.0 - 2.0 * (y + 0.5) / mlx->info.height;
	ray.origin = camera.origin;
	ray.dir = add(camera.forward, add(
		multiply_scalar(camera.right, viewport_x),
		multiply_scalar(camera.up, viewport_y)
		)
	);
	ray.dir = normalize(ray.dir);
	return (ray);
}

void	update_camera(mlx_t *mlx, double dt)
{
	double	speed;

	speed = 6.0;

	if (mlx->keys.up)
		mlx->camera.origin = sub(mlx->camera.origin,
			multiply_scalar(mlx->camera.up, speed * dt));
	if (mlx->keys.down)
		mlx->camera.origin = add(mlx->camera.origin,
			multiply_scalar(mlx->camera.up, speed * dt));
	if (mlx->keys.right)
		mlx->camera.origin = add(mlx->camera.origin,
			multiply_scalar(mlx->camera.right, speed * dt));
	if (mlx->keys.left)
		mlx->camera.origin = sub(mlx->camera.origin,
			multiply_scalar(mlx->camera.right, speed * dt));
	if (mlx->keys.wheel_forwards)
		mlx->camera.origin = sub(mlx->camera.origin,
			multiply_scalar(mlx->camera.forward, speed * dt));
	if (mlx->keys.wheel_backwards)
		mlx->camera.origin = add(mlx->camera.origin,
			multiply_scalar(mlx->camera.forward, speed * dt));
}
