/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 01:45:57 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_update_dt(void)
{
	static struct timeval	last_time;
	struct timeval			current_time;
	float					elapsed;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0)
		last_time = current_time;
	elapsed = (current_time.tv_sec - last_time.tv_sec)
		+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0f;
	if (elapsed > MAX_DT)
		elapsed = MAX_DT;
	ft_game()->dt = elapsed;
	last_time = current_time;
}

static void	ft_update_player_general(t_player *player)
{
	print_debug("updating chars...");
	ft_update_chars();
	print_debug("shaky shaky...");
	if (player->is_shaking)
		shaky_shaky();
	print_debug("player update...");
	ft_update_player();
	if (player->hp <= 0)
	{
		ft_game()->game_over = -1;
		show_end_screen();
	}
	if (ft_is_pod(player->pos))
	{
		ft_game()->game_over = 1;
		show_end_screen();
	}
	print_debug("updating graphics...");
}

void	ft_update(void *param)
{
	t_gs		*game;
	t_player	*player;
	int			i;

	game = ft_game();
	if (game->game_over == -1)
		return ;
	player = game->player;
	(void)param;
	print_debug("updating dt...");
	ft_update_dt();
	print_interact_msg(game);
	print_debug("updating doors...");
	i = 0;
	while (i < game->inter_wall_count)
	{
		if (ft_game()->inter_walls[i].is_opening)
			open_door(i);
		i++;
	}
	ft_update_player_general(player);
	ft_update_graphics();
}
