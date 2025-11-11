/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/10 23:17:54 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_fill_split_bg(mlx_image_t *bg)
{
	uint32_t	u;
	uint32_t	v;
	uint32_t	center;

	center = bg->height / (2 * PIXEL_SIZE) * PIXEL_SIZE;
	v = 0;
	while (v < center)
	{
		u = -1;
		while (++u < bg->width)
			put_pixel(bg, u, v, ft_game()->render.top_color);
		v++;
	}
	while (v < bg->height)
	{
		u = -1;
		while (++u < bg->width)
			put_pixel(bg, u, v, ft_game()->render.bottom_color);
		v++;
	}
}

void	draw(int32_t width, int32_t height, void *param)
{
	t_gs	*game;

	game = (t_gs *) param;
	if (width < MIN_WIDTH || height < MIN_HEIGHT)
	{
		mlx_set_window_size(game->mlx, ft_clamp(width, MIN_WIDTH, width),
			ft_clamp(height, MIN_HEIGHT, height));
		return ;
	}
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
	if (game->render.depth)
		free(game->render.depth);
	game->render.depth = malloc(sizeof(float) * (width / PIXEL_SIZE + 2));
	if (!game->render.depth)
	{
		printf("Error: Could not reallocate depth buffer for width %d\n", width);
		return ;
	}
	game->render.projection_plane_dist = (width / 2.0) / tan(FOV_RAD / 2.0);
	game->view3d_bg = mlx_new_image(game->mlx, width, height);
	ft_fill_split_bg(game->view3d_bg);
	game->view3d = mlx_new_image(game->mlx, width, height);
	game->hud = mlx_new_image(game->mlx, 64, height);
	game->minimap = mlx_new_image(game->mlx, height * 2 / 5, height / 2);
	game->miniplayer = mlx_new_image(game->mlx, height * 2 / 9, height * 2 / 9);
	game->health = mlx_new_image(game->mlx, height / 4, height / 18);
	game->health_bar = mlx_new_image(game->mlx, height / 4, height / 18);
	if (!game->minimap || !game->miniplayer || !game->view3d || !game->view3d_bg
		|| !game->view3d_bg || !game->hud || !game->health || !game->health_bar)
		return ;
	draw_ui();
	ft_game()->render.bg_proportion = (float)game->view3d_bg->height / ((float)game->view3d_bg->width * M_PI / 2);
	mlx_image_to_window(game->mlx, game->view3d_bg, 0, 0);
	mlx_image_to_window(game->mlx, game->view3d, 0, 0);
	game->mmap.miniplayer_pos_show = (t_point)
	{(width / 16) + round((float)height * 0.11f),
		(height / 2) + round((float)height * 0.025f)};
	mlx_image_to_window(game->mlx, game->miniplayer,
		game->mmap.miniplayer_pos_show.u,
		game->mmap.miniplayer_pos_show.v);
	game->mmap.miniplayer_pos_hide = (t_point)
	{game->mmap.miniplayer_pos_show.u + width / 16,
		game->mmap.miniplayer_pos_show.v + height / 2};
	game->mmap.minimap_pos_show = (t_point){width / 16, height / 2};
	mlx_image_to_window(game->mlx, game->minimap,
		game->mmap.minimap_pos_show.u,
		game->mmap.minimap_pos_show.v);
	game->mmap.minimap_pos_hide = (t_point)
	{game->mmap.minimap_pos_show.u + width / 16,
		game->mmap.minimap_pos_show.v + height / 2};
	mlx_image_to_window(game->mlx, game->hud, width - 64, 0);
	printf("Draw completed: %dx%d\n", width, height);
	show_end_screen();
	printf("End screen shown\n");
	if (game->health_bar)
		mlx_image_to_window(game->mlx, game->health_bar, width - width / 16 - height / 4, height - height / 18);
	if (game->health)
		mlx_image_to_window(game->mlx, game->health, width - width / 16 - height / 4, height - height / 18);
	ft_update_graphics();
}

void	draw_item(mlx_image_t *image, int size, t_point pos, mlx_texture_t *texture)
{
	size_t	i;
	size_t	j;

	i = 0;
	(void )size;
	while (i < texture->width)
	{
		j = 0;
		while (j < texture->height)
		{
			draw_square(image, 2, (t_point){pos.u + 2 * i + size / 2, pos.v + 2 * j + size / 2}, ft_get_pixel_color(texture, (t_point){i, j}));
			j++;
		}
		i++;
	}
}

void	fill_background(mlx_image_t *image, uint32_t color)
{
	uint32_t	*pixels;
	int			total;
	int			i;

	pixels = (uint32_t *)image->pixels;
	total = image->width * image->height;
	i = 0;
	while (i < total)
	{
		pixels[i] = color;
		i++;
	}
}

void	draw_walls(mlx_image_t *image)
{
	uint32_t	x;

	x = PIXEL_SIZE / 2;
	while (x < ft_game()->view3d->width)
	{
		draw_wall(image, x);
		x += PIXEL_SIZE;
	}
	draw_wall(image, x);
}
