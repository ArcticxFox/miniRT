/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:24:46 by ejones            #+#    #+#             */
/*   Updated: 2026/09/11 18:53:09 by ejones           ###   ########.fr       */
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

void	render_moving_sphere(mlx_t *mlx, t_camera camera)
{
	int			x;
	int			y;
	double		viewport_x;
	double		viewport_y;
	t_ray		ray;
	mlx_color	color;
	
	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			viewport_x = (2.0 * (x + 0.5) / mlx->info.width - 1.0) * mlx->info.width / mlx->info.height;
			viewport_y = 1.0 - 2.0 * (y + 0.5) / mlx->info.height;
			ray = camera_ray(mlx, camera, x, y);
			color = ray_color(mlx, ray);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x++, y, color);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x++, y, color);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x++, y, color);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x++, y, color);
			x = x + 5;
		}
		y = y + 5;
	}
}

void	render_sphere(mlx_t *mlx, t_camera camera)
{
	int			x;
	int			y;
	double		viewport_x;
	double		viewport_y;
	t_ray		ray;
	mlx_color	color;

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			viewport_x = (2.0 * (x + 0.5) / mlx->info.width - 1.0) * mlx->info.width / mlx->info.height;
			viewport_y = 1.0 - 2.0 * (y + 0.5) / mlx->info.height;
			ray = camera_ray(mlx, camera, x, y);
			color = ray_color(mlx, ray);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	update_camera(mlx_t *mlx, double dt)
{
	double	speed;

	speed = 5.0;

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


}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	render_loop(void *param)
{
	mlx_t	*mlx;
	double	current_time;
	double	delta_time;


	mlx = (mlx_t *)param;

	// if (!mlx->needs_redraw)
	// 	return ;
	printf("rendering\n");
	printf(
	"render: camera = %f %f %f\n",
	mlx->camera.origin.x,
	mlx->camera.origin.y,
	mlx->camera.origin.z
);
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){ {255, 255, 255, 255} });

	current_time = get_time();
	delta_time = current_time - mlx->last_time;
	mlx->last_time = current_time;

	update_camera(mlx, delta_time);

	if (!mlx->needs_redraw)
		render_moving_sphere(mlx, mlx->camera);
	else
		render_sphere(mlx, mlx->camera);

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
	t_sphere	sp;

	init_window(&mlx);
	mlx.camera.origin = (t_vec){0, 2, 10};
	mlx.camera.forward = (t_vec){0, 0, -1};
	mlx.camera.right = (t_vec){1, 0, 0};
	mlx.camera.up = (t_vec){0, 1, 0};
	mlx.camera.fov = 90.0;
	mlx.needs_redraw = 1;

	sp.center = (t_vec){0, 2, -10};
	sp.r = 1;
	mlx.sp = sp;


	mlx.pl.point_in_py = (t_vec){0, 0, -5};

	mlx.cy.axis_dir = normalize((t_vec){-2, 1, 0});
	mlx.cy.center = (t_vec){6, 2, -15};
	mlx.cy.r = 2;
	mlx.cy.h = 10;
	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);

	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);

	return (0);
}
