/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:21:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 14:55:26 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//turns all whitespace into spaces to use ft_split
static int	norm_whitespace(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] >= 7 && line[i] <= 13)
			line[i] = 32;
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

static t_parse_func	get_parse_func(char **split)
{
	int				i;
	const t_parser	funcs[] = {
	{"A", amb_parse},
	{"C", cam_parse},
	{"L", light_parse},
	{"sp", sphere_parse},
	{"pl", plane_parse},
	{"cy", cylinder_parse}
	};

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(split[0], funcs[i].string) == 0)
			return (funcs[i].func);
		i++;
	}
	return (NULL);
}

//parses the line
t_errors	parse_line(char *line, t_data *minirt)
{
	char			**split;
	t_parse_func	func;
	int				ret;

	ret = MRT_OK;
	if (!line)
	{
		return (1);
	}
	if (!norm_whitespace(line))
		return (MRT_PARSE_LINE_ERR);
	split = ft_split(line, ' ');
	if (!split)
		return (MRT_MALLOC);
	func = get_parse_func(split);
	if (func)
		ret = func(split + 1, minirt);
	else
		ret = MRT_PARSE_LINE_ERR;
	ft_free_array(split);
	return (ret);
}
