/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/27 02:57:26 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_texture(const char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		printf(COLOR_R"%s\n"COLOR_X, path);
		ft_exit_perror("Failed to load texture\n");
	}
	printf(COLOR_G"Loaded texture %s (w: %d, h: %d)\n"COLOR_X, path, (*texture)->width, (*texture)->height);
}

void	ft_load_wall_texture(int index, t_direction dir, mlx_texture_t **texture)
{
	uint32_t		y;
	uint32_t		x;
	uint32_t		y_start;
	uint32_t		x_start;
	mlx_texture_t	*atlas;
	//copying to the texture a part of a texture atlas based on index and dir
	ft_load_texture(TEX_WALL_PLCHLDR, texture);
	y_start = (index - 1) * (*texture)->height;
	x_start = dir * (*texture)->width;
	atlas = ft_game()->textures.wall_atlas;
	y = 0;
	while (y < (*texture)->height)
	{
		x = 0;
		while (x < (*texture)->width)
		{
			((uint32_t *)(*texture)->pixels)[(y * (*texture)->width) + x] = ((uint32_t *)atlas->pixels)[((y_start + y) * atlas->width) + (x_start + x)];
			x++;
		}
		y++;
	}

}
