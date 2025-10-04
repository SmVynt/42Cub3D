/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/03 18:52:30 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	player->rot_control = 0;
	player->mouse_x = 0.0f;
	player->mouse_dx = 0.0f;
	ft_game()->player = player;
}

static void	ft_initgame(void)
{
	t_gs	*game;

	game = ft_game();
	game->mlx = NULL;
	game->window = NULL;
}

void	ft_initialize(void)
{
	ft_initgame();
	ft_initmap();
	ft_initplayer();
}
