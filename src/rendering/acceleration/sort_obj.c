/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:05:20 by ejones            #+#    #+#             */
/*   Updated: 2026/11/20 13:51:29 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"



double	get_axis_value(t_bvh *bvh, t_object *objs, int index, t_axis axis)
{
	t_object	*obj;
	t_vec		center;

	obj = &objs[bvh->objects[index].index];
	if (objs[index].type == OBJ_SPHERE)
		center = objs[index].data.sphere.center;
	else if (objs[index].type == OBJ_CYLINDER)
		center = objs[index].data.cylinder.center;
	else
		return (0.0);

}

int	partition(t_object_ref *refs, t_object *objs, int low, int high, t_axis axis)
{
	double	pivot;
	int	i;
	int	j;
	t_object	tmp;

	i = low;
	j = high;
	pivot = get_axis_value(objs, high, axis);
	while (1)
	{
		while (get_axis_value(objs, i, axis) < pivot)
			++i;
		while (get_axis_value(objs, j, axis) > pivot)
			--j;
		if (i >= j)
			return (j);
		tmp = objs[i];
		objs[i] = objs[j];
		objs[j] = tmp;
	}

}

void	quicksort(t_object_ref *refs, t_object *objs, int low, int high)
{
	int		piv;
	t_axis	axis;

	piv = 0;
	if (low < high)
	{
		axis = longest_axis(bvh);
		piv = partition(refs, objs, low, high, axis);
		quicksort(refs, objs, low, piv);
		quicksort(refs, objs, piv + 1, high);
	}
}
