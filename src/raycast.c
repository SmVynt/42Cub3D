/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/03 17:14:52 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	get_next_point_to_draw(t_point *p, int *slope_err,
		t_point diff, t_point dir);

bool touch(t_point p, char **map)
{
	int x;
	int y;

    x = (p.u - MAP_SCALE/2) / MAP_SCALE;
	y = (p.v - MAP_SCALE/2) / MAP_SCALE ;
    if(map[y][x] == '1')
        return (true);
    return (false);
}

// Bresenham's line algorithm
void	draw_line_ray(uint32_t *pixels, t_point p0, t_vec3 lookdir, char **map)
{
	t_point		diff;
	t_point		dir;
	int			slope_err;
	t_point		p1;

	p1.u = p0.u + lookdir.x * MAP_SCALE * 10;
	p1.v = p0.v + lookdir.y * MAP_SCALE * 10;
	diff.u = abs(p1.u - p0.u);
	diff.v = abs(p1.v - p0.v);
	dir.u = (p0.u < p1.u) - (p0.u >= p1.u);
	dir.v = (p0.v < p1.v) - (p0.v >= p1.v);
	slope_err = diff.u - diff.v;
	while (1)
	{
		if (touch(p0, map))
			break ;
		put_pixel(pixels, p0, COLOR_RED);
		get_next_point_to_draw(&p0, &slope_err, diff, dir);
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
