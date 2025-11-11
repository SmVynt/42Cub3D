/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 16:21:40 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d.h"

static void	update_lerp_progress(t_gs *game)
{
	if (game->mmap.opening)
		game->mmap.lerp_progress = ft_lerpf(game->mmap.lerp_progress, 1.0f,
				game->mmap.lerp_speed * game->dt);
	else
		game->mmap.lerp_progress = ft_lerpf(game->mmap.lerp_progress, 0.0f,
				game->mmap.lerp_speed * game->dt);
	if (game->mmap.lerp_progress < 0.01f)
	{
		game->mmap.lerp_progress = 0.0f;
		game->mmap.enabled = false;
	}
	if (game->mmap.lerp_progress > 0.99f)
		game->mmap.lerp_progress = 1.0f;
}

static void	update_minimap_position(t_gs *game)
{
	float	progress;

	progress = game->mmap.lerp_progress;
	game->minimap->instances[0].x = round(ft_lerpf(
				game->mmap.minimap_pos_hide.u,
				game->mmap.minimap_pos_show.u, progress));
	game->minimap->instances[0].y = round(ft_lerpf(
				game->mmap.minimap_pos_hide.v,
				game->mmap.minimap_pos_show.v, progress));
}

static void	update_miniplayer_position(t_gs *game)
{
	float	progress;

	progress = game->mmap.lerp_progress;
	game->miniplayer->instances[0].x = round(ft_lerpf(
				game->mmap.miniplayer_pos_hide.u,
				game->mmap.miniplayer_pos_show.u, progress));
	game->miniplayer->instances[0].y = round(ft_lerpf(
				game->mmap.miniplayer_pos_hide.v,
				game->mmap.miniplayer_pos_show.v, progress));
}

static bool	is_animation_complete(t_gs *game)
{
	return (game->mmap.opening && game->mmap.lerp_progress == 1.0f);
}

void	clear_image(mlx_image_t *image)
{
	memset(image->pixels, 0, image->width * image->height * sizeof(int32_t));
}

void	ft_update_minimap(void)
{
	t_gs	*game;

	game = ft_game();
	game->minimap->enabled = game->mmap.enabled;
	game->miniplayer->enabled = game->mmap.enabled;
	if (!game->mmap.enabled)
		return ;
	if (!is_animation_complete(game))
	{
		update_lerp_progress(game);
		update_minimap_position(game);
		update_miniplayer_position(game);
	}
	clear_image(game->miniplayer);
	draw_map();
}
