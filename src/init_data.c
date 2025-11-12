/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 20:02:02 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_render(void)
{
	t_gs	*game;

	game = ft_game();
	game->render.projection_plane_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	game->render.depth = malloc(sizeof(double) * (WIDTH / PIXEL_SIZE + 1));
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
	player->hp = 100.0;
	player->pos.x = 0;
	player->pos.y = 0;
	player->lookdir.x = 1.0;
	player->lookdir.y = 0.0;
	player->mov_control = (t_point){0, 0};
	player->rot_control = (t_point){0, 0};
	player->mouse_pos = (t_vec2){-1.0, -1.0};
	player->mouse_diff = (t_vec2){0.0, 0.0};
	player->lookupdown = 0.0;
	player->is_jumping = false;
	player->is_shaking = false;
	ft_game()->player = player;
}

static void	ft_init_game(void)
{
	t_gs	*game;

	game = ft_game();
	game->is_bonus = false;
	game->mlx = NULL;
	game->items = NULL;
	game->chars = NULL;
	game->minimap = NULL;
	game->hud = NULL;
	game->miniplayer = NULL;
	game->health = NULL;
	game->health_bar = NULL;
	game->view3d = NULL;
	game->end_screen = NULL;
	game->hints = NULL;
	game->msg = NULL;
	game->view3d_bg = NULL;
	game->playing = true;
	game->game_over = 0;
	game->mmap.enabled = false;
	game->mmap.opening = false;
	game->mmap.picked = false;
	game->mmap.lerp_progress = 0.0;
	game->mmap.lerp_speed = 10.0;
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
