/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_textures_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 17:02:02 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_walls_textures(void)
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
			ft_load_texture_from_atlas(i - 1, dir,
				&game->textures.walls[i].tex[dir],
				game->textures.wall_atlas);
			printf("Loaded wall texture %d dir %d\n", i, dir);
			dir++;
		}
		i++;
	}
}

void	ft_init_floor_textures(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	ft_load_texture(TEX_FLOOR_ATLAS, &game->textures.floor_atlas);
	i = 0;
	while (i < FLOOR_TYPE_COUNT)
	{
		ft_load_texture_from_atlas(0, i, &game->textures.floor[i],
			game->textures.floor_atlas);
		printf("Loaded floor texture %d\n", i);
		i++;
	}
}

void	ft_init_ceiling_textures(void)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	ft_load_texture(TEX_CEILING_ATLAS, &game->textures.ceiling_atlas);
	i = 0;
	while (i < CEILING_TYPE_COUNT)
	{
		ft_load_texture_from_atlas(0, i, &game->textures.ceiling[i],
			game->textures.ceiling_atlas);
		printf("Loaded ceiling texture %d\n", i);
		i++;
	}
}
