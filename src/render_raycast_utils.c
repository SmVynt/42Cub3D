/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:24:47 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 23:54:43 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calc_next_wall_pos(double pos, double dir)
{
	double	next_wall;
	int		step;

	step = 0;
	if (dir > 0)
		step = 1;
	else if (dir < 0)
		step = -1;
	if (dir > 0)
		next_wall = ceil(pos);
	else
		next_wall = floor(pos);
	if (fabs(next_wall - pos) < 1e-9)
		next_wall += step;
	return (next_wall);
}

static double	calc_dist(double pos, double next_wall, double dir)
{
	if (fabs(dir) > 1e-9)
		return ((next_wall - pos) / dir);
	return (INFINITY);
}

t_vec2	get_next_wall_intersection(t_vec2 pos, t_vec2 dir, t_point *tile,
		int *side)
{
	t_vec2	hit_point;
	t_vec2	next_wall;
	t_vec2	dist;

	next_wall.x = calc_next_wall_pos(pos.x, dir.x);
	next_wall.y = calc_next_wall_pos(pos.y, dir.y);
	dist.x = calc_dist(pos.x, next_wall.x, dir.x);
	dist.y = calc_dist(pos.y, next_wall.y, dir.y);
	if (dist.x < dist.y)
	{
		hit_point = (t_vec2){next_wall.x, pos.y + dist.x * dir.y};
		tile->u = (int)next_wall.x - (dir.x < 0);
		tile->v = (int)floor(hit_point.y);
		*side = 0;
	}
	else
	{
		hit_point = (t_vec2){pos.x + dist.y * dir.x, next_wall.y};
		tile->u = (int)floor(hit_point.x);
		tile->v = (int)next_wall.y - (dir.y < 0);
		*side = 1;
	}
	return (hit_point);
}
