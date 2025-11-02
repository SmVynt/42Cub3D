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

t_vec2	ft_mat4_transform_vec2(t_mat4 m, t_vec2 v)
{
	t_vec2	res;

	res.x = (m.m[0][0] * v.x + m.m[0][1] * v.y);
	res.y = (m.m[1][0] * v.x + m.m[1][1] * v.y);
	return (res);
}

float	ft_vec2_length(t_vec2 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}
