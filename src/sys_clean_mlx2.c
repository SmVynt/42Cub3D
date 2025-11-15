/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_clean_mlx2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 16:38:11 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_mlx_envirtex(t_gs *game)
{
	int			i;
	t_direction	dir;

	printf(COLOR_C"Freeing MLX resources...\n"COLOR_X);
	i = -1;
	while (++i < WALLS_TYPES_COUNT)
	{
		dir = DIR_NO;
		while (dir <= DIR_WE)
		{
			ft_free_texture(&game->textures.walls[i].tex[dir]);
			dir++;
		}
	}
	printf(COLOR_C"Freeing floor and ceiling textures...\n"COLOR_X);
	i = -1;
	while (++i < FLOOR_TYPE_COUNT)
		ft_free_texture(&game->textures.floor[i]);
	i = -1;
	while (++i < CEILING_TYPE_COUNT)
		ft_free_texture(&game->textures.ceiling[i]);
}

void	ft_free_mlx_prefabs_chars(t_gs *game)
{
	int	i;
	int	j;

	printf(COLOR_C"Freeing char prefab textures...\n"COLOR_X);
	i = -1;
	while (++i < CHARS_TYPES_COUNT)
	{
		if (game->prefabs.chars[i].sprite.animated)
		{
			j = -1;
			while (++j < (int)game->prefabs.chars[i].sprite.anim.n_frames)
				ft_free_texture(&game->prefabs.chars[i].sprite.anim.frames[j]);
		}
		else
			ft_free_texture(&game->prefabs.chars[i].sprite.texture);
	}
}

void	ft_free_mlx_prefabs_items(t_gs *game)
{
	int	i;
	int	j;

	printf(COLOR_C"Freeing item prefab textures...\n"COLOR_X);
	i = -1;
	while (++i < ITEMS_TYPES_COUNT)
	{
		if (game->prefabs.items[i].sprite.animated)
		{
			j = -1;
			while (++j < (int)game->prefabs.items[i].sprite.anim.n_frames)
				ft_free_texture(&game->prefabs.items[i].sprite.anim.frames[j]);
		}
		else
			ft_free_texture(&game->prefabs.items[i].sprite.texture);
	}
}

void	ft_free_mlx_prefabs_specials(t_gs *game)
{
	int	i;

	printf(COLOR_C"Freeing door prefab textures...\n"COLOR_X);
	i = -1;
	while (++i < SPEC_TYPES_COUNT)
	{
		ft_free_texture(&game->prefabs.doors[i].sprite.texture);
	}
}
