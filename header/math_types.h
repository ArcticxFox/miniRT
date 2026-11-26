/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:37:06 by ejones            #+#    #+#             */
/*   Updated: 2026/11/26 15:22:09 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_TYPES_H
# define MATH_TYPES_H

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_quaternions
{
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quat;

#endif
