/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:21:29 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:47:38 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errors	parse_coords(char *str, double *table, double lower, double upper)
{
	char	**coords;
	int		i;
	t_errors		ret;

	coords = split_multi_comma(str, &ret);
	if (!coords)
		return (ret);
	i = 0;
	while (coords[i])
		i++;
	if (i > 3)
	{
		ft_free_array(coords);
		return (MRT_PARSE_LINE_ERR);
	}
	ret = parse_float_array(coords, table, lower, upper);
	ft_free_array(coords);
	return (ret);
}

char	**split_multi_comma(char *str, t_errors *err)
{
	int		i;
	int		len;
	char	**res;

	*err = MRT_OK;
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
	{
		*err = MRT_MALLOC;
		return (NULL);
	}
	return (res);
}

t_errors	parse_colours(char *str, int *colour_tab)
{
	char		**colours;
	t_errors	ret;

	ret = MRT_OK;
	colours = split_multi_comma(str, &ret);
	if (!colours)
		return (ret);
	ret = parse_int_array(colours, colour_tab, 0, 255);
	ft_free_array(colours);
	return (ret);
}
