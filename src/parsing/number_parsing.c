/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:35:08 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:38:08 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errors	parse_int_array(char **input, int *table, int lower, int upper)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (i >= 3)
			return (MRT_PARSE_LINE_ERR);
		if (!valid_number(input[i]))
			return (MRT_INVALID_NUM);
		table[i] = ft_atoi(input[i]);
		if (table[i] < lower || table[i] > upper)
			return (MRT_OUT_OF_BOUNDS);
		i++;
	}
	if (i != 3)
		return (1);
	return (MRT_OK);
}

t_errors	parse_float_array(char **input, double *table, double lower, double upper)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (i >= 3)
			return (MRT_PARSE_LINE_ERR);
		if (!valid_float_number(input[i]))
			return (MRT_INVALID_NUM);
		table[i] = ft_atof(input[i]);
		if (table[i] < lower || table[i] > upper)
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
