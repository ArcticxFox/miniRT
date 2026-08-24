/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:59:59 by ejones            #+#    #+#             */
/*   Updated: 2026/08/21 17:11:46 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	root;
	t_vec	oc;

	oc = sub(sp.center, ray.origin);
	a = dot(ray.dir, ray.dir);
	b = dot(ray.dir, oc);
	c = dot(oc, oc) - sp.r * sp.r;
	delta = b * b - a * c;
	if (delta < 0)
		return (false);
	root = (b - sqrt(delta)) / a;
	if (root <= ray_tmin || ray_tmax <= root)
	{
		root = (b + sqrt(delta)) / a;
		if (root <= ray_tmin || ray_tmax <= root)
			return (false);
	}
	hit->t = root;
	hit->point = ray_at(ray, root);
	hit->normal = normalize(sub(hit->point, sp.center));
	hit->color = (mlx_color){
			.r = (uint8_t)((hit->normal.x + 1.0) * 0.5 * 255),
			.g = (uint8_t)((hit->normal.y + 1.0) * 0.5 * 255),
			.b = (uint8_t)((hit->normal.z + 1.0) * 0.5 * 255),
			.a = 255};
	return (true);
}
