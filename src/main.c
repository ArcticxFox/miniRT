/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:08:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/09/24 15:09:51 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parerrors.h"
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

int	main(int ac, char **av)
{
	t_data	minirt;

	if (program_setup(ac, av, &minirt) != MRT_OK)
	{
		printf("shitfucked\n");
		free_all(&minirt);
		return (1);
	}
	printf("%s is a good name!\n", av[1]);
	free_all(&minirt);
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

int	main(void)
{
	mlx_t		mlx;
	t_sphere	sp;

	init_window(&mlx);

	mlx.cy.axis_dir = normalize((t_vec){-2, 1, 0});
	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);

	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);

	return (0);
}
