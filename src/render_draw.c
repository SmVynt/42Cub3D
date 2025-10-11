/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/10 00:39:05 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(int32_t width, int32_t height, void *param)
{
	t_gs	*game;
	t_map	*map;


	game = (t_gs *) param;
	map = &game->map;
	if (game->minimap)
		mlx_delete_image(game->mlx, game->minimap);
	if (game->miniplayer)
		mlx_delete_image(game->mlx, game->miniplayer);
	if (game->view3d)
		mlx_delete_image(game->mlx, game->view3d);
	game->view3d = mlx_new_image(game->mlx, width, height);
	game->minimap = mlx_new_image(game->mlx, width / 3, height / 3);
	game->miniplayer = mlx_new_image(game->mlx, width / 3, height / 3);
	if (!game->minimap || !game->miniplayer || !game->view3d)
		return ;
	draw_map(game->minimap, map);
	ft_update(game);
	mlx_image_to_window(game->mlx, game->view3d, 0, 0);
	mlx_image_to_window(game->mlx, game->minimap, 0, 0);
	mlx_image_to_window(game->mlx, game->miniplayer, 0, 0);
}

void put_pixel(mlx_image_t *image, t_point pos, uint32_t color)
{
	// uint32_t *pixels;

	// pixels = (uint32_t *)image->pixels;
	// if (pos.u >= 0 &&  (unsigned int)pos.u < image->width && pos.v >= 0 &&  (unsigned int)pos.v < image->height)
	// 	pixels[pos.v * image->width + pos.u] = color;
	if ((unsigned int)pos.u < image->width && (unsigned int)pos.v < image->height)
		((uint32_t *)image->pixels)[pos.v * image->width + pos.u] = color;
}

void	draw_line(mlx_image_t *image, t_point start, t_point end, uint32_t color)
{
	t_point	delta;
	t_point	sign;
	t_point	err;
	int	t;

	delta.u = abs(end.u - start.u);
	delta.v = abs(end.v - start.v);
	sign.u = ft_sign(end.u - start.u);
	sign.v = ft_sign(end.v - start.v);
	err.u = delta.u - delta.v;
	t = 0;
	while (t++ < 10000)
	{
		put_pixel(image, start, color);
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

void	draw_map_square(mlx_image_t *image, t_point pos, uint32_t color)
{
	int size;
	int i;

	(void) color;
	size = MAP_SCALE;
	i = -size / 2;
	while (i < size / 2)
	{
		put_pixel(image, (t_point){pos.u + i, pos.v - size / 2}, COLOR_RED);
		put_pixel(image, (t_point){pos.u + i, pos.v + size / 2}, COLOR_GREEN);
		put_pixel(image, (t_point){pos.u - size / 2, pos.v + i}, COLOR_YELLOW);
		put_pixel(image, (t_point){pos.u + size / 2, pos.v + i}, COLOR_BLUE);
		i++;
	}
}

void	draw_square(mlx_image_t *image, int size, t_point pos, uint32_t color)
{
	int i;
	int j;

	i = -size / 2;
	while (i <= size / 2)
	{
		j = -size / 2;
		while (j <= size / 2)
		{
			// put_pixel(image, (t_point){pos.u + i, pos.v + j}, color);
			PUT_PIXEL_FAST(image, pos.u + i, pos.v + j, color);
			j++;
		}
		i++;
	}
}

void fill_background(mlx_image_t *image, uint32_t color)
{
	uint32_t *pixels = (uint32_t *)image->pixels;
	int total = image->width * image->height;

	for (int i = 0; i < total; i++)
		pixels[i] = color;
}

void	draw_map(mlx_image_t *image, t_map *map)
{
	int i;
	int j;
	int offset;


	fill_background(image, COLOR_BLACK);
	i = 0;
	offset = MAP_SCALE;
	while (i < map->h)
	{
		j = 0;
		while  (j < map->w)
		{
			if (map->tile[i][j] == '1')
				if (true)
					draw_map_square(image, (t_point){j * MAP_SCALE + offset, i * MAP_SCALE + offset}, COLOR_RED);
			j++;
		}
		i++;
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
				put_pixel(image, (t_point){px, py}, color);
				// if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				// 	pixels[py * WIDTH + px] = color;
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

void	draw_walls(mlx_image_t *image)
{
	t_player	*player;

	player = ft_game()->player;
	float angle = - FOV_RAD / 2;
	float dangle = FOV_RAD / (ft_game()->view3d->width - 1) * PIXEL_SIZE;
	int x = 0;
	ft_game()->render.projection_plane_dist = (image->width / 2.0) / tan(FOV_RAD / 2.0);
	x += PIXEL_SIZE/2;
	angle += dangle / 2;
	while ((unsigned int)x < ft_game()->view3d->width)
	{
		draw_wall(image, (t_vec2){player->pos.x, player->pos.y} , ft_mat4_transform_vec3(ft_mat4_rotation_z(angle), player->lookdir), x);
		angle += dangle;
		// x++;
		x += PIXEL_SIZE;
	}
}
