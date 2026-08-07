/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 17:24:46 by ejones            #+#    #+#             */
/*   Updated: 2026/08/07 13:59:14 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	hit_sphere(t_sphere sp, t_ray ray, double *t)
{
	double	a = 0, b = 0, c = 0;
	double	delta;
	double	sol[2] = { 0 };
	t_vec	oc = sub(sp.center, ray.origin);

	a = dot(ray.dir, ray.dir);
	b = -2 * dot(ray.dir, oc);
	c = dot(oc, oc) - sp.r * sp.r;
	delta = b * b - 4 * a * c;
	if (delta >= 0) {
		sol[0] = (-b - sqrt(delta)) / (2 * a);
		sol[1] = (-b + sqrt(delta)) / (2 * a);
	}
	if (sol[0] < 0 && sol[1] < 0)
		t = NULL;
	else if (sol[0] < 0 && sol[1] > 0)
		*t = sol[1];
	else if (sol[0] > 0 && sol[1] < 0)
		*t = sol[0];
	else if (sol[0] < sol[1])
		*t = sol[0];
	else
		*t = sol[1];
	return (delta >= 0);
}

int	main(void)
{
	t_sphere	sp = {
		{0, 0, 5},
		2.5
	};
	t_ray		ray = {
		{0, 0, 0},
		{0, 0, 1}
	};
	double	t;
	double viewport_x;
	double viewport_y;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			viewport_x = (2.0 * (x + 0.5) / WIDTH - 1.0);
			viewport_y = (1.0 - 2.0 * (y + 0.5) / HEIGHT);
			ray.dir.x = viewport_x;
			ray.dir.y = viewport_y;
			ray.dir.z = 1;
			ray.dir = normalize(ray.dir);
			if (hit_sphere(sp, ray, &t))
				printf("x");
			else
				printf("-");
		}
		printf("\n");
	}
	return 1;
}
