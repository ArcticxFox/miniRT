/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 15:48:10 by ejones            #+#    #+#             */
/*   Updated: 2026/11/26 15:24:31 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdbool.h>
# include "math_types.h"
# include "editor_types.h"
# include "bvh_types.h"
# include "../MacroLibX/includes/mlx.h"

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

typedef struct s_object
{
	t_obj_type	type;
	union
	{
		t_sphere	sphere;
		t_pl		plane;
		t_cy		cylinder;
	}	data;
}	t_object;

typedef struct s_objects
{
	t_object	*objects;
	t_bvh		bvh;
	int			count;
	int			pl_count;
	int			capacity;
}	t_objects;

typedef struct s_camera
{
	t_vec	origin;
	t_vec	threed_nov;
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	double	fov;
}	t_camera;

typedef struct s_tmp_data
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
}	t_tmp_data;

typedef struct s_data
{
	t_amb_light	ambient_light;
	t_camera	camera;
	t_light		light;
	t_objects	items;
}	t_data;

#endif
