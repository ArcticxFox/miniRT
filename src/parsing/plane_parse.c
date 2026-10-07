/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 11:48:07 by dlanehar          #+#    #+#             */
/*   Updated: 2026/10/07 14:16:28 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errors	expand_obj_array(int *cap, void **obj, size_t size)
{
	*obj = ft_realloc(*obj, *cap * size, (*cap + 4) * size);
	if (!(*obj))
		return (MRT_MALLOC);
	*cap += 4;
	return (MRT_OK);
}

static int	parse_nov(char *str, t_vec *NOV)
{
	int		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

t_errors	plane_parse(char **split, t_data *minirt)
{
	int			i;
	t_errors	ret;

	i = 0;
	if (minirt->pl_count == minirt->pl_cap)
	{
		if (expand_obj_array(&minirt->pl_cap, (void **)&minirt->plane,
				sizeof(*minirt->plane)) != MRT_OK)
			return (MRT_MALLOC);
	}
	ret = parse_coords(split[i], &minirt->plane[minirt->pl_count].point_in_py,
			-DBL_MAX, DBL_MAX);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_nov(split[i], &minirt->plane[minirt->pl_count].direction);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_colours(split[i], &minirt->plane[minirt->pl_count].rgb);
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	minirt->pl_count++;
	return (ret);
}
