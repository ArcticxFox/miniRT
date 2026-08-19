/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:29:14 by ejones            #+#    #+#             */
/*   Updated: 2026/08/19 19:52:15 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <float.h>

# include "../MacroLibX/includes/mlx.h"
# include "../MacroLibX/includes/mlx_extended.h"

# include "struct.h"
# include "window.h"

# define	WINDOW_WIDTH	800.0;
# define	WINDOW_HEIGTH	600.0;

void	render_sphere(mlx_t *mlx, t_camera camera);

#endif
