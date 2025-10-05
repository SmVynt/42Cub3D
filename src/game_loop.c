/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/05 17:44:39 by nmikuka          ###   ########.fr       */
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

void	ft_update_player(void)
{
	t_player	*player;
	// float		player_rotation;
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
		if (ft_is_wall((t_vec2){player->pos.x + new_pos.x, player->pos.y}))
			new_pos.x = 0.0f;
		if (ft_is_wall((t_vec2){player->pos.x, player->pos.y + new_pos.y}))
			new_pos.y = 0.0f;

		player->pos.x += new_pos.x;
		player->pos.y += new_pos.y;
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
	// printf("Player movement: %d %d\n", ft_game()->player->move.x, ft_game()->player->move.y);
	// Game loop logic goes here

}
