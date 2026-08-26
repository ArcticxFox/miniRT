/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 09:26:06 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:36:22 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <limits.h>
# include <float.h>
# include <math.h>
# include "parerrors.h"

typedef struct s_cylinder
{
	double	coords[3];
	double	threed_nov[3];
	double	diameter;
	double	height;
	int		rgb[3];
}	t_cylinder;

typedef struct s_plane
{
	double	coords[3];
	double	threed_nov[3];
	int		rgb[3];
}	t_plane;

typedef struct s_sphere
{
	double	coords[3];
	double	diameter;
	int		rgb[3];
}	t_sphere;

typedef struct s_light
{
	double	lightpoint[3];
	double	brightness;
}	t_light;

typedef struct s_camera
{
	double	viewpoint[3];
	double	threed_nov[3];
	double	fov;
}	t_camera;

typedef struct s_amb_light
{
	double	ratio;
	int		rgb[3];
}	t_amb_light;

typedef struct s_data
{
	t_amb_light	ambient_light;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	int			sph_cap;
	int			sph_count;
	t_plane		*plane;
	int			pl_cap;
	int			pl_count;
	t_cylinder	*cylinder;
	int			cyl_cap;
	int			cyl_count;
}	t_data;

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
t_errors		parse_colours(char *str, int *colour_tab);
int		valid_number(char *str);
int		valid_float_number(char *str);
t_errors	parse_float_array(char **input, double *table, double lower,
			double upper);
t_errors	parse_int_array(char **input, int *table, int lower, int upper);
t_errors	parse_coords(char *str, double *table, double lower, double upper);
void		*ft_realloc(void *ptr, int old_size, int new_size);

t_errors	amb_parse(char **split, t_data *minirt);
t_errors	cam_parse(char **split, t_data *minirt);
t_errors	light_parse(char **split, t_data *minirt);
t_errors	sphere_parse(char **split, t_data *minirt);
t_errors	plane_parse(char **split, t_data *minirt);
t_errors	cylinder_parse(char **split, t_data *minirt);

void	print_everything(t_data *minirt);

#endif
