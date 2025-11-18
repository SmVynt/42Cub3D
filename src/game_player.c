/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:08:47 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/17 16:10:44 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_player_try_damage(double damage)
{
	t_player		*player;
	static double	time;

	if (damage <= 0.0)
		return (false);
	if (mlx_get_time() - time < 1.0)
		return (false);
	time = mlx_get_time();
	player = ft_game()->player;
	if (player->hp <= 0.0)
		return (false);
	player->hp -= damage;
	if (damage == LAV_DAMAGE_PER_SEC)
		audio_play(ft_game()->audio.hit_lava_sound);
	else
		audio_play(ft_game()->audio.hit_sound);
	player->is_shaking = true;
	player->shaking_start = mlx_get_time();
	if (player->hp < 0.0)
		player->hp = 0.0;
	ft_update_hp_bar();
	return (true);
}

bool	ft_player_try_heal(double heal)
{
	t_player	*player;

	if (heal <= 0.0)
		return (false);
	player = ft_game()->player;
	if (player->hp >= MAX_HP)
		return (false);
	player->hp += heal;
	if (player->hp > MAX_HP)
		player->hp = MAX_HP;
	ft_update_hp_bar();
	return (true);
}

void	shaky_shaky(void)
{
	t_player	*player;
	t_vec2		perp;
	double		offset;
	double		elapsed;
	double		intensity;

	player = ft_game()->player;
	elapsed = mlx_get_time() - player->shaking_start;
	if (elapsed > SHAKING_TIME)
	{
		player->is_shaking = false;
		player->jump_height = 0.1;
		return ;
	}
	intensity = expf(-5.0 * elapsed / SHAKING_TIME);
	perp.x = -player->lookdir.y;
	perp.y = player->lookdir.x;
	offset = rand_in_range(-MAX_HOR_SHAKING, MAX_HOR_SHAKING) * intensity;
	player->pos.x += perp.x * offset;
	player->pos.y += perp.y * offset;
	player->jump_height = rand_in_range(-MAX_VERT_SHAKING, MAX_VERT_SHAKING)
		* intensity;
}
