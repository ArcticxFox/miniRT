/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 08:50:45 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 14:36:17 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	sphere_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	if (minirt->sph_count == minirt->sph_cap)
	{
		minirt->sph_cap += 4;
		minirt->sphere = ft_realloc(minirt->sphere,
				minirt->sph_count * sizeof(*minirt->sphere),
				minirt->sph_cap * sizeof(*minirt->sphere));
	}
	ret = parse_coords(split[i], minirt->sphere[minirt->sph_count].coords,
			-DBL_MAX, DBL_MAX);
	if (ret)
		return (1);
	i++;
	if (!valid_float_number(split[i]))
		return (1);
	minirt->sphere[minirt->sph_count].diameter = ft_atof(split[i]);
	i++;
	ret = parse_colours(split[i], minirt->sphere[minirt->sph_count].RGB);
	if (split[i + 1] != NULL)
		return (1);
	minirt->sph_count++;
	return (ret);
}
