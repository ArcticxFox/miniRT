/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 15:32:46 by ejones            #+#    #+#             */
/*   Updated: 2026/10/25 15:03:19 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_SELTION_H
# define OBJECT_SELTION_H

#include "mini_rt.h"

// typedef struct s_text_input
// {
// 	char	buffer[64];
// 	int		length;
// 	int		cursor;
// 	char	*label;
// 	int		x;
// 	int		y;
// 	int		width;
// 	int		height;
// 	bool	active;
// 	double	*target;
// }	t_text_input;

// typedef	struct s_editor
// {
// 	mlx_window				win;
// 	mlx_window_create_info	info;
// 	t_text_input			*input;
// 	t_text_input			*active_input;
// 	int						input_count;

// }	t_editor;

// void	init_editor_win(mlx_context *mlx, t_editor *editor);
# define KEY_M	16
# define KEY_C	6
# define KEY_R	21
# define KEY_S	22

typedef enum	e_mode
{
	MODE_CAMERA,
	MODE_MOVE,
	MODE_SCALE,
	MODE_ROTATE
}	t_mode;

// typedef struct s_selection
// {
// 	int		type;
// 	int		index;
// 	bool	valid;
// }	t_selection;

#endif
