/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parerrors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:14:39 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 13:49:15 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARERRORS_H
# define PARERRORS_H

typedef enum e_errors {
	MRT_BAD_ARGS,
	MRT_FILENAME,
	MRT_MALLOC,
	MRT_INVALID_NUM,
	MRT_BAD_COLOUR,
	MRT_BAD_LIGHT_RATIO,
	MRT_BAD_NOV,
	MRT_BAD_FOV,
	MRT_BAD_BRIGHTNESS,
	MRT_PARSE_LINE_ERR,
	MRT_OUT_OF_BOUNDS,
	MRT_ERRNO,
	MRT_OK,
} t_errors;

void	print_error(t_errors error);

#endif
