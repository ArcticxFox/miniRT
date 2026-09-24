/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:48:10 by ejones            #+#    #+#             */
/*   Updated: 2026/09/21 17:12:35 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mini_rt.h"

# define HEIGHT 60
# define WIDTH 148

//=================================objects====================================//

typedef struct	s_sphere
{
	t_vec	center;
	double	r;
}	t_sphere;

typedef struct	s_plane
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

typedef struct	s_hit
{
	double		t;
	t_vec		point;
	t_vec		normal;
	mlx_color	color;
}	t_hit;

typedef struct	s_objects
{
	t_sphere	sp;
	t_pl		pl;
	t_cy		cy;
}	t_objects;

typedef struct	s_mouse_pos
{
	int	x;
	int	y;
}	t_mouse_pos;

//============================================================================//

typedef struct	s_keys
{
	bool	up;
	bool	down;
	bool	right;
	bool	left;
	bool	backwards;
	bool	forwards;
	bool	left_click;
	bool	right_click;
}	t_keys;

typedef struct	s_camera
{
	t_vec	origin;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	fov;
}	t_camera;

typedef struct	s_mlx
{
	mlx_context				mlx;
	mlx_window				win;
	mlx_image				img;
	mlx_window_create_info	info;

	t_camera				camera;
	t_sphere				sp;
	t_pl					pl;
	t_cy					cy;

	t_mouse_pos				prev_mouse_pos;
	t_keys					keys;
	double					last_time;
	int						needs_redraw;
}	mlx_t;

#endif
