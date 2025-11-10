/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 16:54:44 by psmolin          ###   ########.fr       */
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
	printf(COLOR_G"Loaded texture %s (w: %d, h: %d)\n"COLOR_X, path,
		(*texture)->width, (*texture)->height);
}

static void	ft_load_frames_from_texture(t_point frame, int i,
		mlx_texture_t **frames, mlx_texture_t *full)
{
	int	x;
	int	y;
	int	c;
	int	src_i;
	int	dst_i;

	y = 0;
	while (y < frame.v)
	{
		x = 0;
		while (x < frame.u)
		{
			src_i = ((y * full->width) + (x + i * frame.u)) * 4;
			dst_i = ((y * frame.u) + x) * 4;
			c = -1;
			while (++c < 4)
				frames[i]->pixels[dst_i + c] = full->pixels[src_i + c];
			x++;
		}
		y++;
	}
}

static bool	ft_load_empty_mlx_texture(mlx_texture_t **texture,
		t_point frame_size)
{
	*texture = malloc(sizeof(mlx_texture_t));
	if (!*texture)
		return (false);
	(*texture)->width = frame_size.u;
	(*texture)->height = frame_size.v;
	(*texture)->bytes_per_pixel = 4;
	(*texture)->pixels = malloc(frame_size.u * frame_size.v * 4);
	if (!(*texture)->pixels)
	{
		free(*texture);
		return (false);
	}
	return (true);
}

/**
 * Load one horizontally alligned texture and splits it into n_frames
 */
void	ft_load_anim_texture(const char *path, mlx_texture_t **frames,
		int n_frames)
{
	mlx_texture_t	*full;
	int				frame_w;
	int				frame_h;
	int				i;

	full = mlx_load_png(path);
	if (!full)
	{
		printf(COLOR_R"%s\n"COLOR_X, path);
		ft_exit_perror("Failed to load texture\n");
	}
	frame_w = full->width / n_frames;
	frame_h = full->height;
	i = -1;
	while (++i < n_frames)
	{
		if (!ft_load_empty_mlx_texture(&frames[i], (t_point){frame_w, frame_h}))
		{
			mlx_delete_texture(full);
			ft_exit_perror("Could not allocate memory for animated sprite\n");
		}
		ft_load_frames_from_texture((t_point){frame_w, frame_h},
			i, frames, full);
	}
	mlx_delete_texture(full);
}

void	ft_load_texture_from_atlas(int row, int col,
		mlx_texture_t **texture, mlx_texture_t *atlas)
{
	uint32_t		y;
	uint32_t		x;
	uint32_t		y_start;
	uint32_t		x_start;

	ft_load_texture(TEX_WALL_PLCHLDR, texture);
	y_start = row * (*texture)->height;
	x_start = col * (*texture)->width;
	y = 0;
	while (y < (*texture)->height)
	{
		x = 0;
		while (x < (*texture)->width)
		{
			((uint32_t *)(*texture)->pixels)[(y * (*texture)->width) + x]
				= ((uint32_t *)atlas->pixels)[((y_start + y) * atlas->width)
				+ (x_start + x)];
			x++;
		}
		y++;
	}
}
