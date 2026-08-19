/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:35:17 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 11:47:18 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	amb_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	if (!(ft_isdigit(split[i][0]) || split[i][0] == '+'))
		return (1);
	minirt->ambient_light.ratio = ft_atof(split[i]);
	if (minirt->ambient_light.ratio < 0 || minirt->ambient_light.ratio > 1)
		return (1);
	i++;
	ret = parse_colours(split[i], minirt->ambient_light.RGB);
	if (split[i + 1] != NULL)
		return (1);
	return (ret);
}
