/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:51:26 by ejones            #+#    #+#             */
/*   Updated: 2026/10/07 15:59:26 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mini_rt.h"

void	init_window(t_mlx *mlx);

void	key_hook(int key, void *param);
void	key_pressed(int key, void *param);
void	key_released(int key, void *param);
//tmp
void	mouse_down(int wheel, void *param);
void	mouse_up(int wheel, void *param);
//move somewhere else maybe
double	get_time(void);

void	window_hook(int event, void *param);

#endif
