/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/01 15:35:40 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_and_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

static void	ft_freemap(void)
{
	int		i;
	t_map	*map;

	map = &ft_game()->map;
	printf(COLOR_C"Freeing map resources...\n"COLOR_X);
	if (map->tile)
	{
		i = -1;
		while (++i < map->h)
			ft_free_and_null(map->tile[i]);
		ft_free_and_null(map->tile);
	}
	ft_free_and_null(map->no);
	ft_free_and_null(map->so);
	ft_free_and_null(map->we);
	ft_free_and_null(map->ea);
	ft_free_and_null(map->f);
	ft_free_and_null(map->c);
}

void	ft_clean(void)
{
	t_gs	*game;

	game = ft_game();
	printf(COLOR_C"Cleaning up resources...\n"COLOR_X);
	ft_free_and_null(game->player);
	if (game->mlx)
		mlx_terminate(game->mlx);
	// ft_free_and_null(game->mlx);
	// ft_free_and_null(game->window);
	ft_freemap();
}
