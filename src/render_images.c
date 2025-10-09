/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/09 16:54:28 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel)
{
	uint32_t	color;
	int			pixel_index;

	if (pixel.u < 0 || pixel.u >= (int)texture->width
		|| pixel.v < 0 || pixel.v >= (int)texture->height)
		return (0xFF808080);
	pixel_index = (pixel.v * texture->width + pixel.u) * 4;
	color = (texture->pixels[pixel_index + 3] << 24)
		| (texture->pixels[pixel_index + 2] << 16)
		| (texture->pixels[pixel_index + 1] << 8)
		| (texture->pixels[pixel_index]);
	return (color);
}
