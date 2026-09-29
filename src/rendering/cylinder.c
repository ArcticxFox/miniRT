/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:51:43 by ejones            #+#    #+#             */
/*   Updated: 2026/09/29 16:43:16 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	check_cylinder_root(t_cy cy, t_ray ray, t_hit *hit, double root)
{
	double	m;
	t_vec	radial;
	t_vec	oc;

	oc = sub(ray.origin, cy.center);
	m = dot(ray.dir, cy.axis_dir) * root + dot(oc, cy.axis_dir);
	if (m < (-cy.h / 2) || m > (cy.h / 2))
	{
		return (false);
	}
	hit->t = root;
	hit->point = ray_at(ray, root);
	radial = sub(sub(hit->point, cy.center), multiply_scalar(cy.axis_dir, m));
	hit->normal = normalize(radial);
	hit->color = cy.rgb;
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
	if (root_type == true)
		*root = (-b - sqrt(delta)) / a;
	else
		*root = (-b + sqrt(delta)) / a;
	return (true);
}

bool	hit_cylinder(t_cy cy, t_ray ray, t_hit *hit, t_interval range)
{
	double	root;
	double	old_max;

	old_max = range.max;
	if (get_root(cy, ray, true, &root))
	{
		if (root > range.min && root < range.max
			&& check_cylinder_root(cy, ray, hit, root))
			range.max = hit->t;
	}
	if (get_root(cy, ray, false, &root))
	{
		if (root > range.min && root < range.max
			&& check_cylinder_root(cy, ray, hit, root))
			range.max = hit->t;
	}
	if (check_bottom_cap(cy, ray, hit, range))
		range.max = hit->t;
	if (check_top_cap(cy, ray, hit, range))
		range.max = hit->t;
	if (range.max == old_max)
		return (false);
	hit->t = range.max;
	return (true);
}

bool	hit_cylinders(t_data *scene, t_ray ray, t_hit *hit, t_interval range)
{
	int		i;
	t_hit	hit_tmp;
	bool	hit_anything;

	i = 0;
	hit_anything = false;
	while (i < scene->cyl_count)
	{
		if (hit_cylinder(scene->cylinder[i], ray, &hit_tmp, range))
		{
			hit_anything = true;
			range.max = hit_tmp.t;
			*hit = hit_tmp;
			hit->color = scene->cylinder[i].rgb;
		}
		++i;
	}
	if (hit_anything)
		return (true);
	return (false);
}
