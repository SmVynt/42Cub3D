/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_chars_alien.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:28:13 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 20:02:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_can_see_player(t_vec2 char_pos, t_vec2 player_pos)
{
	t_rayrender	ray;
	double		wall_distance;
	double		player_distance;

	char_pos.x += 0.5;
	char_pos.y += 0.5;
	player_pos.x += 0.5;
	player_pos.y += 0.5;
	ray.start = char_pos;
	ray.dir = ft_normalize_vec2((t_vec2){
			player_pos.x - char_pos.x,
			player_pos.y - char_pos.y});
	ray.end = get_ray_end(&ray);
	wall_distance = ft_vec2_length((t_vec2){
			ray.end.x - char_pos.x,
			ray.end.y - char_pos.y});
	player_distance = ft_vec2_length((t_vec2){
			player_pos.x - char_pos.x,
			player_pos.y - char_pos.y});
	if (wall_distance > player_distance)
		return (true);
	return (false);
}

void	ft_ai_alien_moving(t_char *ch)
{
	if (ch->ai.state == AI_MOVING)
	{
		ch->ai.timer -= ft_game()->dt;
		ch->ai.lerp_progress += ch->ai.lerp_speed * ft_game()->dt;
		if (ch->ai.lerp_progress >= 1.0 || ch->ai.timer <= 0.0)
			ch->ai.state = AI_IDLE;
		ch->sprite.pos = ft_lerpvec2(ch->ai.start_pos,
				ch->ai.target_pos, ch->ai.lerp_progress);
	}
}

void	ft_ai_alien(t_char *ch)
{
	double	distance;

	if (ch->ai.state == AI_IDLE)
	{
		if (ft_can_see_player(ch->sprite.pos, ft_game()->player->pos))
		{
			ch->ai.state = AI_MOVING;
			ch->ai.lerp_progress = 0.0;
			ch->ai.speed = AI_SPEED_ALIEN;
			distance = ft_vec2_length((t_vec2){
					ft_game()->player->pos.x - ch->sprite.pos.x,
					ft_game()->player->pos.y - ch->sprite.pos.y});
			if (distance > 0.01)
				ch->ai.lerp_speed = ch->ai.speed / distance;
			ch->ai.start_pos = ch->sprite.pos;
			ch->ai.target_pos = ft_game()->player->pos;
			ch->ai.timer = AI_TIMER;
		}
	}
	ft_ai_alien_moving(ch);
}
