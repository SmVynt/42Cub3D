/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:38:28 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 19:52:48 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAT4_H
# define FT_MAT4_H

# include <math.h>
# include "structs.h"

// Constructors
t_mat4	ft_mat4_identity(void);
t_mat4	ft_mat4_translation(double tx, double ty, double tz);
t_mat4	ft_mat4_scaling(double sx, double sy, double sz);
t_mat4	ft_mat4_rotation_x(double radians);
t_mat4	ft_mat4_rotation_y(double radians);
t_mat4	ft_mat4_rotation_z(double radians);

// Operations
t_mat4	ft_mat4_mul(t_mat4 a, t_mat4 b);
t_vec2	ft_mat4_transform_vec2(t_mat4 m, t_vec2 v);
double	ft_vec2_length(t_vec2 v);

#endif
