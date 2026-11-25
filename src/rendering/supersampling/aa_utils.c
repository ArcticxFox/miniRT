/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 17:19:06 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 18:38:13 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	sub_ray(t_mlx *mlx, int pix[2], int sub[2])
{
	return (camera_ray(mlx, mlx->scene.camera,
		pix[0] + (sub[0] + 0.5) / mlx->render.samples,
		pix[1] + (sub[1] + 0.5) / mlx->render.samples));
}

int	is_corner(int sub[2], int n)
{
	return (((sub[0] == 0) || (sub[0] == n - 1))
		&& ((sub[1] == 0) || (sub[1] == n - 1)));
}

static int	diff_colour(mlx_color a, mlx_color b)
{
	a.r -= b.r;
	a.g -= b.g;
	a.b -= b.b;
	return (a.r * a.r + a.g * a.g + a.b * a.b);
}

int	needs_refine(mlx_color c[5])
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		j = i + 1;
		while (j < 5)
		{
			if (diff_colour(c[i], c[j]) > AA_THRESHOLD)
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
