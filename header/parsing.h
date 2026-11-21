/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 09:26:06 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/16 14:04:46 by ejones           ###   ########.fr       */
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


typedef t_errors	(*t_parse_func)(char **split, t_tmp_data *minirt);

typedef struct	s_parser
{
	char			*string;
	t_parse_func	func;
}	t_parser;

t_errors	program_setup(int ac, char **av, t_tmp_data *minirt);
t_errors	lsi_loop(char **res, t_tmp_data *minirt, int fd);

//============== PARSING ==============

t_errors	parse_line(char *line, t_tmp_data *minirt);

char		**split_multi_comma(char *str, t_errors *err);
t_errors	parse_colours(char *str, mlx_color *rgb);
int			valid_number(char *str);
int			valid_float_number(char *str);
t_errors	parse_float_array(char **input, t_vec *coords, double lower,
				double upper);
t_errors	parse_int_array(char **input, mlx_color *rgb, int lower, int upper);
t_errors	parse_coords(char *str, t_vec *coords, double lower, double upper);
void		*ft_realloc(void *ptr, int old_size, int new_size);

t_errors	amb_parse(char **split, t_tmp_data *minirt);
t_errors	cam_parse(char **split, t_tmp_data *minirt);
t_errors	light_parse(char **split, t_tmp_data *minirt);
t_errors	sphere_parse(char **split, t_tmp_data *minirt);
t_errors	plane_parse(char **split, t_tmp_data *minirt);
t_errors	cylinder_parse(char **split, t_tmp_data *minirt);

void		print_everything(t_tmp_data *minirt);
t_errors	expand_obj_array(int *cap, void **obj, size_t size);

#endif
