/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:27 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/10 23:20:59 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(mlx_image_t *image, int size, t_point pos, uint32_t color)
{
	int		i;
	int		j;
	t_point	start_pos;

	if ((color & 0xFF000000) == 0)
		return ;
	start_pos = (t_point){pos.u - size / 2, pos.v - size / 2};
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(image, start_pos.u + i, start_pos.v + j, color);
			j++;
		}
		i++;
	}
}

void	draw_circle(mlx_image_t *image, t_point center, int radius,
		uint32_t color)
{
	int	x;
	int	y;
	int	px;
	int	py;
	int	r_squared;

	r_squared = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= r_squared)
			{
				px = center.u + x;
				py = center.v + y;
				put_pixel(image, px, py, color);
			}
			x++;
		}
		y++;
	}
}
