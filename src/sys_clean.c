/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/27 02:51:33 by psmolin          ###   ########.fr       */
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

static void	ft_free_mlx(void)
{
	t_gs		*game;
	int			i;
	t_direction	dir;

	game = ft_game();
	printf(COLOR_C"Freeing MLX resources...\n"COLOR_X);
	i = 0;
	while (i < WALLS_TYPES_COUNT)
	{
		dir = DIR_NO;
		while (dir <= DIR_WE)
		{
			if (game->textures.walls[i].tex[dir])
				mlx_delete_texture(game->textures.walls[i].tex[dir]);
			dir++;
		}
		i++;
	}
	if (game->textures.wall_atlas)
		mlx_delete_texture(game->textures.wall_atlas);
	if (game->textures.bg)
		mlx_delete_texture(game->textures.bg);
	if (game->mlx)
	{
		if (game->minimap)
			mlx_delete_image(game->mlx, game->minimap);
		if (game->miniplayer)
			mlx_delete_image(game->mlx, game->miniplayer);
		if (game->view3d)
			mlx_delete_image(game->mlx, game->view3d);
		if (game->view3d_bg)
			mlx_delete_image(game->mlx, game->view3d_bg);
		mlx_terminate(game->mlx);
	}
	i = 0;
	while (i < ITEMS_TYPES_COUNT)
	{
		if (game->item_prefabs[i].sprite.texture)
			mlx_delete_texture(game->item_prefabs[i].sprite.texture);
		i++;
	}
	i = 0;
	while (i < CHARS_TYPES_COUNT)
	{
		if (game->char_prefabs[i].sprite.texture)
			mlx_delete_texture(game->char_prefabs[i].sprite.texture);
		i++;
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
