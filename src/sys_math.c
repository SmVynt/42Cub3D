/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/13 15:11:10 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

int	ft_signd(double n)
{
	if (n < 0.0)
		return (-1);
	return (1);
}

t_vec2	ft_normalize_vec2(t_vec2 v)
{
	double	length;

	length = ft_vec2_length(v);
	if (length < 1e-9)
		return ((t_vec2){0.0, 0.0});
	return ((t_vec2){v.x / length, v.y / length});
}

/**
 * Returns the angle in degrees between two 2D vectors.
 */
double	ft_angle_between_vec2(t_vec2 a, t_vec2 b)
{
	double	angle;

	angle = atan2(b.y, b.x) - atan2(a.y, a.x);
	if (angle < -M_PI)
		angle += 2.0 * M_PI;
	if (angle > M_PI)
		angle -= 2.0 * M_PI;
	return (angle);
}
