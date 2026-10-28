/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:16:58 by ejones            #+#    #+#             */
/*   Updated: 2026/10/28 13:50:55 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	scale_sphere(t_mlx *mlx, t_data *scene, int mouse_x, int mouse_y)
{
	int		dx;
	int		dy;
	double	scale;

	dx = mouse_x - mlx->drag_start.x;
	dy = mouse_y - mlx->drag_start.y;
	scale = sqrt(dx * dx + dy * dy);
	scene->sphere[mlx->selected.index].r = mlx->selected.r * (1 + scale / 100);
}

void	scale_object(t_mlx *mlx)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(mlx->mlx, &mouse_x, &mouse_y);
	if (mlx->selected.type == OBJ_SPHERE)
		scale_sphere(mlx, &mlx->scene, mouse_x, mouse_y);
}
