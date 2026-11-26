/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 15:32:46 by ejones            #+#    #+#             */
/*   Updated: 2026/11/26 15:21:18 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_TYPES_H
# define EDITOR_TYPES_H

# include <stdbool.h>

typedef enum e_mode
{
	MODE_CAMERA,
	MODE_MOVE,
	MODE_SCALE,
	MODE_ROTATE
}	t_mode;

typedef enum e_obj_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_selection
{
	t_obj_type	type;
	int			index;
	bool		valid;
	double		r;
	double		h;
}	t_selection;

#endif
