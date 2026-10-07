/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:42:26 by ejones            #+#    #+#             */
/*   Updated: 2026/10/07 16:18:21 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTILS_H
# define RENDER_UTILS_H

# include "mini_rt.h"

int	hit_spheres(t_data *scene, t_ray ray, t_hit *hit, t_interval range);

bool		hit_planes(t_data *scene, t_ray ray, t_hit *hit, t_interval range);

bool		check_top_cap(t_cy cy, t_ray ray, t_hit *hit, t_interval range);
bool		check_bottom_cap(t_cy cy, t_ray ray, t_hit *hit, t_interval range);
bool		check_cylinder_root(t_cy cy, t_ray ray, t_hit *hit, double root);

bool		hit_cylinders(t_data *scene, t_ray ray, t_hit *hit,
				t_interval range);

bool		hit_object(t_mlx *mlx, t_ray ray, t_hit *hit);
void		fill_tab(t_mlx *mlx, t_ray *ray, mlx_color *tab_col, int size);

mlx_color	ray_color(t_mlx *mlx, t_ray ray);
t_ray		camera_ray(t_mlx *mlx, t_camera camera, int x, int y);
void		update_camera(t_mlx *mlx, double dt);

void		render_loop(void *param);

#endif
