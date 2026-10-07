/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:59:59 by ejones            #+#    #+#             */
/*   Updated: 2026/10/06 17:13:20 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	get_sphere_roots(t_sphere sp, t_ray ray,
	double *root1, double *root2)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vec	oc;

	oc = sub(sp.center, ray.origin);
	a = dot(ray.dir, ray.dir);
	b = dot(ray.dir, oc);
	c = dot(oc, oc) - sp.r * sp.r;
	delta = b * b - a * c;
	if (delta < 0)
		return (false);
	*root1 = (b - sqrt(delta)) / a;
	*root2 = (b + sqrt(delta)) / a;
	return (true);
}

bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit, t_interval range)
{
	double	root1;
	double	root2;

	if (!get_sphere_roots(sp, ray, &root1, &root2))
		return (false);
	if (root1 <= range.min || range.max <= root1)
	{
		root1 = root2;
		if (root1 <= range.min || range.max <= root1)
			return (false);
	}
	hit->t = root1;
	hit->point = ray_at(ray, root1);
	hit->normal = normalize(sub(hit->point, sp.center));
	return (true);
}

int	hit_spheres(t_data *scene, t_ray ray, t_hit *hit, t_interval range)
{
	int		i;
	int		n;
	bool	hit_anything;

	i = 0;
	n = 0;
	hit_anything = false;
	while (i < scene->sph_count)
	{
		if (hit_sphere(scene->sphere[i], ray, hit, range))
		{
			hit_anything = true;
			range.max = hit->t;
			hit->color = scene->sphere[i].rgb;
			n = i;
		}
		++i;
	}
	if (hit_anything)
		return (n);
	return (-1);
}
