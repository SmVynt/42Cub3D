/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_key_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:30:56 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/08 22:51:13 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement_keys(t_gs *game, t_player *player)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		player->mov_control.u = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		player->mov_control.u = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		player->mov_control.v = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		player->mov_control.v = -1;
}

static void	handle_rotation_keys(t_gs *game, t_player *player)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->rot_control.u = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->rot_control.u = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		player->rot_control.v = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		player->rot_control.v = 1;
}

static void	handle_action_keys(t_gs *game, t_player *player)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE) && !player->is_jumping)
	{
		player->jump_impuls = JUMP_IMPULSE;
		player->is_jumping = true;
	}
}

void	ft_key_press_hook(void *param)
{
	t_player	*player;
	t_gs		*game;

	game = (t_gs *)param;
	player = game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		ft_exit();
	handle_movement_keys(game, player);
	handle_rotation_keys(game, player);
	if (game->game_over == 1)
		return ;
	handle_action_keys(game, player);
}
