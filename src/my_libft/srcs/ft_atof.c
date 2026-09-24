/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 08:55:32 by dlanehar          #+#    #+#             */
/*   Updated: 2026/08/11 09:34:28 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static double	create_num(char *str)
{
	int		i;
	double	nb;
	double	fraction;

	i = 0;
	nb = 0;
	fraction = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		fraction /= 10;
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			nb += fraction * (str[i] - '0');
			fraction /= 10;
			i++;
		}
	}
	return (nb);
}

double	ft_atof(char *str)
{
	int		i;
	double	sign;
	double	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nb = create_num(&str[i]);
	return (nb * sign);
}
