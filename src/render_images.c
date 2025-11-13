/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/12 19:52:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel)
{
	uint32_t	*pixels;

	pixel.u = ft_clamp(pixel.u, 0, texture->width - 1);
	pixel.v = ft_clamp(pixel.v, 0, texture->height - 1);
	pixels = (uint32_t *)texture->pixels;
	return (pixels[pixel.v * texture->width + pixel.u]);
}

int	ft_get_tex_coord(double x, int texture_width)
{
	int	tex_coord;

	if (x < 0)
		return (0);
	tex_coord = (int)((x - floorf(x)) * (double)texture_width);
	return (tex_coord);
}
