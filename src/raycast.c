/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/04 21:48:58 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	get_next_point_to_draw(t_point *p, int *slope_err,
		t_point diff, t_point dir);

bool hit_wall(t_point p, t_map map)
{
	int x;
	int y;

	if (p.u < 0 || p.u >= WIDTH || p.v < 0 || p.v >= HEIGHT)
		return (true);
    x = (p.u - MAP_SCALE / 2) / MAP_SCALE;
	y = (p.v - MAP_SCALE / 2) / MAP_SCALE;
	if (x < 0 || x >= map.w || y < 0 || y >= map.h)
		return (true);
    if(map.tile[y][x] == '1')
        return (true);
    return (false);
}

u_int32_t get_wall_dir(t_point draw_point, t_point prev_point, t_map map)
{
	uint32_t color;

	if (draw_point.u - prev_point.u > 0)
		color = COLOR_YELLOW;
	if (draw_point.u - prev_point.u < 0)
		color = COLOR_BLUE;
	if (draw_point.v - prev_point.v > 0)
		color = COLOR_RED;
	if (draw_point.v - prev_point.v < 0)
		color = COLOR_GREEN;
	if (draw_point.u - prev_point.u)
	{
		if (hit_wall((t_point){draw_point.u, prev_point.v}, map))
		{
			if (draw_point.u - prev_point.u > 0)
				color = COLOR_YELLOW;
			else
				color = COLOR_BLUE;
		}
	}
	if (draw_point.v - prev_point.v)
	{
		if (hit_wall((t_point){prev_point.u, draw_point.v}, map))
		{
			if (draw_point.v - prev_point.v > 0)
				color = COLOR_RED;
			else
				color = COLOR_GREEN;
		}
	}
	return (color);
}

// Bresenham's line algorithm 
void	draw_line_ray(uint32_t *pixels, t_point p0, t_vec3 lookdir, t_map map, int x)
{
	t_point		diff;
	t_point		dir;
	int			slope_err;
	t_point		draw_point;
	t_point		prev_point;

	draw_point = (t_point){p0.u, p0.v};
	prev_point = draw_point; 
	diff.u = fabsf(lookdir.x * 1000000);
	diff.v = fabsf(lookdir.y * 1000000);
	dir.u = (lookdir.x > 0.0) - (lookdir.x < 0.0);
	dir.v = (lookdir.y > 0.0) - (lookdir.y < 0.0);
	slope_err = diff.u - diff.v;
	uint32_t color = COLOR_WHITE;
	int max_iter = 1000;
	int i = 0;
	while (i < max_iter)
	{
		if (hit_wall(draw_point, map))
		{
			color = get_wall_dir(draw_point, prev_point, map);
			break ;
		}
		put_pixel(pixels, draw_point, COLOR_RED);
		prev_point = draw_point;
		get_next_point_to_draw(&draw_point, &slope_err, diff, dir);
		i++;
	}
	double angle = - FOV_RAD / 2 + x * (FOV_RAD / (double) WIDTH);
	double dist = sqrt((draw_point.u - p0.u) * (draw_point.u - p0.u) + (draw_point.v - p0.v) * (draw_point.v - p0.v)) * cos(angle);
	if (dist <= 0)
		return ;
	double projection_plane_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	double height = (MAP_SCALE / dist) * projection_plane_dist;
	int start = (HEIGHT - height) / 2.0;
	int delta = 0;
	while (delta < height)
	{
		// if (delta == 0|| delta + 1 > height || x % 64 == 0 )
			put_pixel(pixels, (t_point){x, start + delta}, color);
		delta ++;
	}
}

static void	get_next_point_to_draw(t_point *p, int *slope_err,
		t_point diff, t_point dir)
{
	int	err2;

	err2 = 2 * (*slope_err);
	if (err2 >= -diff.v)
	{
		*slope_err -= diff.v;
		p->u += dir.u;
	}
	if (err2 <= diff.u)
	{
		*slope_err += diff.u;
		p->v += dir.v;
	}
}
