/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:02:20 by ejones            #+#    #+#             */
/*   Updated: 2026/10/07 16:36:29 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_objects(t_mlx *mlx, t_ray ray, t_hit *hit)
{
	bool		hit_anything;
	t_hit		hit_tmp;
	t_interval	range;

	hit_anything = false;
	range.min = 0.001f;
	range.max = DBL_MAX;
	if (-1 < hit_spheres(&mlx->scene, ray, &hit_tmp, range))
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

	if (hit_objects(mlx, ray, &hit))
	{
		return (hit.color); // add ambient lighting here.
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

void	movement(t_mlx *mlx, double dt)
{
	double	speed;

	speed = 6.0;
	if (mlx->keys.up)
		mlx->scene.camera.origin = sub(mlx->scene.camera.origin,
				multiply_scalar(mlx->scene.camera.up, speed * dt));
	if (mlx->keys.down)
		mlx->scene.camera.origin = add(mlx->scene.camera.origin,
				multiply_scalar(mlx->scene.camera.up, speed * dt));
	if (mlx->keys.right)
		mlx->scene.camera.origin = add(mlx->scene.camera.origin,
				multiply_scalar(mlx->scene.camera.right, speed * dt));
	if (mlx->keys.left)
		mlx->scene.camera.origin = sub(mlx->scene.camera.origin,
				multiply_scalar(mlx->scene.camera.right, speed * dt));
	if (mlx->keys.forwards)
		mlx->scene.camera.origin = sub(mlx->scene.camera.origin,
				multiply_scalar(mlx->scene.camera.forward, speed * dt));
	if (mlx->keys.backwards)
		mlx->scene.camera.origin = add(mlx->scene.camera.origin,
				multiply_scalar(mlx->scene.camera.forward, speed * dt));
}

void	camera_mouse_rotate(t_mlx *mlx, double dx, double dy)
{
	double	sensitivity;
	double	yaw;
	double	pitch;
	t_quat	q_yaw;
	t_quat	q_pitch;

	sensitivity = 0.002;
	yaw = dx * sensitivity;
	pitch = dy * sensitivity;
	q_yaw = quat_from_axis_angle((t_vec){0, 1, 0}, yaw);
	mlx->scene.camera.forward = quat_rotate_vec(q_yaw,
			mlx->scene.camera.forward);
	mlx->scene.camera.right = quat_rotate_vec(q_yaw, mlx->scene.camera.right);
	mlx->scene.camera.up = quat_rotate_vec(q_yaw, mlx->scene.camera.up);
	q_pitch = quat_from_axis_angle(mlx->scene.camera.right, pitch);
	mlx->scene.camera.forward = quat_rotate_vec(q_pitch,
			mlx->scene.camera.forward);
	mlx->scene.camera.up = quat_rotate_vec(q_pitch, mlx->scene.camera.up);
	mlx->scene.camera.forward = normalize(mlx->scene.camera.forward);
	mlx->scene.camera.right = normalize(mlx->scene.camera.right);
	mlx->scene.camera.up = normalize(mlx->scene.camera.up);
}

void	rotations(t_mlx *mlx, int mouse_x, int mouse_y)
{
	int	dx;
	int	dy;

	if (mlx->keys.left_click)
	{
		dx = mouse_x - mlx->prev_mouse_pos.x;
		dy = mouse_y - mlx->prev_mouse_pos.y;
		camera_mouse_rotate(mlx, dx, dy);
		mlx->prev_mouse_pos.x = mouse_x;
		mlx->prev_mouse_pos.y = mouse_y;
	}
}

void	update_camera(t_mlx *mlx, double dt)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(mlx->mlx, &mouse_x, &mouse_y);
	movement(mlx, dt);
	rotations(mlx, mouse_x, mouse_y);
}
