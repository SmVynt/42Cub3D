/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/02 17:21:03 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_gs *game)
{
	// mlx_image_t	*image;
	// uint32_t*	pixels;
	t_map		*map;

	map = &ft_game()->map;
	game->minimap = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->miniplayer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->minimap || !game->miniplayer)
		return ;
	draw_map((uint32_t*)game->minimap->pixels, map);
	// printf("Map drawn\n");
	// init_player();
	mlx_image_to_window(game->mlx, game->minimap, 0, 0);
	mlx_image_to_window(game->mlx, game->miniplayer, 0, 0);
}

void put_pixel(uint32_t *pixels, t_vec2 pos, uint32_t color)
{
	if (pos.x >= 0 && pos.x < WIDTH && pos.y >= 0 && pos.y < HEIGHT)
		pixels[pos.y * WIDTH + pos.x] = color;
}

void	draw_line(uint32_t *pixels, t_vec2 start, t_vec2 end, uint32_t color)
{
	t_vec2	delta;
	t_vec2	sign;
	t_vec2	err;
	int	t;

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	sign.x = (end.x - start.x < 0) * -1 + (end.x - start.x > 0) * 1;
	sign.y = (end.y - start.y < 0) * -1 + (end.y - start.y > 0) * 1;
	err.x = delta.x - delta.y;
	t = 0;
	while (t++ < 10000)
	{
		put_pixel(pixels, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		err.y = err.x * 2;
		if (err.y > -delta.y)
		{
			err.x -= delta.y;
			start.x += sign.x;
		}
		if (err.y < delta.x)
		{
			err.x += delta.x;
			start.y += sign.y;
		}
	}
}

t_vec2	center_point(t_vec2 point, int w, int h)
{
	return ((t_vec2){point.x + w / 2, point.y + h / 2});
}

void	draw_square(uint32_t* pixels, t_vec2 pos, uint32_t color)
{
	int size;
	int i;

	(void) color;
	size = 10;
	i = -size / 2;
	while (i < size / 2)
	{
		put_pixel(pixels, (t_vec2){pos.x + i, pos.y - size / 2}, COLOR_RED);
		put_pixel(pixels, (t_vec2){pos.x + i, pos.y + size / 2}, COLOR_GREEN);
		put_pixel(pixels, (t_vec2){pos.x - size / 2, pos.y + i}, COLOR_YELLOW);
		put_pixel(pixels, (t_vec2){pos.x + size / 2, pos.y + i}, COLOR_BLUE);
		i++;
	}
}

void	draw_map(uint32_t* pixels, t_map *map)
{
	int i;
	int j;
	int offset;

	i = 0;
	offset = MAP_SCALE;
	while (i < map->h)
	{
		j = 0;
		while  (j < map->w)
		{
			if (map->tile[i][j] == '1')
				draw_square(pixels, (t_vec2){j * MAP_SCALE + offset, i * MAP_SCALE + offset}, COLOR_RED);
			j++;
		}
		i++;
	}
}

void draw_circle(uint32_t *pixels, t_vec2 center, int radius, uint32_t color)
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
				int px = center.x + x;
				int py = center.y + y;
				if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
					pixels[py * WIDTH + px] = color;
			}
		}
	}
}

void	draw_player(uint32_t *pixels)
{
	t_vec2 center;
	int radius;
	t_player	*player;


	player = ft_game()->player;
	center = (t_vec2){(int)(player->pos.x * MAP_SCALE + MAP_SCALE),
		(int)(player->pos.y * MAP_SCALE + MAP_SCALE)};
	radius = 3;
	draw_circle(pixels, center, radius, COLOR_BLUE);
	draw_line(pixels, center,
		(t_vec2){(int)(center.x + player->lookdir.x * 20),
		(int)(center.y - player->lookdir.y * 20)}, COLOR_YELLOW);
}
