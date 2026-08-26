/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 08:01:09 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:55:27 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errors	light_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	ret = parse_coords(split[i], minirt->light.lightpoint, -DBL_MAX, DBL_MAX);
	if (ret != MRT_OK)
		return (ret);
	i++;
	if (!valid_float_number(split[i]))
		return (MRT_INVALID_NUM);
	minirt->light.brightness = ft_atof(split[i]);
	if (minirt->light.brightness < 0 || minirt->light.brightness > 1)
		return (MRT_OUT_OF_BOUNDS);
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	return (MRT_OK);
}
