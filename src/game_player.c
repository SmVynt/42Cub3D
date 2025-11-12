/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:08:47 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 15:34:27 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_player_try_damage(float damage)
{
	t_player	*player;

	if (damage <= 0.0f)
		return (false);
	player = ft_game()->player;
	if (player->hp <= 0.0f)
		return (false);
	player->hp -= damage;
	player->is_shaking = true;
	player->shaking_start = mlx_get_time();
	if (player->hp < 0.0f)
		player->hp = 0.0f;
	ft_update_hp_bar();
	return (true);
}

bool	ft_player_try_heal(float heal)
{
	t_player	*player;

	if (heal <= 0.0f)
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
	float		offset;
	double		elapsed;
	float		intensity;

	player = ft_game()->player;
	elapsed = mlx_get_time() - player->shaking_start;
	if (elapsed > SHAKING_TIME)
	{
		player->is_shaking = false;
		player->jump_height = 0.0f;
		return ;
	}
	intensity = expf(-5.0f * elapsed / SHAKING_TIME);
	perp.x = -player->lookdir.y;
	perp.y = player->lookdir.x;
	offset = rand_in_range(-MAX_HOR_SHAKING, MAX_HOR_SHAKING) * intensity;
	player->pos.x += perp.x * offset;
	player->pos.y += perp.y * offset;
	player->jump_height = rand_in_range(-MAX_VERT_SHAKING, MAX_VERT_SHAKING)
		* intensity;
}
