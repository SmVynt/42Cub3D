/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:16:51 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/28 20:33:46 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include <GLFW/glfw3.h>

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
