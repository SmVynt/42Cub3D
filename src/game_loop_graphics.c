/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_graphics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 17:41:59 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_update_view3d(void *param)
{
	mlx_image_t	*image;

	if (!param)
		return ;
	image = (mlx_image_t *)param;
	print_debug("clearing memory...");
	clear_image(image);
	print_debug("memory cleared");
	draw_walls(ft_game()->view3d);
	print_debug("walls drawn");
	draw_sprites(ft_game()->view3d);
	print_debug("sprites drawn");
}

static void	ft_update_hud(void *param)
{
	mlx_image_t	*image;
	t_list		*pocket_items;
	t_item		*item;
	int			i;

	pocket_items = ft_game()->player->pocket;
	if (!param || !pocket_items)
		return ;
	image = (mlx_image_t *)param;
	i = 0;
	while (pocket_items)
	{
		item = (t_item *)pocket_items->content;
		draw_ui_item(image, 64, (t_point){0, i * 64}, item->sprite.texture);
		pocket_items = pocket_items->next;
		i++;
	}
}

void	ft_update_graphics(void)
{
	if (ft_game()->view3d->height == 0 || ft_game()->view3d->width == 0)
		return ;
	print_debug("--view3d...");
	ft_update_view3d(ft_game()->view3d);
	print_debug("--hud...");
	ft_update_hud(ft_game()->hud);
	print_debug("--minimap...");
	ft_update_minimap();
}
