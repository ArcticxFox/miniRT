/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 14:21:48 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/19 14:21:49 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	load_scene_info(char *filename, t_data *minirt)
{
	int		fd;
	char	*res;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	res = get_next_line(fd);
	while (res)
	{
		if (res[0] == '\0' || res[0] == '\n')
		{
			free(res);
			res = get_next_line(fd);
		}
		else if (parse_line(res, minirt) == 0)
		{
			free(res);
			res = get_next_line(fd);
		}
		else
			return (1);
	}
	close(fd);
	return (0);
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
		return (1);
	if (file_name_check(av[1]))
		return (1);
	return (0);
}

int	data_init(t_data *minirt)
{
	ft_bzero(minirt, sizeof(t_data));
	minirt->sph_cap = 4;
	minirt->sph_count = 0;
	minirt->sphere = ft_calloc(minirt->sph_cap, sizeof(t_sphere));
	if (!minirt->sphere)
		return (1);
	minirt->pl_cap = 4;
	minirt->pl_count = 0;
	minirt->plane = ft_calloc(minirt->pl_cap, sizeof(t_plane));
	if (!minirt->plane)
		return (1);
	minirt->cyl_cap = 4;
	minirt->cyl_count = 0;
	minirt->cylinder = ft_calloc(minirt->cyl_cap, sizeof(t_cylinder));
	if (!minirt->cylinder)
		return (1);
	return (0);
}

int	program_setup(int ac, char **av, t_data *minirt)
{
	int	err_num;

	err_num = data_init(minirt);
	if (err_num)
		return (1);
	err_num = input_parsing(ac, av);
	if (err_num)
	{
		return (err_num);
	}
	err_num = load_scene_info(av[1], minirt);
	if (err_num)
	{
		return (err_num);
	}
	print_everything(minirt);
	return (0);
}
