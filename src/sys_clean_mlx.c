/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_clean_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/14 11:55:16 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_image(mlx_image_t **image)
{
	if (image && *image)
	{
		mlx_delete_image(ft_game()->mlx, *image);
		*image = NULL;
	}
}

void	ft_free_texture(mlx_texture_t **texture)
{
	if (texture && *texture)
	{
		mlx_delete_texture(*texture);
		*texture = NULL;
	}
}

static void	ft_free_mlx_textures_images(t_gs *game)
{
	printf(COLOR_C"Freeing textures...\n"COLOR_X);
	ft_free_texture(&game->textures.floor_atlas);
	ft_free_texture(&game->textures.ceiling_atlas);
	ft_free_texture(&game->textures.bg);
	ft_free_texture(&game->textures.wall_atlas);
	ft_free_texture(&game->textures.ui_minimap);
	ft_free_texture(&game->textures.ui_health);
	ft_free_texture(&game->textures.screen_defeat);
	ft_free_texture(&game->textures.screen_victory);
	if (game->mlx)
	{
		printf(COLOR_C"Freeing images...\n"COLOR_X);
		ft_free_image(&game->minimap);
		ft_free_image(&game->miniplayer);
		ft_free_image(&game->view3d);
		ft_free_image(&game->view3d_bg);
		ft_free_image(&game->hud);
		ft_free_image(&game->health);
		ft_free_image(&game->health_bar);
		ft_free_image(&game->end_screen);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
}

void	ft_free_mlx(void)
{
	t_gs		*game;

	game = ft_game();
	ft_free_mlx_envirtex(game);
	ft_free_mlx_prefabs_chars(game);
	ft_free_mlx_prefabs_items(game);
	ft_free_mlx_textures_images(game);
}
