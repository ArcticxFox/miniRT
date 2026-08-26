/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:04:24 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:54:11 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_nov(char *str, double *NOV)
{
	int		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

t_errors	cam_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	ret = parse_coords(split[i], minirt->camera.viewpoint, -DBL_MAX, DBL_MAX);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_nov(split[i], minirt->camera.threed_nov);
	if (ret != MRT_OK)
		return (ret);
	i++;
	if (!valid_number(split[i]))
		return (MRT_INVALID_NUM);
	minirt->camera.fov = ft_atoi(split[i]);
	if (minirt->camera.fov < 0 || minirt->camera.fov > 180)
		return (MRT_OUT_OF_BOUNDS);
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	return (MRT_OK);
}
