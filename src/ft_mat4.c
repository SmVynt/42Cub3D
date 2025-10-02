/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_mat4.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nmikuka <nmikuka@student.42heilbronn.de	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/22 16:38:32 by nmikuka		   #+#	#+#			 */
/*   Updated: 2025/06/22 16:38:54 by nmikuka		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "ft_mat4.h"

t_mat4	ft_mat4_identity(void)
{
	t_mat4	m;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m.m[i][j] = 1.0f;
			else
				m.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (m);
}

t_mat4	ft_mat4_mul(t_mat4 a, t_mat4 b)
{
	t_mat4	res;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			res.m[i][j] = 0.0f;
			while (k < 4)
			{
				res.m[i][j] += a.m[i][k] * b.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

t_vec3	ft_mat4_transform_vec3(t_mat4 m, t_vec3 v)
{
	t_vec3	res;

	res.x = (m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3]);
	res.y = (m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3]);
	res.z = (m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3]);
	return (res);
}

t_mat4	ft_mat4_proj_iso(void)
{
	return (ft_mat4_mul(ft_mat4_rotation_x(M_PI / 2.0 - atanf(1 / sqrtf(2.0f))),
			ft_mat4_rotation_z(M_PI / 4)));
}

t_mat4	ft_mat4_proj_cab(void)
{
	t_mat4	res;

	res = ft_mat4_identity();
	res.m[0][2] = -cos(M_PI / 4) / 2;
	res.m[1][2] = sin(M_PI / 4) / 2;
	res = ft_mat4_mul(res, ft_mat4_rotation_x(M_PI / 2));
	return (res);
}
