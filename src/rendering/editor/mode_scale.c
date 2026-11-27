/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:16:58 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 16:45:29 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	get_distance(t_mlx *mlx, int mouse_x, int mouse_y)
{
	double	depth;
	double	t;
	double	denom;
	t_ray	ray;
	t_vec	mouse_world;

	ray = camera_ray(mlx, &mlx->scene.camera, mouse_x, mouse_y);
	depth = dot(sub(mlx->object_start, mlx->scene.camera.origin),
			mlx->scene.camera.forward);
	denom = dot(ray.dir, mlx->scene.camera.forward);
	if (fabs(denom) < 1e-6)
		return (mlx->value_start);
	t = depth / denom;
	mouse_world = add(ray.origin, multiply_scalar(ray.dir, t));
	t = vec_lenght(sub(mouse_world, mlx->object_start));
	return (t);
}

void	scale_objects(t_mlx *mlx, t_data *scene, int mouse_x, int mouse_y)
{
	double		distance;
	double		ratio;
	t_object	*obj;

	obj = scene->items.objects;
	distance = get_distance(mlx, mouse_x, mouse_y);
	ratio = distance / mlx->value_start;
	if (!(ratio > 0.05) || ratio > 100)
		return ;
	if (mlx->selected.type == OBJ_SPHERE)
		obj[mlx->selected.index].data.sphere.r = mlx->selected.r * ratio;
	if (mlx->selected.type == OBJ_CYLINDER)
	{
		obj[mlx->selected.index].data.cylinder.r = mlx->selected.r * ratio;
		obj[mlx->selected.index].data.cylinder.h = mlx->selected.h * ratio;
	}
}

void	scale_object(t_mlx *mlx)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(mlx->mlx, &mouse_x, &mouse_y);
	scale_objects(mlx, &mlx->scene, mouse_x, mouse_y);
}
