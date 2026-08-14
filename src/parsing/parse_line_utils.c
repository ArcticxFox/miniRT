/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:21:29 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/14 15:09:00 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//checks if the given string is all letters
int	check_alpha(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (!ft_isalpha(string[i]))
			return (0);
		i++;
	}
	return (1);
}

// checks if the given string matech any valid identifier. If no valid identifier, throws an error.
int	find_input_type(char *string)
{
	int	len;

	len = ft_strlen(string);
	if (ft_strncmp(string, "A", len) == 0)
		return (10);
	else if (ft_strncmp(string, "C", len) == 0)
		return (20);
	else if (ft_strncmp(string, "L", len) == 0)
		return (30);
	else if (ft_strncmp(string, "sp", len) == 0)
		return (40);
	else if (ft_strncmp(string, "pl", len) == 0)
		return (50);
	else if (ft_strncmp(string, "cy", len) == 0)
		return (60);
	return (0);
}

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

int	parse_colours(char *str, t_data *minirt)
{
	char **colours;
	int		i;

	colours = split_multi_comma(str);
	if (!colours)
		return (1);
	i = 0;
	while (colours[i])
	{
		if (!valid_number(colours[i]))
		{
			ft_free_array(colours);
			return (1);
		}
		minirt->ambient_light->RGB[i] = ft_atoi(colours[i]);
		if (minirt->ambient_light->RGB[i] < 0 || minirt->ambient_light->RGB[i] > 256)
		{
			ft_free_array(colours);
			return (1);
		}
		i++;
	}
	ft_free_array(colours);
	return (0);
}
