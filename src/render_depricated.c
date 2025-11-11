/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_depricated.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:53:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 15:14:24 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(mlx_image_t *image)
{
	t_point center;
	t_player	*player;
	t_map		map;

	player = ft_game()->player;
	map = ft_game()->map;
	center = (t_point){(int)(player->pos.x * MAP_SCALE + MAP_SCALE),
		(int)(player->pos.y * MAP_SCALE + MAP_SCALE)};
	draw_circle(image, center, 3, COLOR_BLUE);
	float angle = - FOV_RAD / 2;
	float dangle = FOV_RAD / (ft_game()->view3d->width - 1);
	int x = 0;
	while ((unsigned int)x < ft_game()->view3d->width)
	{
		draw_line_ray(image, center, ft_mat4_transform_vec2(ft_mat4_rotation_z(angle), player->lookdir), map, x);
		angle += dangle;
		x++;
	}
	draw_line(image, center,
		(t_point){(int)(center.u + player->lookdir.x * 20),
		(int)(center.v + player->lookdir.y * 20)}, COLOR_YELLOW);
}

void	draw_line(mlx_image_t *image, t_point start, t_point end, uint32_t color)
{
	t_point	delta;
	t_point	sign;
	t_point	err;
	int		t;

	delta.u = abs(end.u - start.u);
	delta.v = abs(end.v - start.v);
	sign.u = ft_sign(end.u - start.u);
	sign.v = ft_sign(end.v - start.v);
	err.u = delta.u - delta.v;
	t = 0;
	while (t++ < 10000)
	{
		put_pixel(image, start.u, start.v, color);
		if (start.u == end.u && start.v == end.v)
			break ;
		err.v = err.u * 2;
		if (err.v > -delta.v)
		{
			err.u -= delta.v;
			start.u += sign.u;
		}
		if (err.v < delta.u)
		{
			err.u += delta.u;
			start.v += sign.v;
		}
	}
}

void	draw_map_square(mlx_image_t *image, t_point pos, uint32_t color)
{
	int size;
	int i;

	(void) color;
	size = MAP_SCALE;
	i = -size / 2;
	while (i < size / 2)
	{
		put_pixel(image, pos.u + i, pos.v - size / 2, COLOR_RED);
		put_pixel(image, pos.u + i, pos.v + size / 2, COLOR_GREEN);
		put_pixel(image, pos.u - size / 2, pos.v + i, COLOR_YELLOW);
		put_pixel(image, pos.u + size / 2, pos.v + i, COLOR_BLUE);
		i++;
	}
}
