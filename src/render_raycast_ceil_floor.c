/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_ceil_floor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:00:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 20:20:43 by nmikuka          ###   ########.fr       */
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
			draw_cubemap(ft_game()->view3d, (t_point){x, y});
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
			draw_cubemap(ft_game()->view3d, (t_point){x, y});
		y += PIXEL_SIZE;
	}
}
