/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:44:47 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 20:19:09 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	camera_init(t_camera *cam, int width, int height)
{
	cam->half_h = tan(cam->fov * 0.5 * M_PI / 180);
	cam->half_w = cam->half_h * ((double)width / height);
}

t_ray	camera_ray(t_mlx *mlx, const t_camera *camera, double x, double y)
{
	t_ray	ray;
	double	viewport_x;
	double	viewport_y;

	viewport_x = (2.0 * x / mlx->info.width - 1.0) * camera->half_w;
	viewport_y = (1.0 - 2.0 * y / mlx->info.height) * camera->half_h;
	ray.origin = camera->origin;
	ray.dir = add(camera->forward, add(
				multiply_scalar(camera->right, viewport_x),
				multiply_scalar(camera->up, viewport_y)
				)
			);
	ray.dir = normalize(ray.dir);
	return (ray);
}
