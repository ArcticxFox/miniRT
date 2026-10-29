/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 15:32:46 by ejones            #+#    #+#             */
/*   Updated: 2026/10/29 16:41:13 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_SELTION_H
# define OBJECT_SELTION_H

#include "mini_rt.h"


# define KEY_M	16
# define KEY_C	6
# define KEY_R	21
# define KEY_S	22

typedef enum	e_mode
{
	MODE_CAMERA,
	MODE_MOVE,
	MODE_SCALE,
	MODE_ROTATE
}	t_mode;



#endif
