/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 20:02:14 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_set_player(void)
{
	t_player	*player;
	t_gs		*game;
	char		start_char;

	game = ft_game();
	player = game->player;
	player->pos = (t_vec2){(double)game->map.start.u, (double)game->map.start.v};
	start_char = game->map.tile[game->map.start.v][game->map.start.u];
	if (start_char == 'N')
		player->lookdir = (t_vec2){0.0, -1.0};
	if (start_char == 'E')
		player->lookdir = (t_vec2){1.0, 0.0};
	if (start_char == 'S')
		player->lookdir = (t_vec2){0.0, 1.0};
	if (start_char == 'W')
		player->lookdir = (t_vec2){-1.0, 0.0};
	player->jump_height = 0.1;
	player->jump_impuls = 0.0;
	player->is_jumping = false;
	player->pocket = NULL;
}

static void	ft_calculate_max_entities(void)
{
	t_gs	*game;
	int		i;
	int		j;

	game = ft_game();
	game->max_items = 0;
	game->max_chars = 0;
	game->max_doors = 0;
	i = -1;
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			if (ft_strchar(MAP_ITEM_CHARS, game->map.tile[i][j]) != NULL)
				game->max_items++;
			if (ft_strchar(MAP_CHAR_CHARS, game->map.tile[i][j]) != NULL)
				game->max_chars++;
			if (ft_strchar(SPEC_WALL_CHARS, game->map.tile[i][j]) != NULL)
				game->max_doors++;
		}
	}
	printf("Max items: %d, max chars: %d, max doors: %d\n",
		game->max_items, game->max_chars, game->max_doors);
}

void	ft_setgame(void)
{
	t_gs	*game;

	game = ft_game();
	ft_set_player();
	ft_init_walls_textures();
	ft_init_floor_textures();
	ft_init_ceiling_textures();
	ft_init_ui_textures();
	ft_init_end_screen_textures();
	ft_init_sprites();
	ft_calculate_max_entities();
	ft_set_doors();
	printf("Initialized %d interactive walls\n", game->inter_wall_count);
	ft_set_items();
	ft_set_chars();
}
