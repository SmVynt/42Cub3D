/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:33:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/06 16:58:00 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t *load_centered_image(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*tex;
	int32_t			x;
	int32_t			y;
	
	tex = mlx_load_png(path);
	if (!tex)
	{
		fprintf(stderr, "Error: failed to load %s\n", path);
		return (NULL);
	}
	mlx_image_t *img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
	{
		fprintf(stderr, "Error: failed to convert texture %s to image\n", path);
		return (NULL);
	}
	x = ft_clamp((ft_game()->view3d->width - img->width) / 2, 0,ft_game()->view3d->width);
	y = ft_clamp((ft_game()->view3d->height - img->height) / 2, 0,ft_game()->view3d->height);
	if (mlx_image_to_window(mlx, img, x, y) < 0)
	{
		fprintf(stderr, "Error: failed to put image %s to window\n", path);
		mlx_delete_image(mlx, img);
		return NULL;
	}
	// img->enabled = false;
	return img;
}

void show_end_screen(int victory)
{
	if (!victory)
		return ;
	ft_game()->playing = false;
    if (victory == 1)
		ft_game()->end_screen = load_centered_image(ft_game()->mlx, TEX_VICTORY);
    else
        ft_game()->end_screen = load_centered_image(ft_game()->mlx, TEX_DEFEAT);
	// if (ft_game()->end_screen)
	// 	mlx_image_to_window(ft_game()->mlx, ft_game()->end_screen, 0, 0);
	printf("game over\n");
	// mlx_set_instance_depth(&ft_game()->end_screen->instances[0], 1000);
}
