/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 13:02:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 15:25:08 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_nov(char *str, double *NOV)
{
	int		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

int	parse_cyl_data(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	ret = parse_coords(split[i], minirt->cylinder[minirt->cyl_count].coords,
			-DBL_MAX, DBL_MAX);
	if (ret)
		return (1);
	i++;
	ret = parse_nov(split[i], minirt->cylinder[minirt->cyl_count].threed_NOV);
	if (ret)
		return (1);
	i++;
	if (!valid_float_number(split[i]))
		return (1);
	minirt->cylinder[minirt->cyl_count].diameter = ft_atof(split[i]);
	i++;
	if (!valid_float_number(split[i]))
		return (1);
	minirt->cylinder[minirt->cyl_count].height = ft_atof(split[i]);
	i++;
	ret = parse_colours(split[i], minirt->cylinder[minirt->cyl_count].RGB);
	if (split[i + 1] != NULL)
		return (1);
	return (0);
}

int	cylinder_parse(char **split, t_data *minirt)
{
	int	ret;

	if (minirt->cyl_count == minirt->cyl_cap)
	{
		minirt->cylinder = ft_realloc(minirt->cylinder,
				minirt->cyl_cap * sizeof(*minirt->cylinder),
				(minirt->cyl_cap + 4) * sizeof(*minirt->cylinder));
		if (!minirt->cylinder)
			return (1);
		minirt->cyl_cap += 4;
	}
	ret = parse_cyl_data(split, minirt);
	minirt->cyl_count++;
	return (ret);
}
