/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 15:42:26 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 16:07:46 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTILS_H
# define RENDER_UTILS_H

# include "scene.h"
# include "render_types.h"
# include "input_types.h"
# include "../MacroLibX/includes/mlx.h"

int			init_scene(t_tmp_data *tmp, t_data *scene);
void		free_tmp_data(t_tmp_data *minirt);

//Intersections
bool		hit_sphere(t_sphere *sp, t_query *query);
bool		hit_plane(t_pl *pl, t_query *query);
bool		hit_cylinder(t_cy *cy, t_query *query);


//Raytracing
mlx_color	ssaa(t_mlx *mlx, int x, int y);
mlx_color	ray_color(t_mlx *mlx, t_ray ray);
void		camera_init(t_camera *cam, int width, int height);
t_ray		camera_ray(t_mlx *mlx, const t_camera *camera, double x, double y);

//Rendering
void		fill_tab(t_mlx *mlx, t_ray *ray, mlx_color *tab_col, int size);
void		render_loop(void *param);
void		render_scene(t_mlx *mlx);
void		render_moving_scene(t_mlx *mlx, t_camera *camera);

//Object interactions
bool		hit_object(t_object *obj, t_query *query);
bool		hit_objects(t_objects *items, t_query *query);
bool		hit_objects(t_objects *items, t_query *query);
bool		find_objects(t_mlx *mlx);
void		move_object(t_mlx *mlx);
double		get_distance(t_mlx *mlx, int mouse_x, int mouse_y);
void		scale_object(t_mlx *mlx);
double		get_distance(t_mlx *mlx, int mouse_x, int mouse_y);
void		rotate_objects(t_mlx *mlx);
void		update_camera(t_mlx *mlx, double dt);

#endif
