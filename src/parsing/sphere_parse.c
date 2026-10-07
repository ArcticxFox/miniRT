/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 08:50:45 by dlanehar          #+#    #+#             */
/*   Updated: 2026/10/07 14:16:10 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new;

	new = ft_calloc(new_size, sizeof(*ptr));
	if (!new)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			ft_memcpy(new, ptr, old_size);
		else
			ft_memcpy(new, ptr, new_size);
		free(ptr);
	}
	return (new);
}

t_errors	sphere_parse(char **split, t_data *minirt)
{
	int			i;
	t_errors	ret;

	i = 0;
	if (minirt->sph_count == minirt->sph_cap)
	{
		if (expand_obj_array(&minirt->sph_cap, (void **)&minirt->sphere,
				sizeof(*minirt->sphere)) != MRT_OK)
			return (MRT_MALLOC);
	}
	ret = parse_coords(split[i], &minirt->sphere[minirt->sph_count].center,
			-DBL_MAX, DBL_MAX);
	if (ret != MRT_OK)
		return (ret);
	i++;
	if (!valid_float_number(split[i]))
		return (MRT_INVALID_NUM);
	minirt->sphere[minirt->sph_count].d = ft_atof(split[i]);
	i++;
	ret = parse_colours(split[i], &minirt->sphere[minirt->sph_count].rgb);
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	minirt->sph_count++;
	return (ret);
}
