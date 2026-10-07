/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:29:14 by ejones            #+#    #+#             */
/*   Updated: 2026/10/07 15:59:26 by dlanehar         ###   ########.fr       */
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
# include <sys/time.h>

# include "../MacroLibX/includes/mlx.h"
# include "../MacroLibX/includes/mlx_extended.h"

# include "arithmetics.h"
# include "scene.h"
# include "window.h"
# include "render_utils.h"
# include "parsing.h"
# include "parerrors.h"

# define WINDOW_WIDTH	640.0
# define WINDOW_HEIGTH	360.0

# define KEY_DOWN		82
# define KEY_UP			81
# define KEY_LEFT		80
# define KEY_RIGHT		79

void	render_scene(t_mlx *mlx, t_camera camera);

#endif
