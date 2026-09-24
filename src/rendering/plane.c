/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:44:43 by ejones            #+#    #+#             */
/*   Updated: 2026/08/24 16:55:17 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_plane(t_pl	pl, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax)
{
	double	denom;
	double	t;
	t_vec	oc;

	oc = sub(pl.point_in_py, ray.origin);
	denom = dot(ray.dir, (t_vec){0, 1, 0});
	if (denom == 0)
		return	(false);
	t = (dot(oc, (t_vec){0, 1, 0}) / denom);
	if (t <= ray_tmin || ray_tmax <= t)
		return (false);
	hit->t = t;
	hit->point = ray_at(ray, t);
	if (fabs(denom) < 1e-8)
		hit->normal = (t_vec){0, -1, 0};
	else
		hit->normal = (t_vec){0, 1, 0};
	hit->color = (mlx_color){
		.r = (uint8_t)(120),
		.g = (uint8_t)(150),
		.b = (uint8_t)(0),
		.a = 255 };
	return (true);
}
