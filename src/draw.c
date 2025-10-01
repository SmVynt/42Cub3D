/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/30 19:16:57 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_gs *game)
{
	mlx_image_t	*image;
	uint32_t*	pixels;
	t_map		*map;

	map = &ft_game()->map;
	image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!image)
		return ;
	pixels = (uint32_t*)image->pixels;
	draw_map(pixels, map->tile, map->w, map->h);
	init_player(map->tile, map->w, map->h);
	mlx_image_to_window(game->mlx, image, 0, 0);
}

void put_pixel(uint32_t *pixels, t_vec2 pos, uint32_t color)
{
	if (pos.x >= 0 && pos.x < WIDTH && pos.y >= 0 && pos.y < HEIGHT)
		pixels[pos.y * WIDTH + pos.x] = color;
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

void	draw_map(uint32_t* pixels, char **map, int w, int h)
{
	int i;
	int j;
	int offset;

	i = 0;
	offset = 10;
	while (i < h)
	{
		j = 0;
		while  (j < w)
		{
			if (map[i][j] == '1')
				draw_square(pixels, (t_vec2){j * 10 + offset, i * 10 + offset}, COLOR_RED);
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
				draw_circle(pixels, (t_vec2){j * 10 + offset, i * 10 + offset}, 5, COLOR_GREEN);
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

void init_player(char **map, int w, int h)
{
	t_player *player;
	int i;
	int j;

	player = malloc(sizeof(player));
	i = 0;
	while (i < h)
	{
		j = 0;
		while  (j < w)
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
			{
				player->pos = (t_vec2){j, i};
				if (map[i][j] == 'N')
					player->lookdir = (t_vec3){0.0f, 1.0f, 0.0f};
				if (map[i][j] == 'E')
					player->lookdir = (t_vec3){1.0f, 0.0f, 0.0f};
				if (map[i][j] == 'S')
					player->lookdir = (t_vec3){0.0f, -1.0f, 0.0f};
				if (map[i][j] == 'W')
					player->lookdir = (t_vec3){-1.0f, 0.0f, 0.0f};
			}
			j++;	
		}
		i++;
	}
}
