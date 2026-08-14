/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:04:24 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/14 15:13:06 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_helper(char **input, double *table, double lower, double upper)
{
	int		i;

	i = 0;
	while(input[i])
	{
		if (i >= 3)
			return (1);
		if (!valid_float_number(input[i]))
			return (1);
		table[i] = ft_atof(input[i]);
		if (table[i] < lower || table[i] > upper)
			return (1);
		i++;
	}
	return (0);
}

static int	parse_NOV(char *str, t_data *minirt)
{
	char 	**NOV;
	int		i;
	int		ret;

	NOV = split_multi_comma(str);
	if (!NOV)
		return (1);
	i = 0;
	while (NOV[i])
		i++;
	if (i > 3)
		return (1);
	ret = parse_helper(NOV, minirt->camera->threed_NOV, -1.0, 1.0);
	ft_free_array(NOV);
	return (0);
}

int	valid_float_number(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '.')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		if (!str[i])
			return (0);
		while (str[i])
		{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
		}
	}
	return (1);
}

static int	parse_coords(char *str, t_data *minirt)
{
	char	**coords;
	int		i;
	int		ret;

	coords = split_multi_comma(str);
	if (!coords)
		return (1);
	i = 0;
	while (coords[i])
		i++;
	if (i > 3)
		return (1);
	ret = parse_helper(coords, minirt->camera->viewpoint, -DBL_MAX, DBL_MAX);
	ft_free_array(coords);
	return (ret);
}

int	cam_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	minirt->camera = ft_calloc(1, sizeof(t_camera));
	if (!minirt->camera)
		return (1);
	ret = parse_coords(split[i], minirt);
	if (ret)
		return (ret);
	i++;
	ret = parse_NOV(split[i], minirt);
	if (ret)
		return (ret);
	i++;
	if (!valid_number(split[i]))
		return (1);
	minirt->camera->FOV = ft_atoi(split[i]);
	if (minirt->camera->FOV < 0 || minirt->camera->FOV > 180)
		return (1);
	if (split[i + 1] != NULL)
		return (1);
	return (0);
}
