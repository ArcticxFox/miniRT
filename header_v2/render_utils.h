/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:42:26 by ejones            #+#    #+#             */
/*   Updated: 2026/11/12 14:28:59 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTILS_H
# define RENDER_UTILS_H

# include "scene.h"
# include "render_types.h"
# include "input_types.h"
# include "../MacroLibX/includes/mlx.h"

//Intersections
bool		hit_sphere(t_sphere sp, t_ray ray, t_hit *hit, t_interval range);
bool		hit_spheres(t_data *scene, t_ray ray, t_hit *hit, t_interval range);

bool		hit_plane(t_pl pl, t_ray ray, t_hit *hit, t_interval range);
bool		hit_planes(t_data *scene, t_ray ray, t_hit *hit, t_interval range);

bool		check_top_cap(t_cy cy, t_ray ray, t_hit *hit, t_interval range);
bool		check_bottom_cap(t_cy cy, t_ray ray, t_hit *hit, t_interval range);
bool		check_cylinder_root(t_cy cy, t_ray ray, t_hit *hit, double root);

bool		hit_cylinder(t_cy cy, t_ray ray, t_hit *hit, t_interval range);
bool		hit_cylinders(t_data *scene, t_ray ray, t_hit *hit,
				t_interval range);

//Raytracing
mlx_color	ssaa(t_mlx *mlx, int x, int y);
mlx_color	ray_color(t_mlx *mlx, t_ray ray);
t_ray		camera_ray(t_mlx *mlx, t_camera camera, double x, double y);

//Rendering
void		fill_tab(t_mlx *mlx, t_ray *ray, mlx_color *tab_col, int size);
void		render_loop(void *param);
void		render_scene(t_mlx *mlx, t_camera camera);

//Object interactions
bool		hit_objects(t_mlx *mlx, t_ray ray, t_hit *hit, t_interval range);
bool		find_objects(t_mlx *mlx);
void		move_object(t_mlx *mlx);
void		scale_object(t_mlx *mlx);
double		get_distance(t_mlx *mlx, int mouse_x, int mouse_y);
void		rotate_objects(t_mlx *mlx);
void		update_camera(t_mlx *mlx, double dt);

#endif
