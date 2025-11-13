/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_prefabs_doors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 20:02:02 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_prefabs_doors(t_gs *game)
{
	game->door_prefabs[0] = (t_door){
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_DOOR,
		.sprite.bottom_offset = 0.0,
		.key_needed = false
	};
	game->door_prefabs[1] = (t_door){
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_DOOR,
		.sprite.bottom_offset = 0.0,
		.key_needed = true
	};
}

static void	ft_init_prefabs_switches(t_gs *game)
{
	game->door_prefabs[2] = (t_door){
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_DOOR,
		.sprite.bottom_offset = 0.0,
		.key_needed = false
	};
	game->door_prefabs[3] = (t_door){
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_DOOR,
		.sprite.bottom_offset = 0.0,
		.key_needed = false
	};
}

void	ft_init_prefabs_interacts(t_gs *game)
{
	ft_init_prefabs_doors(game);
	ft_init_prefabs_switches(game);
}
