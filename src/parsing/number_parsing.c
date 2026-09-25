/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:35:08 by dlanehar          #+#    #+#             */
/*   Updated: 2026/09/24 17:53:56 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errors	parse_int_array(char **input, mlx_color *rgb, int lower, int upper)
{
	int		i;
	uint8_t		*colour[3];

	colour[0] = &rgb->r;
	colour[1] = &rgb->g;
	colour[2] = &rgb->b;
	i = 0;
	while (input[i])
	{
		if (i >= 3)
			return (MRT_PARSE_LINE_ERR);
		if (!valid_number(input[i]))
			return (MRT_INVALID_NUM);
		*colour[i] = (uint8_t)ft_atoi(input[i]);
		if (*colour[i] < lower || *colour[i] > upper)
			return (MRT_OUT_OF_BOUNDS);
		i++;
	}
	if (i != 3)
		return (1);
	return (MRT_OK);
}

t_errors	parse_float_array(char **input, t_vec *coords, double lower, double upper)
{
	int				i;
	double	*coordinate[3];

	coordinate[0] = &coords->x;
	coordinate[1] = &coords->y;
	coordinate[2] = &coords->z;
	i = 0;
	while (input[i])
	{
		if (i >= 3)
			return (MRT_PARSE_LINE_ERR);
		if (!valid_float_number(input[i]))
			return (MRT_INVALID_NUM);
		*coordinate[i] = ft_atof(input[i]);
		if (*coordinate[i] < lower || *coordinate[i] > upper)
			return (MRT_OUT_OF_BOUNDS);
		i++;
	}
	if (i != 3)
		return (MRT_PARSE_LINE_ERR);
	return (MRT_OK);
}

int	valid_number(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	loop_thru_str(char *str, int i)
{
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

int	valid_float_number(char *str)
{
	int	i;
	int	ret;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	ret = loop_thru_str(str, i);
	return (ret);
}
