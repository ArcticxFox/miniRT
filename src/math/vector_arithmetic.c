/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:11:37 by ejones            #+#    #+#             */
/*   Updated: 2026/08/07 13:50:35 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec	sub(t_vec a, t_vec b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec multiply_scalar(t_vec vec1, double t)
{
	vec1.x *= t;
	vec1.y *= t;
	vec1.z *= t;
	return (vec1);
}

t_vec normalize(t_vec v)
{
	double length;

	length = sqrt(v.x * v.x
		+ v.y * v.y
		+ v.z * v.z);
	v.x /= length;
	v.y /= length;
	v.z /= length;
	return v;
}

double	lenght(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}



