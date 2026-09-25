/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:08:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/09/25 15:53:21 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_all(t_data *minirt)
{
	if (minirt->cylinder)
		free(minirt->cylinder);
	if (minirt->sphere)
		free(minirt->sphere);
	if (minirt->plane)
		free(minirt->plane);
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

int	main(int ac, char **av)
{
	mlx_t	mlx;


	if (program_setup(ac, av, &mlx.scene) != MRT_OK)
	{
		free_all(&mlx.scene);
		return (1);
	}
	print_everything(&mlx.scene);
	mlx.scene.cylinder[0].r = mlx.scene.cylinder[0].d / 2;
	mlx.scene.sphere[0].r = mlx.scene.sphere[0].d / 2;
	init_window(&mlx);

	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);

	free_all(&mlx.scene);
	return (0);
}

// int	main(void)
// {
// 	mlx_t		mlx;
// 	t_sphere	sp;

// 	init_window(&mlx);

// 	mlx.cy.axis_dir = normalize((t_vec){-2, 1, 0});
// 	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
// 	mlx_loop(mlx.mlx);

// 	mlx_destroy_image(mlx.mlx, mlx.img);
// 	mlx_destroy_window(mlx.mlx, mlx.win);
// 	mlx_destroy_context(mlx.mlx);

// 	return (0);
// }
