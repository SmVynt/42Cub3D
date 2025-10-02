/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:31:04 by nmikuka           #+#    #+#             */
/*   Updated: 2025/06/27 23:32:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mat4.h"

t_mat4	ft_mat4_translation(float tx, float ty, float tz)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][3] = tx;
	m.m[1][3] = ty;
	m.m[2][3] = tz;
	return (m);
}

t_mat4	ft_mat4_scaling(float sx, float sy, float sz)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][0] = sx;
	m.m[1][1] = sy;
	m.m[2][2] = sz;
	return (m);
}

t_mat4	ft_mat4_rotation_x(float radians)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[1][1] = cosf(radians);
	m.m[1][2] = -sinf(radians);
	m.m[2][1] = sinf(radians);
	m.m[2][2] = cosf(radians);
	return (m);
}

t_mat4	ft_mat4_rotation_y(float radians)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][0] = cosf(radians);
	m.m[0][2] = sinf(radians);
	m.m[2][0] = -sinf(radians);
	m.m[2][2] = cosf(radians);
	return (m);
}

t_mat4	ft_mat4_rotation_z(float radians)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][0] = cosf(radians);
	m.m[0][1] = -sinf(radians);
	m.m[1][0] = sinf(radians);
	m.m[1][1] = cosf(radians);
	return (m);
}
