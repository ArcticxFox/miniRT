/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:21:48 by dlanehar          #+#    #+#             */
/*   Updated: 2026/10/07 15:15:37 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parerrors.h"

t_errors	load_scene_info(char *filename, t_data *minirt)
{
	int			fd;
	char		*res;
	t_errors	err_ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (MRT_ERRNO);
	res = get_next_line(fd);
	err_ret = lsi_loop(&res, minirt, fd);
	close(fd);
	return (err_ret);
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

t_errors	input_parsing(int ac, char **av)
{
	if (ac != 2)
		return (MRT_BAD_ARGS);
	if (file_name_check(av[1]))
		return (MRT_FILENAME);
	return (MRT_OK);
}

t_errors	data_init(t_data *scene)
{
	scene->sph_cap = 4;
	scene->sph_count = 0;
	scene->sphere = ft_calloc(scene->sph_cap, sizeof(t_sphere));
	if (!scene->sphere)
		return (MRT_MALLOC);
	scene->pl_cap = 4;
	scene->pl_count = 0;
	scene->plane = ft_calloc(scene->pl_cap, sizeof(t_pl));
	if (!scene->plane)
		return (MRT_MALLOC);
	scene->cyl_cap = 4;
	scene->cyl_count = 0;
	scene->cylinder = ft_calloc(scene->cyl_cap, sizeof(t_cy));
	if (!scene->cylinder)
		return (MRT_MALLOC);
	return (MRT_OK);
}

t_errors	program_setup(int ac, char **av, t_data *scene)
{
	t_errors	err;

	ft_bzero(scene, sizeof(*scene));
	err = input_parsing(ac, av);
	if (err != MRT_OK)
	{
		print_error(err);
		return (err);
	}
	err = data_init(scene);
	if (err != MRT_OK)
	{
		print_error(err);
		return (err);
	}
	err = load_scene_info(av[1], scene);
	if (err != MRT_OK)
	{
		print_error(err);
		return (err);
	}
	print_everything(scene);
	return (err);
}
