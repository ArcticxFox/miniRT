/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 16:01:58 by ejones            #+#    #+#             */
/*   Updated: 2026/10/06 17:16:19 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	find_objects(mlx_t *mlx, t_ray ray, t_hit *hit)
{
	bool		hit_anything;
	t_hit		hit_tmp;
	t_interval	range;

	int	n = 0;
	int	type = 0;

	hit_anything = false;
	range.min = 0.001f;
	range.max = DBL_MAX;
	if (-1 < (n = hit_spheres(&mlx->scene, ray, &hit_tmp, range)))
	{
		hit_anything = true;
		range.max = hit_tmp.t;
		*hit = hit_tmp;
		type = 1;
		mlx->scene.sphere[n].r = 4;
	}
	if (hit_cylinders(&mlx->scene, ray, &hit_tmp, range))
	{
		hit_anything = true;
		range.max = hit_tmp.t;
		*hit = hit_tmp;
	}
	if (hit_planes(&mlx->scene, ray, &hit_tmp, range))
	{
		hit_anything = true;
		*hit = hit_tmp;
	}
	return (hit_anything);
}
