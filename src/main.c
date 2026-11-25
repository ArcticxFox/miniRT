/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:08:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/25 18:24:47 by ejones           ###   ########.fr       */
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
#include <time.h>
double	get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((double)ts.tv_sec + (double)ts.tv_nsec / 1e9);
}
// double	get_time(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
// }

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

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_tmp_data	tmp_scene;

	ft_bzero(&mlx, sizeof(t_mlx));
	if (program_setup(ac, av, &tmp_scene) != MRT_OK)
	{
		free_tmp_data(&tmp_scene);
		return (1);
	}
	add_radius(&tmp_scene);
	if (init_scene(&tmp_scene, &mlx.scene) == MRT_MALLOC)
	{
		free_tmp_data(&tmp_scene);
		return (MRT_MALLOC);
	}
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
