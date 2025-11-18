/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/17 12:17:21 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_clamp_new_position(t_vec2 *player_pos, t_vec2 new_pos_delta)
{
	t_vec2	border_offset;
	t_vec2	closest_tile_border;
	t_vec2	signs;

	signs.x = ft_signd(new_pos_delta.x);
	signs.y = ft_signd(new_pos_delta.y);
	closest_tile_border.x = round(player_pos->x + signs.x * 0.5)
		- signs.x * (TILE_BORDER + 0.5);
	if (new_pos_delta.x == 0.0)
		closest_tile_border.x = player_pos->x;
	closest_tile_border.y = round(player_pos->y + signs.y * 0.5)
		- signs.y * (TILE_BORDER + 0.5);
	if (new_pos_delta.y == 0.0)
		closest_tile_border.y = player_pos->y;
	border_offset = (t_vec2){ft_signd(new_pos_delta.x) * TILE_BORDER,
		ft_signd(new_pos_delta.y) * TILE_BORDER};
	if (ft_is_wall((t_vec2){player_pos->x + new_pos_delta.x
			+ border_offset.x, player_pos->y}))
		new_pos_delta.x = closest_tile_border.x - player_pos->x;
	if (ft_is_wall((t_vec2){player_pos->x, player_pos->y
			+ new_pos_delta.y + border_offset.y}))
		new_pos_delta.y = closest_tile_border.y - player_pos->y;
	player_pos->x += new_pos_delta.x;
	player_pos->y += new_pos_delta.y;
}

static void	ft_step_check_for_stop(bool *footsteps_playing)
{
	if (*footsteps_playing)
	{
		audio_stop(ft_game()->audio.footstep_sound);
		*footsteps_playing = false;
	}
}

void	ft_update_player_movement(t_player *player)
{
	t_vec2		move_step;
	t_vec2		new_pos;
	static bool	footsteps_playing = false;

	if (player->is_jumping)
		ft_step_check_for_stop(&footsteps_playing);
	if (player->mov_control.v != 0 || player->mov_control.u != 0)
	{
		if (!footsteps_playing && !player->is_jumping)
		{
			audio_play_music(ft_game()->audio.footstep_sound, true);
			footsteps_playing = true;
		}
		move_step = ft_normalize_vec2(
				(t_vec2){player->mov_control.u, player->mov_control.v});
		move_step.x *= PLAYERSPEED * ft_game()->dt;
		move_step.y *= PLAYERSPEED * ft_game()->dt;
		new_pos.x = player->lookdir.x * move_step.y;
		new_pos.y = player->lookdir.y * move_step.y;
		new_pos.x -= player->lookdir.y * move_step.x;
		new_pos.y += player->lookdir.x * move_step.x;
		ft_clamp_new_position(&player->pos, new_pos);
	}
	else
		ft_step_check_for_stop(&footsteps_playing);
}
