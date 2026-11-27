/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:35:09 by ejones            #+#    #+#             */
/*   Updated: 2026/11/27 15:45:13 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_TYPES_H
# define APP_TYPES_H

# include "scene.h"
# include "render_types.h"
# include "input_types.h"
# include "editor_types.h"

# include "../MacroLibX/includes/mlx.h"
# include "../MacroLibX/includes/mlx_extended.h"

typedef struct s_mlx
{
	mlx_context				mlx;
	mlx_window				win;
	mlx_image				img;
	mlx_window_create_info	info;

	t_data					scene;
	t_render				render;

	t_mouse_pos				old_mouse_pos;
	t_keys					keys;
	double					last_time;
	int						needs_redraw;

	t_mode					mode;
	t_selection				selected;
	t_mouse_pos				drag_start;
	t_vec					object_start;
	t_vec					*object_dir;
	double					value_start;
}	t_mlx;

#endif
