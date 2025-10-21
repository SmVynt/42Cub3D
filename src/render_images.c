/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/20 14:01:06 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel)
{
	uint32_t *pixels;

	pixel.u = ft_clamp(pixel.u, 0, texture->width - 1);
	pixel.v = ft_clamp(pixel.v, 0, texture->height - 1);
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
