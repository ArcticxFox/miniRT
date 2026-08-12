/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:51:26 by ejones            #+#    #+#             */
/*   Updated: 2026/08/09 16:53:48 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include "mini_rt.h"

void	init_window(mlx_t *mlx, mlx_window_create_info *info);

void	key_hook(int key, void* param);
void	window_hook(int event, void* param);

#endif
