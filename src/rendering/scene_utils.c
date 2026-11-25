/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:02:20 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 15:49:02 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_object(t_object *obj, t_query *query)
{
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere(&obj->data.sphere, query));
	else if (obj->type == OBJ_CYLINDER)
		return (hit_cylinder(&obj->data.cylinder, query));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane(&obj->data.plane, query));
	return (false);
}

bool	hit_objects(t_objects *items, t_query *query)
{
	int			i;
	bool		hit_anything;
	t_hit		tmp;
	t_query		test;

	i = 0;
	hit_anything = hit_bvh(&items->bvh, query);
	test = *query;
	test.hit = &tmp;
	while (i < items->count)
	{
		if (items->objects[i].type == OBJ_PLANE
			&& hit_object(&items->objects[i], &test))
		{
			*query->hit = tmp;
			query->iv.max = tmp.t;
			test.iv.max = tmp.t;
			hit_anything = true;
		}
		++i;
	}
	return (hit_anything);
}

mlx_color	ray_color(t_mlx *mlx, t_ray ray)
{
	double	a;
	t_hit	hit;
	t_hit	shadow_hit;
	t_vec	unit_direction;
	t_query	query;

	query.iv = (t_interval){0.001f, INFINITY};
	query.ray = ray;
	query.hit = &hit;
	if (hit_objects(&mlx->scene.items, &query))
	{
		hit = *query.hit;
		t_vec	light_dir;
		double	light_distance;
		double	diffuse;
		uint8_t	ambient_r = hit.color.r * mlx->scene.ambient_light.rgb.r * mlx->scene.ambient_light.ratio / 255;
		uint8_t	ambient_g = hit.color.g * mlx->scene.ambient_light.rgb.g * mlx->scene.ambient_light.ratio / 255;
		uint8_t	ambient_b = hit.color.b * mlx->scene.ambient_light.rgb.b * mlx->scene.ambient_light.ratio / 255;


		light_dir = normalize(sub(mlx->scene.light.lightpoint, hit.point));
		light_distance = vec_lenght(sub(mlx->scene.light.lightpoint, hit.point));
		diffuse = dot(hit.normal, light_dir);
		if (diffuse < 0.0)
			diffuse = 0.0;
		else
			{
				query.iv = (t_interval){0.001f, light_distance};
				query.ray = (t_ray){
					.dir = light_dir,
					.origin = add(hit.point, multiply_scalar(hit.normal, 0.001))
				};
				query.hit = &shadow_hit;
				if (hit_objects(&mlx->scene.items, &query))
					diffuse = 0.0;
			}
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

void	fill_tab(t_mlx *mlx, t_ray *ray, mlx_color *tab_col, int size)
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
