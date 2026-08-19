/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:21:29 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 15:36:14 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_coords(char *str, double *table, double lower, double upper)
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
	{
		ft_free_array(coords);
		return (1);
	}
	ret = parse_float_array(coords, table, lower, upper);
	ft_free_array(coords);
	return (ret);
}

int	parse_int_array(char **input, int *table, int lower, int upper)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (i >= 3)
			return (1);
		if (!valid_number(input[i]))
			return (1);
		table[i] = ft_atoi(input[i]);
		if (table[i] < lower || table[i] > upper)
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

int	parse_float_array(char **input, double *table, double lower, double upper)
{
	int		i;

	i = 0;
	while (input[i])
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
	if (i != 3)
		return (1);
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

//checks if the given string is all letters
// int	check_alpha(char *string)
// {
// 	int	i;

// 	i = 0;
// 	if (!string)
// 		return (0);
// 	while (string[i])
// 	{
// 		if (!ft_isalpha(string[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

char	**split_multi_comma(char *str)
{
	int		i;
	int		len;
	char	**res;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	if (str[0] == ',' || str[len - 1] == ',')
		return (NULL);
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (NULL);
		i++;
	}
	res = ft_split(str, ',');
	if (!res)
		return (NULL);
	return (res);
}

// int	valid_number(char *str)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	if (str[0] == '+' || str[0] == '-')
// 		i++;
// 	if (!str[i])
// 		return (0);
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int	parse_colours(char *str, int *colour_tab)
{
	char	**colours;
	int		ret;

	colours = split_multi_comma(str);
	if (!colours)
		return (1);
	ret = parse_int_array(colours, colour_tab, 0, 255);
	ft_free_array(colours);
	return (0);
}
