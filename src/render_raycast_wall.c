/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_wall.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:12 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 21:28:19 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_wall_type(t_rayrender ray)
{
	int	wall_type;

	if (ray.is_doorway)
		return (9);
	wall_type = ray.wall_type - '1';
	return (ft_clamp(wall_type, 0, WALLS_TYPES_COUNT - 1));
}

static int	calculate_tex_u(t_vec2 loc, t_direction dir, bool is_door,
				int tex_width)
{
	double	frac_x;
	double	frac_y;

	frac_x = loc.x - floor(loc.x);
	frac_y = loc.y - floor(loc.y);
	if (dir == DIR_NO)
		return ((int)(frac_x * tex_width));
	else if (dir == DIR_SO)
	{
		if (!is_door)
			return ((int)((1.0 - frac_x) * tex_width));
		return ((int)(frac_x * tex_width));
	}
	else if (dir == DIR_EA)
	{
		if (!is_door)
			return ((int)(frac_y * tex_width));
		return ((int)((1.0 - frac_y) * tex_width));
	}
	else
		return ((int)((1.0 - frac_y) * tex_width));
}

static int	ft_find_texture_u(mlx_texture_t **texture, t_rayrender ray)
{
	t_vec2		loc;
	t_direction	dir;
	int			wall_type;

	dir = ray.wall_dir;
	loc = ray.end;
	wall_type = get_wall_type(ray);
	if (ray.is_door)
	{
		*texture = ray.door->sprite.texture;
		if (ray.door->is_opening)
		{
			loc.x -= (DOOR_OPEN_TIME - ray.door->dt) / DOOR_OPEN_TIME;
			loc.y += (DOOR_OPEN_TIME - ray.door->dt) / DOOR_OPEN_TIME;
		}
	}
	else
		*texture = ft_game()->textures.walls[wall_type].tex[dir];
	return (calculate_tex_u(loc, dir, ray.is_door, (*texture)->width));
}

static void	init_colrender(t_colrender *cr, double wall_start,
				double wall_height)
{
	cr->wall_start = floor(wall_start);
	cr->wall_end = round(wall_start + wall_height + 0.5);
	cr->wall_height = cr->wall_end - cr->wall_start;
}

void	draw_wall_part(t_rayrender ray, int x, double wall_start, int *y)
{
	mlx_image_t		*image;
	t_point			pixel;
	uint32_t		color;
	t_colrender		cr;

	image = ft_game()->view3d;
	init_colrender(&cr, wall_start, ray.wall_height);
	pixel.u = ft_find_texture_u(&cr.texture, ray);
	if (!ft_game()->is_bonus)
		*y = cr.wall_start - cr.wall_start % PIXEL_SIZE;
	while (*y <= cr.wall_start + cr.wall_height)
	{
		if (*y >= (int)image->height + PIXEL_SIZE)
			break ;
		pixel.v = (*y - wall_start) * cr.texture->height / ray.wall_height;
		color = ft_get_pixel_color(cr.texture, pixel);
		if (color != 0)
			draw_square(image, PIXEL_SIZE, (t_point){x, *y}, color);
		else
			draw_cubemap(image, (t_point){x, *y});
		*y += PIXEL_SIZE;
	}
}
