/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_rayend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:34:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 23:42:44 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_state(t_rayrender *ray, t_vec2 start)
{
	ray->is_door = false;
	ray->door = NULL;
	ray->is_doorway = ft_is_door((t_vec2){start.x - 0.5, start.y - 0.5});
	ray->wall_type = '2';
	ray->wall_height = (double)PIXEL_SIZE;
	ray->dist = RAYCAST_MAX_DIST;
	ray->wall_dir = DIR_EA;
	ray->end.x = ray->start.x + RAYCAST_MAX_DIST * ray->dir.x;
	ray->end.y = ray->start.y + RAYCAST_MAX_DIST * ray->dir.y;
}

static bool	is_tile_out_of_bounds(t_point tile)
{
	return (tile.u < 0 || tile.v < 0
		|| tile.u >= ft_game()->map.w || tile.v >= ft_game()->map.h);
}

static bool	should_skip_doorway(t_rayrender *ray, t_point tile, t_vec2 start)
{
	if (!ray->is_doorway)
		return (false);
	if (ray->door)
	{
		if (!((abs(ray->door->idx.u - tile.u) == 1
					&& ray->door->idx.v == tile.v)
				|| (ray->door->idx.u == tile.u
					&& abs(ray->door->idx.v - tile.v) == 1)))
			return (true);
	}
	else
	{
		if (!((abs((int)round(start.x) - tile.u) == 1
					&& round(start.y) == tile.v)
				|| (round(start.x) == tile.u
					&& abs((int)round(start.y) - tile.v) == 1)))
			return (true);
	}
	return (false);
}

static t_direction	get_wall_direction(int side, t_vec2 dir)
{
	t_direction	wall_dir;

	if (side && dir.y > 0)
		wall_dir = DIR_SO;
	else if (side)
		wall_dir = DIR_NO;
	else if (dir.x > 0)
		wall_dir = DIR_EA;
	else
		wall_dir = DIR_WE;
	return (wall_dir);
}

t_vec2	get_ray_end(t_rayrender *ray)
{
	t_vec2	curr;
	t_point	tile;
	int		side;
	int		i;

	curr = ray->start;
	init_ray_state(ray, ray->start);
	i = -1;
	while (++i < RAYCAST_MAX_ITER)
	{
		curr = get_next_wall_intersection(curr, ray->dir, &tile, &side);
		if (is_tile_out_of_bounds(tile))
			return (curr);
		ray->is_door = ft_is_door((t_vec2){tile.u, tile.v});
		if (should_skip_doorway(ray, tile, ray->start))
			ray->is_doorway = false;
		if (ft_is_wall((t_vec2){tile.u, tile.v}) || ray->is_door)
		{
			if (!process_wall_hit(ray, &curr, tile, &side))
				continue ;
			ray->wall_dir = get_wall_direction(side, ray->dir);
			return (curr);
		}
	}
	return ((t_vec2){ray->end.x, ray->end.y});
}
