/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_rayend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:34:33 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 15:05:26 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_state(t_rayrender *ray, t_vec2 start)
{
	ray->is_door = false;
	ray->door = NULL;
	ray->is_doorway = ft_is_door((t_vec2){start.x - 0.5, start.y - 0.5});
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

static bool	check_door_opening_threshold(t_rayrender *ray, t_vec2 curr,
				int side)
{
	double	threshold;

	if (!ray->door->is_opening)
		return (false);
	threshold = (DOOR_OPEN_TIME - ray->door->dt) / DOOR_OPEN_TIME;
	ray->is_doorway = true;
	if (side && curr.x - floor(curr.x) > threshold)
		return (true);
	if (!side && ceil(curr.y) - curr.y > threshold)
		return (true);
	return (false);
}

static t_vec2	adjust_door_position(t_rayrender *ray, t_vec2 curr, int side)
{
	double	coeff;

	if (side == 0)
		coeff = 0.5 / fabs(ray->dir.x);
	else
		coeff = 0.5 / fabs(ray->dir.y);
	curr.x -= coeff * ray->dir.x;
	curr.y -= coeff * ray->dir.y;
	return (curr);
}

static t_vec2	process_door_intersection(t_rayrender *ray, t_vec2 curr,
				t_vec2 dir, int *side)
{
	t_point	tile_check;
	t_vec2	check;
	int		new_side;

	check = get_next_wall_intersection(curr, dir, &tile_check, &new_side);
	if (new_side == *side)
		return (check);
	else if ((*side && ((dir.y < 0 && fabs(check.y - floor(curr.y)) >= 0.5)
				|| (dir.y > 0 && fabs(-check.y + floor(curr.y)) >= 0.5)))
		|| (!*side && ((dir.x < 0 && fabs(check.x - floor(curr.x)) >= 0.5)
				|| (dir.x > 0 && fabs(-check.x + floor(curr.x)) >= 0.5))))
		return (get_next_wall_intersection(check, dir, &tile_check, side));
	else
	{
		ray->is_door = false;
		ray->door = NULL;
		*side = new_side;
		return (check);
	}
}

static bool	process_wall_hit(t_rayrender *ray, t_vec2 *curr,
				t_point tile, int *side)
{
	ray->wall_type = ft_game()->map.tile[tile.v][tile.u];
	if (ray->is_door)
	{
		ray->door = ft_get_door(tile.v, tile.u);
		*curr = process_door_intersection(ray, *curr, ray->dir, side);
		if (ray->is_door)
		{
			*curr = adjust_door_position(ray, *curr, *side);
			if (check_door_opening_threshold(ray, *curr, *side))
				return (false);
		}
	}
	return (true);
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
	return ((t_vec2){0.0, 0.0});
}
