/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 11:48:07 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 14:36:48 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_nov(char *str, double *NOV)
{
	int		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

int	plane_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	if (minirt->pl_count == minirt->pl_cap)
	{
		minirt->pl_cap += 4;
		minirt->plane = ft_realloc(minirt->plane,
				minirt->pl_count * sizeof(*minirt->plane),
				minirt->pl_cap * sizeof(*minirt->plane));
	}
	ret = parse_coords(split[i], minirt->plane[minirt->pl_count].coords,
			-DBL_MAX, DBL_MAX);
	if (ret)
		return (1);
	i++;
	ret = parse_nov(split[i], minirt->plane[minirt->pl_count].threed_NOV);
	if (ret)
		return (1);
	i++;
	ret = parse_colours(split[i], minirt->plane[minirt->pl_count].RGB);
	if (split[i + 1] != NULL)
		return (1);
	minirt->pl_count++;
	return (ret);
}
