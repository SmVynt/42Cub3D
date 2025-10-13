/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/12 21:38:47 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

int	ft_signf(float n)
{
	if (n < 0.0f)
		return (-1);
	return (1);
}

t_vec2	ft_normalize_vec2(t_vec2 v)
{
	float length;

	length = ft_vec2_length(v);
	if (length < 1e-9)
		return (t_vec2){0.0f, 0.0f};
	return (t_vec2){v.x / length, v.y / length};
}

/**
 * Returns the angle in degrees between two 2D vectors.
 */
float ft_angle_between_vec2(t_vec2 a, t_vec2 b)
{
	float angle;

	angle = atan2f(b.y, b.x) - atan2f(a.y, a.x);
	if (angle < - M_PI)
		angle += 2.0f * M_PI;
	if (angle > M_PI)
		angle -= 2.0f * M_PI;
	return (angle * (180.0f / M_PI));
}

float	ft_clampf(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
