/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_ceil_floor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:00:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 11:17:27 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_dist_to_screen_point(int y, t_rayrender ray)
{
	double	screen_center_y;
	double	height_from_center;
	double	jump_scale_factor;
	double	dist;

	screen_center_y = ft_game()->view3d->height / 2.0;
	height_from_center = y - screen_center_y - ft_game()->player->lookupdown;
	jump_scale_factor = ft_game()->player->jump_height
		+ ft_signd(height_from_center) * 1.0;
	dist = (ft_game()->render.projection_plane_dist * jump_scale_factor)
		/ (2.0 * fabs(height_from_center) * cos(ray.angle));
	return (dist);
}

static mlx_texture_t	*get_texture_ceil_floor(t_vec2 p,
		mlx_texture_t **tex_array)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)(p.x);
	y = (int)(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (tex_array[3]);
	if (map->tile[y][x] == '0')
		return (tex_array[0]);
	if (map->tile[y][x] == ' ')
		return (tex_array[1]);
	if (map->tile[y][x] == '_')
		return (tex_array[2]);
	return (tex_array[3]);
}

void	draw_ceil_part(t_rayrender ray, int x, double wall_start)
{
	t_vec2			world_pos;
	t_point			tex_coord;
	double			dist;
	uint32_t		color;
	int				y;

	y = 0;
	while (y < wall_start)
	{
		dist = get_dist_to_screen_point(y, ray);
		world_pos.x = ray.start.x - ray.dir.x * dist;
		world_pos.y = ray.start.y - ray.dir.y * dist;
		tex_coord.u = ft_get_tex_coord(world_pos.x, STANDARD_SPRITE_SIZE);
		tex_coord.v = ft_get_tex_coord(world_pos.y, STANDARD_SPRITE_SIZE);
		color = ft_get_pixel_color(get_texture_ceil_floor(world_pos,
					ft_game()->textures.ceiling), tex_coord);
		if (color != 0)
			draw_square(ft_game()->view3d, PIXEL_SIZE, (t_point){x, y}, color);
		else
			draw_cubemap(ft_game()->view3d, &ray, (t_point){x, y});
		y += PIXEL_SIZE;
	}
}

void	draw_floor_part(t_rayrender ray, int x, int wall_end)
{
	t_vec2			world_pos;
	t_point			tex_coord;
	double			dist;
	uint32_t		color;
	int				y;

	y = wall_end / PIXEL_SIZE * PIXEL_SIZE;
	while (y < (int)ft_game()->view3d->height + PIXEL_SIZE / 2)
	{
		dist = get_dist_to_screen_point(y, ray);
		world_pos.x = ray.start.x + ray.dir.x * dist;
		world_pos.y = ray.start.y + ray.dir.y * dist;
		tex_coord.u = ft_get_tex_coord(world_pos.x, STANDARD_SPRITE_SIZE);
		tex_coord.v = ft_get_tex_coord(world_pos.y, STANDARD_SPRITE_SIZE);
		color = ft_get_pixel_color(get_texture_ceil_floor(world_pos,
					ft_game()->textures.floor), tex_coord);
		if (color != 0)
			draw_square(ft_game()->view3d, PIXEL_SIZE, (t_point){x, y}, color);
		else
			draw_cubemap(ft_game()->view3d, &ray, (t_point){x, y});
		y += PIXEL_SIZE;
	}
}

void	draw_cubemap_1(mlx_image_t *image, t_rayrender *ray,
		t_point screen_coords)
{
	mlx_texture_t	*bg;
	t_point			pixel;
	double			angle;
	double			scale_correction;
	double			screen_center_offset;

	bg = ft_game()->textures.bg;
	if (ray->bgx == -1)
	{
		angle = atan2(ray->dir.y, ray->dir.x);
		if (angle < 0)
			angle += 2.0 * M_PI;
		ray->bgx = (int)((angle / (2.0 * M_PI)) * (double)bg->width);
	}
	pixel.u = ray->bgx;
	scale_correction = ft_game()->render.bg_proportion * (double)bg->height
		/ (double)image->height;
	screen_center_offset = (double)screen_coords.v - (double)image->height / 2;
	pixel.v = (int)(screen_center_offset * scale_correction
			+ (double)bg->height / 2
			- ft_game()->player->lookupdown * scale_correction);
	draw_square(image, PIXEL_SIZE, screen_coords,
		ft_get_pixel_color(bg, pixel));
}

void	draw_cubemap(mlx_image_t *image, t_rayrender *ray,
		t_point screen_coords)
{
	t_point			tex_coord;
	double			angle;
	double			horizontal_offset;
	double			scale;
	mlx_texture_t	*texture;

	(void)ray;
	texture = ft_game()->textures.bg;
	if (!texture || !texture->pixels)
		return ;
	angle = atan2(ft_game()->player->lookdir.y, ft_game()->player->lookdir.x);
	if (angle < 0)
		angle += 2.0 * M_PI;
	horizontal_offset = angle * (double)texture->width / (2.0 * M_PI);
	scale = FOV_RAD * ((double)texture->width / (2.0 * M_PI)
			/ (double)image->width);
	int u = -PIXEL_SIZE / 2;
	while (u < PIXEL_SIZE)
	{
		int v = -PIXEL_SIZE / 2;
		while (v < PIXEL_SIZE)
		{
			tex_coord.u = ((int)round((screen_coords.u + u) * scale + horizontal_offset))
				% (int)texture->width;
			if (tex_coord.u < 0)
			tex_coord.u += texture->width;
			tex_coord.v = (int)round((((screen_coords.v + v) - image->height / 2.0)
				- ft_game()->player->lookupdown) * scale)
				+ texture->height / 2;
			put_pixel(image, (screen_coords.u + u), (screen_coords.v + v), ft_get_pixel_color(texture, tex_coord));
			v++;
		}
		u++;
	}
	// tex_coord.u = ((int)round(screen_coords.u * scale + horizontal_offset))
	// 	% (int)texture->width;
	// if (tex_coord.u < 0)
	// 	tex_coord.u += texture->width;
	// tex_coord.v = (int)round(((screen_coords.v - image->height / 2.0)
	// 			- ft_game()->player->lookupdown) * scale)
	// 	+ texture->height / 2;
	// draw_square(image, PIXEL_SIZE, screen_coords,
	// 	ft_get_pixel_color(texture, tex_coord));
}
