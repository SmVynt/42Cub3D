/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/07 18:02:13 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static int ft_is_wall(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)(p.x - 0.5f);
	y = (int)(p.y - 0.5f);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (1);
	if (ft_strchar(MAP_WALL_CHARS, map->tile[y][x]) != NULL)
		return (1);
	return (0);
}

static void	ft_clamp_new_position(t_vec2 *player_pos,t_vec2 new_pos_delta)
{
	float	border_width = 0.2f;
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
	border_offset = (t_vec2){border_width, border_width};
	if (new_pos_delta.x < 0.0f)
		border_offset.x = -border_width;
	if (new_pos_delta.y < 0.0f)
		border_offset.y = -border_width;
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
		player->lookdir = ft_mat4_transform_vec3(ft_mat4_rotation_z(player->rot_control * PI / 90.0f), player->lookdir);
	}
	if (player->mouse_dx != 0.0f)
	{
		player->lookdir = ft_mat4_transform_vec3(ft_mat4_rotation_z(-player->mouse_dx * PI / 60.0f), player->lookdir);
		player->mouse_dx = 0.0f;
	}
	if (player->mov_control.v != 0 || player->mov_control.u != 0)
	{
		move_step = (t_vec2){player->mov_control.u * 0.1f, player->mov_control.v * 0.1f};
		new_pos.x = player->lookdir.x * move_step.y;
		new_pos.y = player->lookdir.y * move_step.y;
		new_pos.x -= player->lookdir.y * move_step.x;
		new_pos.y += player->lookdir.x * move_step.x;
		ft_clamp_new_position(&player->pos, new_pos);
	}
	// mlx_set_mouse_pos(ft_game()->mlx, WIDTH / 2, HEIGHT / 2);
}

void	ft_update_graphics(void)
{
	int width;
	int height;

	width = ft_game()->miniplayer->width;
	height = ft_game()->miniplayer->height;
	printf("%i %i\n", width, height);
	mlx_delete_image(ft_game()->mlx, ft_game()->miniplayer);
	ft_game()->miniplayer = mlx_new_image(ft_game()->mlx, width, height);
	draw_player(ft_game()->miniplayer);
	mlx_image_to_window(ft_game()->mlx, ft_game()->miniplayer, 0, 0);
}

void	ft_update(void *param)
{
	(void)param;
	ft_update_player();
	ft_update_graphics();
	// printf("Player pos: %f %f\n", ft_game()->player->pos.x, ft_game()->player->pos.y);
	// printf("Player movement: %d %d\n", ft_game()->player->move.x, ft_game()->player->move.y);
	// Game loop logic goes here

}
