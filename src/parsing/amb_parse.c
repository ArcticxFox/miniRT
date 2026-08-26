/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:35:17 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:53:22 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errors	amb_parse(char **split, t_data *minirt)
{
	int			i;
	t_errors	ret;

	i = 0;
	if (!(ft_isdigit(split[i][0]) || split[i][0] == '+'))
		return (MRT_INVALID_NUM);
	minirt->ambient_light.ratio = ft_atof(split[i]);
	if (minirt->ambient_light.ratio < 0 || minirt->ambient_light.ratio > 1)
		return (MRT_BAD_LIGHT_RATIO);
	i++;
	ret = parse_colours(split[i], minirt->ambient_light.rgb);
	if (ret == MRT_OUT_OF_BOUNDS)
		ret = MRT_BAD_COLOUR;
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	return (ret);
}
