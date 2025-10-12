/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/12 11:39:17 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_next_point_to_draw(t_point *p, int *slope_err,
		t_point diff, t_point dir);

static t_vec2 get_ray_end(t_vec2 start, t_vec3 dir, int max_steps, uint32_t *color);

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

u_int32_t	get_wall_dir(t_point draw_point, t_point prev_point, t_map map, mlx_image_t *image)
{
	uint32_t	color;

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
		if (hit_wall((t_point){draw_point.u, prev_point.v}, map, image))
		{
			if (draw_point.u - prev_point.u > 0)
				color = COLOR_YELLOW;
			else
				color = COLOR_BLUE;
		}
	}
	if (draw_point.v - prev_point.v)
	{
		if (hit_wall((t_point){prev_point.u, draw_point.v}, map, image))
		{
			if (draw_point.v - prev_point.v > 0)
				color = COLOR_RED;
			else
				color = COLOR_GREEN;
		}
	}
	return (color);
}

void	draw_line_ray(mlx_image_t *image, t_point p0, t_vec3 lookdir, t_map map, int x)
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
		put_pixel(image, draw_point, COLOR_RED);
		get_next_point_to_draw(&draw_point, &slope_err, diff, dir);
		i++;
	}
}

static int	ft_find_texture_u(mlx_texture_t **texture, t_vec2 loc, uint32_t color)
{
	int	tex_u;

	if (color == COLOR_RED)
	{
		*texture = ft_game()->textures.so;
		tex_u = (int)((loc.x - floorf(loc.x)) * ((*texture)->width));
	}
	else if (color == COLOR_GREEN)
	{
		*texture = ft_game()->textures.no;
		tex_u = (int)((1.0f -(loc.x - floorf(loc.x))) * ((*texture)->width));
	}
	else if (color == COLOR_YELLOW)
	{
		*texture = ft_game()->textures.ea;
		tex_u = (int)((loc.y - floorf(loc.y)) * ((*texture)->width));
	}
	else
	{
		*texture = ft_game()->textures.we;
		tex_u = (int)((1.0f - (loc.y - floorf(loc.y))) * ((*texture)->width));
	}
	return (tex_u);
}

void ft_draw_wall_part(t_vec2 loc, uint32_t color, double height, int x)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	t_point			pixel;
	int				start;
	int				delta;

	image = ft_game()->view3d;
	pixel.u = ft_find_texture_u(&texture, loc, color);
	start = (((int)(image->height - height) / 2) / PIXEL_SIZE) * PIXEL_SIZE;
	delta = 0;
	while (delta <= height)
	{
		int y = start + delta;
		pixel.v = (int)(delta / height * texture->height);
		draw_square(image, PIXEL_SIZE, (t_point){x, y}, ft_get_pixel_color(texture, pixel));
		delta += PIXEL_SIZE;
	}
}

static void ft_draw_floor_ceil_part(t_rowrender row, t_vec3 lookdir, int x)
{
	mlx_image_t *image;
	// mlx_texture_t *texture;
	t_point		pixel;
	int			y;
	double		fisheye_correction;

	image = ft_game()->view3d;
	y = (((int)(image->height + row.height) / 2) / PIXEL_SIZE) * PIXEL_SIZE;
	fisheye_correction = cos(row.angle);

	while (y < (int)image->height)
	{
		double screen_y = y - image->height / 2.0;
		double floor_distance = ft_game()->render.projection_plane_dist / screen_y / fisheye_correction / 2.0;
		pixel.u = ft_get_tex_coord(row.player_point.x + lookdir.x * floor_distance, ft_game()->textures.no->width);
		pixel.v = ft_get_tex_coord(row.player_point.y + lookdir.y * floor_distance, ft_game()->textures.no->height);
		draw_square(image, PIXEL_SIZE, (t_point){x, y}, ft_get_pixel_color(ft_game()->textures.no, pixel));
		draw_square(image, PIXEL_SIZE, (t_point){x, image->height - y}, ft_get_pixel_color(ft_game()->textures.so, pixel));
		// delta++;
		y += PIXEL_SIZE;
	}
}

