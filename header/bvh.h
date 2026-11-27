/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:51:35 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 16:57:48 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "bvh_types.h"

/*======= bvh_range.c =========*/

double	vec_axis(t_vec v, t_axis axis);
int		longest_axis(t_aabb bounds);
t_aabb	ref_aabb(t_bvh *bvh, int i);
t_aabb	range_bounds(t_bvh *bvh, t_range r);
double	centroid(t_bvh *bvh, int i, t_axis axis);
int		split_range(t_bvh *bvh, t_range r, t_aabb bounds);

/*========= bvh_hit_aabb.c ===========*/

bool	hit_aabb(t_ray ray, t_aabb box, t_interval interval);

/*=========== bvh_aabb.c =============*/

t_aabb	surrounding_box(t_aabb a, t_aabb b);
t_aabb	sphere_aabb(t_sphere sphere);
t_aabb	cylinder_aabb(t_cy cy);
t_aabb	object_aabb(t_object *obj);

int		init_bvh(t_bvh *bvh, t_objects *objs);
void	free_bvh(t_bvh *bvh);
bool	hit_bvh(t_bvh *bvh, t_query *q);
void	rebuild_bvh(t_bvh *bvh, t_objects *objs);

#endif
