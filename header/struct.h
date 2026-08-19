/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:48:10 by ejones            #+#    #+#             */
/*   Updated: 2026/08/19 19:48:06 by ejones           ###   ########.fr       */
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

typedef struct s_plane
{
	t_vec	point_in_py;
}	t_pl;

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	axis_dir;
	float	d;
	float	h;
	double	r;
}	t_cy;

typedef struct s_hit
{
	double		t;
	t_vec		point;
	t_vec		normal;
	mlx_color	color;
}	t_hit;

typedef	struct	s_hittable_list
{

}	t_hit_list;

typedef struct s_camera
{
	t_vec	origin;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	fov;
}	t_camera;

typedef struct	s_objects
{
	t_sphere	sp;
	t_pl		pl;
	t_cy		cy;
}	t_objects;

typedef struct s_mlx
{
	mlx_context	mlx;
	mlx_window	win;
	mlx_image	img;

	t_camera	camera;
	t_sphere	sp;
	t_pl		pl;
	t_cy		cy;

	int			needs_redraw;
}	mlx_t;

double	dot(t_vec a, t_vec b);
t_vec	add(t_vec a, t_vec b);
t_vec	sub(t_vec a, t_vec b);
t_vec	mult(t_vec a, t_vec b);
t_vec	multiply_scalar(t_vec vec1, double t);
t_vec	normalize(t_vec v);
double	vec_lenght(t_vec vec);
t_vec	ray_at(t_ray ray, double t);


#endif
