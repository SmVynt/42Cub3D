/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/29 15:56:42 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_bg(void)
{
	uint32_t x;
	uint32_t y;
	uint32_t x_tex;
	uint32_t y_tex;
	mlx_texture_t *bg;
	float win_scale;

	win_scale = (float)ft_game()->view3d->height / HEIGHT * (float)UI_SCALE;
	bg = ft_game()->textures.ui_minimap;
	x = PIXEL_SIZE / 2;
	while (x < bg->width * win_scale)
	{
		y = PIXEL_SIZE / 2;
		x_tex = x / win_scale;
		while (y < bg->height * win_scale)
		{
			y_tex = y / win_scale;
			draw_square(ft_game()->minimap, PIXEL_SIZE, (t_point){x, y}, ft_get_pixel_color(bg, (t_point){x_tex, y_tex}));
			y += PIXEL_SIZE;
		}
		x+=PIXEL_SIZE;
	}
}

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
		draw_line_ray(image, center, ft_mat4_transform_vec3(ft_mat4_rotation_z(angle), player->lookdir), map, x);
		angle += dangle;
		x++;
	}
	draw_line(image, center,
		(t_point){(int)(center.u + player->lookdir.x * 20),
		(int)(center.v + player->lookdir.y * 20)}, COLOR_YELLOW);
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

void	draw_map(mlx_image_t *image, t_map *map)
{
	int		x;
	int		y;
	int		halfx;
	int		halfy;
	t_vec3	coords;
	t_player	*player;

	(void)map;
	player = ft_game()->player;
	halfx = (int)image->width / 2;
	halfy = (int)image->height / 2;
	x = - halfx;
	while (x < halfx)
	{
		y = - halfy;
		while (y < (int)image->height / 2)
		{
			coords = (t_vec3){(float)x / MM_SCALE, (float)y / MM_SCALE ,0.f};
			coords = ft_mat4_transform_vec3(ft_mat4_rotation_z(atan2(player->lookdir.y, player->lookdir.x) + HALF_PI), coords);
			coords.x += player->pos.x;
			coords.y += player->pos.y;
			if (ft_is_wall((t_vec2){coords.x, coords.y}))
				draw_square(image, PIXEL_SIZE, (t_point){x + halfx, y + halfy}, MM_COLOR_WALLS);
		y += PIXEL_SIZE;
		}
	x += PIXEL_SIZE;
	}
}

void draw_circle(mlx_image_t *image, t_point center, int radius, uint32_t color)
{
	int x;
	int y;
	int r_squared;

	r_squared = radius * radius;
	for (y = -radius; y <= radius; y++)
	{
		for (x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= r_squared)
			{
				int px = center.u + x;
				int py = center.v + y;
				put_pixel(image, px, py, color);
			}
		}
	}
}
