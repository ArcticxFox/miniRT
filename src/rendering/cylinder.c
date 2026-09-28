/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:51:43 by ejones            #+#    #+#             */
/*   Updated: 2026/09/28 16:37:24 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	check_cylinder_root(t_cy cy, t_ray ray, t_hit *hit, double root, t_vec oc)
{
	double	m;
	t_vec	radial;

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

bool	hit_cylinder(t_cy cy, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax)
{
	t_vec	oc;
	double	root;
	double	closest_so_far;

	oc = sub(ray.origin, cy.center);
	closest_so_far = ray_tmax;
	if (get_root(cy, ray, true, &root))
	{
		if (root > ray_tmin && root < closest_so_far
			&& check_cylinder_root(cy, ray, hit, root, oc))
			closest_so_far = hit->t;
	}
	if (get_root(cy, ray, false, &root))
	{
		if (root > ray_tmin && root < closest_so_far
			&& check_cylinder_root(cy, ray, hit, root, oc))
			closest_so_far = hit->t;
	}
	if (check_bottom_cap(cy, ray, hit, ray_tmin, closest_so_far))
		closest_so_far = hit->t;
	if (check_top_cap(cy, ray, hit, ray_tmin, closest_so_far))
		closest_so_far = hit->t;
	if (ray_tmax == closest_so_far)
		return (false);
	hit->t = closest_so_far;
	return (true);
}

bool	hit_cylinders(t_data *scene, t_ray ray, t_hit *hit,
	double closest_so_far)
{
	int		i;
	t_hit	hit_tmp;
	bool	hit_anything;

	i = 0;
	hit_anything = false;
	while (i < scene->cyl_count)
	{
		if (hit_cylinder(scene->cylinder[i], ray, &hit_tmp, 0.001f,
				closest_so_far))
		{
			hit_anything = true;
			closest_so_far = hit_tmp.t;
			*hit = hit_tmp;
			hit->color = scene->cylinder[i].rgb;
		}
		++i;
	}
	if (hit_anything)
		return (true);
	return (false);
}
