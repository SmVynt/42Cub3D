/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/09 17:03:38 by psmolin          ###   ########.fr       */
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

// Bresenham's line algorithm
void	draw_line_ray(mlx_image_t *image, t_point p0, t_vec3 lookdir, t_map map, int x)
{
	t_point		diff;
	t_point		dir;
	int			slope_err;
	t_point		draw_point;
	// t_point		prev_point;

	(void) x;
	draw_point = (t_point){p0.u, p0.v};
	// prev_point = draw_point;
	diff.u = fabsf(lookdir.x * 1000000);
	diff.v = fabsf(lookdir.y * 1000000);
	dir.u = (lookdir.x > 0.0) - (lookdir.x < 0.0);
	dir.v = (lookdir.y > 0.0) - (lookdir.y < 0.0);
	slope_err = diff.u - diff.v;
	// uint32_t color = COLOR_WHITE;
	int max_iter = 1000;
	int i = 0;
	while (i < max_iter)
	{
		if (hit_wall(draw_point, map, image))
		{
			// color = get_wall_dir(draw_point, prev_point, map, image);
			break ;
		}
		put_pixel(image, draw_point, COLOR_RED);
		// prev_point = draw_point;
		get_next_point_to_draw(&draw_point, &slope_err, diff, dir);
		i++;
	}
	// double angle = - FOV_RAD / 2 + x * (FOV_RAD / (double) image->width);
	// double dist = sqrt((draw_point.u - p0.u) * (draw_point.u - p0.u) + (draw_point.v - p0.v) * (draw_point.v - p0.v)) * cos(angle);
	// if (dist <= 0)
	// 	return ;
	// double projection_plane_dist = (image->width / 2.0) / tan(FOV_RAD / 2.0);
	// double height = (MAP_SCALE / dist) * projection_plane_dist;
	// int start = (image->height - height) / 2.0;
	// int delta = 0;
	// while (delta < height)
	// {
	// 	// if (delta == 0|| delta + 1 > height || x % 64 == 0 )
	// 		put_pixel(image, (t_point){x, start + delta}, color);
	// 	delta++;
	// }
}

void ft_draw_wall_part(t_vec2 loc, uint32_t color, double height, int x)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	t_point			pixel;
	int				start;
	int				delta;

	image = ft_game()->view3d;
	if (color == COLOR_RED)
	{
		texture = ft_game()->textures.so;
		pixel.u = (int)((loc.x - (int)loc.x) * (texture->width));
	}
	else if (color == COLOR_GREEN)
	{
		texture = ft_game()->textures.no;
		pixel.u = (int)((1.0f -loc.x + (int)loc.x) * (texture->width));
	}
	else if (color == COLOR_YELLOW)
	{
		texture = ft_game()->textures.ea;
		pixel.u = (int)((loc.y - (int)loc.y) * (texture->width));
	}
	else
	{
		texture = ft_game()->textures.ea;
		pixel.u = (int)((1.0f - loc.y + (int)loc.y) * (texture->width));
	}
	start = (image->height - height) / 2.0;
	delta = 0;
	while (delta < height)
	{
		pixel.v = (int)(delta / height * texture->height);
		color = ft_get_pixel_color(texture, pixel);
		put_pixel(image, (t_point){x, start + delta}, color);
		delta++;
	}
}

static void ft_draw_floor_part(t_vec2 p0, t_vec3 lookdir, double wall_height, int x)
{
	mlx_image_t *image;
	mlx_texture_t *texture;
	t_point		pixel;
	int			start;
	int			delta;
	uint32_t	color;

	image = ft_game()->view3d;
	texture = ft_game()->textures.no; // Using north texture for floor
	start = (image->height + wall_height) / 2.0;
	delta = 0;
	while (start + delta < (int)image->height)
	{
		double current_dist = (MAP_SCALE * (image->height / 2.0)) / (start + delta - image->height / 2.0);
		double weight = current_dist / (MAP_SCALE / 2.0);
		double floor_x = p0.x + weight * lookdir.x;
		double floor_y = p0.y + weight * lookdir.y;
		//

		pixel.u = (int)((floor_x - (int)floor_x) * texture->width);
		pixel.v = (int)((floor_y - (int)floor_y) * texture->height);
		color = ft_get_pixel_color(texture, pixel);
		put_pixel(image, (t_point){x, start + delta}, color);
		delta++;
	}
}

void	draw_wall(mlx_image_t *image, t_vec2 p0, t_vec3 lookdir, int x)
{
	t_vec2		draw_point;

	p0.x += 0.5f;
	p0.y += 0.5f;
	draw_point = (t_vec2){p0.x, p0.y};
	uint32_t color = COLOR_GREEN;
	int max_iter = 1000;
	draw_point = get_ray_end(draw_point, lookdir, max_iter, &color);
	double angle = - FOV_RAD / 2 + x * (FOV_RAD / (double) (image->width - 1));
	double dist = ft_vec2_length((t_vec2){draw_point.x - p0.x, draw_point.y - p0.y})* cos(angle);
	// printf("%f %f\n", draw_point.x, draw_point.y);
	if (dist <= 0)
		return ;
	double projection_plane_dist = (image->width / 2.0) / tan(FOV_RAD / 2.0);
	double height = (1.0 / dist) * projection_plane_dist;
	ft_draw_wall_part(draw_point, color, height, x);
	ft_draw_floor_part(p0, lookdir, height, x);
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
