/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_prefabs_chars.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 22:08:07 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_prefab_alien(t_gs *game)
{
	game->char_prefabs[CH_ALIEN] = (t_char){
		.type = CH_ALIEN,
		.alive = true,
		.dps = AI_ALIEN_DMG_PS,
		.sprite = (t_sprite){
			.texture = NULL,
			.path = TEX_ALIEN,
			.bottom_offset = 0.0f,
			.animated = true,
			.anim = (t_anim){
				.n_frames = 8,
				.frame_duration = 0.07f,
				.anim_timer = 0.0f,
				.curr_frame = rand() % 8
			}
		}
	};
}

static void	ft_init_prefab_slime(t_gs *game)
{
	game->char_prefabs[CH_SLIME] = (t_char){
		.type = CH_SLIME,
		.alive = true,
		.dps = AI_SLIME_DMG_PS,
		.sprite = (t_sprite){
			.texture = NULL,
			.path = TEX_SLIME,
			.bottom_offset = 0.6f,
			.animated = true,
			.anim = (t_anim){
				.n_frames = 8,
				.frame_duration = 0.07f,
				.anim_timer = 0.0f,
				.curr_frame = rand() % 8
			}
		}
	};
}

void ft_init_prefabs_chars(t_gs *game)
{
	ft_init_prefab_alien(game);
	ft_init_prefab_slime(game);
}
