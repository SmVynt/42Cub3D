/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_prefabs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 22:03:26 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	ft_init_prefabs_items(t_gs *game)
// {
// 	game->item_prefabs[IT_HEALTH] = (t_item){
// 		.type = IT_HEALTH,
// 		.pickupable = true,
// 		.active = true,
// 		.pickup_value = 25,
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_HEALTH,
// 		.sprite.bottom_offset = 0.0f
// 	};
// 	game->item_prefabs[IT_CHANDELIER] = (t_item){
// 		.type = IT_CHANDELIER,
// 		.pickupable = false,
// 		.active = true,
// 		.pickup_value = 0,
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_CHANDELIER,
// 		.sprite.bottom_offset = -0.1f
// 	};
// 	game->item_prefabs[IT_KEY] = (t_item){
// 		.type = IT_KEY,
// 		.pickupable = true,
// 		.active = true,
// 		.pickup_value = 1,
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_KEY,
// 		.sprite.bottom_offset = 0.0f
// 	};
// 	game->item_prefabs[IT_BARREL] = (t_item){
// 		.type = IT_BARREL,
// 		.pickupable = false,
// 		.active = true,
// 		.pickup_value = 1,
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_BARREL,
// 		.sprite.bottom_offset = 0.0f
// 	};
// 	game->item_prefabs[IT_FIRE] = (t_item){
// 		.type = IT_FIRE,
// 		.pickupable = false,
// 		.active = true,
// 		.pickup_value = 1,
// 		.sprite = (t_sprite){
// 			.texture = NULL,
// 			.path = TEX_FIRE,
// 			.bottom_offset = 0.0f,
// 			.animated = true,
// 			.anim = (t_anim){
// 				.n_frames = 8,
// 				.frame_duration = 0.07f,
// 				.anim_timer = 0.0f,
// 				.curr_frame = rand() % 8
// 			}
// 		}
// 	};
// 	game->item_prefabs[IT_MAP] = (t_item){
// 		.type = IT_MAP,
// 		.pickupable = true,
// 		.active = true,
// 		.pickup_value = 1,
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_MAP,
// 		.sprite.bottom_offset = 0.0f
// 	};
// }

// void ft_init_prefabs_chars(t_gs *game)
// {
// 	game->char_prefabs[CH_ALIEN] = (t_char){
// 		.type = CH_ALIEN,
// 		.alive = true,
// 		.dps = AI_ALIEN_DMG_PS,
// 		.sprite = (t_sprite){
// 			.texture = NULL,
// 			.path = TEX_ALIEN,
// 			.bottom_offset = 0.0f,
// 			.animated = true,
// 			.anim = (t_anim){
// 				.n_frames = 8,
// 				.frame_duration = 0.07f,
// 				.anim_timer = 0.0f,
// 				.curr_frame = rand() % 8
// 			}
// 		}
// 	};
// 	game->char_prefabs[CH_SLIME] = (t_char){
// 		.type = CH_SLIME,
// 		.alive = true,
// 		.dps = AI_SLIME_DMG_PS,
// 		.sprite = (t_sprite){
// 			.texture = NULL,
// 			.path = TEX_SLIME,
// 			.bottom_offset = 0.6f,
// 			.animated = true,
// 			.anim = (t_anim){
// 				.n_frames = 8,
// 				.frame_duration = 0.07f,
// 				.anim_timer = 0.0f,
// 				.curr_frame = rand() % 8
// 			}
// 		}
// 	};
// }

// void ft_init_prefabs_doors(t_gs *game)
// {
// 	game->door_prefabs[0] = (t_door){
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_DOOR,
// 		.sprite.bottom_offset = 0.0f,
// 		.key_needed = false
// 	};
// 	game->door_prefabs[1] = (t_door){
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_DOOR,
// 		.sprite.bottom_offset = 0.0f,
// 		.key_needed = true
// 	};
// 	game->door_prefabs[2] = (t_door){
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_DOOR,
// 		.sprite.bottom_offset = 0.0f,
// 		.key_needed = false
// 	};
// 	game->door_prefabs[3] = (t_door){
// 		.sprite.texture = NULL,
// 		.sprite.animated = false,
// 		.sprite.path = TEX_DOOR,
// 		.sprite.bottom_offset = 0.0f,
// 		.key_needed = false
// 	};
// }

void	ft_init_prefabs(void)
{
	t_gs	*game;

	game = ft_game();
	ft_init_prefabs_items(game);
	ft_init_prefabs_chars(game);
	ft_init_prefabs_doors(game);
}
