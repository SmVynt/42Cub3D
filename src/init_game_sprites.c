/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 17:25:54 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_sprites(void)
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
			ft_load_texture(game->item_prefabs[i].sprite.path,
				&game->item_prefabs[i].sprite.texture);
		else
		{
			ft_load_anim_texture(game->item_prefabs[i].sprite.path,
				game->item_prefabs[i].sprite.anim.frames,
				game->item_prefabs[i].sprite.anim.n_frames);
			game->item_prefabs[i].sprite.texture
				= game->item_prefabs[i].sprite.anim.frames[0];
		}
		i++;
	}
	i = 0;
	while (i < CHARS_TYPES_COUNT)
	{
		if (game->char_prefabs[i].sprite.path == NULL)
			ft_exit_error("Char prefab texture path is NULL\n");
		if (!game->char_prefabs[i].sprite.animated)
			ft_load_texture(game->char_prefabs[i].sprite.path,
				&game->char_prefabs[i].sprite.texture);
		else
		{
			ft_load_anim_texture(game->char_prefabs[i].sprite.path,
				game->char_prefabs[i].sprite.anim.frames,
				game->char_prefabs[i].sprite.anim.n_frames);
			game->char_prefabs[i].sprite.texture
				= game->char_prefabs[i].sprite.anim.frames[0];
		}
		i++;
	}
	i = 0;
	while (i < SPEC_TYPES_COUNT)
	{
		if (game->door_prefabs[i].sprite.path == NULL)
			ft_exit_error("Door prefab texture path is NULL\n");
		ft_load_texture(game->door_prefabs[i].sprite.path,
			&game->door_prefabs[i].sprite.texture);
		i++;
	}
	game->sh = malloc(sizeof(t_sprite));
	if (!game->sh)
		ft_exit_perror("Could not allocate memory \
for sprite sorting list\n");
	game->sh->next = NULL;
	game->sh->texture = NULL;
}
