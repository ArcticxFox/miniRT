/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:24:46 by ejones            #+#    #+#             */
/*   Updated: 2026/08/24 17:10:25 by ejones           ###   ########.fr       */
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

t_ray	camera_ray(t_camera camera, int x, int y)
{
	t_ray	ray;
	double	viewport_x;
	double	viewport_y;
	double	ratio_aspect;

	ratio_aspect = 1920.0 / 1080.0;
	viewport_x = (2.0 * (x + 0.5) / 1920.0 - 1.0) * ratio_aspect;
	viewport_y = 1.0 - 2.0 * (y + 0.5) / 1080.0;
	ray.origin = camera.origin;
	ray.dir = add(camera.forward,add(
		multiply_scalar(camera.right, viewport_x),
		multiply_scalar(camera.up, viewport_y)
		)
	);
	ray.dir = normalize(ray.dir);
	return (ray);
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
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			viewport_x = (2.0 * (x + 0.5) / 1920.0 - 1.0) * 1920 / 1080;
			viewport_y = 1.0 - 2.0 * (y + 0.5) / 1080.0;
			ray = camera_ray(camera, x, y);
			color = ray_color(mlx, ray);
			mlx_set_image_pixel(mlx->mlx, mlx->img, x, y, color);
			x++;
		}
		y++;
	}
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
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){ {255, 255, 255, 255} });
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
	mlx_window_create_info info;
	t_sphere	sp;

	init_window(&mlx, &info);
	mlx.camera.origin = (t_vec){0, 2, 10};
	mlx.camera.forward = (t_vec){0, 0, -1};
	mlx.camera.right = (t_vec){1, 0, 0};
	mlx.camera.up = (t_vec){0, 1, 0};
	mlx.camera.fov = 90.0;
	mlx.needs_redraw = 1;

	sp.center = (t_vec){0, 2, 5};
	sp.r = 1;
	mlx.sp = sp;


	mlx.pl.point_in_py = (t_vec){0, 0, 0};

	mlx.cy.axis_dir = normalize((t_vec){0, 1, 0});
	mlx.cy.center = (t_vec){3, 4, 0};
	mlx.cy.r = 2;
	mlx.cy.h = 10;
	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);

	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);

	return (0);
}
