/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/12 21:28:25 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel)
{
	uint32_t *pixels;

	if (pixel.u < 0)
		pixel.u = 0;
	else if (pixel.u >= (int)texture->width)
		pixel.u = texture->width - 1;
	if (pixel.v < 0)
		pixel.v = 0;
	else if (pixel.v >= (int)texture->height)
		pixel.v = texture->height - 1;
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
