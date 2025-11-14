/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_bg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:20:02 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 20:22:50 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	calculate_bg_tex_coord(t_point pixel_pos, mlx_image_t *image,
				mlx_texture_t *texture)
{
	t_point	tex_coord;

	tex_coord.u = ((int)round(pixel_pos.u * ft_game()->render.bg_scale
				+ ft_game()->render.bg_start_offset)) % (int)texture->width;
	if (tex_coord.u < 0)
		tex_coord.u += texture->width;
	tex_coord.v = (int)round(((pixel_pos.v - image->height / 2.0)
				- ft_game()->player->lookupdown)
			* ft_game()->render.bg_scale) + texture->height / 2;
	return (tex_coord);
}

void	draw_cubemap(mlx_image_t *image, t_point screen_coords)
{
	t_point			tex_coord;
	mlx_texture_t	*texture;
	t_point			pos;
	t_point			pixel_pos;

	texture = ft_game()->textures.bg;
	if (!texture || !texture->pixels)
		return ;
	pos.u = -1;
	while (++pos.u < PIXEL_SIZE)
	{
		pos.v = -1;
		while (++pos.v < PIXEL_SIZE)
		{
			pixel_pos.u = screen_coords.u + pos.u - PIXEL_SIZE / 2;
			pixel_pos.v = screen_coords.v + pos.v - PIXEL_SIZE / 2;
			tex_coord = calculate_bg_tex_coord(pixel_pos, image, texture);
			put_pixel(image, pixel_pos.u, pixel_pos.v,
				ft_get_pixel_color(texture, tex_coord));
		}
	}
}

void	draw_cubemap_pixel_size(mlx_image_t *image, t_point screen_coords)
{
	t_point			tex_coord;
	mlx_texture_t	*texture;

	texture = ft_game()->textures.bg;
	if (!texture || !texture->pixels)
		return ;
	tex_coord = calculate_bg_tex_coord(screen_coords, image, texture);
	draw_square(image, PIXEL_SIZE, screen_coords,
		ft_get_pixel_color(texture, tex_coord));
}
