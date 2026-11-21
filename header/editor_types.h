/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:37:48 by ejones            #+#    #+#             */
/*   Updated: 2026/11/12 14:47:32 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_TYPES_H
# define EDITOR_TYPES_H

# include <stdbool.h>

typedef enum	e_mode
{
	MODE_CAMERA,
	MODE_MOVE,
	MODE_SCALE,
	MODE_ROTATE
}	t_mode;

typedef enum	e_obj_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct	s_selection
{
	t_obj_type	type;
	int			index;
	bool		valid;
	double		r;
	double		h;
}	t_selection;

#endif
