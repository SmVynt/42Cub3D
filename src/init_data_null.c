/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 22:41:12 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_null_textures_wall_ceil_floor(t_gs *game)
{
	int		i;

	i = 0;
	while (i < WALLS_TYPES_COUNT)
	{
		game->textures.walls[i].tex[DIR_NO] = NULL;
		game->textures.walls[i].tex[DIR_SO] = NULL;
		game->textures.walls[i].tex[DIR_WE] = NULL;
		game->textures.walls[i].tex[DIR_EA] = NULL;
		i++;
	}
	i = -1;
	while (++i < FLOOR_TYPE_COUNT)
		game->textures.floor[i] = NULL;
	i = -1;
	while (++i < CEILING_TYPE_COUNT)
		game->textures.ceiling[i] = NULL;
}

void	ft_init_null_textures(void)
{
	t_gs	*game;

	game = ft_game();
	game->textures.wall_atlas = NULL;
	game->textures.bg = NULL;
	game->textures.ui_minimap = NULL;
	game->textures.screen_defeat = NULL;
	game->textures.screen_victory = NULL;
	game->textures.ui_health = NULL;
	game->textures.floor_atlas = NULL;
	game->textures.ceiling_atlas = NULL;
	ft_init_null_textures_wall_ceil_floor(game);
}
