/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_wall.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:12 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 10:49:39 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_find_texture_u(mlx_texture_t **texture, t_rayrender ray)
{
	int	tex_u;
	t_vec2 loc;
	t_direction dir;
	int	wall_type;

	dir = ray.wall_dir;
	loc = ray.end;
	wall_type = ray.wall_type - '1';
	wall_type = ft_clamp(wall_type, 0, WALLS_TYPES_COUNT - 1);
	if (ray.is_doorway)
		wall_type = 9;
	if (ray.is_door)
	{
		*texture = ray.door->sprite.texture;
		if (ray.door->is_opening)
		{
			loc.x -= (DOOR_OPEN_TIME - ray.door->dt)/DOOR_OPEN_TIME;
			loc.y += (DOOR_OPEN_TIME - ray.door->dt)/DOOR_OPEN_TIME;
		}
	}
	if (dir == DIR_NO)
	{
		if (!ray.is_door)
			*texture = ft_game()->textures.walls[wall_type].tex[DIR_NO];
		tex_u = (int)((loc.x - floorf(loc.x)) * ((*texture)->width));
	}
	else if (dir == DIR_SO)
	{
		if (!ray.is_door)
		{
			*texture = ft_game()->textures.walls[wall_type].tex[DIR_SO];
			tex_u = (int)((1.0f -(loc.x - floorf(loc.x))) * ((*texture)->width));
		}
		else
			tex_u = (int)(((loc.x - floorf(loc.x))) * ((*texture)->width));
	}
	else if (dir == DIR_EA)
	{
		if (!ray.is_door)
		{
			*texture = ft_game()->textures.walls[wall_type].tex[DIR_EA];
			tex_u = (int)((loc.y - floorf(loc.y)) * ((*texture)->width));
		}
		else
			tex_u = (int)((1.0f - (loc.y - floorf(loc.y))) * ((*texture)->width));
	}
	else
	{
		if (!ray.is_door)
			*texture = ft_game()->textures.walls[wall_type].tex[DIR_WE];
		tex_u = (int)((1.0f - (loc.y - floorf(loc.y))) * ((*texture)->width));
	}
	return (tex_u);
}

static void	init_colrender(t_colrender *cr, double wall_start,
				double wall_height)
{
	cr->wall_start = floor(wall_start);
	cr->wall_end = round(wall_start + wall_height + 0.5);
	cr->wall_height = cr->wall_end - cr->wall_start;
}

void	draw_wall_part(t_rayrender ray, int x, double wall_start)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	t_point			pixel;
	uint32_t		color;
	int				delta;
	t_colrender		cr;

	image = ft_game()->view3d;
	pixel.u = ft_find_texture_u(&texture, ray);
	init_colrender(&cr, wall_start, ray.wall_height);
	delta = PIXEL_SIZE - cr.wall_start % PIXEL_SIZE;
	if (cr.wall_start < 0)
		delta = -cr.wall_start;
	while (delta <= cr.wall_height)
	{
		if ((cr.wall_start + delta) >= (int)image->height + PIXEL_SIZE)
			break ;
		pixel.v = ((float)(delta + cr.wall_start) - wall_start) * texture->height / (float)ray.wall_height;
		color = ft_get_pixel_color(texture, pixel);
		if (color != 0)
			draw_square(image, PIXEL_SIZE, (t_point){x, cr.wall_start + delta}, color);
		else
			draw_cubemap(image, &ray, (t_point){x, cr.wall_start + delta});
		delta += PIXEL_SIZE;
	}
}
