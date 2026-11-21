/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:51:26 by ejones            #+#    #+#             */
/*   Updated: 2026/11/12 14:47:57 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "app_types.h"

void	init_window(t_mlx *mlx);

void	key_hook(int key, void *param);
void	key_pressed(int key, void *param);
void	key_released(int key, void *param);

void	mouse_down(int wheel, void *param);
void	mouse_up(int wheel, void *param);

void	window_hook(int event, void *param);

double	get_time(void);

#endif
