/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:21:42 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 14:27:43 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//turns all whitespace into spaces to use ft_split
static void	norm_whitespace(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] >= 7 && line[i] <= 13)
			line[i] = 32;
		i++;
	}
	return ;
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
int	parse_line(char *line, t_data *minirt)
{
	char			**split;
	t_parse_func	func;
	int				ret;

	ret = 1;
	if (!line)
	{
		return (1);
	}
	norm_whitespace(line);
	split = ft_split(line, ' ');
	if (!split)
		return (1);
	func = get_parse_func(split);
	if (func)
		ret = func(split + 1, minirt);
	ft_free_array(split);
	return (ret);
}
