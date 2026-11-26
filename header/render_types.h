/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:40:20 by ejones            #+#    #+#             */
/*   Updated: 2026/11/26 15:23:08 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_TYPES_H
# define RENDER_TYPES_H

# include <stdbool.h>
# include "math_types.h"
# include "scene.h"
# include "../MacroLibX/includes/mlx.h"

typedef struct s_hit
{
	double		t;
	t_vec		point;
	t_vec		normal;
	mlx_color	color;
}	t_hit;

typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

typedef struct s_render
{
	int		x;
	int		y;
	int		samples;
	bool	active;
	bool	moving;
}	t_render;

#endif
