/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:38:28 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/02 18:08:02 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAT4_H
# define FT_MAT4_H

# include <math.h>
# include "structs.h"

// Constructors
t_mat4	ft_mat4_identity(void);
t_mat4	ft_mat4_translation(float tx, float ty, float tz);
t_mat4	ft_mat4_scaling(float sx, float sy, float sz);
t_mat4	ft_mat4_rotation_x(float radians);
t_mat4	ft_mat4_rotation_y(float radians);
t_mat4	ft_mat4_rotation_z(float radians);

// Operations
t_mat4	ft_mat4_mul(t_mat4 a, t_mat4 b);
t_vec2	ft_mat4_transform_vec2(t_mat4 m, t_vec2 v);
float	ft_vec2_length(t_vec2 v);

#endif
