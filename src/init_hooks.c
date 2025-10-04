/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:16:51 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/03 19:16:35 by psmolin          ###   ########.fr       */
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
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		player->mov_control.u = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		player->mov_control.v = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		player->mov_control.v = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->rot_control = -1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->rot_control = 1;
}

static void ft_mouse_move(double x, double y, void *param)
{
	t_player	*player;
	t_gs		*game;

	game = (t_gs *)param;
	player = game->player;
	player->mouse_dx = player->mouse_x - x;
	player->mouse_x = x;
	(void)y;
}


void	ft_createhooks(void)
{
	t_gs	*game;

	game = ft_game();
	printf(COLOR_G"Creating hooks...\n"COLOR_X);
	mlx_loop_hook(game->mlx, ft_key_press_hook, game);
	mlx_cursor_hook(game->mlx, ft_mouse_move, game);
	mlx_loop_hook(game->mlx, ft_update, game);
	printf(COLOR_G"Hooks created successfully.\n"COLOR_X);
}
