/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:02:20 by ejones            #+#    #+#             */
/*   Updated: 2026/10/30 16:53:04 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_objects(t_mlx *mlx, t_ray ray, t_hit *hit, t_interval range)
{
	bool		hit_anything;
	t_hit		hit_tmp;

	hit_anything = false;
	if (hit_spheres(&mlx->scene, ray, &hit_tmp, range))
	{
		hit_anything = true;
		range.max = hit_tmp.t;
		*hit = hit_tmp;
	}
	if (hit_cylinders(&mlx->scene, ray, &hit_tmp, range))
	{
		hit_anything = true;
		range.max = hit_tmp.t;
		*hit = hit_tmp;
	}
	if (hit_planes(&mlx->scene, ray, &hit_tmp, range))
	{
		hit_anything = true;
		range.max = hit_tmp.t;
		*hit = hit_tmp;
	}
	return (hit_anything);
}

void	fill_tab(t_mlx *mlx, t_ray *ray, mlx_color	*tab_col, int size)
{
	mlx_color	color;
	int			i;

	color = ray_color(mlx, *ray);
	i = 0;
	while (i < size)
	{
		tab_col[i] = color;
		++i;
	}
}

mlx_color	ray_color(t_mlx *mlx, t_ray ray)
{
	double	a;
	t_hit	hit;
	t_vec	unit_direction;
	t_interval	range;

	range.min = 0.001f;
	range.max = DBL_MAX;
	if (hit_objects(mlx, ray, &hit, range))
	{
		t_vec	light_dir;
		double	light_distance;
		double	diffuse;
		uint8_t	ambient_r = hit.color.r * mlx->scene.ambient_light.rgb.r * mlx->scene.ambient_light.ratio / 255;
		uint8_t	ambient_g = hit.color.g * mlx->scene.ambient_light.rgb.g * mlx->scene.ambient_light.ratio / 255;
		uint8_t	ambient_b = hit.color.b * mlx->scene.ambient_light.rgb.b * mlx->scene.ambient_light.ratio / 255;

		// t_hit	tmp_hit;

		light_dir = normalize(sub(mlx->scene.light.lightpoint, hit.point));
		light_distance = vec_lenght(sub(mlx->scene.light.lightpoint, hit.point));
		diffuse = dot(hit.normal, light_dir);
		if (diffuse < 0.0)
			diffuse = 0.0;
		// else
		// 	{
		// 		range.min = 0.001f;
		// 		range.max = light_distance;
		// 		if (hit_objects(mlx, (t_ray){
		// 		.dir = light_dir,
		// 		.origin = add(hit.point, multiply_scalar(hit.normal, 0.001))},
		// 		&tmp_hit, range))
		// 			diffuse = 0.0;
		// 	}
		diffuse *= mlx->scene.light.brightness;

		double red = ambient_r + hit.color.r * diffuse;
		double green = ambient_g + hit.color.g * diffuse;
		double blue = ambient_b + hit.color.b * diffuse;

		if (red > 255)
			red = 255;
		if (green > 255)
			green = 255;
		if (blue > 255)
			blue = 255;
		return ((mlx_color){
			.r = (uint8_t)red,
			.g = (uint8_t)green,
			.b = (uint8_t)blue,
			.a = 255
		});
	}
	unit_direction = normalize(ray.dir);
	a = 0.5 * (unit_direction.y + 1.0);
	return ((mlx_color){
		.r = (uint8_t)((1.0 - a) * 255 + a * 127),
		.g = (uint8_t)((1.0 - a) * 255 + a * 178),
		.b = (uint8_t)((1.0 - a) * 255 + a * 255),
		.a = 255
	});
}

t_ray	camera_ray(t_mlx *mlx, t_camera camera, int x, int y)
{
	t_ray	ray;
	double	viewport_x;
	double	viewport_y;
	double	aspect;
	double	fov_scale;

	aspect = (double)mlx->info.width / mlx->info.height;
	fov_scale = tan(camera.fov * 0.5 * M_PI / 180);
	viewport_x = (2.0 * (x + 0.5) / mlx->info.width - 1.0)
		* aspect * fov_scale;
	viewport_y = (1.0 - 2.0 * (y + 0.5) / mlx->info.height)
		* fov_scale;
	ray.origin = camera.origin;
	ray.dir = add(camera.forward, add(
				multiply_scalar(camera.right, viewport_x),
				multiply_scalar(camera.up, viewport_y)
				)
			);
	ray.dir = normalize(ray.dir);
	return (ray);
}
mlx_color	ray_color(t_mlx *mlx, t_ray ray)
{
	double	a;
	t_hit	hit;
	t_vec	unit_direction;

	if (hit_object(mlx, ray, &hit))
	{
		t_vec	light_dir;
		double	diffuse;
		uint8_t	ambient_r = hit.color.r * mlx->scene.ambient_light.rgb.r * mlx->scene.ambient_light.ratio / 255;
		uint8_t	ambient_g = hit.color.g * mlx->scene.ambient_light.rgb.g * mlx->scene.ambient_light.ratio / 255;
		uint8_t	ambient_b = hit.color.b * mlx->scene.ambient_light.rgb.b * mlx->scene.ambient_light.ratio / 255;

		light_dir = normalize(sub(mlx->scene.light.lightpoint, hit.point));
		diffuse = dot(hit.normal, light_dir);
		if (diffuse < 0.0)
			diffuse = 0.0;
		diffuse *= mlx->scene.light.brightness;

		double red = ambient_r + hit.color.r * diffuse;
		double green = ambient_g + hit.color.g * diffuse;
		double blue = ambient_b + hit.color.b * diffuse;

		return ((mlx_color){
			.r = (uint8_t)red,
			.g = (uint8_t)green,
			.b = (uint8_t)blue,
			.a = 255
		});
	}
	unit_direction = normalize(ray.dir);
	a = 0.5 * (unit_direction.y + 1.0);
	return ((mlx_color){
		.r = (uint8_t)((1.0 - a) * 255 + a * 127),
		.g = (uint8_t)((1.0 - a) * 255 + a * 178),
		.b = (uint8_t)((1.0 - a) * 255 + a * 255),
		.a = 255
	});
}
