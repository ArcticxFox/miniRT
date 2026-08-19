/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:04:24 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 14:34:32 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_nov(char *str, double *NOV)
{
	int		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

int	cam_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	ret = parse_coords(split[i], minirt->camera.viewpoint, -DBL_MAX, DBL_MAX);
	if (ret)
		return (ret);
	i++;
	ret = parse_nov(split[i], minirt->camera.threed_NOV);
	if (ret)
		return (ret);
	i++;
	if (!valid_number(split[i]))
		return (1);
	minirt->camera.FOV = ft_atoi(split[i]);
	if (minirt->camera.FOV < 0 || minirt->camera.FOV > 180)
		return (1);
	if (split[i + 1] != NULL)
		return (1);
	return (0);
}