void	draw_wall(mlx_image_t *image, t_vec2 point, t_vec3 lookdir, int x)
{
	t_rowrender	row;

	row.player_point.x = point.x + 0.5f;
	row.player_point.y = point.y + 0.5f;
	row.draw_point = (t_vec2){row.player_point.x, row.player_point.y};
	row.color = COLOR_GREEN;
	int max_iter = 1000;

	row.draw_point = get_ray_end(row.draw_point, lookdir, max_iter, &row.color);
	row.angle = - FOV_RAD / 2 + x * (FOV_RAD / (double) (image->width - 1));
	row.dist = ft_vec2_length((t_vec2){row.draw_point.x - row.player_point.x, row.draw_point.y - row.player_point.y})* cos(row.angle);
	if (row.dist <= 0)
		return ;
	// double projection_plane_dist = (image->width / 2.0) / tan(FOV_RAD / 2.0);
	row.height = (1.0 / row.dist) * ft_game()->render.projection_plane_dist;

	ft_draw_wall_part(row.draw_point, row.color, row.height, x);
	ft_draw_floor_ceil_part(row, lookdir, x);
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

static t_vec2 get_next_wall_intersection(t_vec2 pos, t_vec3 dir, int *tile_x, int *tile_y, int *side)
{
	t_vec2	hit_point;
	t_vec2	next_wall;
	t_vec2	dist;

	int step_x = (dir.x >= 0) - (dir.x <= 0);
	int step_y = (dir.y >= 0) - (dir.y <= 0);
	if (dir.x > 0)
		next_wall.x = ceil(pos.x);
	else
		next_wall.x = floor(pos.x);
	if (fabs(next_wall.x - pos.x) < 1e-9)
		next_wall.x += step_x;
	if (dir.y > 0)
		next_wall.y = ceil(pos.y);
	else
		next_wall.y = floor(pos.y);
	if (fabs(next_wall.y - pos.y) < 1e-9)
		next_wall.y += step_y;
	if (fabs(dir.x) > 1e-9)
		dist.x = (next_wall.x - pos.x) / dir.x;
	else
		dist.x = INFINITY;
	if (fabs(dir.y) > 1e-9)
		dist.y = (next_wall.y - pos.y) / dir.y;
	else
		dist.y = INFINITY;
	if (dist.x < dist.y)
	{
		hit_point.x = next_wall.x;
		hit_point.y = pos.y + dist.x * dir.y;
		*tile_x = (int)next_wall.x;
		if (step_x < 0)
			*tile_x -= 1;
		*tile_y = (int)floor(hit_point.y);
		*side = 0;
	}
	else
	{
		hit_point.x = pos.x + dist.y * dir.x;
		hit_point.y = next_wall.y;
		*tile_x = (int)floor(hit_point.x);
		*tile_y = (int)next_wall.y;
		if (step_y < 0)
			*tile_y -= 1;
		*side = 1;
	}
	return hit_point;
}

static t_vec2 get_ray_end(t_vec2 start, t_vec3 dir, int max_iter, uint32_t *color)
{
	t_vec2	curr;
	t_point	tile;
	int		i;
	int		side;

	curr = start;
	i = 0;
	while (i < max_iter)
	{
		curr = get_next_wall_intersection(curr, dir, &tile.u, &tile.v, &side);
		// printf("Hit wall at (%.2f, %.2f), tile[%d][%d], side=%d\n",
		//        hit_point.x, hit_point.y, tile_y, tile_x, side);
		if (ft_is_wall((t_vec2){tile.u, tile.v}))
		{
			if (side && dir.y > 0)
				*color = COLOR_RED;
			else if (side)
				*color = COLOR_GREEN;
			else if (dir.x > 0)
				*color = COLOR_YELLOW;
			else
				*color = COLOR_BLUE;
			return (curr);
		}
	}
	return (t_vec2){0.0, 0.0};
}
