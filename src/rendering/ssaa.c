/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 17:12:04 by ejones            #+#    #+#             */
/*   Updated: 2026/11/20 14:15:18 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	add_colour(int colour1[], mlx_color coulour2)
{
	colour1[0] += coulour2.r;
	colour1[1] += coulour2.g;
	colour1[2] += coulour2.b;
}

static mlx_color	divide_colour(int colour1[], int denom)
{
	mlx_color	tmp;

	tmp.r = colour1[0] / denom;
	tmp.g = colour1[1] / denom;
	tmp.b = colour1[2] / denom;
	return (tmp);
}

mlx_color	ssaa(t_mlx *mlx, int x, int y)
{
	int			sub_x;
	int			sub_y;
	mlx_color	color;
	int	colour[3] = {0};
	t_ray	ray;

	sub_y = 0;
	while (sub_y < mlx->render.samples)
	{
		sub_x = 0;
		while (sub_x < mlx->render.samples)
		{
			ray = camera_ray(mlx, mlx->scene.camera,
				x + (double)sub_x / mlx->render.samples,
				y + (double)sub_y /mlx->render.samples
				);
			add_colour(colour, ray_color(mlx, ray));
			++sub_x;
		}
		++sub_y;
	}
	color = divide_colour(colour, mlx->render.samples * mlx->render.samples);
	return (color);
}
