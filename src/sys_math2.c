/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/09 16:10:10 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_clampf(float value, float min, float max)
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

float	ft_lerpf(float a, float b, float t)
{
	return (a + t * (b - a));
}

t_vec2	ft_lerpvec2(t_vec2 a, t_vec2 b, float t)
{
	t_vec2	result;

	result.x = ft_lerpf(a.x, b.x, t);
	result.y = ft_lerpf(a.y, b.y, t);
	return (result);
}

float	rand_in_range(float min, float max)
{
	return (min + (float)rand() / (float)RAND_MAX * (max - min));
}
