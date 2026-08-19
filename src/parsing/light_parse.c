/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 08:01:09 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 14:34:50 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	light_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	ret = parse_coords(split[i], minirt->light.lightpoint, -DBL_MAX, DBL_MAX);
	if (ret)
		return (ret);
	i++;
	if (!valid_float_number(split[i]))
		return (1);
	minirt->light.brightness = ft_atof(split[i]);
	if (minirt->light.brightness < 0 || minirt->light.brightness > 1)
		return (1);
	if (split[i + 1] != NULL)
		return (1);
	return (0);
}
