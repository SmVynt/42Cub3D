/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/12 18:26:14 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_is_wall(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)roundf(p.x);
	y = (int)roundf(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (1);
	if (ft_strchar(MAP_WALL_CHARS, map->tile[y][x]) != NULL)
		return (1);
	return (0);
}

static void	ft_clamp_new_position(t_vec2 *player_pos,t_vec2 new_pos_delta)
{
	float	border_width = 0.1f;
	t_vec2	border_offset;
	t_vec2	closest_tile_border;

	if (new_pos_delta.x < 0.0f)
		closest_tile_border.x = (float)((int)(player_pos->x)) + 0.5f + border_width;
	else
		closest_tile_border.x = (float)((int)(player_pos->x + 1.0f)) - 0.5f - border_width;
	if (new_pos_delta.y < 0.0f)
		closest_tile_border.y = (float)((int)(player_pos->y)) + 0.5f + border_width;
	else
		closest_tile_border.y = (float)((int)(player_pos->y + 1.0f)) - 0.5f - border_width;
	border_offset = (t_vec2){ft_signf(new_pos_delta.x) * border_width, ft_signf(new_pos_delta.y) * border_width};
	if (ft_is_wall((t_vec2){player_pos->x + new_pos_delta.x + border_offset.x, player_pos->y}))
		new_pos_delta.x = closest_tile_border.x - player_pos->x;
	if (ft_is_wall((t_vec2){player_pos->x, player_pos->y + new_pos_delta.y + border_offset.y}))
		new_pos_delta.y = closest_tile_border.y - player_pos->y;
	if (ft_is_wall((t_vec2){player_pos->x + new_pos_delta.x + border_offset.x, player_pos->y + border_offset.y}))
		{
			if (fabs(new_pos_delta.x) > fabs(new_pos_delta.y))
				new_pos_delta.y = closest_tile_border.y - player_pos->y;
			else
				new_pos_delta.x = closest_tile_border.x - player_pos->x;
		}
	player_pos->x += new_pos_delta.x;
	player_pos->y += new_pos_delta.y;
}

void	ft_update_player(void)
{
	t_player	*player;
	t_vec2		move_step;
	t_vec2		new_pos;

	player = ft_game()->player;
	if (player->rot_control != 0)
	{
		player->lookdir = ft_mat4_transform_vec3(ft_mat4_rotation_z(player->rot_control * ROTATIONSPEED * ft_game()->dt), player->lookdir);
	}
	if (player->mouse_dx != 0.0f)
	{
		player->lookdir = ft_mat4_transform_vec3(ft_mat4_rotation_z(-player->mouse_dx * ROTATIONSPEED * ft_game()->dt * MOUSE_SENS), player->lookdir);
		player->mouse_dx = 0.0f;
	}
	if (player->mov_control.v != 0 || player->mov_control.u != 0)
	{
		move_step = ft_normalize_vec2((t_vec2){player->mov_control.u, player->mov_control.v});
		// move_step = (t_vec2){player->mov_control.u, player->mov_control.v};
		move_step.x *= PLAYERSPEED * ft_game()->dt;
		move_step.y *= PLAYERSPEED * ft_game()->dt;
		// printf("move_step: %.2f, %.2f\n", move_step.x, move_step.y);
		new_pos.x = player->lookdir.x * move_step.y;
		new_pos.y = player->lookdir.y * move_step.y;
		new_pos.x -= player->lookdir.y * move_step.x;
		new_pos.y += player->lookdir.x * move_step.x;
		ft_clamp_new_position(&player->pos, new_pos);
	}
	// mlx_set_mouse_pos(ft_game()->mlx, WIDTH / 2, HEIGHT / 2);
}

static void	ft_update_view3d(void *param)
{
	mlx_image_t	*image;

	if (!param)
		return ;
	image = (mlx_image_t *)param;
	memset(image->pixels, 0, image->width * image->height * sizeof(int32_t));
	draw_walls(ft_game()->view3d);
	draw_sprites(ft_game()->view3d);
}

void	ft_update_graphics(void)
{
	ft_update_view3d(ft_game()->view3d);
	ft_update_minimap(ft_game()->miniplayer);
}

void	ft_update_minimap(void *param)
{
	mlx_image_t	*image;

	if (!param)
		return ;
	image = (mlx_image_t *)param;
	memset(image->pixels, 0, image->width * image->height * sizeof(int32_t));
	draw_player(image);
}

static void ft_update_dt(void)
{
	static struct timeval last_time;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0) {
		last_time = current_time;
	}

	float elapsed = (current_time.tv_sec - last_time.tv_sec) +
					(current_time.tv_usec - last_time.tv_usec) / 1000000.0f;
	if (elapsed > MAX_DT)
		elapsed = MAX_DT;
	ft_game()->dt = elapsed;
	// printf("fps: %.1f\n", 1.0f / ft_game()->dt);
	last_time = current_time;
}

void	ft_update(void *param)
{
	t_player	*player;

	player = ft_game()->player;
	(void)param;
	ft_update_dt();
	if (player->mov_control.u != 0
		|| player->mov_control.v != 0
		|| player->rot_control != 0
		|| player->mouse_dx != 0.0f)
	{
		ft_update_player();
		ft_update_graphics();
	}
}
