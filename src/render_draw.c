/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:56:11 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 20:46:08 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	validate_window_size(t_gs *game, int32_t width, int32_t height)
{
	if (width < MIN_WIDTH || height < MIN_HEIGHT)
	{
		mlx_set_window_size(game->mlx, ft_clamp(width, MIN_WIDTH, width),
			ft_clamp(height, MIN_HEIGHT, height));
		return (false);
	}
	return (true);
}

static void	cleanup_images(t_gs *game)
{
	if (game->hud)
		mlx_delete_image(game->mlx, game->hud);
	if (game->minimap)
		mlx_delete_image(game->mlx, game->minimap);
	if (game->miniplayer)
		mlx_delete_image(game->mlx, game->miniplayer);
	if (game->health)
		mlx_delete_image(game->mlx, game->health);
	if (game->health_bar)
		mlx_delete_image(game->mlx, game->health_bar);
	if (game->view3d)
		mlx_delete_image(game->mlx, game->view3d);
	if (game->view3d_bg)
		mlx_delete_image(game->mlx, game->view3d_bg);
	if (game->end_screen)
		mlx_delete_image(game->mlx, game->end_screen);
}

static bool	create_images(t_gs *game, int32_t width, int32_t height)
{
	t_vec2	mmap_ui_size;

	mmap_ui_size.y = height / 2.0;
	mmap_ui_size.x = mmap_ui_size.y * game->textures.ui_minimap->width
		/ (double)game->textures.ui_minimap->height;
	game->view3d_bg = mlx_new_image(game->mlx, width, height);
	ft_fill_split_bg(game->view3d_bg);
	game->view3d = mlx_new_image(game->mlx, width, height);
	game->hud = mlx_new_image(game->mlx, 64, height);
	game->minimap = mlx_new_image(game->mlx, round(mmap_ui_size.x),
			round(mmap_ui_size.y));
	game->miniplayer = mlx_new_image(game->mlx,
			round(mmap_ui_size.y * MM_SIZE / 180.0),
			round(mmap_ui_size.y * MM_SIZE / 180.0));
	game->health = mlx_new_image(game->mlx, height / 4, height / 18);
	game->health_bar = mlx_new_image(game->mlx, height / 4, height / 18);
	if (!game->minimap || !game->miniplayer || !game->view3d
		|| !game->view3d_bg || !game->hud || !game->health
		|| !game->health_bar)
		return (false);
	return (true);
}

static void	display_images(t_gs *game, int32_t width, int32_t height)
{
	mlx_image_to_window(game->mlx, game->view3d_bg, 0, 0);
	mlx_image_to_window(game->mlx, game->view3d, 0, 0);
	mlx_image_to_window(game->mlx, game->miniplayer,
		game->mmap.miniplayer_pos_show.u,
		game->mmap.miniplayer_pos_show.v);
	mlx_image_to_window(game->mlx, game->minimap,
		game->mmap.minimap_pos_show.u,
		game->mmap.minimap_pos_show.v);
	mlx_image_to_window(game->mlx, game->hud, width - 64, 0);
	if (game->health_bar)
		mlx_image_to_window(game->mlx, game->health_bar,
			width - width / 16 - height / 4, height - height / 18);
	if (game->health)
		mlx_image_to_window(game->mlx, game->health,
			width - width / 16 - height / 4, height - height / 18);
}

void	draw(int32_t width, int32_t height, void *param)
{
	t_gs	*game;

	game = (t_gs *)param;
	if (!validate_window_size(game, width, height))
		return ;
	cleanup_images(game);
	if (!allocate_depth_buffer(game, width))
		ft_exit_perror("Could not reallocate depth buffer\n");
	if (!create_images(game, width, height))
		return ;
	draw_ui();
	ft_game()->render.bg_scale = FOV_RAD * ((double)game->textures.bg->width
		/ (2.0 * M_PI) / (double)game->view3d->width);
	setup_minimap_positions(game, width, height);
	display_images(game, width, height);
	printf("Draw completed: %dx%d\n", width, height);
	show_end_screen();
	printf("End screen shown\n");
	ft_update_graphics();
}
