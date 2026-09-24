/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:24:46 by ejones            #+#    #+#             */
/*   Updated: 2026/09/24 16:59:13 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	mlx.camera.origin = (t_vec){0, 2, 10};
	mlx.camera.forward = (t_vec){0, 0, 1};
	mlx.camera.right = (t_vec){1, 0, 0};
	mlx.camera.up = (t_vec){0, 1, 0};
	mlx.camera.fov = 90.0;
	mlx.needs_redraw = 1;

	sp.center = (t_vec){0, 2, 10};
	sp.r = 1;
	mlx.sp = sp;


	mlx.pl.point_in_py = (t_vec){0, 0, 5};

	mlx.cy.axis_dir = normalize((t_vec){-2, 1, 0});
	mlx.cy.center = (t_vec){6, 2, 15};
	mlx.cy.r = 2;
	mlx.cy.h = 10;
	mlx_add_loop_hook(mlx.mlx, render_loop, &mlx);
	mlx_loop(mlx.mlx);

	mlx_destroy_image(mlx.mlx, mlx.img);
	mlx_destroy_window(mlx.mlx, mlx.win);
	mlx_destroy_context(mlx.mlx);

	return (0);
}

