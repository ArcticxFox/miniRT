/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 17:19:06 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 20:21:45 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	sub_ray(t_mlx *mlx, int pix[2], int sub[2])
{
	return (camera_ray(mlx, &mlx->scene.camera,
		pix[0] + (sub[0] + 0.5) / mlx->render.samples,
		pix[1] + (sub[1] + 0.5) / mlx->render.samples));
}
// use int because otherwise if diff negative wrap around to a big number
static int	diff_colour(mlx_color a, mlx_color b)
{
	int	dr;
	int	dg;
	int	db;

	dr = a.r - b.r;
	dg = a.g - b.g;
	db = a.b - b.b;
	return (dr * dr + dg * dg + db * db);
}

int	is_probed(int sub[2], int n)
{
	if ((n % 2 && sub[0] == n / 2 && sub[1] == n / 2))
		return (1);
	return (((sub[0] == 0) || (sub[0] == n - 1))
		&& ((sub[1] == 0) || (sub[1] == n - 1)));
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
