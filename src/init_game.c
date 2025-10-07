/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/07 18:04:06 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_set_player(void)
{
	t_player	*player;
	t_gs		*game;
	char		start_char;

	game = ft_game();
	player = game->player;
	player->pos = (t_vec2){(float)game->map.start.u + 1.0f, (float)game->map.start.v + 1.0f};
	start_char = game->map.tile[game->map.start.v][game->map.start.u];
	if (start_char == 'N')
		player->lookdir = (t_vec3){0.0f, -1.0f, 0.0f};
	if (start_char == 'E')
		player->lookdir = (t_vec3){1.0f, 0.0f, 0.0f};
	if (start_char == 'S')
		player->lookdir = (t_vec3){0.0f, 1.0f, 0.0f};
	if (start_char == 'W')
		player->lookdir = (t_vec3){-1.0f, 0.0f, 0.0f};
}

void	ft_setgame(void)
{
	ft_set_player();
}
