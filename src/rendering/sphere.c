/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:59:59 by ejones            #+#    #+#             */
/*   Updated: 2026/09/28 16:37:42 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit,
	double ray_tmin, double ray_tmax)
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
	return (true);
}

bool	hit_spheres(t_data *scene, t_ray ray, t_hit *hit, double closest_so_far)
{
	int		i;
	t_hit	hit_tmp;
	bool	hit_anything;

	i = 0;
	hit_anything = false;
	while (i < scene->sph_count)
	{
		if (hit_sphere(scene->sphere[i], ray, &hit_tmp, 0.001f, closest_so_far))
		{
			hit_anything = true;
			closest_so_far = hit_tmp.t;
			*hit = hit_tmp;
			hit->color = scene->sphere[i].rgb;
		}
		++i;
	}
	if (hit_anything)
		return (true);
	return (false);
}
