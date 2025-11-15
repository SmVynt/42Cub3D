/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_prefabs_items.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 16:33:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_prefab_hp_chand(t_gs *game)
{
	game->prefabs.items[IT_HEALTH] = (t_item){
		.type = IT_HEALTH,
		.pickupable = true,
		.active = true,
		.pickup_value = 25,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_HEALTH,
		.sprite.bottom_offset = 0.0
	};
	game->prefabs.items[IT_CHANDELIER] = (t_item){
		.type = IT_CHANDELIER,
		.pickupable = false,
		.active = true,
		.pickup_value = 0,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_CHANDELIER,
		.sprite.bottom_offset = -0.05
	};
}

static void	ft_init_prefab_key_barrel(t_gs *game)
{
	game->prefabs.items[IT_KEY] = (t_item){
		.type = IT_KEY,
		.pickupable = true,
		.active = true,
		.pickup_value = 1,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_KEY,
		.sprite.bottom_offset = 0.0
	};
	game->prefabs.items[IT_BARREL] = (t_item){
		.type = IT_BARREL,
		.pickupable = false,
		.active = true,
		.pickup_value = 1,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_BARREL,
		.sprite.bottom_offset = -0.05
	};
}

static void	ft_init_prefab_map(t_gs *game)
{
	game->prefabs.items[IT_MAP] = (t_item){
		.type = IT_MAP,
		.pickupable = true,
		.active = true,
		.pickup_value = 1,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_MAP,
		.sprite.bottom_offset = 0.0
	};
}

static void	ft_init_prefab_fire(t_gs *game)
{
	game->prefabs.items[IT_FIRE] = (t_item){
		.type = IT_FIRE,
		.pickupable = false,
		.active = true,
		.pickup_value = 1,
		.sprite = (t_sprite){
		.texture = NULL,
		.path = TEX_FIRE,
		.bottom_offset = 0.0,
		.animated = true,
		.anim = (t_anim){
		.n_frames = 8,
		.frame_duration = 0.07f,
		.anim_timer = 0.0,
		.curr_frame = rand() % 8
	}
	}
	};
}

void	ft_init_prefabs_items(t_gs *game)
{
	ft_init_prefab_hp_chand(game);
	ft_init_prefab_key_barrel(game);
	ft_init_prefab_fire(game);
	ft_init_prefab_map(game);
}
