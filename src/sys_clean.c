/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/06 00:59:32 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static void	ft_free_string(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static void	ft_freemap(void)
{
	int		i;
	t_map	*map;

	map = &ft_game()->map;
	printf(COLOR_C"Freeing map resources...\n"COLOR_X);
	if (map->tile)
	{
		i = -1;
		while (++i < map->h)
			ft_free_string(&map->tile[i]);
		ft_free_and_null((void**)&map->tile);
	}
	ft_free_string(&map->no);
	ft_free_string(&map->so);
	ft_free_string(&map->we);
	ft_free_string(&map->ea);
	ft_free_string(&map->f);
	ft_free_string(&map->c);
}

static void ft_free_texture(mlx_texture_t **texture)
{
	if (texture && *texture)
	{
		printf(COLOR_G"Freeing texture...\n"COLOR_X);
		mlx_delete_texture(*texture);
		*texture = NULL;
	}
}

static void ft_free_image(mlx_image_t **image)
{
	if (image && *image)
	{
		printf(COLOR_G"Freeing image...\n"COLOR_X);
		mlx_delete_image(ft_game()->mlx, *image);
		*image = NULL;
	}
}

static void	ft_free_mlx(void)
{
	t_gs		*game;
	int			i;
	int			j;
	t_direction	dir;

	game = ft_game();
	printf(COLOR_C"Freeing MLX resources...\n"COLOR_X);
	i = -1;
	while (++i < WALLS_TYPES_COUNT)
	{
		dir = DIR_NO;
		while (dir <= DIR_WE)
		{
			ft_free_texture(&game->textures.walls[i].tex[dir]);
			dir++;
		}
	}
	printf(COLOR_C"Freeing floor and ceiling textures...\n"COLOR_X);
	i = -1;
	while (++i < FLOOR_TYPE_COUNT)
		ft_free_texture(&game->textures.floor[i]);
	i = -1;
	while (++i < CEILING_TYPE_COUNT)
		ft_free_texture(&game->textures.ceiling[i]);
	printf(COLOR_C"Freeing char prefab textures...\n"COLOR_X);
	i = -1;
	while (++i < CHARS_TYPES_COUNT)
	{
		if (game->char_prefabs[i].sprite.animated)
		{
			j = -1;
			while (++j < (int)game->char_prefabs[i].sprite.anim.n_frames)
				ft_free_texture(&game->char_prefabs[i].sprite.anim.frames[j]);
		}
		else
			ft_free_texture(&game->char_prefabs[i].sprite.texture);
	}
	printf(COLOR_C"Freeing item prefab textures...\n"COLOR_X);
	i = -1;
	while (++i < ITEMS_TYPES_COUNT)
	{
		if (game->item_prefabs[i].sprite.animated)
		{
			j = -1;
			while (++j < (int)game->item_prefabs[i].sprite.anim.n_frames)
				ft_free_texture(&game->item_prefabs[i].sprite.anim.frames[j]);
		}
		else
			ft_free_texture(&game->item_prefabs[i].sprite.texture);
	}
	ft_free_texture(&game->textures.floor_atlas);
	ft_free_texture(&game->textures.ceiling_atlas);
	ft_free_texture(&game->textures.bg);
	ft_free_texture(&game->textures.wall_atlas);
	ft_free_texture(&game->textures.bg);
	ft_free_texture(&game->textures.ui_minimap);
	ft_free_texture(&game->textures.ui_health);
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
		mlx_terminate(game->mlx);
	}
}

static void	ft_free_render(void)
{
	t_gs	*game;

	game = ft_game();
	printf(COLOR_C"Freeing render resources...\n"COLOR_X);
	if (game->render.depth)
		ft_free_and_null((void**)&game->render.depth);
	if (game->sh)
		ft_free_and_null((void**)&game->sh);
}

void	ft_clean(void)
{
	t_gs	*game;

	game = ft_game();
	printf(COLOR_C"Cleaning up resources...\n"COLOR_X);
	ft_free_and_null((void**)&game->player);
	ft_freemap();
	ft_free_mlx();
	ft_free_render();
	printf(COLOR_C"Freeing items...\n"COLOR_X);
	ft_free_and_null((void**)&game->items);
	printf(COLOR_C"Freeing chars...\n"COLOR_X);
	ft_free_and_null((void**)&game->chars);
}
