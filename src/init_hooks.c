/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:16:51 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/27 23:33:48 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include <GLFW/glfw3.h>

static bool	has_key(t_player *player)
{
	t_list		*pocket_items;
	t_item		*item;

	pocket_items = player->pocket;
	if (!pocket_items)
		return (false);
	while (pocket_items)
	{
		item = (t_item *)pocket_items->content;
		if (item->type == IT_KEY)
			return (true);
		pocket_items = pocket_items->next;
	}
	return (false);
}

void	try_open_doors(t_gs *game)
{
	t_player	*player;
	t_vec2		vec_door;
	float		door_angle;
	int			i;

	player = game->player;
	i = 0;
	while (i < game->door_count)
	{
		vec_door = (t_vec2){game->doors[i].pos.x - player->pos.x,
			game->doors[i].pos.y - player->pos.y};
		door_angle = fabsf(ft_angle_between_vec2(vec_door,
					(t_vec2){player->lookdir.x, player->lookdir.y}));
		if (ft_vec2_length(vec_door) <= DOOR_OPEN_DIST
			&& door_angle < DOOR_OPEN_ANGLE)
		{
			if (!game->doors[i].key_needed || has_key(player))
			{
				if (!game->doors[i].is_opening)
					game->doors[i].is_opening = 1;
			}
		}
		i++;
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_gs		*game;

	game = (t_gs *)param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_RELEASE)
	{
		game->playing = !game->playing;
		if (game->playing)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	}
}

static void	ft_mouse_move(double x, double y, void *param)
{
	t_player	*player;
	t_gs		*game;

	game = (t_gs *)param;
	if (!game->playing)
		return ;
	player = game->player;
	if (player->mouse_pos.x == -1)
		player->mouse_diff.x = 0.0f;
	else
		player->mouse_diff.x = player->mouse_pos.x - x;
	player->mouse_pos.x = x;
	if (player->mouse_pos.y == -1)
		player->mouse_diff.y = 0.0f;
	else
		player->mouse_diff.y = player->mouse_pos.y - y;
	player->mouse_pos.y = y;
}

void	ft_createhooks(void)
{
	t_gs	*game;

	game = ft_game();
	printf(COLOR_G"Creating hooks...\n"COLOR_X);
	if (game->playing)
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	else
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	mlx_resize_hook(game->mlx, draw, game);
	mlx_loop_hook(game->mlx, ft_key_press_hook, game);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_cursor_hook(game->mlx, ft_mouse_move, game);
	mlx_loop_hook(game->mlx, ft_update, game);
	printf(COLOR_G"Hooks created successfully.\n"COLOR_X);
}
