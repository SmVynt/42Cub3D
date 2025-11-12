/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_rayend_door.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:31:08 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 15:34:39 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	process_wall_hit(t_rayrender *ray, t_vec2 *curr,
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
