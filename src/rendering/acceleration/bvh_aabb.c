/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:39:42 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 19:44:01 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_aabb	surrounding_box(t_aabb a, t_aabb b)
{
	t_aabb	result;

	result.min.x = fmin(a.min.x, b.min.x);
	result.min.y = fmin(a.min.y, b.min.y);
	result.min.z = fmin(a.min.z, b.min.z);
	result.max.x = fmax(a.max.x, b.max.x);
	result.max.y = fmax(a.max.y, b.max.y);
	result.max.z = fmax(a.max.z, b.max.z);
	return (result);
}

t_aabb	sphere_aabb(t_sphere sphere)
{
	t_aabb	box;
	t_vec	radius;

	radius = (t_vec){sphere.r, sphere.r, sphere.r};
	box.min = sub(sphere.center, radius);
	box.max = add(sphere.center, radius);
	return (box);
}
static double	cy_half(t_cy cy, double axis_comp)
{
	double	k;

	k = 1.0 - axis_comp * axis_comp;
	if (k < 0.0)
		k = 0.0;
	return (cy.r *sqrt(k) + 0.5 * cy.h * fabs(axis_comp));
}

t_aabb	cylinder_aabb(t_cy cy)
{
	t_aabb	box;
	t_vec	e;

	e.x = cy_half(cy, cy.axis_dir.x);
	e.y = cy_half(cy, cy.axis_dir.y);
	e.z = cy_half(cy, cy.axis_dir.z);
	box.min = sub(cy.center, e);
	box.max = add(cy.center, e);
	return (box);
}

t_aabb	object_aabb(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (sphere_aabb(obj->data.sphere));
	return (cylinder_aabb(obj->data.cylinder));
}




