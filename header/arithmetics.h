/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:33:05 by ejones            #+#    #+#             */
/*   Updated: 2026/11/26 15:17:33 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETICS_H
# define ARITHMETICS_H

# include "mini_rt.h"

typedef struct s_get_root
{
	double	a;
	double	b;
	double	c;
	double	delta;
}	t_get_root;

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
