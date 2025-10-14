/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_checkmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:58:46 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/14 10:51:46 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_checkdigits(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_game()->map.h)
	{
		j = 0;
		while (j < ft_game()->map.w)
		{
			if (ft_strchar(MAP_ALLOWED_CHARS, ft_game()->map.tile[i][j])
					== NULL)
				ft_exit_error(COLOR_R"Map contains invalid characters\n"COLOR_X);
			j++;
			if (ft_strchar(MAP_PLAYER_CHARS, ft_game()->map.tile[i][j]) != NULL)
			{
				printf("Found player start at %d,%d\n", j, i);
				if (ft_game()->map.start.u != -1
					|| ft_game()->map.start.v != -1)
					ft_exit_error("Map contains multiple starting positions\n");
				ft_game()->map.start.u = j;
				ft_game()->map.start.v = i;
			}
		}
		i++;
	}
}

static void	ft_check_neighbours(t_map *map, int h, int w, const char *walls)
{
	map->tile[h][w] -= 128;
	if (w <= 1 || w >= map->w - 1 || h <= 1 || h >= map->h - 1)
		return ;
	if (ft_strchar(walls, map->tile[h + 1][w]) == NULL
			&& map->tile[h + 1][w] >= 0)
		ft_check_neighbours(map, h + 1, w, walls);
	if (ft_strchar(walls, map->tile[h - 1][w]) == NULL
			&& map->tile[h - 1][w] >= 0)
		ft_check_neighbours(map, h - 1, w, walls);
	if (ft_strchar(walls, map->tile[h][w + 1]) == NULL
			&& map->tile[h][w + 1] >= 0)
		ft_check_neighbours(map, h, w + 1, walls);
	if (ft_strchar(walls, map->tile[h][w - 1]) == NULL
			&& map->tile[h][w - 1] >= 0)
		ft_check_neighbours(map, h, w - 1, walls);
}

static void	ft_restoremap(t_map *map)
{
	int	h;
	int	w;

	h = -1;
	while (++h < map->h)
	{
		w = -1;
		while (++w < map->w)
		{
			if (map->tile[h][w] < 0)
				map->tile[h][w] += 128;
		}
	}
}

static void	ft_checkwalls(void)
{
	t_map	*map;
	int		h;
	int		w;

	map = &ft_game()->map;
	printf("Checking walls...\n");
	ft_check_neighbours(map, map->start.v, map->start.u, MAP_WALL_CHARS);
	h = -1;
	while (++h < map->h)
	{
		if (map->tile[h][0] < 0 || map->tile[h][map->w - 1] < 0)
			ft_exit_error("Map is not closed\n");
	}
	w = -1;
	while (++w < map->w)
	{
		if (map->tile[0][w] < 0 || map->tile[map->h - 1][w] < 0)
			ft_exit_error("Map is not closed\n");
	}
	ft_restoremap(map);
}

void	ft_checkmap(void)
{
	ft_checkdigits();
	printf(COLOR_G"Map digits check passed!\n"COLOR_X);
	ft_checkwalls();
	printf(COLOR_G"Map walls check passed!\n"COLOR_X);
	ft_printmap(&ft_game()->map);
}
