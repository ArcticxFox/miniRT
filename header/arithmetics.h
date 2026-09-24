/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:33:05 by ejones            #+#    #+#             */
/*   Updated: 2026/09/21 17:31:05 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETICS_H
# define ARITHMETICS_H

# include "mini_rt.h"

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_get_root
{
	double	a;
	double	b;
	double	c;
	double	delta;
}	t_get_root;

typedef struct s_quaternions
{
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quat;

double	dot(t_vec a, t_vec b);
t_vec	add(t_vec a, t_vec b);
t_vec	sub(t_vec a, t_vec b);
t_vec	mult(t_vec a, t_vec b);
t_vec	cross(t_vec a, t_vec b);
t_vec	multiply_scalar(t_vec vec1, double t);
t_vec	normalize(t_vec v);
double	vec_lenght(t_vec vec);
t_vec	ray_at(t_ray ray, double t);


t_quat	quat_multiply(t_quat a, t_quat b);
t_quat	quat_normalize(t_quat q);
t_quat	quat_conjugate(t_quat q);
t_quat	quat_from_axis_angle(t_vec axis, double angle);
t_vec	quat_rotate_vec(t_quat q, t_vec v);

#endif
