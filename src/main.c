/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:08:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/18 15:24:26 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_all(t_tmp_data *minirt)
{
	if (minirt->cylinder)
		free(minirt->cylinder);
	if (minirt->sphere)
		free(minirt->sphere);
	if (minirt->plane)
		free(minirt->plane);
	return ;
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	add_radius(t_tmp_data *scene)
{
	int	i;

	i = 0;
	while(i < scene->sph_count)
	{
		scene->sphere[i].r = scene->sphere[i].d / 2;
		++i;
	}
	i = 0;
	while(i < scene->cyl_count)
	{
		scene->cylinder[i].r = scene->cylinder[i].d / 2;
		++i;
	}
}

void	*init_scene(t_tmp_data *tmp, t_data *scene)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	scene->ambient_light = tmp->ambient_light;
	scene->light = tmp->light;
	scene->camera = tmp->camera;
	scene->items.capacity = tmp->cyl_cap + tmp->pl_cap + tmp->sph_cap;
	scene->items.count = tmp->pl_count + tmp->sph_count + tmp->cyl_count;
	scene->items.objects = ft_calloc(scene->items.count, sizeof(t_object));
	while (n < tmp->sph_count)
	{
		scene->items.objects[n].data.sphere = tmp->sphere[n];
		scene->items.objects[n++].type = OBJ_SPHERE;
	}
	while (i < tmp->cyl_count)
	{
		scene->items.objects[n].data.cylinder = tmp->cylinder[i++];
		scene->items.objects[n++].type = OBJ_CYLINDER;
	}
	i = 0;
	while (i < tmp->pl_count)
	{
		scene->items.objects[n].data.plane = tmp->plane[i++];
		scene->items.objects[n++].type = OBJ_PLANE;
	}
	scene->items.pl_count = tmp->pl_count;
	free_all(tmp);
	return (scene);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_tmp_data	tmp_scene;

	mlx = (t_mlx){0};
	if (program_setup(ac, av, &tmp_scene) != MRT_OK)
	{
		free_all(&tmp_scene);
		return (1);
	}
	add_radius(&tmp_scene);
	init_scene(&tmp_scene, &mlx.scene);
	init_window(&mlx);
	render_moving_scene(&mlx, mlx.scene.camera);
	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);
	free(mlx.scene.items.objects);
	return (0);
}

// int main(void)
// {
//     t_aabb      box;
//     t_ray       ray;
//     t_interval  interval;

//     box.min = (t_vec){-2, -2, -2};
//     box.max = (t_vec){2, 2, 2};

//     ray.origin = (t_vec){2, 0, -5};
//     ray.dir = (t_vec){0, 0, 1};

//     interval.min = 0.001;
//     interval.max = INFINITY;

//     printf("Hit: %d\n", hit_aabb(ray, box, interval));
// 	box.min = sub()
//     return (0);
// }
