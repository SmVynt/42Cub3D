/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:28:13 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/08 22:53:15 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_can_see_player(t_vec2 char_pos, t_vec2 player_pos)
{
	t_rayrender	ray;
	float		wall_distance;
	float		player_distance;

	char_pos.x += 0.5f;
	char_pos.y += 0.5f;
	player_pos.x += 0.5f;
	player_pos.y += 0.5f;
	ray.start = char_pos;
	ray.dir = ft_normalize_vec2((t_vec2){
		player_pos.x - char_pos.x,
		player_pos.y - char_pos.y
	});
	ray.end = get_ray_end(&ray, ray.start, ray.dir, 100, &ray.wall_dir);
	wall_distance = ft_vec2_length((t_vec2){
		ray.end.x - char_pos.x,
		ray.end.y - char_pos.y
	});
	player_distance = ft_vec2_length((t_vec2){
		player_pos.x - char_pos.x,
		player_pos.y - char_pos.y
	});
	if (wall_distance > player_distance)
		return (true);
	return (false);
}

static void	ft_ai_alien(t_char *ch)
{
	float	distance;

	if (ch->ai.state == AI_IDLE)
	{
		if (ft_can_see_player(ch->sprite.pos, ft_game()->player->pos))
		{
			ch->ai.state = AI_MOVING;
			ch->ai.lerp_progress = 0.0f;
			ch->ai.speed = AI_SPEED_ALIEN;
			distance = ft_vec2_length((t_vec2){
				ft_game()->player->pos.x - ch->sprite.pos.x,
				ft_game()->player->pos.y - ch->sprite.pos.y
			});
			if (distance > 0.01f)
				ch->ai.lerp_speed = ch->ai.speed / distance;
			ch->ai.start_pos = ch->sprite.pos;
			ch->ai.target_pos = ft_game()->player->pos;
			ch->ai.timer = AI_TIMER;
		}
	}
	if (ch->ai.state == AI_MOVING)
	{
		ch->ai.timer -= ft_game()->dt;
		ch->ai.lerp_progress += ch->ai.lerp_speed * ft_game()->dt;
		if (ch->ai.lerp_progress >= 1.0f || ch->ai.timer <= 0.0f)
			ch->ai.state = AI_IDLE;
		ch->sprite.pos = ft_lerpvec2(ch->ai.start_pos, ch->ai.target_pos, ch->ai.lerp_progress);
	}
}

static void	ft_ai_slime(t_char *ch)
{
	t_vec2	new_target;

	if (ch->ai.state == AI_IDLE)
	{
		if (ch->ai.facing == DIR_NO)
			new_target = (t_vec2){ch->sprite.pos.x, ch->sprite.pos.y - 1.0f};
		else if (ch->ai.facing == DIR_EA)
			new_target = (t_vec2){ch->sprite.pos.x + 1.0f, ch->sprite.pos.y};
		else if (ch->ai.facing == DIR_SO)
			new_target = (t_vec2){ch->sprite.pos.x, ch->sprite.pos.y + 1.0f};
		else
			new_target = (t_vec2){ch->sprite.pos.x - 1.0f, ch->sprite.pos.y};
		if (ft_is_wall(new_target) == false)
		{
			ch->ai.state = AI_MOVING;
			ch->ai.lerp_progress = 0.0f;
			ch->ai.speed = AI_SPEED_SLIME;
			ch->ai.lerp_speed = ch->ai.speed / 1.0f;
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
	if (ch->ai.state == AI_THINKING)
	{
		ch->ai.timer -= ft_game()->dt;
		if (ch->ai.timer <= 0.0f)
			ch->ai.state = AI_IDLE;
	}
	if (ch->ai.state == AI_MOVING)
	{
		ch->ai.lerp_progress += ch->ai.lerp_speed * ft_game()->dt;
		if (ch->ai.lerp_progress >= 1.0f)
			ch->ai.state = AI_IDLE;
		ch->sprite.pos = ft_lerpvec2(ch->ai.start_pos, ch->ai.target_pos, ch->ai.lerp_progress);
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
		ft_game()->player->pos.y - ch->sprite.pos.y
	}) < AI_CONTACT_DIST)
	{
		ft_player_try_damage(AI_DAMAGE_PER_SEC * ft_game()->dt);
	}
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
