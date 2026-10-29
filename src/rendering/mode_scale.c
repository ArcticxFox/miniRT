/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:16:58 by ejones            #+#    #+#             */
/*   Updated: 2026/10/29 16:51:28 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	get_distance(t_mlx *mlx, int mouse_x, int mouse_y)
{
	double	depth;
	double	t;
	t_ray	ray;
	t_vec	mouse_world;
	t_vec	diff;

	ray = camera_ray(mlx, mlx->scene.camera, mouse_x, mouse_y);
	depth = dot(sub(mlx->object_start, mlx->scene.camera.origin),
		 mlx->scene.camera.forward);
	t = depth / dot(ray.dir, mlx->scene.camera.forward);
	mouse_world = add(ray.origin, multiply_scalar(ray.dir, t));
	diff = sub(mouse_world, mlx->object_start);
	return (vec_lenght(diff));
}

void	scale_objects(t_mlx *mlx, t_data *scene, int mouse_x, int mouse_y)
{
	double	distance;

	distance = get_distance(mlx, mouse_x, mouse_y);
	if (mlx->selected.type == OBJ_SPHERE)
		scene->sphere[mlx->selected.index].r = mlx->selected.r * distance / mlx->value_start;
	if (mlx->selected.type == OBJ_CYLINDER)
	{
		scene->cylinder[mlx->selected.index].r = mlx->selected.r * distance / mlx->value_start;
		scene->cylinder[mlx->selected.index].h = mlx->selected.h * distance / mlx->value_start;
	}
}

void	scale_object(t_mlx *mlx)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(mlx->mlx, &mouse_x, &mouse_y);
	scale_objects(mlx, &mlx->scene, mouse_x, mouse_y);
}
