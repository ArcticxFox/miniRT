/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:21:29 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 09:21:52 by dlanehar         ###   ########.fr       */
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
