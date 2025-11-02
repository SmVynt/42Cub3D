/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/02 18:12:02 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ui_minimap(void)
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
		draw_line_ray(image, center, ft_mat4_transform_vec2(ft_mat4_rotation_z(angle), player->lookdir), map, x);
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

static void draw_characters_on_minimap(mlx_image_t *image, float zoom, t_point image_center)
{
	t_vec2		coords;
	t_player	*player;
	int			i;

	player = ft_game()->player;
	i = -1;
	while (++i < ft_game()->char_count)
	{
		coords = (t_vec2){(ft_game()->chars[i].sprite.pos.x - player->pos.x) * zoom,
			(ft_game()->chars[i].sprite.pos.y - player->pos.y) * zoom};
		if (ft_game()->chars[i].alive == false)
			continue ;
		if ((int)coords.x < -image_center.u || (int)coords.x > image_center.u
			|| (int)coords.y < -image_center.v || (int)coords.y > image_center.v)
			continue ;
		coords = ft_mat4_transform_vec2(ft_mat4_rotation_z(- atan2(player->lookdir.y, player->lookdir.x) - HALF_PI), coords);
		draw_circle(image, (t_point){(int)(coords.x) + image_center.u, (int)(coords.y) + image_center.v}, 3, MM_COLOR_ENEMIES);
	}
}

static void draw_items_on_minimap(mlx_image_t *image, float zoom, t_point image_center)
{
	t_vec2		coords;
	t_player	*player;
	int			i;
	uint32_t	color;

	player = ft_game()->player;
	i = -1;
	while (++i < ft_game()->item_count)
	{
		if (!(ft_game()->items[i].type ==  IT_HEALTH
				|| ft_game()->items[i].type == IT_KEY))
			continue ;
		if (ft_game()->items[i].active == false)
			continue ;
		coords = (t_vec2){(ft_game()->items[i].sprite.pos.x - player->pos.x) * zoom,
			(ft_game()->items[i].sprite.pos.y - player->pos.y) * zoom};
		if ((int)coords.x < -image_center.u || (int)coords.x > image_center.u
			|| (int)coords.y < -image_center.v || (int)coords.y > image_center.v)
			continue ;
		coords = ft_mat4_transform_vec2(ft_mat4_rotation_z(- atan2(player->lookdir.y, player->lookdir.x) - HALF_PI), coords);
		if (ft_game()->items[i].type == IT_HEALTH)
			color = MM_COLOR_HEALTH;
		if (ft_game()->items[i].type == IT_KEY)
			color = MM_COLOR_KEY;
		draw_circle(image, (t_point){(int)(coords.x) + image_center.u, (int)(coords.y) + image_center.v}, 3, color);
	}
}

void	draw_map(mlx_image_t *image, t_map *map)
{
	int		x;
	int		y;
	t_point	image_center;
	t_vec2	coords;
	t_player	*player;
	float		zoom;

	(void)map;
	player = ft_game()->player;
	image_center.u = (int)image->width / 2;
	image_center.v = (int)image->height / 2;
	zoom = MM_SCALE * (float)ft_game()->view3d->height / HEIGHT;
	x = - image_center.u;
	while (x < image_center.u)
	{
		y = - image_center.v;
		while (y < (int)image->height / 2)
		{
			coords = (t_vec2){(float)x / zoom, (float)y / zoom};
			coords = ft_mat4_transform_vec2(ft_mat4_rotation_z(atan2(player->lookdir.y, player->lookdir.x) + HALF_PI), coords);
			coords.x += player->pos.x;
			coords.y += player->pos.y;
			if (ft_is_door((t_vec2){coords.x, coords.y}))
				draw_square(image, PIXEL_SIZE, (t_point){x + image_center.u, y + image_center.v}, MM_COLOR_DOORS);
			else if (ft_is_wall((t_vec2){coords.x, coords.y}))
				draw_square(image, PIXEL_SIZE, (t_point){x + image_center.u, y + image_center.v}, MM_COLOR_WALLS);
			else
				draw_square(image, PIXEL_SIZE, (t_point){x + image_center.u, y + image_center.v}, MM_COLOR_EMPTY);
		y += PIXEL_SIZE;
		}
	x += PIXEL_SIZE;
	}
	draw_characters_on_minimap(image, zoom, image_center);
	draw_items_on_minimap(image, zoom, image_center);
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
