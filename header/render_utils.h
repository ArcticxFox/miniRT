/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:42:26 by ejones            #+#    #+#             */
/*   Updated: 2026/08/22 19:39:00 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	RENDER_UTILS_H
# define RENDER_UTILS_H

# include "mini_rt.h"

bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax);
bool	hit_plane(t_pl	pl, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax);

bool	check_cylinder_root(t_cy cy, t_ray ray, t_hit *hit, double root, t_vec oc);
bool	hit_cylinder(t_cy cy, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax);

#endif
