/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:08:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/26 15:27:41 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_tmp_data(t_tmp_data *minirt)
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
	while (i < scene->sph_count)
	{
		scene->sphere[i].r = scene->sphere[i].d / 2;
		++i;
	}
	i = 0;
	while (i < scene->cyl_count)
	{
		scene->cylinder[i].r = scene->cylinder[i].d / 2;
		++i;
	}
}

int	init_scene(t_tmp_data *tmp, t_data *scene)
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
	if (init_bvh(&scene->items.bvh, &scene->items))
	{
		free_bvh(&scene->items.bvh);
		free(scene->items.objects);
		return (MRT_MALLOC);
	}
	free_tmp_data(tmp);
	return (MRT_OK);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_tmp_data	tmp_scene;

	mlx = (t_mlx){0};
	if (program_setup(ac, av, &tmp_scene) != MRT_OK)
	{
		free_tmp_data(&tmp_scene);
		return (1);
	}
	add_radius(&tmp_scene);
	if (init_scene(&tmp_scene, &mlx.scene) == MRT_MALLOC)
		return (MRT_MALLOC);
	init_window(&mlx);
	render_moving_scene(&mlx, mlx.scene.camera);
	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);
	free(mlx.scene.items.objects);
	free_bvh(&mlx.scene.items.bvh);
	return (0);
}
