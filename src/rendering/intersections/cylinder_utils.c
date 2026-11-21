/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:26:02 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 17:30:18 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	check_top_cap(t_cy cy, t_query *query)
{
	double	denom;
	double	t;
	t_vec	top_cap;
	t_vec	radial;
	t_vec	oc;

	top_cap = add(cy.center, multiply_scalar(cy.axis_dir, (cy.h / 2)));
	denom = dot(query->ray.dir, cy.axis_dir);
	if (fabs(denom) < 1e-8)
		return (false);
	t = dot(sub(top_cap, query->ray.origin), cy.axis_dir) / denom;
	if (t <= query->iv.min || query->iv.max <= t)
		return (false);
	oc = sub(ray_at(query->ray, t), top_cap);
	radial = sub(oc, multiply_scalar(cy.axis_dir, dot(oc, cy.axis_dir)));
	if (dot(radial, radial) > cy.r * cy.r)
		return (false);
	query->hit->t = t;
	query->hit->point = ray_at(query->ray, t);
	query->hit->normal = multiply_scalar(cy.axis_dir, 1);
	query->hit->color = cy.rgb;
	return (true);
}

bool	check_bottom_cap(t_cy cy, t_query *query)
{
	double	denom;
	double	t;
	t_vec	bottom_center;
	t_vec	radial;
	t_vec	oc;

	bottom_center = sub(cy.center, multiply_scalar(cy.axis_dir, (cy.h / 2)));
	denom = dot(query->ray.dir, cy.axis_dir);
	if (fabs(denom) < 1e-8)
		return (false);
	t = dot(sub(bottom_center, query->ray.origin), cy.axis_dir) / denom;
	if (t <= query->iv.min || query->iv.max <= t)
		return (false);
	oc = sub(ray_at(query->ray, t), bottom_center);
	radial = sub(oc, multiply_scalar(cy.axis_dir, dot(oc, cy.axis_dir)));
	if (dot(radial, radial) > cy.r * cy.r)
		return (false);
	query->hit->t = t;
	query->hit->point = ray_at(query->ray, t);
	query->hit->normal = multiply_scalar(cy.axis_dir, -1);
	query->hit->color = cy.rgb;
	return (true);
}
