/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/14 21:47:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_initprefabs(void)
{
	t_gs	*game;

	game = ft_game();
	game->item_prefabs[IT_HEALTH] = (t_item){
		.type = IT_HEALTH,
		.pickupable = true,
		.active = true,
		.pickup_value = 25,
		.sprite.texture = NULL,
		.sprite.path = TEX_HEALTH,
		.sprite.bottom_offset = 0.0f
	};
	game->item_prefabs[IT_CHANDELIER] = (t_item){
		.type = IT_CHANDELIER,
		.pickupable = false,
		.active = true,
		.pickup_value = 0,
		.sprite.texture = NULL,
		.sprite.path = TEX_CHANDELIER,
		.sprite.bottom_offset = -0.1f
	};
	game->item_prefabs[IT_KEY] = (t_item){
		.type = IT_KEY,
		.pickupable = true,
		.active = true,
		.pickup_value = 1,
		.sprite.texture = NULL,
		.sprite.path = TEX_KEY,
		.sprite.bottom_offset = 0.0f
	};
	game->item_prefabs[IT_BARREL] = (t_item){
		.type = IT_BARREL,
		.pickupable = false,
		.active = true,
		.pickup_value = 1,
		.sprite.texture = NULL,
		.sprite.path = TEX_BARREL,
		.sprite.bottom_offset = 0.0f
	};
	game->char_prefabs[CH_ALIEN] = (t_char){
		.type = CH_ALIEN,
		.health = 100,
		.max_health = 100,
		.alive = true,
		.sprite.texture = NULL,
		.sprite.path = TEX_ALIEN,
		.sprite.bottom_offset = 0.0f
	};
	game->char_prefabs[CH_SLIME] = (t_char){
		.type = CH_SLIME,
		.health = 50,
		.max_health = 50,
		.alive = true,
		.sprite.texture = NULL,
		.sprite.path = TEX_SLIME,
		.sprite.bottom_offset = 0.6f
	};

}

static void ft_initrender(void)
{
	t_gs	*game;

	game = ft_game();
	game->render.projection_plane_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	game->render.depth = malloc(sizeof(float) * (WIDTH / PIXEL_SIZE + 1));
	if (!game->render.depth)
		ft_exit_perror("Could not allocate memory for render depth buffer\n");
}

static void	ft_initmap(void)
{
	t_map	*map;

	map = &ft_game()->map;
	map->tile = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
	map->start.u = -1;
	map->start.v = -1;
	map->w = 0;
	map->h = 0;
}

static void	ft_initplayer(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		ft_exit_perror("Could not allocate memory for player\n");
	player->pos.x = 0;
	player->pos.y = 0;
	player->lookdir.x = 1.0f;
	player->lookdir.y = 0.0f;
	player->lookdir.z = 0.0f;
	player->mov_control.u = 0;
	player->mov_control.v = 0;
	player->rot_control.u = 0;
	player->rot_control.v = 0;
	player->mouse_pos.x = -1.0f;
	player->mouse_diff.x = 0.0f;
	player->mouse_pos.y = -1.0f;
	player->mouse_diff.y = 0.0f;
	ft_game()->player = player;
}

static void	ft_initgame(void)
{
	t_gs	*game;

	game = ft_game();
	game->mlx = NULL;
	game->items = NULL;
	game->chars = NULL;
}

void	ft_initialize(void)
{
	ft_initgame();
	ft_initprefabs();
	ft_initmap();
	ft_initplayer();
	ft_initrender();
}
