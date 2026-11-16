/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 13:02:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/02 16:08:48 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_errors	parse_nov(char *str, t_vec *NOV)
{
	t_errors		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

t_errors	parse_positive_float(char *input, double *value)
{
	if (!valid_float_number(input))
		return (MRT_INVALID_NUM);
	*value = ft_atof(input);
	if (*value <= 0)
		return (MRT_NEGATIVE_VALUE);
	return (MRT_OK);
}

t_errors	parse_cyl_data(char **split, t_cy *cyl)
{
	int			i;
	t_errors	ret;

	i = 0;
	ret = parse_coords(split[i], &cyl->center, -DBL_MAX, DBL_MAX);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_nov(split[i], &cyl->axis_dir);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_positive_float(split[i], &cyl->d);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_positive_float(split[i], &cyl->h);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_colours(split[i], &cyl->rgb);
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	return (ret);
}

t_errors	cylinder_parse(char **split, t_data *minirt)
{
	t_errors	ret;
	t_cy		*current_cyl;

	current_cyl = &minirt->cylinder[minirt->cyl_count];
	if (minirt->cyl_count == minirt->cyl_cap)
	{
		if (expand_obj_array(&minirt->cyl_cap, (void **)&minirt->cylinder,
				sizeof(*minirt->cylinder)) != MRT_OK)
			return (MRT_MALLOC);
	}
	ret = parse_cyl_data(split, current_cyl);
	minirt->cyl_count++;
	return (ret);
}
