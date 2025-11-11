/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:16:51 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/11 13:26:37 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <signal.h>

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_gs		*game;

	game = (t_gs *)param;
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_RELEASE)
	{
		game->playing = !game->playing;
		if (game->playing)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		interact(game);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_RELEASE)
	{
		if (game->mmap.picked)
		{
			game->mmap.opening = !game->mmap.opening;
			game->mmap.enabled = true;
		}
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

static void	ft_close_hook(void *param)
{
	(void)param;
	ft_exit();
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
	mlx_close_hook(game->mlx, ft_close_hook, game);
	mlx_resize_hook(game->mlx, draw, game);
	mlx_loop_hook(game->mlx, ft_key_press_hook, game);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_cursor_hook(game->mlx, ft_mouse_move, game);
	mlx_loop_hook(game->mlx, ft_update, game);
	printf(COLOR_G"Hooks created successfully.\n"COLOR_X);
}
