/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 16:32:45 by ejones            #+#    #+#             */
/*   Updated: 2026/10/25 20:16:33 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	update_selection(t_mlx *mlx, t_obj_type type, int index)
{
	mlx->selected.type = type;
	mlx->selected.index = index;
	mlx->selected.valid = true;
	mlx->needs_redraw = 1;
}

static bool	find_sphere(t_mlx *mlx, t_ray ray, t_hit *hit, t_interval range)
{
	int		i;
	t_hit	tmp;

	i = 0;
	while (i < mlx->scene.sph_count)
	{
		if (hit_sphere(mlx->scene.sphere[i], ray, &tmp, range))
		{
			*hit = tmp;
			range.max = hit->t;
			update_selection(mlx, OBJ_SPHERE, i);
		}
		++i;
	}
	return (mlx->selected.valid);
}

static bool	find_cylinder(t_mlx *mlx, t_ray ray, t_hit *hit, t_interval range)
{
	int		i;
	t_hit	tmp;

	i = 0;
	while (i < mlx->scene.cyl_count)
	{
		if (hit_cylinder(mlx->scene.cylinder[i], ray, &tmp, range))
		{
			*hit = tmp;
			range.max = hit->t;
			update_selection(mlx, OBJ_CYLINDER, i);
		}
		++i;
	}
	return (mlx->selected.valid);
}

static bool	find_plane(t_mlx *mlx, t_ray ray, t_hit *hit, t_interval range)
{
	int		i;
	t_hit	tmp;

	i = 0;
	while (i < mlx->scene.pl_count)
	{
		if (hit_plane(mlx->scene.plane[i], ray, &tmp, range))
		{
			*hit = tmp;
			range.max = hit->t;
			update_selection(mlx, OBJ_PLANE, i);
		}
		++i;
	}
	return (mlx->selected.valid);
}

bool	find_objects(t_mlx *mlx)
{
	t_interval	range;
	t_hit		hit;
	t_ray		ray;

	range.min = 0.001;
	range.max = DBL_MAX;
	ray = camera_ray(mlx, mlx->scene.camera,
		mlx->prev_mouse_pos.x, mlx->prev_mouse_pos.y);
	mlx->selected.valid = false;
	find_sphere(mlx, ray, &hit, range);
	if(mlx->selected.valid)
		range.max = hit.t;
	find_cylinder(mlx, ray, &hit, range);
	if(mlx->selected.valid)
		range.max = hit.t;
	find_plane(mlx, ray, &hit, range);
	return (mlx->selected.valid);
}
