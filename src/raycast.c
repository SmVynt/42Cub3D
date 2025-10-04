/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/04 20:36:38 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	get_next_point_to_draw(t_point *p, int *slope_err,
		t_point diff, t_point dir);

bool hit_wall(t_vec2 p, t_map map)
{
	int x;
	int y;

	if (p.x < 0 || p.x >= WIDTH || p.y < 0 || p.y >= HEIGHT)
		return (true);
    x = (p.x - MAP_SCALE / 2) / MAP_SCALE;
	y = (p.y - MAP_SCALE / 2) / MAP_SCALE;
	if (x < 0 || x >= map.w || y < 0 || y >= map.h)
		return (true);
    if(map.tile[y][x] == '1')
        return (true);
    return (false);
}

u_int32_t get_wall_dir(t_vec2 draw_point, t_vec2 prev_point, t_map map)
{
	uint32_t color;

	if (draw_point.x - prev_point.x > 0)
		color = COLOR_YELLOW;
	if (draw_point.x - prev_point.x < 0)
		color = COLOR_BLUE;
	if (draw_point.y - prev_point.y > 0)
		color = COLOR_RED;
	if (draw_point.y - prev_point.y < 0)
		color = COLOR_GREEN;
	if (draw_point.x - prev_point.x)
	{
		if (hit_wall((t_vec2){draw_point.x, prev_point.y}, map))
		{
			if (draw_point.x - prev_point.x > 0)
				color = COLOR_YELLOW;
			else
				color = COLOR_BLUE;
		}
	}
	if (draw_point.y - prev_point.y)
	{
		if (hit_wall((t_vec2){prev_point.x, draw_point.y}, map))
		{
			if (draw_point.y - prev_point.y > 0)
				color = COLOR_RED;
			else
				color = COLOR_GREEN;
		}
	}
	return (color);
}

// Bresenham's line algorithm 
void	draw_line_ray(uint32_t *pixels, t_vec2 p0, t_vec3 lookdir, t_map map, int x)
{
	t_point		diff;
	t_point		dir;
	int			slope_err;
	t_vec2		draw_point;
	t_vec2		prev_point;

	draw_point = (t_vec2){p0.x, p0.y};
	prev_point = draw_point; 
	diff.x = fabsf(lookdir.x * 1000000);
	diff.y = fabsf(lookdir.y * 1000000);
	dir.x = (lookdir.x > 0.0) - (lookdir.x < 0.0);
	dir.y = (lookdir.y > 0.0) - (lookdir.y < 0.0);
	slope_err = diff.x - diff.y;
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
	double dist = sqrt((draw_point.x - p0.x) * (draw_point.x - p0.x) + (draw_point.y - p0.y) * (draw_point.y - p0.y)) * cos(angle);
	if (dist <= 0)
		return ;
	double projection_plane_dist = (WIDTH / 2.0) / tan(FOV_RAD / 2.0);
	double height = (MAP_SCALE / dist) * projection_plane_dist;
	int start = (HEIGHT - height) / 2.0;
	int delta = 0;
	while (delta < height)
	{
		// if (delta == 0|| delta + 1 > height || x % 64 == 0 )
			put_pixel(pixels, (t_vec2){x, start + delta}, color);
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
