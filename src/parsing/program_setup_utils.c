/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_setup_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:15:26 by dlanehar          #+#    #+#             */
/*   Updated: 2026/10/07 15:15:52 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parerrors.h"

t_errors	lsi_loop(char **res, t_data *minirt, int fd)
{
	while (*res)
	{
		if ((*res)[0] == '\0' || (*res)[0] == '\n')
		{
			free(*res);
			*res = get_next_line(fd);
		}
		else if (parse_line(*res, minirt) == MRT_OK)
		{
			free(*res);
			*res = get_next_line(fd);
		}
		else
		{
			while (1)
			{
				free(*res);
				*res = get_next_line(fd);
				if (!(*res))
					break ;
			}
			return (MRT_PARSE_LINE_ERR);
		}
	}
	return (MRT_OK);
}
