/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:04:24 by dlanehar          #+#    #+#             */
/*   Updated: 2026/09/25 14:33:47 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void init_camera_basis(t_camera *cam, t_vec rawnov)
{
	t_vec	world_up;

	cam->forward = normalize(rawnov);
	world_up = (t_vec){0,1,0};
	if (fabs(dot(cam->forward, world_up)) > 0.999)
		world_up = (t_vec){0,0,1};
	cam->right = normalize(cross(world_up, cam->forward));
	cam->up = cross(cam->forward, cam->right);
	return ;
}

static int	parse_nov(char *str, t_vec *NOV)
{
	int		ret;

	ret = parse_coords(str, NOV, -1.0, 1.0);
	return (ret);
}

t_errors	cam_parse(char **split, t_data *minirt)
{
	int	i;
	int	ret;

	i = 0;
	ret = parse_coords(split[i], &minirt->camera.origin, -DBL_MAX, DBL_MAX);
	if (ret != MRT_OK)
		return (ret);
	i++;
	ret = parse_nov(split[i], &minirt->camera.threed_nov);
	if (ret != MRT_OK)
		return (ret);
	init_camera_basis(&minirt->camera, minirt->camera.threed_nov);
	i++;
	if (!valid_number(split[i]))
		return (MRT_INVALID_NUM);
	minirt->camera.fov = ft_atoi(split[i]);
	if (minirt->camera.fov < 0 || minirt->camera.fov > 180)
		return (MRT_OUT_OF_BOUNDS);
	if (split[i + 1] != NULL)
		return (MRT_PARSE_LINE_ERR);
	return (MRT_OK);
}
