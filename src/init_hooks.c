/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:16:51 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/03 19:45:17 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_key_press_hook(void *param)
{
	t_player	*player;
	t_gs		*game;

	game = (t_gs *)param;
	player = game->player;
	player->move = (t_vec2){0, 0};
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		ft_exit();
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)
			|| mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->move.x = -1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D)
			|| mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->move.x = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W)
			|| mlx_is_key_down(game->mlx, MLX_KEY_UP))
		player->move.y = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S)
			|| mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		player->move.y = -1;
	else
		return ;
	ft_update(NULL);
}
static void ft_mouse_move(double x, double y, void *param)
{
	t_player	*player;
	t_gs		*game;
	
	(void) y;
	game = (t_gs *)param;
	player = game->player;
	if (x - player->mouse_x)
	{
		player->move.x = ((x - player->mouse_x) > 0) - ((x - player->mouse_x) < 0);
		player->mouse_x = x;
		ft_update(NULL);
	}
}

void	ft_createhooks(void)
{
	t_gs	*game;

	game = ft_game();
	printf(COLOR_G"Creating hooks...\n"COLOR_X);
	mlx_loop_hook(game->mlx, ft_key_press_hook, game);
	mlx_cursor_hook(game->mlx, ft_mouse_move, game);
	// mlx_loop_hook(game->mlx, ft_update, game);
	printf(COLOR_G"Hooks created successfully.\n"COLOR_X);
}
