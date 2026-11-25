/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:22:17 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 16:25:34 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	fill_spheres(t_tmp_data *tmp, t_object *obj)
{
	int	i;

	i = 0;
	while (i < tmp->sph_count)
	{
		obj[i].data.sphere = tmp->sphere[i];
		obj[i].type = OBJ_SPHERE;
		++i;
	}
	return (i);
}

static int	fill_cylinders(t_tmp_data *tmp, t_object *obj)
{
	int	i;

	i = 0;
	while (i < tmp->cyl_count)
	{
		obj[i].data.cylinder = tmp->cylinder[i];
		obj[i].type = OBJ_CYLINDER;
		++i;
	}
	return (i);
}

static int	fill_planes(t_tmp_data *tmp, t_object *obj)
{
	int	i;

	i = 0;
	while (i < tmp->pl_count)
	{
		obj[i].data.plane = tmp->plane[i];
		obj[i].type = OBJ_PLANE;
		++i;
	}
	return (i);
}

static void	fill_objects(t_tmp_data *tmp, t_object *obj)
{
	int	n;
	n = fill_spheres(tmp, obj);
	n += fill_cylinders(tmp, obj + n);
	fill_planes(tmp, obj + n);
}

int	init_scene(t_tmp_data *tmp, t_data *scene)
{
	scene->ambient_light = tmp->ambient_light;
	scene->light = tmp->light;
	scene->camera = tmp->camera;
	scene->items.capacity = tmp->cyl_cap + tmp->pl_cap + tmp->sph_cap;
	scene->items.count = tmp->pl_count + tmp->sph_count + tmp->cyl_count;
	scene->items.objects = ft_calloc(scene->items.count, sizeof(t_object));
	if (!scene->items.objects)
		return (MRT_MALLOC);
	fill_objects(tmp, scene->items.objects);
	scene->items.pl_count = tmp->pl_count;
		if (init_bvh(&scene->items.bvh, &scene->items))
	{
		free_bvh(&scene->items.bvh);
		free(scene->items.objects);
		return (MRT_MALLOC);
	}
	free_tmp_data(tmp);
	return (MRT_OK);
}
