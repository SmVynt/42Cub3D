/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 16:37:18 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_sprites_items(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	i = 0;
	while (i < ITEMS_TYPES_COUNT)
	{
		if (game->prefabs.items[i].sprite.path == NULL)
			ft_exit_error("Item prefab texture path is NULL\n");
		if (!game->prefabs.items[i].sprite.animated)
			ft_load_texture(game->prefabs.items[i].sprite.path,
				&game->prefabs.items[i].sprite.texture);
		else
		{
			ft_load_anim_texture(game->prefabs.items[i].sprite.path,
				game->prefabs.items[i].sprite.anim.frames,
				game->prefabs.items[i].sprite.anim.n_frames);
			game->prefabs.items[i].sprite.texture
				= game->prefabs.items[i].sprite.anim.frames[0];
		}
		i++;
	}
}

static void	ft_init_sprites_chars(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	i = 0;
	while (i < CHARS_TYPES_COUNT)
	{
		if (game->prefabs.chars[i].sprite.path == NULL)
			ft_exit_error("Char prefab texture path is NULL\n");
		if (!game->prefabs.chars[i].sprite.animated)
			ft_load_texture(game->prefabs.chars[i].sprite.path,
				&game->prefabs.chars[i].sprite.texture);
		else
		{
			ft_load_anim_texture(game->prefabs.chars[i].sprite.path,
				game->prefabs.chars[i].sprite.anim.frames,
				game->prefabs.chars[i].sprite.anim.n_frames);
			game->prefabs.chars[i].sprite.texture
				= game->prefabs.chars[i].sprite.anim.frames[0];
		}
		i++;
	}
}

static void	ft_init_sprites_specials(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	i = 0;
	while (i < SPEC_TYPES_COUNT)
	{
		if (game->prefabs.doors[i].sprite.path == NULL)
			ft_exit_error("Door prefab texture path is NULL\n");
		ft_load_texture(game->prefabs.doors[i].sprite.path,
			&game->prefabs.doors[i].sprite.texture);
		i++;
	}
}

void	ft_init_sprites(void)
{
	t_gs	*game;

	game = ft_game();
	ft_init_sprites_items();
	ft_init_sprites_chars();
	ft_init_sprites_specials();
	game->sh = malloc(sizeof(t_sprite));
	if (!game->sh)
		ft_exit_perror("Could not allocate memory \
for sprite sorting list\n");
	game->sh->next = NULL;
	game->sh->texture = NULL;
}
