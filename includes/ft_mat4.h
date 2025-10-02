/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:38:28 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/02 19:36:43 by nmikuka          ###   ########.fr       */
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
t_vec3	ft_mat4_transform_vec3(t_mat4 m, t_vec3 v);

// Projection matrices
t_mat4	ft_mat4_proj_iso(void);
t_mat4	ft_mat4_proj_cab(void);

#endif
