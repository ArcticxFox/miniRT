/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_setup_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:15:26 by dlanehar          #+#    #+#             */
/*   Updated: 2026/11/16 14:04:46 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parerrors.h"

t_errors	lsi_loop(char **res, t_tmp_data *minirt, int fd)
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
