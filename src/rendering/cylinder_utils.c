/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:26:02 by ejones            #+#    #+#             */
/*   Updated: 2026/09/28 16:44:36 by ejones           ###   ########.fr       */
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
		return (false);
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
	hit->color = cy.rgb;
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
		return (false);
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
	hit->color = cy.rgb;
	return (true);
}
