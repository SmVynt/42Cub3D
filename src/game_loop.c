/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/17 17:05:47 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_update_dt(void)
{
	static double			last_time;
	double					current_time;
	double					elapsed;

	current_time = mlx_get_time();
	elapsed = current_time - last_time;
	if (elapsed > MAX_DT)
		elapsed = MAX_DT;
	ft_game()->dt = (double)elapsed;
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
	if (!ft_game()->game_over && player->hp <= 0)
	{
		ft_game()->game_over = -1;
		printf(COLOR_R"Player has died! Game Over!\n"COLOR_X);
		show_end_screen();
		audio_stop_all(&ft_game()->audio);
		audio_play(ft_game()->audio.absorbtion);
	}
	if (!ft_game()->game_over && ft_is_pod(player->pos))
	{
		ft_game()->game_over = 1;
		printf(COLOR_G"Player reached the pod! Victory!\n"COLOR_X);
		show_end_screen();
		audio_stop_all(&ft_game()->audio);
		audio_play(ft_game()->audio.victory);
	}
	print_debug("updating graphics...");
}

void	ft_update(void *param)
{
	t_gs		*game;
	t_player	*player;
	int			i;

	game = ft_game();
	if (game->game_over)
		return ;
	if (game->view3d->height == 0 || game->view3d->width == 0)
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
