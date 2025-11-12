/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_tile_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 19:54:22 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_is_special_wall(t_vec2 p, const char *wall_type)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)round(p.x);
	y = (int)round(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (ft_strchar(wall_type, map->tile[y][x]) != NULL)
		return (true);
	return (false);
}

bool	ft_is_wall(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)round(p.x);
	y = (int)round(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (ft_strchar(MAP_WALL_CHARS, map->tile[y][x]) != NULL)
		return (true);
	if (ft_strchar(MAP_DOOR_CHARS, map->tile[y][x]) != NULL
			&& ft_get_door(y, x)->closed)
		return (true);
	return (false);
}

bool	ft_is_lava(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)round(p.x);
	y = (int)round(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (map->tile[y][x] == '_')
		return (true);
	return (false);
}

bool	ft_is_pod(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)round(p.x);
	y = (int)round(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (map->tile[y][x] == 'X')
		return (true);
	return (false);
}

bool	ft_is_door(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)round(p.x);
	y = (int)round(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (ft_strchar(MAP_DOOR_CHARS, map->tile[y][x]) != NULL)
		return (true);
	return (false);
}
