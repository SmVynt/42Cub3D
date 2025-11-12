/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 19:52:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_clampf(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

double	ft_lerpf(double a, double b, double t)
{
	return (a + t * (b - a));
}

t_vec2	ft_lerpvec2(t_vec2 a, t_vec2 b, double t)
{
	t_vec2	result;

	result.x = ft_lerpf(a.x, b.x, t);
	result.y = ft_lerpf(a.y, b.y, t);
	return (result);
}

double	rand_in_range(double min, double max)
{
	return (min + (double)rand() / (double)RAND_MAX * (max - min));
}
