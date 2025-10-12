/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/12 11:08:16 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel)
{
	// uint32_t	color;
	// int			pixel_index;
	uint32_t *pixels;

	if (pixel.u < 0 || pixel.u >= (int)texture->width
		|| pixel.v < 0 || pixel.v >= (int)texture->height)
		return (COLOR_GREY);
	// pixel_index = (pixel.v * texture->width + pixel.u) * 4;
	// color = (texture->pixels[pixel_index + 3] << 24)
	// 	| (texture->pixels[pixel_index + 2] << 16)
	// 	| (texture->pixels[pixel_index + 1] << 8)
	// 	| (texture->pixels[pixel_index]);
	// return (color);
	pixels = (uint32_t *)texture->pixels;
	return (pixels[pixel.v * texture->width + pixel.u]);
}

int	ft_get_tex_coord(float x, int texture_width)
{
	int	tex_coord;

	tex_coord = (int)((x - (int)x) * (float)texture_width);
	if (tex_coord < 0)
		tex_coord = 0;
	return (tex_coord);
}
