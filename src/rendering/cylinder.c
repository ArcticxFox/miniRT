/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:51:43 by ejones            #+#    #+#             */
/*   Updated: 2026/08/24 17:14:19 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	check_top_cap(t_cy cy, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax)
{
	double	denom;
	double	t;

	t_vec	top_cap;
	t_vec	radial;
	t_vec	oc;

	top_cap = add(cy.center, multiply_scalar(cy.axis_dir, (cy.h / 2)));
	denom = dot(ray.dir, cy.axis_dir);
	if (fabs(denom) < 1e-8)
		return	(false);
	t = dot(sub(top_cap, ray.origin), cy.axis_dir) / denom;
	if (t <= ray_tmin || ray_tmax <= t)
		return (false);
	hit->t = t;
	hit->point = ray_at(ray, t);

	oc = sub(hit->point, top_cap);
	radial = sub(oc, multiply_scalar(cy.axis_dir, dot(oc, cy.axis_dir)));

	if (dot(radial, radial) > cy.r * cy.r)
		return (false);
	hit->normal = multiply_scalar(cy.axis_dir, -1);
		hit->color = (mlx_color){
		.r = (uint8_t)(200),
		.g = (uint8_t)(0),
		.b = (uint8_t)(200),
		.a = 255
	};
	return (true);
}



bool	check_bottom_cap(t_cy cy, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax)
{
	double	denom;
	double	t;

	t_vec	bottom_center;
	t_vec	radial;
	t_vec	oc;

	bottom_center = sub(cy.center, multiply_scalar(cy.axis_dir, (cy.h / 2)));
	denom = dot(ray.dir, cy.axis_dir);
	if (fabs(denom) < 1e-8)
		return	(false);
	t = dot(sub(bottom_center, ray.origin), cy.axis_dir) / denom;
	if (t <= ray_tmin || ray_tmax <= t)
		return (false);
	hit->t = t;
	hit->point = ray_at(ray, t);

	oc = sub(hit->point, bottom_center);
	radial = sub(oc, multiply_scalar(cy.axis_dir, dot(oc, cy.axis_dir)));

	if (dot(radial, radial) > cy.r * cy.r)
		return (false);
	hit->normal = multiply_scalar(cy.axis_dir, -1);
		hit->color = (mlx_color){
		.r = (uint8_t)(200),
		.g = (uint8_t)(0),
		.b = (uint8_t)(200),
		.a = 255
	};
	return (true);
}

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
	hit->color = (mlx_color){
		.r = (uint8_t)(255),
		.g = (uint8_t)(0),
		.b = (uint8_t)(255),
		.a = 255
	};
	return (true);
}

// bool	hit_cylinder(t_cy cy, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	delta;
// 	double	root;
// 	t_vec	oc;

// 	oc = sub(ray.origin, cy.center);
// 	a = dot(ray.dir, ray.dir) - dot(ray.dir, cy.axis_dir) *  dot(ray.dir, cy.axis_dir);
// 	if (fabs(a) < 1e-8)
// 		return (false);
// 	b = dot(ray.dir, oc) - dot(ray.dir, cy.axis_dir) * dot(oc, cy.axis_dir);
// 	c = dot(oc, oc) - dot(oc, cy.axis_dir) * dot(oc, cy.axis_dir) - cy.r * cy.r;
// 	delta = b * b - a * c;
// 	if (delta < 0)
// 		return (false);
// 	root = (-b - sqrt(delta)) / a;
// 	if (root > ray_tmin && root < ray_tmax
// 		&& check_cylinder_root(cy, ray, hit, root, oc))
// 		return (true);
// 	root = (-b + sqrt(delta)) / a;
// 	if (root > ray_tmin && root < ray_tmax
// 		&& check_cylinder_root(cy, ray, hit, root, oc))
// 		return (true);
// 	if (check_bottom_cap(cy, ray, hit, ray_tmin, ray_tmax))
// 		return (true);
// 	return (false);
// }

bool	get_root(t_cy cy, t_ray ray, bool root_type, double *root)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vec	oc;

	oc = sub(ray.origin, cy.center);
	a = dot(ray.dir, ray.dir) - dot(ray.dir, cy.axis_dir) *  dot(ray.dir, cy.axis_dir);
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
