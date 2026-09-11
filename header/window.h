/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:51:26 by ejones            #+#    #+#             */
/*   Updated: 2026/09/11 18:12:19 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include "mini_rt.h"

void	init_window(mlx_t *mlx);

void	key_hook(int key, void* param);
void	key_pressed(int key, void* param);
void	key_released(int key, void* param);

//move somewhere else maybe
double	get_time(void);

void	window_hook(int event, void* param);

#endif
