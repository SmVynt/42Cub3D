/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 17:40:20 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_string(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_freemap(void)
{
	int		i;
	t_map	*map;

	map = &ft_game()->map;
	printf(COLOR_C"Freeing map resources...\n"COLOR_X);
	if (map->tile)
	{
		i = -1;
		while (++i < map->h)
			ft_free_string(&map->tile[i]);
		ft_free_and_null((void **)&map->tile);
	}
	ft_free_string(&map->no);
	ft_free_string(&map->so);
	ft_free_string(&map->we);
	ft_free_string(&map->ea);
	ft_free_string(&map->f);
	ft_free_string(&map->c);
}

void	ft_free_render(void)
{
	t_gs	*game;

	game = ft_game();
	printf(COLOR_C"Freeing render resources...\n"COLOR_X);
	if (game->render.depth)
		ft_free_and_null((void **)&game->render.depth);
	if (game->sh)
		ft_free_and_null((void **)&game->sh);
}

void	ft_clean(void)
{
	t_gs	*game;

	game = ft_game();
	audio_cleanup(&game->audio);
	printf(COLOR_C"Cleaning up resources...\n"COLOR_X);
	ft_lstclear(&game->player->pocket, ft_dummy_delete);
	ft_free_and_null((void **)&game->player);
	ft_freemap();
	ft_free_mlx();
	ft_free_render();
	printf(COLOR_C"Freeing items...\n"COLOR_X);
	ft_free_and_null((void **)&game->items);
	printf(COLOR_C"Freeing chars...\n"COLOR_X);
	ft_free_and_null((void **)&game->chars);
	printf(COLOR_C"Freeing doors...\n"COLOR_X);
	ft_free_and_null((void **)&game->inter_walls);
}
