/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:21:48 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/26 15:50:11 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parerrors.h"

t_errors	load_scene_info(char *filename, t_data *minirt)
{
	int		fd;
	char	*res;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (MRT_ERRNO);
	res = get_next_line(fd);
	while (res)
	{
		if (res[0] == '\0' || res[0] == '\n')
		{
			free(res);
			res = get_next_line(fd);
		}
		else if (parse_line(res, minirt) == MRT_OK)
		{
			free(res);
			res = get_next_line(fd);
		}
		else
		{
			while (1)
			{
				free(res);
				res = get_next_line(fd);
				if (!res)
					break ;
			}
			return (MRT_PARSE_LINE_ERR);
		}
	}
	close(fd);
	return (MRT_OK);
}

int	file_name_check(char *filename)
{
	char	*str;
	int		len;

	if (ft_strlen(filename) <= ft_strlen(".rt"))
		return (1);
	str = ft_strchr(filename, '.');
	if (!str)
		return (1);
	len = ft_strlen(str);
	if (ft_strncmp(str, ".rt", len) != 0)
		return (1);
	return (0);
}

int	input_parsing(int ac, char **av)
{
	if (ac != 2)
		return (MRT_BAD_ARGS);
	if (file_name_check(av[1]))
		return (MRT_FILENAME);
	return (MRT_OK);
}

t_errors	data_init(t_data *minirt)
{
	ft_bzero(minirt, sizeof(t_data));
	minirt->sph_cap = 4;
	minirt->sph_count = 0;
	minirt->sphere = ft_calloc(minirt->sph_cap, sizeof(t_sphere));
	if (!minirt->sphere)
		return (MRT_MALLOC);
	minirt->pl_cap = 4;
	minirt->pl_count = 0;
	minirt->plane = ft_calloc(minirt->pl_cap, sizeof(t_plane));
	if (!minirt->plane)
		return (MRT_MALLOC);
	minirt->cyl_cap = 4;
	minirt->cyl_count = 0;
	minirt->cylinder = ft_calloc(minirt->cyl_cap, sizeof(t_cylinder));
	if (!minirt->cylinder)
		return (MRT_MALLOC);
	return (MRT_OK);
}

t_errors	program_setup(int ac, char **av, t_data *minirt)
{
	t_errors	err;

	err = input_parsing(ac, av);
	if (err != MRT_OK)
	{
		print_error(err);
		return (err);
	}
	err = data_init(minirt);
	if (err != MRT_OK)
	{
		print_error(err);
		return (err);
	}
	err = load_scene_info(av[1], minirt);
	if (err != MRT_OK)
	{
		printf("here");
		print_error(err);
		return (err);
	}
	print_everything(minirt);
	return (err);
}
