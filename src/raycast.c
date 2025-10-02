/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/02 21:53:19 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	get_next_point_to_draw(t_vec2 *p, int *slope_err,
		t_vec2 diff, t_vec2 dir);

bool touch(t_vec2 p, char **map)
{
	int x;
	int y;

    x = (p.x - 10/2) / 10;
	y = (p.y - 10/2) / 10 ;
    if(map[y][x] == '1')
        return (true);
    return (false);
}

// Bresenham's line algorithm 
void	draw_line_ray(uint32_t *pixels, t_vec2f p, t_vec3 lookdir, char **map)
{
	t_vec2		diff;
	t_vec2		dir;
	int			slope_err;
	t_vec2		p1;
	t_vec2		p0;

	p0.x = (int)p.x * 10 + 10;
	p0.y = (int)p.y * 10 + 10;
	p1.x = p0.x + lookdir.x * 100;
	p1.y = p0.y + lookdir.y * 100;
	diff.x = abs(p1.x - p0.x);
	diff.y = abs(p1.y - p0.y);
	dir.x = (p0.x < p1.x) - (p0.x >= p1.x);
	dir.y = (p0.y < p1.y) - (p0.y >= p1.y);
	slope_err = diff.x - diff.y;
	while (1)
	{
		if (touch(p0, map))
			break ;
		put_pixel(pixels, p0, COLOR_RED);
		get_next_point_to_draw(&p0, &slope_err, diff, dir);
	}
}

static void	get_next_point_to_draw(t_vec2 *p, int *slope_err,
		t_vec2 diff, t_vec2 dir)
{
	int	err2;

	err2 = 2 * (*slope_err);
	if (err2 >= -diff.y)
	{
		*slope_err -= diff.y;
		p->x += dir.x;
	}
	if (err2 <= diff.x)
	{
		*slope_err += diff.x;
		p->y += dir.y;
	}
}
