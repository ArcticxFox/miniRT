/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:59:59 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 14:05:05 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	get_sphere_roots(t_sphere *sp, t_ray ray, double roots[2])
{
	double	a;
	double	b;
	double	delta;
	t_vec	oc;

	oc = sub(sp->center, ray.origin);
	a = dot(ray.dir, ray.dir);
	b = dot(ray.dir, oc);
	delta = b * b - a * (dot(oc, oc) - sp->r * sp->r);
	if (delta < 0)
		return (false);
	delta = sqrt(delta);
	roots[0] = (b - delta) / a;
	roots[1] = (b + delta) / a;
	return (true);
}

bool	hit_sphere(t_sphere *sp, t_query *query)
{
	double	roots[2];
	double	t;

	if (!get_sphere_roots(sp, query->ray, roots))
		return (false);
	t = roots[0];
	if (t <= query->iv.min || query->iv.max <= t)
		t = roots[1];
	if (t <= query->iv.min || query->iv.max <= t)
		return (false);
	query->hit->t = t;
	query->hit->point = ray_at(query->ray, t);
	query->hit->normal = multiply_scalar(
		sub(query->hit->point, sp->center), 1.0 / sp->r);
	if (dot(query->hit->normal, query->ray.dir) > 0)
		query->hit->normal = multiply_scalar(query->hit->normal, -1);
	query->hit->color = sp->rgb;
	query->iv.max = t;
	return (true);
}

