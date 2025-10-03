/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/02 22:09:08 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_update_player(void)
{
	t_player	*player;
	// float		player_rotation;
	float		move_step;
	t_vec2f		new_pos;

	player = ft_game()->player;
	// player_rotation = atan2f(player->lookdir.y, player->lookdir.x);
	if (player->move.x != 0)
	{
		// player_rotation -= (player->move.x * (PI / 90.0f));
		// player->lookdir.x = cosf(player_rotation);
		// player->lookdir.y = sinf(player_rotation);
		player->lookdir = ft_mat4_transform_vec3(ft_mat4_rotation_z(player->move.x * PI / 90.0f), player->lookdir);
	}
	if (player->move.y != 0)
	{
		move_step = player->move.y * 0.1f;
		new_pos.x = player->pos.x + player->lookdir.x * move_step;
		new_pos.y = player->pos.y + player->lookdir.y * move_step;
		player->pos = new_pos;
	}

}

void	ft_update_graphics(void)
{
	mlx_delete_image(ft_game()->mlx, ft_game()->miniplayer);
	ft_game()->miniplayer = mlx_new_image(ft_game()->mlx, WIDTH, HEIGHT);
	draw_player((uint32_t *)ft_game()->miniplayer->pixels);
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
