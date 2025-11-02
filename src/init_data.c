/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/02 18:07:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_init_prefabs(void)
{
	t_gs	*game;

	game = ft_game();
	game->item_prefabs[IT_HEALTH] = (t_item){
		.type = IT_HEALTH,
		.pickupable = true,
		.active = true,
		.pickup_value = 25,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_HEALTH,
		.sprite.bottom_offset = 0.0f
	};
	game->item_prefabs[IT_CHANDELIER] = (t_item){
		.type = IT_CHANDELIER,
		.pickupable = false,
		.active = true,
		.pickup_value = 0,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_CHANDELIER,
		.sprite.bottom_offset = -0.1f
	};
	game->item_prefabs[IT_KEY] = (t_item){
		.type = IT_KEY,
		.pickupable = true,
		.active = true,
		.pickup_value = 1,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_KEY,
		.sprite.bottom_offset = 0.0f
	};
	game->item_prefabs[IT_BARREL] = (t_item){
		.type = IT_BARREL,
		.pickupable = false,
		.active = true,
		.pickup_value = 1,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_BARREL,
		.sprite.bottom_offset = 0.0f
	};
	game->item_prefabs[IT_FIRE] = (t_item){
		.type = IT_FIRE,
		.pickupable = false,
		.active = true,
		.pickup_value = 1,
		.sprite = (t_sprite){
			.texture = NULL,
			.path = TEX_FIRE,
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
	game->char_prefabs[CH_ALIEN] = (t_char){
		.type = CH_ALIEN,
		.health = 100,
		.max_health = 100,
		.alive = true,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_ALIEN,
		.sprite.bottom_offset = 0.0f
	};
	game->char_prefabs[CH_SLIME] = (t_char){
		.type = CH_SLIME,
		.health = 50,
		.max_health = 50,
		.alive = true,
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_SLIME,
		.sprite.bottom_offset = 0.6f
	};
	game->door_prefabs[0] = (t_door){
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_DOOR,
		.sprite.bottom_offset = 0.0f,
		.key_needed = false
	};
	game->door_prefabs[1] = (t_door){
		.sprite.texture = NULL,
		.sprite.animated = false,
		.sprite.path = TEX_DOOR,
		.sprite.bottom_offset = 0.0f,
		.key_needed = true
	};
}

static void ft_init_render(void)
{
	t_gs	*game;

	game = ft_game();
	game->render.projection_plane_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	game->render.depth = malloc(sizeof(float) * (WIDTH / PIXEL_SIZE + 1));
	if (!game->render.depth)
		ft_exit_perror("Could not allocate memory for render depth buffer\n");
}

static void	ft_init_map(void)
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

static void	ft_init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		ft_exit_perror("Could not allocate memory for player\n");
	player->pos.x = 0;
	player->pos.y = 0;
	player->lookdir.x = 1.0f;
	player->lookdir.y = 0.0f;
	player->mov_control = (t_point){0, 0};
	player->rot_control = (t_point){0, 0};
	player->mouse_pos = (t_vec2){-1.0f, -1.0f};
	player->mouse_diff = (t_vec2){0.0f, 0.0f};
	player->lookupdown = 0.0f;
	player->is_jumping = false;
	ft_game()->player = player;
}

static void	ft_init_game(void)
{
	t_gs	*game;

	game = ft_game();
	game->mlx = NULL;
	game->items = NULL;
	game->chars = NULL;
	game->minimap = NULL;
	game->hud = NULL;
	game->miniplayer = NULL;
	game->view3d = NULL;
	game->view3d_bg = NULL;
	game->playing = true;
}

static void	ft_init_null_textures(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	game->textures.wall_atlas = NULL;
	game->textures.bg = NULL;
	game->textures.ui_minimap = NULL;
	i = 0;
	while (i < WALLS_TYPES_COUNT)
	{
		game->textures.walls[i].tex[DIR_NO] = NULL;
		game->textures.walls[i].tex[DIR_SO] = NULL;
		game->textures.walls[i].tex[DIR_WE] = NULL;
		game->textures.walls[i].tex[DIR_EA] = NULL;
		i++;
	}
}

void	ft_initialize(void)
{
	ft_init_game();
	ft_init_prefabs();
	ft_init_map();
	ft_init_player();
	ft_init_render();
	ft_init_null_textures();
}
