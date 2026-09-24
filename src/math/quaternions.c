/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:32:23 by ejones            #+#    #+#             */
/*   Updated: 2026/09/21 17:52:34 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_quat	quat_multiply(t_quat a, t_quat b)
{
	t_quat	res;

	res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return (res);
}

t_quat	quat_normalize(t_quat q)
{
	double length;

	length = sqrt(q.w * q.w
		+ q.x * q.x
		+ q.y * q.y
		+ q.z * q.z);
	q.w /= length;
	q.x /= length;
	q.y /= length;
	q.z /= length;
	return (q);
}

// Always normalize first before using func
t_quat	quat_conjugate(t_quat q)
{
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	return (q);
}

t_quat	quat_from_axis_angle(t_vec axis, double angle)
{
	t_quat	q;
	double	half_angle;
	double	s;

	axis = normalize(axis);
	half_angle = angle / 2;
	s = sin(half_angle);
	q.w = cos(half_angle);
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	return (q);
}

t_vec	quat_rotate_vec(t_quat q, t_vec v)
{
	t_vec	qv;
	t_vec	t;

	q = quat_normalize(q);
	qv.x = q.x;
	qv.y = q.y;
	qv.z = q.z;
	t = multiply_scalar(cross(qv, v), 2.0);
	return (add(v, add(multiply_scalar(t, q.w), cross(qv, t))));
}
