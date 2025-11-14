/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:10:54 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 20:51:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_tile_color(t_vec2 world_pos)
{
	if (ft_is_door(world_pos))
		return (MM_COLOR_DOORS);
	else if (ft_is_wall(world_pos))
		return (MM_COLOR_WALLS);
	else
		return (MM_COLOR_EMPTY);
}

static t_vec2	screen_to_world_coords(int x, int y, t_player *player,
		double zoom)
{
	t_vec2	coords;
	double	rotation_angle;

	coords = (t_vec2){(double)x / zoom, (double)y / zoom};
	rotation_angle = player->lookdir_angle + HALF_PI;
	coords = ft_mat4_transform_vec2(ft_mat4_rotation_z(rotation_angle), coords);
	coords.x += player->pos.x;
	coords.y += player->pos.y;
	return (coords);
}

static void	draw_map_tiles(mlx_image_t *image, t_point image_center,
		double zoom)
{
	int			x;
	int			y;
	t_vec2		world_coords;
	t_player	*player;
	uint32_t	color;

	player = ft_game()->player;
	x = -image_center.u;
	while (x < image_center.u)
	{
		y = -image_center.v;
		while (y < image_center.v)
		{
			world_coords = screen_to_world_coords(x, y, player, zoom);
			color = get_tile_color(world_coords);
			draw_square(image, UI_PIXEL_SIZE,
				(t_point){x + image_center.u, y + image_center.v}, color);
			y += UI_PIXEL_SIZE;
		}
		x += UI_PIXEL_SIZE;
	}
}

void	draw_map(void)
{
	t_point		image_center;
	double		zoom;
	mlx_image_t	*image;

	image = ft_game()->miniplayer;
	image_center.u = image->width / 2;
	image_center.v = image->height / 2;
	zoom = MM_SCALE * (double)ft_game()->view3d->height / HEIGHT;
	draw_map_tiles(image, image_center, zoom);
	draw_chars_on_minimap(image, zoom, image_center);
	draw_items_on_minimap(image, zoom, image_center);
}
