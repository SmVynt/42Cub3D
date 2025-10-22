/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/22 00:02:20 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_fill_split_bg(mlx_image_t *bg)
{
	uint32_t	u;
	uint32_t	v;
	uint32_t	center;

	center = bg->height / 2 / PIXEL_SIZE * PIXEL_SIZE;
	v = 0;
	while (v < center)
	{
		u = -1;
		while (++u < bg->width)
			put_pixel(bg, u, v, ft_game()->render.top_color);
		v++;
	}
	while (v < bg->height)
	{
		u = -1;
		while (++u < bg->width)
			put_pixel(bg, u, v, ft_game()->render.bottom_color);
		v++;
	}
}

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
	if (game->view3d_bg)
		mlx_delete_image(game->mlx, game->view3d_bg);
	if (game->render.depth)
		free(game->render.depth);
	game->render.depth = malloc(sizeof(float) * (width / PIXEL_SIZE + 1));
	if (!game->render.depth)
	{
		printf("Error: Could not reallocate depth buffer for width %d\n", width);
		return ;
	}
	game->render.projection_plane_dist = (width / 2.0) / tan(FOV_RAD / 2.0);
	game->view3d_bg = mlx_new_image(game->mlx, width, height);
	ft_fill_split_bg(game->view3d_bg);
	game->view3d = mlx_new_image(game->mlx, width, height);
	game->minimap = mlx_new_image(game->mlx, width / 3, height / 3);
	game->miniplayer = mlx_new_image(game->mlx, width / 3, height / 3);
	if (!game->minimap || !game->miniplayer || !game->view3d)
		return ;
	draw_map(game->minimap, map);
	ft_update(game);
	mlx_image_to_window(game->mlx, game->view3d_bg, 0, 0);
	mlx_image_to_window(game->mlx, game->view3d, 0, 0);
	mlx_image_to_window(game->mlx, game->minimap, 0, 0);
	mlx_image_to_window(game->mlx, game->miniplayer, 0, 0);
}

// static inline void put_pixel(mlx_image_t *image, u_int32_t x, u_int32_t y, uint32_t color)
// {
// 	if (x < image->width && y < image->height)
// 		((uint32_t *)image->pixels)[y * image->width + x] = color;
// }

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
		put_pixel(image, pos.u + i, pos.v - size / 2, COLOR_RED);
		put_pixel(image, pos.u + i, pos.v + size / 2, COLOR_GREEN);
		put_pixel(image, pos.u - size / 2, pos.v + i, COLOR_YELLOW);
		put_pixel(image, pos.u + size / 2, pos.v + i, COLOR_BLUE);
		i++;
	}
}

void	draw_square(mlx_image_t *image, int size, t_point pos, uint32_t color)
{
	int i;
	int j;

	if ((color & 0xFF000000) == 0)
		return ;
	i = -size / 2;
	while (i <= size / 2)
	{
		j = -size / 2;
		while (j <= size / 2)
		{
			put_pixel(image, pos.u + i, pos.v + j, color);
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
				put_pixel(image, px, py, color);
				// if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				// 	pixels[py * WIDTH + px] = color;
			}
		}
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

void	draw_walls(mlx_image_t *image)
{
	uint32_t	x;

	x = PIXEL_SIZE / 2;
	while (x < ft_game()->view3d->width)
	{
		draw_wall(image, x);
		x += PIXEL_SIZE;
	}
}

void	ft_calculate_sprite(mlx_image_t *image, t_sprite *sprite)
{
	t_player		*player;
	t_spriterender	*sp;
	t_vec2			sp_dir;

	sp = &sprite->sp;
	if (!sprite->texture || !sprite->texture->pixels)
		return ;
	sp->visible = true;
	sprite->next = NULL;
	player = ft_game()->player;
	sp_dir = (t_vec2){sprite->pos.x - player->pos.x, sprite->pos.y - player->pos.y};
	sp->dist = ft_vec2_length(sp_dir);
	sp->angle = ft_angle_between_vec2((t_vec2){player->lookdir.x, player->lookdir.y}, sp_dir);
	if (sp->dist < 0.2f || fabs(sp->angle) > FOV_RAD / 2 + M_PI / 20)
	{
		sp->visible = false;
		return ;
	}
	sp->dist *= cos(sp->angle);
	sp->screen_pos.x = (float)(image->width / 2.0f + (sp->angle / FOV_RAD) * image->width);
	sp->screen_pos.y = (float)(image->height / 2.0f);
	sp->max_size = (1.0f / sp->dist) * ft_game()->render.projection_plane_dist;
	sp->size.u = (int)(sprite->texture->width * sp->max_size / STANDARD_SPRITE_SIZE);
	sp->size.v = (int)(sprite->texture->height * sp->max_size / STANDARD_SPRITE_SIZE);
	sp->start.u = (int)(sp->screen_pos.x) - sp->size.u / 2;
	sp->start.v = (int)(sp->screen_pos.y) - sp->size.v + sp->max_size * (0.5f - sprite->bottom_offset / 2);
	sp->start.v += sp->max_size * 0.5f * ft_game()->player->jump_height + player->lookupdown;
}

void	ft_add_sprite_to_list(t_sprite *head, t_sprite *sprite)
{
	t_sprite	*current;

	if (!head || !sprite || !sprite->sp.visible)
		return ;
	current = head;
	while (current->next && current->next->sp.dist > sprite->sp.dist)
		current = current->next;
	sprite->next = current->next;
	current->next = sprite;
}

void	draw_sprites(mlx_image_t *image)
{
	int			i;
	t_sprite	*temp;

	if (!ft_game()->sh)
		return ;
	ft_game()->sh->next = NULL;
	ft_game()->sh->sp.dist = 100000.0f;
	i = -1;
	while (++i < ft_game()->item_count)
	{
		ft_calculate_sprite(image, &ft_game()->items[i].sprite);
		ft_add_sprite_to_list(ft_game()->sh, &ft_game()->items[i].sprite);
	}
	i = -1;
	while (++i < ft_game()->char_count)
	{
		ft_calculate_sprite(image, &ft_game()->chars[i].sprite);
		ft_add_sprite_to_list(ft_game()->sh, &ft_game()->chars[i].sprite);
	}
	temp = ft_game()->sh->next;
	while (temp)
	{
		draw_sprite(image, temp);
		temp = temp->next;
	}
}

void	draw_doors(mlx_image_t *image)
{
	t_door door;

	door = ft_game()->doors[0];
	door.sprite.pos = door.pos;
	door.closed = true;
	door.key_needed = false;
	ft_calculate_sprite(image, &door.sprite);
	// draw_sprite(image, &(door.sprite));
}

void open_door(int i)
{
	t_door *door;

	door = &ft_game()->doors[i];
	if (!door->is_opening)
		return ;
	door->dt += door->is_opening * ft_game()->dt;
	if (door->closed && door->dt >= DOOR_OPEN_TIME)
	{
		door->closed = false;
	}
	if (door->dt >= 2 * DOOR_OPEN_TIME)
		door->is_opening = -1;
	if (door->is_opening == -1 && door->dt <= DOOR_OPEN_TIME)
		door->closed = true;
	if (door->dt <= 0.0f)
	{
		door->is_opening = 0;
		door->dt = 0.0f;
	}
}