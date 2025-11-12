/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4_transform.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 23:31:04 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 19:56:06 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mat4.h"

t_mat4	ft_mat4_translation(double tx, double ty, double tz)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][3] = tx;
	m.m[1][3] = ty;
	m.m[2][3] = tz;
	return (m);
}

t_mat4	ft_mat4_scaling(double sx, double sy, double sz)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][0] = sx;
	m.m[1][1] = sy;
	m.m[2][2] = sz;
	return (m);
}

t_mat4	ft_mat4_rotation_x(double radians)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[1][1] = cos(radians);
	m.m[1][2] = -sin(radians);
	m.m[2][1] = sin(radians);
	m.m[2][2] = cos(radians);
	return (m);
}

t_mat4	ft_mat4_rotation_y(double radians)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][0] = cos(radians);
	m.m[0][2] = sin(radians);
	m.m[2][0] = -sin(radians);
	m.m[2][2] = cos(radians);
	return (m);
}

t_mat4	ft_mat4_rotation_z(double radians)
{
	t_mat4	m;

	m = ft_mat4_identity();
	m.m[0][0] = cos(radians);
	m.m[0][1] = -sin(radians);
	m.m[1][0] = sin(radians);
	m.m[1][1] = cos(radians);
	return (m);
}
