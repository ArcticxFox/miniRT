/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:13:59 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:14:29 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parerrors.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

void	print_error(t_errors error)
{
	const char *msg[] = {
		"Minirt is launched with one argument, the scene filename",
		"Scene must be named and must end in '.rt'. Example: scene.rt",
		"Malloc",
		"Object values must be numerical",
		"Colours must have a value between 0 - 255",
		"Lighting ratio must be between 0.0 - 1.0",
		"Normalised orientation vector must have a value between -1.0 - 1.0",
		"FOV must have a value between 0 - 180",
		"Brightness must have a value between 0.0 - 1.0",
		"Misconfiguration in scene file"
	};
	if (error != MRT_ERRNO)
		printf("Error\n%s\n", msg[error]);
	else
		printf("Error\n%s\n", strerror(errno));
}
