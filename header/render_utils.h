/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:42:26 by ejones            #+#    #+#             */
/*   Updated: 2026/09/15 18:08:48 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	RENDER_UTILS_H
# define RENDER_UTILS_H

# include "mini_rt.h"

bool	hit_sphere(t_sphere sp, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax);
bool	hit_plane(t_pl	pl, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax);

bool	check_cylinder_root(t_cy cy, t_ray ray, t_hit *hit, double root, t_vec oc);
bool	hit_cylinder(t_cy cy, t_ray ray, t_hit *hit, double ray_tmin, double ray_tmax);

bool	hit_object(mlx_t *mlx, t_ray ray, t_hit *hit);
void	fill_tab(mlx_t *mlx, t_ray *ray, mlx_color	*tab_col);

mlx_color	ray_color(mlx_t *mlx, t_ray ray);
t_ray	camera_ray(mlx_t *mlx, t_camera camera, int x, int y);
void	update_camera(mlx_t *mlx, double dt);

void	render_loop(void *param);


#endif
