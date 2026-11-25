/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:29:14 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 19:22:27 by ejones           ###   ########.fr       */
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

# include "math_types.h"
# include "scene.h"
# include "render_types.h"
# include "input_types.h"
# include "app_types.h"
# include "bvh.h"
# include "bvh_types.h"

# include "arithmetics.h"
# include "render_utils.h"
# include "window.h"
# include "parsing.h"
# include "parerrors.h"

# define WINDOW_WIDTH	640.0
# define WINDOW_HEIGTH	360.0

# define KEY_DOWN		82
# define KEY_UP			81
# define KEY_LEFT		80
# define KEY_RIGHT		79

# define KEY_M			16
# define KEY_C			6
# define KEY_R			21
# define KEY_S			22


#endif
