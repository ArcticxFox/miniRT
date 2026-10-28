/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_setup_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:15:26 by dlanehar          #+#    #+#             */
/*   Updated: 2026/10/28 13:44:42 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parerrors.h"

t_errors	lsi_loop(char **res, t_data *minirt, int fd)
{
	t_errors	err;
	while (*res)
	{
		if ((*res)[0] == '\0' || (*res)[0] == '\n')
		{
			free(*res);
			*res = get_next_line(fd);
		}
		else
		{
			err = parse_line(*res, minirt);
			if (err != MRT_OK)
			{
				while (1)
				{
					free(*res);
					*res = get_next_line(fd);
					if (!(*res))
						break ;
				}
				return (err);
			}
			free(*res);
			*res = get_next_line(fd);
		}
	}
	return (MRT_OK);
}
