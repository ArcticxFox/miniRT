/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:51:43 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 11:04:29 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// bool	check_cylinder_root(t_cy cy, t_query *query, double root)
// {
// 	double	m;
// 	t_vec	radial;
// 	t_vec	oc;

// 	oc = sub(query->ray.origin, cy.center);
// 	m = dot(query->ray.dir, cy.axis_dir) * root + dot(cy.axis_dir, oc);
// 	if (m < (-cy.h / 2) || m > (cy.h / 2))
// 	{
// 		return (false);
// 	}
// 	query->hit->t = root;
// 	query->hit->point = ray_at(query->ray, root);
// 	radial = sub(sub(query->hit->point, cy.center),
// 		multiply_scalar(cy.axis_dir, m));
// 	query->hit->normal = normalize(radial);
// 	return (true);
// }

// bool	get_root(t_cy cy, t_ray ray, bool root_type, double *root)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	delta;
// 	t_vec	oc;

// 	oc = sub(ray.origin, cy.center);
// 	a = dot(ray.dir, ray.dir) - dot(ray.dir, cy.axis_dir)
// 		* dot(ray.dir, cy.axis_dir);
// 	if (fabs(a) < 1e-8)
// 		return (false);
// 	b = dot(ray.dir, oc) - dot(ray.dir, cy.axis_dir) * dot(oc, cy.axis_dir);
// 	c = dot(oc, oc) - dot(oc, cy.axis_dir) * dot(oc, cy.axis_dir) - cy.r * cy.r;
// 	delta = b * b - a * c;
// 	if (delta < 0)
// 		return (false);
// 	if (root_type == false)
// 		*root = (-b - sqrt(delta)) / a;
// 	else
// 		*root = (-b + sqrt(delta)) / a;
// 	return (true);
// }

// bool	hit_cylinder(t_cy cy, t_query *query)
// {
// 	double	root;
// 	double	old_max;

// 	old_max = query->iv.max;
// 	if (get_root(cy, query->ray, false, &root))
// 	{
// 		if (root > query->iv.min && root < query->iv.max
// 			&& check_cylinder_root(cy, query, root))
// 			query->iv.max = query->hit->t;
// 	}
// 	if (get_root(cy, query->ray, true, &root))
// 	{
// 		if (root > query->iv.min && root < query->iv.max
// 			&& check_cylinder_root(cy, query, root))
// 			query->iv.max = query->hit->t;
// 	}
// 	if (check_bottom_cap(cy, query))
// 		query->iv.max = query->hit->t;
// 	if (check_top_cap(cy, query))
// 		query->iv.max = query->hit->t;
// 	if (query->iv.max == old_max)
// 		return (false);
// 	query->hit->t = query->iv.max;
// 	query->hit->color = cy.rgb;
// 	return (true);
// }

//////////////////////////////////////////////////////////////
bool	check_cap(t_cy *cy, t_query *query, double sign)
{
	t_vec	center;
	t_vec	p;
	t_vec	oc;
	double	denom;
	double	t;

	center = add(cy->center, multiply_scalar(cy->axis_dir, sign * cy->h / 2));
	denom = dot(query->ray.dir, cy->axis_dir);
	if (fabs(denom) < 1e-8)
		return (false);
	t = dot(sub(center, query->ray.origin), cy->axis_dir) / denom;
	if (t <= query->iv.min || query->iv.max <= t)
		return (false);
	p = ray_at(query->ray, t);
	oc = sub(p, center);
	if (dot(oc, oc) > cy->r * cy->r)
		return (false);
	query->hit->t = t;
	query->hit->point = p;
	query->hit->normal = multiply_scalar(cy->axis_dir, sign);
	if (denom * sign > 0)
		query->hit->normal = multiply_scalar(cy->axis_dir, -1);
	query->hit->color = cy->rgb;
	query->iv.max = t;
	return (true);
}

bool	check_cylinder_roots(t_cy *cy, t_query *query, double root)
{
	double	m;
	t_vec	p;
	t_vec	radial;

	p = ray_at(query->ray, root);
	m = dot(sub(p, cy->center), cy->axis_dir);
	if (fabs(m) > cy->h / 2)
		return (false);
	radial = sub(sub(p, cy->center), multiply_scalar(cy->axis_dir, m));
	query->hit->t = root;
	query->hit->point = p;
	query->hit->normal = multiply_scalar(radial, 1.0 / cy->r);
	if (dot(query->hit->normal, query->ray.dir) > 0)
		query->hit->normal = multiply_scalar(query->hit->normal, -1);
	query->hit->color = cy->rgb;
	query->iv.max = root;
	return (true);
}

bool	get_roots(t_cy *cy, t_ray ray, double roots[2])
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vec	oc;

	oc = sub(ray.origin, cy->center);
	a = dot(ray.dir, ray.dir) - pow(dot(ray.dir, cy->axis_dir), 2);
	if (fabs(a) < 1e-8)
		return (false);
	b = dot(ray.dir, oc) - dot(ray.dir, cy->axis_dir) * dot(oc, cy->axis_dir);
	c = dot(oc, oc) - pow(dot(oc, cy->axis_dir), 2) - cy->r * cy->r;
	delta = b * b - a * c;
	if (delta < 0)
		return (false);
	delta = sqrt(delta);
	roots[0] = (-b - delta) / a;
	roots[1] = (-b + delta) / a;
	return (true);
}

bool	hit_cylinder(t_cy *cy, t_query *query)
{
	double	roots[2];
	bool	hit;
	int		i;

	hit = false;
	if (get_roots(cy, query->ray, roots))
	{
		i = 0;
		while (i < 2 && !hit)
		{
			if (roots[i] > query->iv.min && roots[i] < query->iv.max)
				hit = check_cylinder_roots(cy, query, roots[i]);
			++i;
		}
	}
	hit |= check_cap(cy, query, -1);
	hit |= check_cap(cy, query, 1);
	return (hit);
}

