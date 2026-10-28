/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:48:10 by ejones            #+#    #+#             */
/*   Updated: 2026/10/28 13:04:36 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mini_rt.h"

# define HEIGHT 60
# define WIDTH 148

//============================================================================//
//									OBJECTS									  //
//============================================================================//

typedef struct s_amb_light
{
	double		ratio;
	mlx_color	rgb;
}	t_amb_light;

typedef struct s_light
{
	t_vec	lightpoint;
	double	brightness;
}	t_light;

typedef struct s_sphere
{
	t_vec		center;
	double		r;
	double		d;
	mlx_color	rgb;
}	t_sphere;

typedef struct s_plane
{
	t_vec		point_in_py;
	t_vec		direction;
	mlx_color	rgb;
}	t_pl;

typedef struct s_cylinder
{
	t_vec		center;
	t_vec		axis_dir;
	double		d;
	double		h;
	mlx_color	rgb;
	double		r;
}	t_cy;

typedef enum	e_obj_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;


//============================================================================//
//								HELPER
//============================================================================//

typedef struct s_selection
{
	t_obj_type	type;
	int			index;
	bool		valid;
	double		r;
	double		h;
}	t_selection;

typedef struct s_hit
{
	double		t;
	t_vec		point;
	t_vec		normal;
	mlx_color	color;
}	t_hit;

typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

typedef struct s_mouse_pos
{
	int	x;
	int	y;
}	t_mouse_pos;

//============================================================================//

typedef struct s_keys
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

typedef struct s_camera
{
	t_vec	origin;
	t_vec	threed_nov;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	fov;
}	t_camera;

typedef struct s_data
{
	t_amb_light	ambient_light;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	int			sph_cap;
	int			sph_count;
	t_pl		*plane;
	int			pl_cap;
	int			pl_count;
	t_cy		*cylinder;
	int			cyl_cap;
	int			cyl_count;
}	t_data;

typedef struct s_mlx
{
	mlx_context				mlx;
	mlx_window				win;
	mlx_image				img;
	mlx_window_create_info	info;

	t_data					scene;

	t_mouse_pos				prev_mouse_pos;
	t_keys					keys;
	double					last_time;
	int						needs_redraw;

	t_mode					mode;
	t_selection				selected;
	t_mouse_pos				drag_start;
	t_vec					object_start;
	double					value_start;
}	t_mlx;

#endif
