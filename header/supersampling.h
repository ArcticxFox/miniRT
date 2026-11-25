/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersampling.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 17:19:48 by ejones            #+#    #+#             */
/*   Updated: 2026/11/25 18:06:36 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPERSAMPLING_H
# define SUPERSAMPLING_H

# define AA_THRESHOLD	900

# include "render_types.h"

t_ray	sub_ray(t_mlx *mlx, int pix[2], int sub[2]);
int		is_corner(int sub[2], int n);
int		needs_refine(mlx_color c[4]);

#endif
