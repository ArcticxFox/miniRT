/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:41:05 by ejones            #+#    #+#             */
/*   Updated: 2026/11/12 14:47:22 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_TYPE_H
# define INPUT_TYPE_H

# include <stdbool.h>

typedef struct	s_mouse_pos
{
	int	x;
	int	y;
}	t_mouse_pos;

typedef struct	s_keys
{
	bool	up;
	bool	down;
	bool	right;
	bool	left;
	bool	backwards;
	bool	forwards;
	bool	left_click;
	bool	right_click;
}	t_keys;

#endif
