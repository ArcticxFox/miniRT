/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 17:12:04 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 18:18:59 by ejones           ###   ########.fr       */
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
	tmp.a = 255;
	return (tmp);
}

static void	probe(t_mlx *mlx, int pix[2], int colour[3], mlx_color out[4])
{
	int	n;
	int	i;
	int sub[2];

	n = mlx->render.samples;
	i = 0;
	while (i < 4)
	{
		sub[0] = (i % 2) * (n - 1);
		sub[1] = (i / 2) * (n - 1);
		out[i] = ray_color(mlx, sub_ray(mlx, pix, sub));
		add_colour(colour, out[i]);
		++i;
	}
}

static void	grid_sample(t_mlx *mlx, int pix[2], int colour[3], int skip)
{
	int	sub[2];
	int	n;

	n = mlx->render.samples;
	sub[1] = 0;
	while (sub[1] < n)
	{
		sub[0] = 0;
		while (sub[0] < n)
		{
			if (!skip || !is_corner(sub, n))
				add_colour(colour, ray_color(mlx, sub_ray(mlx, pix, sub)));
			++sub[0];
		}
		++sub[1];
	}
}

mlx_color	ssaa(t_mlx *mlx, int x, int y)
{
	int			pix[2];
	int			colour[3];
	mlx_color	probes[4];
	int			skip;

	pix[0] = x;
	pix[1] = y;
	ft_bzero(colour, sizeof(colour));
	skip = (mlx->render.samples > 2);
	if (skip)
	{
		probe(mlx, pix, colour, probes);
		if (!needs_refine(probes))
			return (divide_colour(colour, 4));
	}
	grid_sample(mlx, pix, colour, skip);
	return (divide_colour(colour, mlx->render.samples * mlx->render.samples));
}
