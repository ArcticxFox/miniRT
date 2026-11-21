/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:39:55 by ejones            #+#    #+#             */
/*   Updated: 2026/11/21 19:28:12 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_TYPES_H
# define BVH_TYPES_H

# include "math_types.h"
# include "editor_types.h"
# include "render_types.h"

# define LEAF_MAX	4

struct	s_object;

typedef enum	e_axis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z
}	t_axis;

typedef enum	e_bvh_node_type
{
	BVH_INTERNAL,
	BVH_LEAF
}	t_bvh_node_type;

typedef struct	s_range
{
	int	start;
	int	end;
}	t_range;

typedef struct s_object_ref
{
	t_obj_type	type;
	int			index;
}	t_object_ref;

typedef struct	s_aabb
{
	t_vec	min;
	t_vec	max;
}	t_aabb;

typedef struct	s_bvh_node
{
	t_aabb				bounds;
	union
	{
		struct
		{
			struct s_bvh_node	*left;
			struct s_bvh_node	*right;
		}	children;
		struct
		{
			int	start;
			int	count;
		}	leaf;

	};
	bool	is_leaf;
}	t_bvh_node;

typedef struct	s_bvh
{
	t_bvh_node			*node;
	t_bvh_node			*root;
	struct s_object		*scene;
	t_object_ref		*objects;
	int					node_count;
	int					node_capacity;
	int					object_count;
}	t_bvh;

typedef struct s_query
{
	t_ray		ray;
	t_interval	iv;
	t_hit		*hit;
}	t_query;

#endif
