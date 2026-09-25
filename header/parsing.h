/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 09:26:06 by dlanehar          #+#    #+#             */
/*   Updated: 2026/09/24 17:46:00 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "mini_rt.h"
# include "arithmetics.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <limits.h>
# include <float.h>
# include <math.h>
# include "parerrors.h"

// typedef struct s_cylinder
// {
// 	t_vec		center;
// 	t_vec		axis_dir;
// 	double		d;
// 	double		h;
// 	mlx_color	rgb;
// }	t_cylinder;

// typedef struct s_plane
// {
// 	t_vec		point_in_py;
// 	t_vec		direction;
// 	mlx_color	rgb;
// }	t_plane;

// typedef struct s_sphere
// {
// 	t_vec		center;
// 	double		r;
// 	double		d;
// 	mlx_color	rgb;
// }	t_sphere;

// typedef struct s_light
// {
// 	t_vec	lightpoint;
// 	double	brightness;
// }	t_light;

// typedef struct s_camera
// {
// 	t_vec	origin;
// 	t_vec	threed_nov;
// 	double	fov;
// }	t_camera;

// typedef struct s_amb_light
// {
// 	double		ratio;
// 	mlx_color	rgb;
// }	t_amb_light;

// typedef struct s_data
// {
// 	t_amb_light	ambient_light;
// 	t_camera	camera;
// 	t_light		light;
// 	t_sphere	*sphere;
// 	int			sph_cap;
// 	int			sph_count;
// 	t_pl		*plane;
// 	int			pl_cap;
// 	int			pl_count;
// 	t_cy		*cylinder;
// 	int			cyl_cap;
// 	int			cyl_count;
// }	t_data;

typedef t_errors	(*t_parse_func)(char **split, t_data *minirt);

typedef struct s_parser
{
	char			*string;
	t_parse_func	func;
}	t_parser;

t_errors	program_setup(int ac, char **av, t_data *minirt);

//============== PARSING ==============

t_errors	parse_line(char *line, t_data *minirt);

char	**split_multi_comma(char *str, t_errors *err);
t_errors		parse_colours(char *str, mlx_color *rgb);
int		valid_number(char *str);
int		valid_float_number(char *str);
t_errors	parse_float_array(char **input, t_vec *coords, double lower,
			double upper);
t_errors	parse_int_array(char **input, mlx_color *rgb, int lower, int upper);
t_errors	parse_coords(char *str, t_vec *coords, double lower, double upper);
void		*ft_realloc(void *ptr, int old_size, int new_size);

t_errors	amb_parse(char **split, t_data *minirt);
t_errors	cam_parse(char **split, t_data *minirt);
t_errors	light_parse(char **split, t_data *minirt);
t_errors	sphere_parse(char **split, t_data *minirt);
t_errors	plane_parse(char **split, t_data *minirt);
t_errors	cylinder_parse(char **split, t_data *minirt);

void	print_everything(t_data *minirt);

#endif
