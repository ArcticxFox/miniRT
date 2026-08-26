/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 13:02:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:55:27 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_errors	parse_nov(char *str, double *NOV)
{
	t_errors		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

t_errors	parse_cyl_data(char **split, t_data *minirt)
{
	int	i;
	t_errors	ret;

	i = 0;
	ret = parse_coords(split[i], minirt->cylinder[minirt->cyl_count].coords,
			-DBL_MAX, DBL_MAX);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_nov(split[i], minirt->cylinder[minirt->cyl_count].threed_nov);
	if (ret != MRT_OK)
		return (ret);
	i++;
	if (!valid_float_number(split[i]))
		return (MRT_INVALID_NUM);
	minirt->cylinder[minirt->cyl_count].diameter = ft_atof(split[i]);
	i++;
	if (!valid_float_number(split[i]))
		return (MRT_INVALID_NUM);
	minirt->cylinder[minirt->cyl_count].height = ft_atof(split[i]);
	i++;
	ret = parse_colours(split[i], minirt->cylinder[minirt->cyl_count].rgb);
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	return (MRT_OK);
}

t_errors	cylinder_parse(char **split, t_data *minirt)
{
	int	ret;

	if (minirt->cyl_count == minirt->cyl_cap)
	{
		minirt->cylinder = ft_realloc(minirt->cylinder,
				minirt->cyl_cap * sizeof(*minirt->cylinder),
				(minirt->cyl_cap + 4) * sizeof(*minirt->cylinder));
		if (!minirt->cylinder)
			return (MRT_MALLOC);
		minirt->cyl_cap += 4;
	}
	ret = parse_cyl_data(split, minirt);
	minirt->cyl_count++;
	return (ret);
}
