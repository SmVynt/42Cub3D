/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:08:47 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/05 00:14:21 by psmolin          ###   ########.fr       */
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
