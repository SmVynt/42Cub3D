/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/02 21:19:18 by nmikuka          ###   ########.fr       */
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
	player->pos = (t_vec2){(float)game->map.start.u, (float)game->map.start.v};
	start_char = game->map.tile[game->map.start.v][game->map.start.u];
	if (start_char == 'N')
		player->lookdir = (t_vec2){0.0f, -1.0f};
	if (start_char == 'E')
		player->lookdir = (t_vec2){1.0f, 0.0f};
	if (start_char == 'S')
		player->lookdir = (t_vec2){0.0f, 1.0f};
	if (start_char == 'W')
		player->lookdir = (t_vec2){-1.0f, 0.0f};
	player->jump_height = 0.1f;
	player->jump_impuls = 0.0f;
	player->is_jumping = false;
	player->pocket = NULL;
}

static void ft_init_walls_textures(void)
{
	t_gs		*game;
	int			i;
	t_direction	dir;

	game = ft_game();
	ft_load_texture(TEX_WALL_ATLAS, &game->textures.wall_atlas);
	i = 1;
	while (i < WALLS_TYPES_COUNT)
	{
		dir = DIR_NO;
		while (dir <= DIR_WE)
		{
			ft_load_wall_texture(i, dir, &game->textures.walls[i].tex[dir]);
			printf("Loaded wall texture %d dir %d\n", i, dir);
			dir++;
		}
		i++;
	}
}

static void ft_init_ui_textures(void)
{
	t_gs		*game;

	game = ft_game();
	ft_load_texture(TEX_UI_MM, &game->textures.ui_minimap);
	printf("Loaded UI minimap texture\n");
}

static void ft_calculate_max_entities(void)
{
	t_gs	*game;
	int		i;
	int		j;

	game = ft_game();
	game->max_items = 0;
	game->max_chars = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			if (ft_strchar(MAP_ITEM_CHARS, game->map.tile[i][j]) != NULL)
				game->max_items++;
			if (ft_strchar(MAP_CHAR_CHARS, game->map.tile[i][j]) != NULL)
				game->max_chars++;
			if (ft_strchar(MAP_DOOR_CHARS, game->map.tile[i][j]) != NULL)
				game->max_doors++;
			j++;
		}
		i++;
	}
	printf("Max items: %d, max chars: %d, max doors: %d\n", game->max_items, game->max_chars, game->max_doors);
}

static void	ft_set_doors(void)
{
	t_gs	*game;
	int		i;
	int		j;
	int		door_index;
	int		door_num;

	game = ft_game();
	if (game->max_doors == 0)
		return ;
	game->doors = malloc(sizeof(t_door) * game->max_doors);
	if (!game->doors)
		ft_exit_perror("Could not allocate memory for doors\n");
	door_index = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			door_num = ft_strchar_index(MAP_DOOR_CHARS, game->map.tile[i][j]);
			if (door_num != -1 && door_num < DOORS_TYPES_COUNT)
			{
				if (door_index >= game->max_doors)
					ft_exit_error("Item index out of bounds\n");
				game->doors[door_index] = game->door_prefabs[door_num];
				game->doors[door_index].idx.u = j;
				game->doors[door_index].idx.v = i;
				game->doors[door_index].closed = true;
				game->doors[door_index].is_opening = false;
				game->doors[door_index].dt = 0.0f;
				game->doors[door_index].sprite.pos = (t_vec2){(float)j, (float)i};
				door_index++;
			}
			j++;
		}
		i++;
	}
	game->door_count = door_index;
	printf("Initialized %d doors\n", game->door_count);
}

static void	ft_set_items(void)
{
	t_gs	*game;
	int		i;
	int		j;
	int		item_index;
	int		item_num;

	game = ft_game();
	if (game->max_items == 0)
		return ;
	game->items = malloc(sizeof(t_item) * game->max_items);
	if (!game->items)
		ft_exit_perror("Could not allocate memory for items\n");
	item_index = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			item_num = ft_strchar_index(MAP_ITEM_CHARS, game->map.tile[i][j]);
			if (item_num != -1 && item_num < ITEMS_TYPES_COUNT)
			{
				if (item_index >= game->max_items)
					ft_exit_error("Item index out of bounds\n");
				game->items[item_index] = game->item_prefabs[item_num];
				game->items[item_index].sprite.pos = (t_vec2){(float)j, (float)i};
				item_index++;
			}
			j++;
		}
		i++;
	}
	game->item_count = item_index;
	printf("Initialized %d items\n", game->item_count);
}

static void	ft_set_chars(void)
{
	t_gs	*game;
	int		i;
	int		j;
	int		char_index;
	int		char_num;

	game = ft_game();
	if (game->max_chars == 0)
		return ;
	game->chars = malloc(sizeof(t_char) * game->max_chars);
	if (!game->chars)
		ft_exit_perror("Could not allocate memory for chars\n");
	char_index = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			char_num = ft_strchar_index(MAP_CHAR_CHARS, game->map.tile[i][j]);
			if (ft_strchar(MAP_CHAR_CHARS, game->map.tile[i][j]) != NULL)
			if (char_num != -1 && char_num < CHARS_TYPES_COUNT)
			{
				if (char_index >= game->max_chars)
					ft_exit_error("Char index out of bounds\n");
				game->chars[char_index] = game->char_prefabs[char_num];
				game->chars[char_index].sprite.pos = (t_vec2){(float)j, (float)i};
				char_index++;
			}
			j++;
		}
		i++;
	}
	game->char_count = char_index;
	printf("Initialized %d chars\n", game->char_count);
}

static void ft_init_sprites(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	i = 0;
	while (i < ITEMS_TYPES_COUNT)
	{
		if (game->item_prefabs[i].sprite.path == NULL)
			ft_exit_error("Item prefab texture path is NULL\n");
		if (!game->item_prefabs[i].sprite.animated)
			ft_load_texture(game->item_prefabs[i].sprite.path, &game->item_prefabs[i].sprite.texture);
		else
		{
			ft_load_anim_texture(game->item_prefabs[i].sprite.path, game->item_prefabs[i].sprite.anim.frames, game->item_prefabs[i].sprite.anim.n_frames);
			game->item_prefabs[i].sprite.texture = game->item_prefabs[i].sprite.anim.frames[0];
		}
			i++;
	}
	i = 0;
	while (i < CHARS_TYPES_COUNT)
	{
		if (game->char_prefabs[i].sprite.path == NULL)
			ft_exit_error("Char prefab texture path is NULL\n");
		ft_load_texture(game->char_prefabs[i].sprite.path, &game->char_prefabs[i].sprite.texture);
		i++;
	}
	i = 0;
	while (i < DOORS_TYPES_COUNT)
	{
		if (game->door_prefabs[i].sprite.path == NULL)
			ft_exit_error("Door prefab texture path is NULL\n");
		ft_load_texture(game->door_prefabs[i].sprite.path, &game->door_prefabs[i].sprite.texture);
		i++;
	}
	game->sh = NULL;
	// game->sh = malloc(sizeof(t_sprite));
	// if (!game->sh)
	// 	ft_exit_perror("Could not allocate memory for sprite sorting list\n");
	// game->sh->texture = NULL;
}

void	ft_setgame(void)
{
	ft_set_player();
	ft_init_walls_textures();
	ft_init_ui_textures();
	ft_init_sprites();
	ft_calculate_max_entities();
	ft_set_doors();
	ft_set_items();
	ft_set_chars();
}
