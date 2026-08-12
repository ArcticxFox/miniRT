/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:24:46 by ejones            #+#    #+#             */
/*   Updated: 2026/08/12 19:44:30 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// double	hit_sphere(t_sphere sp, t_ray ray)
// {
// 	double	a = 0, b = 0, c = 0;
// 	double	delta;
// 	t_vec	oc = sub(sp.center, ray.origin);

// 	a = dot(ray.dir, ray.dir);
// 	b = dot(ray.dir, oc);
// 	c = dot(oc, oc) - sp.r * sp.r;
// 	delta = b * b - a * c;

// 	if (delta < 0)
// 		return (-1.0);
// 	else
// 		return ((b - sqrt(delta)) / a);
// }

bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vec	oc;

	oc = sub(sp.center, ray.origin);
	a = dot(ray.dir, ray.dir);
	b = dot(ray.dir, oc);
	c = dot(oc, oc) - sp.r * sp.r;
	delta = b * b - a * c;

	if (delta < 0)
		return (false);
	if ((hit->t = (b - sqrt(delta)) / a) > 0.0)
		hit->point = ray_at(ray, hit->t);
	else if ((hit->t = (b + sqrt(delta)) / a) > 0.0)
		hit->point = ray_at(ray, hit->t);
	else
		return (false);
	hit->normal = normalize(sub(hit->point, sp.center));
	return (true);
}

mlx_color	ray_color(t_ray ray, t_sphere sp)
{
	double	a;
	t_hit	hit;
	t_vec	unit_direction;

	if (hit_sphere(sp, ray, &hit))
	{
		return ((mlx_color){
			.r = (uint8_t)((hit.normal.x + 1.0) * 0.5 * 255),
			.g = (uint8_t)((hit.normal.y + 1.0) * 0.5 * 255),
			.b = (uint8_t)((hit.normal.z + 1.0) * 0.5 * 255),
			.a = 255
		});
	}
	// background gradient
	unit_direction = normalize(ray.dir);
	a = 0.5 * (unit_direction.y + 1.0);
	return ((mlx_color){
		.r = (uint8_t)((1.0-a) * 255 + a * 127),
		.g = (uint8_t)((1.0-a) * 255 + a * 178),
		.b = (uint8_t)((1.0-a) * 255 + a * 255),
		.a = 255
	});
}

t_ray	camera_ray(t_camera camera, int x, int y)
{
	t_ray	ray;
	double	viewport_x;
	double	viewport_y;
	double	ratio_aspect;

	ratio_aspect = 800.0 / 600.0;
	viewport_x = (2.0 * (x + 0.5) / 800.0 - 1.0) * ratio_aspect;
	viewport_y = 1.0 - 2.0 * (y + 0.5) / 600.0;
	ray.origin = camera.origin;
	ray.dir = add(camera.forward,add(
		multiply_scalar(camera.right, viewport_x),
		multiply_scalar(camera.up, viewport_y)
		)
	);
	ray.dir = normalize(ray.dir);
	return (ray);
}

void	render_sphere(mlx_t *mlx, t_camera camera, t_sphere sp)
{
	int			x;
	int			y;
	double		viewport_x;
	double		viewport_y;
	t_ray		ray;
	mlx_color	color;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			viewport_x = (2.0 * (x + 0.5) / 800.0 - 1.0) * 800 / 600;
			viewport_y = 1.0 - 2.0 * (y + 0.5) / 600.0;
			ray = camera_ray(camera, x, y);
			color = ray_color(ray, sp);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	render_loop(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;

	if (!mlx->needs_redraw)
		return ;
	printf("rendering\n");
	printf(
	"render: camera = %f %f %f\n",
	mlx->camera.origin.x,
	mlx->camera.origin.y,
	mlx->camera.origin.z
);
	render_sphere(mlx, mlx->camera, mlx->sp);

	mlx_put_image_to_window(
		mlx->mlx,
		mlx->win,
		mlx->img,
		0,
		0
	);
	mlx->needs_redraw = 0;
}

int	main(void)
{
	mlx_t		mlx;
	mlx_window_create_info info;
	t_sphere	sp;

	init_window(&mlx, &info);
	mlx.camera.origin = (t_vec){0, -2, 10};
	mlx.camera.forward = (t_vec){0, 0, -1};
	mlx.camera.right = (t_vec){1, 0, 0};
	mlx.camera.up = (t_vec){0, 1, 0};
	mlx.camera.fov = 90.0;
	sp.center = (t_vec){0, -2, 5};
	sp.r = 2;
	mlx.sp = sp;
	mlx.needs_redraw = 1;
	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);

	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);

	return (0);
}
