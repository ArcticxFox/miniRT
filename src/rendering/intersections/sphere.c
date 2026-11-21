/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:59:59 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 17:18:56 by ejones           ###   ########.fr       */
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

bool	hit_sphere(t_sphere sp, t_query *query)
{
	double	root1;
	double	root2;

	if (!get_sphere_roots(sp, query->ray, &root1, &root2))
		return (false);
	if (root1 <= query->iv.min || query->iv.max <= root1)
	{
		root1 = root2;
		if (root1 <= query->iv.min || query->iv.max <= root1)
			return (false);
	}
	query->hit->t = root1;
	query->hit->point = ray_at(query->ray, root1);
	query->hit->normal = normalize(sub(query->hit->point, sp.center));
	query->hit->color = sp.rgb;
	return (true);
}

