/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:16:51 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/14 17:34:09 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <GLFW/glfw3.h>

static void	ft_key_press_hook(void *param)
{
	t_player	*player;
	t_gs		*game;

	game = (t_gs *)param;
	player = game->player;
	player->mov_control = (t_point){0, 0};
	player->rot_control = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		ft_exit();
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		player->mov_control.u = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		player->mov_control.u = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		player->mov_control.v = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		player->mov_control.v = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->rot_control = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->rot_control = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE) && !player->is_jumping)
	{
		player->jump_impuls = 500.0;
		player->is_jumping = true;
	}
	// if (player->mov_control.u != 0 || player->mov_control.v != 0 || player->rot_control != 0)
		// ft_update(game);
}

static void ft_mouse_move(double x, double y, void *param)
{
	t_player	*player;
	t_gs		*game;

	game = (t_gs *)param;
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
	mlx_resize_hook(game->mlx, draw, game);
	mlx_loop_hook(game->mlx, ft_key_press_hook, game);
	mlx_cursor_hook(game->mlx, ft_mouse_move, game);
	// mlx_loop_hook(game->mlx, ft_update_minimap, game->miniplayer);
	// mlx_loop_hook(game->mlx, ft_update_view3d, game->view3d);
	mlx_loop_hook(game->mlx, ft_update, game);
	printf(COLOR_G"Hooks created successfully.\n"COLOR_X);
}
