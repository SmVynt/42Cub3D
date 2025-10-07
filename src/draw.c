/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/05 00:05:23 by nmikuka          ###   ########.fr       */
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
	// player = init_player(map->tile, map->w, map->h);
	// draw_line(pixels, player->pos, player->lookdir, map->tile);
	draw_map((uint32_t*)game->minimap->pixels, map);
	// printf("Map drawn\n");
	// init_player();
	mlx_image_to_window(game->mlx, game->minimap, 0, 0);
	mlx_image_to_window(game->mlx, game->miniplayer, 0, 0);
}

void put_pixel(uint32_t *pixels, t_point pos, uint32_t color)
{
	if (pos.u >= 0 && pos.u < WIDTH && pos.v >= 0 && pos.v < HEIGHT)
		pixels[pos.v * WIDTH + pos.u] = color;
}

void	draw_line(uint32_t *pixels, t_point start, t_point end, uint32_t color)
{
	t_point	delta;
	t_point	sign;
	t_point	err;
	int	t;

	delta.u = abs(end.u - start.u);
	delta.v = abs(end.v - start.v);
	sign.u = (end.u - start.u < 0) * -1 + (end.u - start.u > 0) * 1;
	sign.v = (end.v - start.v < 0) * -1 + (end.v - start.v > 0) * 1;
	err.u = delta.u - delta.v;
	t = 0;
	while (t++ < 10000)
	{
		put_pixel(pixels, start, color);
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

t_point	center_point(t_point point, int w, int h)
{
	return ((t_point){point.u + w / 2, point.v + h / 2});
}

void	draw_square(uint32_t* pixels, t_point pos, uint32_t color)
{
	int size;
	int i;

	(void) color;
	size = MAP_SCALE;
	i = -size / 2;
	while (i < size / 2)
	{
		put_pixel(pixels, (t_point){pos.u + i, pos.v - size / 2}, COLOR_RED);
		put_pixel(pixels, (t_point){pos.u + i, pos.v + size / 2}, COLOR_GREEN);
		put_pixel(pixels, (t_point){pos.u - size / 2, pos.v + i}, COLOR_YELLOW);
		put_pixel(pixels, (t_point){pos.u + size / 2, pos.v + i}, COLOR_BLUE);
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
				if (true)
					draw_square(pixels, (t_point){j * MAP_SCALE + offset, i * MAP_SCALE + offset}, COLOR_RED);
			j++;
		}
		i++;
	}
}

void draw_circle(uint32_t *pixels, t_point center, int radius, uint32_t color)
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
				if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
					pixels[py * WIDTH + px] = color;
			}
		}
	}
}

// t_player *init_player(char **map, int w, int h)
// {
// 	t_player *player;
// 	int row;
// 	int col;

// 	player = malloc(sizeof(player));
// 	row = 0;
// 	while (row < h)
// 	{
// 		col = 0;
// 		while  (col < w)
// 		{
// 			if (map[row][col] == 'N' || map[row][col] == 'E' || map[row][col] == 'S' || map[row][col] == 'W')
// 			{
// 				player->pos = (t_vec2){col, row};
// 				if (map[row][col] == 'N')
// 					player->lookdir = (t_vec3){0.0f, -1.0f, 0.0f};
// 				if (map[row][col] == 'E')
// 					player->lookdir = (t_vec3){1.0f, 0.0f, 0.0f};
// 				if (map[row][col] == 'S')
// 					player->lookdir = (t_vec3){0.0f, 1.0f, 0.0f};
// 				if (map[row][col] == 'W')
// 					player->lookdir = (t_vec3){-1.0f, 0.0f, 0.0f};
// 			}
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (player);
// }

void	draw_player(uint32_t *pixels)
{
	t_point center;
	t_player	*player;
	t_map		map;

	player = ft_game()->player;
	map = ft_game()->map;
	center = (t_point){(int)(player->pos.x * MAP_SCALE/* + MAP_SCALE*/),
		(int)(player->pos.y * MAP_SCALE/* + MAP_SCALE*/)};
	draw_circle(pixels, center, 3, COLOR_BLUE);
	float angle = - FOV_RAD / 2;
	float dangle = FOV_RAD / WIDTH;
	int x = 0;
	while (x < WIDTH)
	{
		draw_line_ray(pixels, center, ft_mat4_transform_vec3(ft_mat4_rotation_z(angle), player->lookdir), map, x);
		angle += dangle;
		x++;
	}
	draw_line(pixels, center,
		(t_point){(int)(center.u + player->lookdir.x * 20),
		(int)(center.v + player->lookdir.y * 20)}, COLOR_YELLOW);
}
