/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/06 00:39:23 by psmolin          ###   ########.fr       */
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

/**
 * Load one horizontally alligned texture and splits it into n_frames
 */
void	ft_load_anim_texture(const char *path, mlx_texture_t **frames, int n_frames)
{
	mlx_texture_t	*full;
	int				frame_w;
	int				frame_h;

	full = mlx_load_png(path);
	if (!full)
	{
		printf(COLOR_R"%s\n"COLOR_X, path);
		ft_exit_perror("Failed to load texture\n");
	}
	frame_w = full->width / n_frames;
	frame_h = full->height;

	for (int i = 0; i < n_frames; i++)
	{
		frames[i] = malloc(sizeof(mlx_texture_t));
		if (!frames[i])
			ft_exit_perror("Could not allocate memory for animated sprite\n");
		frames[i]->width = frame_w;
		frames[i]->height = frame_h;
		frames[i]->bytes_per_pixel = full->bytes_per_pixel;
		frames[i]->pixels = malloc(frame_w * frame_h * 4);
		if (!frames[i]->pixels)
			ft_exit_perror("Could not allocate memory for animated sprite\n");
		// Copy pixels for this frame
		for (int y = 0; y < frame_h; y++)
		{
			for (int x = 0; x < frame_w; x++)
			{
				int src_i = ((y * full->width) + (x + i * frame_w)) * 4;
				int dst_i = ((y * frame_w) + x) * 4;
				for (int c = 0; c < 4; c++)
					frames[i]->pixels[dst_i + c] = full->pixels[src_i + c];
			}
		}
		printf(COLOR_G"Loaded frame %d from %s (w: %d, h: %d)\n"COLOR_X,
			i, path, frames[i]->width, frames[i]->height);
	}

	mlx_delete_texture(full);
}


void	ft_load_texture_from_atlas(int row, int col, mlx_texture_t **texture)
{
	uint32_t		y;
	uint32_t		x;
	uint32_t		y_start;
	uint32_t		x_start;
	mlx_texture_t	*atlas;
	//copying to the texture a part of a texture atlas based on index and dir
	ft_load_texture(TEX_WALL_PLCHLDR, texture);
	y_start = row * (*texture)->height;
	x_start = col * (*texture)->width;
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
