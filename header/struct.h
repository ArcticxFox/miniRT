/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:48:10 by ejones            #+#    #+#             */
/*   Updated: 2026/08/12 19:18:33 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "mini_rt.h"

# define HEIGHT 60
# define WIDTH 148

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

typedef struct s_sphere
{
	t_vec	center;
	double	r;
}	t_sphere;

typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
}	t_hit;

typedef struct s_camera
{
	t_vec	origin;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	fov;
}	t_camera;

typedef struct s_mlx
{
	mlx_context	mlx;
	mlx_window	win;
	mlx_image	img;

	t_camera	camera;
	t_sphere	sp;

	int			needs_redraw;
}	mlx_t;

double	dot(t_vec a, t_vec b);
t_vec	add(t_vec a, t_vec b);
t_vec	sub(t_vec a, t_vec b);
t_vec	multiply_scalar(t_vec vec1, double t);
t_vec	normalize(t_vec v);
double	vec_lenght(t_vec vec);
t_vec	ray_at(t_ray ray, double t);


#endif
