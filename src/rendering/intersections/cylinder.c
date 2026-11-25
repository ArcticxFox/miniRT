/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:51:43 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 17:23:52 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	check_cylinder_root(t_cy cy, t_query *query, double root)
{
	double	m;
	t_vec	radial;
	t_vec	oc;

	oc = sub(query->ray.origin, cy.center);
	m = dot(query->ray.dir, cy.axis_dir) * root + dot(cy.axis_dir, oc);
	if (m < (-cy.h / 2) || m > (cy.h / 2))
	{
		return (false);
	}
	query->hit->t = root;
	query->hit->point = ray_at(query->ray, root);
	radial = sub(sub(query->hit->point, cy.center),
		multiply_scalar(cy.axis_dir, m));
	query->hit->normal = normalize(radial);
	return (true);
}

bool	get_root(t_cy cy, t_ray ray, bool root_type, double *root)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vec	oc;

	oc = sub(ray.origin, cy.center);
	a = dot(ray.dir, ray.dir) - dot(ray.dir, cy.axis_dir)
		* dot(ray.dir, cy.axis_dir);
	if (fabs(a) < 1e-8)
		return (false);
	b = dot(ray.dir, oc) - dot(ray.dir, cy.axis_dir) * dot(oc, cy.axis_dir);
	c = dot(oc, oc) - dot(oc, cy.axis_dir) * dot(oc, cy.axis_dir) - cy.r * cy.r;
	delta = b * b - a * c;
	if (delta < 0)
		return (false);
	if (root_type == false)
		*root = (-b - sqrt(delta)) / a;
	else
		*root = (-b + sqrt(delta)) / a;
	return (true);
}

bool	hit_cylinder(t_cy cy, t_query *query)
{
	double	root;
	double	old_max;

	old_max = query->iv.max;
	if (get_root(cy, query->ray, false, &root))
	{
		if (root > query->iv.min && root < query->iv.max
			&& check_cylinder_root(cy, query, root))
			query->iv.max = query->hit->t;
	}
	if (get_root(cy, query->ray, true, &root))
	{
		if (root > query->iv.min && root < query->iv.max
			&& check_cylinder_root(cy, query, root))
			query->iv.max = query->hit->t;
	}
	if (check_bottom_cap(cy, query))
		query->iv.max = query->hit->t;
	if (check_top_cap(cy, query))
		query->iv.max = query->hit->t;
	if (query->iv.max == old_max)
		return (false);
	query->hit->t = query->iv.max;
	query->hit->color = cy.rgb;
	return (true);
}
