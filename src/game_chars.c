/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:28:13 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 20:53:41 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_ai_slime_idle(t_char *ch)
{
	t_vec2	new_target;

	if (ch->ai.facing == DIR_NO)
		new_target = (t_vec2){ch->sprite.pos.x, ch->sprite.pos.y - 1.0};
	else if (ch->ai.facing == DIR_EA)
		new_target = (t_vec2){ch->sprite.pos.x + 1.0, ch->sprite.pos.y};
	else if (ch->ai.facing == DIR_SO)
		new_target = (t_vec2){ch->sprite.pos.x, ch->sprite.pos.y + 1.0};
	else
		new_target = (t_vec2){ch->sprite.pos.x - 1.0, ch->sprite.pos.y};
	if (ft_is_wall(new_target) == false)
	{
		ch->ai.state = AI_MOVING;
		ch->ai.lerp_progress = 0.0;
		ch->ai.speed = AI_SPEED_SLIME;
		ch->ai.lerp_speed = ch->ai.speed / 1.0;
		ch->ai.start_pos = ch->sprite.pos;
		ch->ai.target_pos = new_target;
	}
	else
	{
		ch->ai.facing = (ch->ai.facing + 1 + 2 * (rand() % 2)) % 4;
		ch->ai.timer = AI_TIMER;
		ch->ai.state = AI_THINKING;
	}
}

static void	ft_ai_slime(t_char *ch)
{
	if (ch->ai.state == AI_IDLE)
		ft_ai_slime_idle(ch);
	if (ch->ai.state == AI_THINKING)
	{
		ch->ai.timer -= ft_game()->dt;
		if (ch->ai.timer <= 0.0)
			ch->ai.state = AI_IDLE;
	}
	if (ch->ai.state == AI_MOVING)
	{
		ch->ai.lerp_progress += ch->ai.lerp_speed * ft_game()->dt;
		if (ch->ai.lerp_progress >= 1.0)
			ch->ai.state = AI_IDLE;
		ch->sprite.pos = ft_lerpvec2(ch->ai.start_pos, ch->ai.target_pos,
				ch->ai.lerp_progress);
	}
}

static void	update_char(t_char *ch)
{
	if (!ch->alive)
		return ;
	if (ch->type == CH_ALIEN)
		ft_ai_alien(ch);
	if (ch->type == CH_SLIME)
		ft_ai_slime(ch);
	if (ft_vec2_length((t_vec2){
			ft_game()->player->pos.x - ch->sprite.pos.x,
			ft_game()->player->pos.y - ch->sprite.pos.y}) < AI_CONTACT_DIST)
		ft_player_try_damage(ch->dps);
	return ;
}

void	ft_update_chars(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	if (game->game_over)
		return ;
	i = 0;
	while (i < game->char_count)
	{
		update_char(&game->chars[i]);
		i++;
	}
}
