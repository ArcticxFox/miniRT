/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:35:17 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/11 11:36:26 by dlanehar         ###   ########.fr       */
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
	minirt->ambient_light = ft_calloc(1, sizeof(t_amb_light));
	minirt->ambient_light->ratio = ft_atof(split[i]);
	if (minirt->ambient_light->ratio < 0 || minirt->ambient_light->ratio > 1)
		return (1);
	i++;
	ret = parse_colours(split[i], minirt);
	return (ret);
}
