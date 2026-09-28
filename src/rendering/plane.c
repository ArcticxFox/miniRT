/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:44:43 by ejones            #+#    #+#             */
/*   Updated: 2026/09/28 16:38:52 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_plane(t_pl pl, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax)
{
	double	denom;
	double	t;
	t_vec	oc;

	oc = sub(pl.point_in_py, ray.origin);
	denom = dot(ray.dir, pl.direction);
	if (denom == 0)
		return (false);
	t = (dot(oc, (t_vec){0, 1, 0}) / denom);
	if (t <= ray_tmin || ray_tmax <= t)
		return (false);
	hit->t = t;
	hit->point = ray_at(ray, t);
	if (fabs(denom) < 1e-8)
		hit->normal = (t_vec){0, -1, 0};
	else
		hit->normal = (t_vec){0, 1, 0};
	hit->color = pl.rgb;
	return (true);
}

bool	hit_planes(t_data *scene, t_ray ray, t_hit *hit, double closest_so_far)
{
	int		i;
	t_hit	hit_tmp;
	bool	hit_anything;

	i = 0;
	hit_anything = false;
	while (i < scene->pl_count)
	{
		if (hit_plane(scene->plane[i], ray, &hit_tmp, 0.001f, closest_so_far))
		{
			hit_anything = true;
			closest_so_far = hit_tmp.t;
			*hit = hit_tmp;
		}
		++i;
	}
	if (hit_anything)
		return (true);
	return (false);
}
