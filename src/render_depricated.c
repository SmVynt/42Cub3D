/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_depricated.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:53:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 17:56:54 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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


bool hit_wall(t_point p, t_map map, mlx_image_t* image)
{
	int x;
	int y;

	if (p.u < 0 || (unsigned int)p.u >= image->width || p.v < 0 || (unsigned int)p.v >= image->height)
		return (true);
	x = (p.u - MAP_SCALE / 2) / MAP_SCALE;
	y = (p.v - MAP_SCALE / 2) / MAP_SCALE;
	if (x < 0 || x >= map.w || y < 0 || y >= map.h)
		return (true);
	if (ft_strchar(MAP_WALL_CHARS, map.tile[y][x]) != NULL)
		return (true);
	return (false);
}

void	draw_line_ray(mlx_image_t *image, t_point p0, t_vec2 lookdir, t_map map, int x)
{
	t_point		diff;
	t_point		dir;
	int			slope_err;
	t_point		draw_point;

	(void) x;
	draw_point = (t_point){p0.u, p0.v};
	diff.u = fabsf(lookdir.x * 1000000);
	diff.v = fabsf(lookdir.y * 1000000);
	dir.u = (lookdir.x > 0.0) - (lookdir.x < 0.0);
	dir.v = (lookdir.y > 0.0) - (lookdir.y < 0.0);
	slope_err = diff.u - diff.v;
	int max_iter = 1000;
	int i = 0;
	while (i < max_iter)
	{
		if (hit_wall(draw_point, map, image))
			break ;
		put_pixel(image, draw_point.u, draw_point.v, COLOR_RED);
		get_next_point_to_draw(&draw_point, &slope_err, diff, dir);
		i++;
	}
}

void	draw_player(mlx_image_t *image)
{
	t_point center;
	t_player	*player;
	t_map		map;

	player = ft_game()->player;
	map = ft_game()->map;
	center = (t_point){(int)(player->pos.x * MAP_SCALE + MAP_SCALE),
		(int)(player->pos.y * MAP_SCALE + MAP_SCALE)};
	draw_circle(image, center, 3, COLOR_BLUE);
	float angle = - FOV_RAD / 2;
	float dangle = FOV_RAD / (ft_game()->view3d->width - 1);
	int x = 0;
	while ((unsigned int)x < ft_game()->view3d->width)
	{
		draw_line_ray(image, center, ft_mat4_transform_vec2(ft_mat4_rotation_z(angle), player->lookdir), map, x);
		angle += dangle;
		x++;
	}
	draw_line(image, center,
		(t_point){(int)(center.u + player->lookdir.x * 20),
		(int)(center.v + player->lookdir.y * 20)}, COLOR_YELLOW);
}

void	draw_line(mlx_image_t *image, t_point start, t_point end, uint32_t color)
{
	t_point	delta;
	t_point	sign;
	t_point	err;
	int		t;

	delta.u = abs(end.u - start.u);
	delta.v = abs(end.v - start.v);
	sign.u = ft_sign(end.u - start.u);
	sign.v = ft_sign(end.v - start.v);
	err.u = delta.u - delta.v;
	t = 0;
	while (t++ < 10000)
	{
		put_pixel(image, start.u, start.v, color);
		if (start.u == end.u && start.v == end.v)
			break ;
		err.v = err.u * 2;
		if (err.v > -delta.v)
		{
			err.u -= delta.v;
			start.u += sign.u;
		}
		if (err.v < delta.u)
		{
			err.u += delta.u;
			start.v += sign.v;
		}
	}
}

void	draw_map_square(mlx_image_t *image, t_point pos, uint32_t color)
{
	int size;
	int i;

	(void) color;
	size = MAP_SCALE;
	i = -size / 2;
	while (i < size / 2)
	{
		put_pixel(image, pos.u + i, pos.v - size / 2, COLOR_RED);
		put_pixel(image, pos.u + i, pos.v + size / 2, COLOR_GREEN);
		put_pixel(image, pos.u - size / 2, pos.v + i, COLOR_YELLOW);
		put_pixel(image, pos.u + size / 2, pos.v + i, COLOR_BLUE);
		i++;
	}
}

float	ft_height_delta(float distance)
{
	float jump_height;

	jump_height = (float)ft_game()->player->jump_height;
	if (distance < 0.0001f)
		distance = 0.0001f;
	return (ft_game()->render.projection_plane_dist / distance) * (jump_height + 1.0f);
}
