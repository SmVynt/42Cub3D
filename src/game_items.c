/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/15 21:39:13 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_pick_up_map(t_item *item)
{
	t_list	*new_item;
	t_gs	*game;

	game = ft_game();
	if (item->type == IT_MAP)
	{
		item->active = false;
		new_item = ft_lstnew(item);
		if (!new_item)
			ft_exit_error("Could not allocate memory for picked up item\n");
		ft_lstadd_back(&ft_game()->player->pocket, new_item);
		ft_game()->mmap.picked = true;
		ft_game()->mmap.opening = true;
		ft_game()->mmap.enabled = true;
		ft_game()->minimap->enabled = true;
		ft_game()->miniplayer->enabled = true;
		if (game->msg)
			mlx_delete_image(game->mlx, game->msg);
		game->msg = mlx_put_string(game->mlx,
				"Press [M] to hide/show the map", game->view3d->height
				- 200, game->view3d->height - 100);
		game->msg_time = mlx_get_time();
		printf(COLOR_G"Picked up the map!\n"COLOR_X);
	}
}

static void	check_pick_up_health(t_item *item)
{
	if (item->type == IT_HEALTH)
	{
		if (ft_player_try_heal(item->pickup_value))
		{
			item->active = false;
			printf(COLOR_G"Picked up health!\n"COLOR_X);
		}
	}
}

static void	check_pick_up_key(t_item *item)
{
	t_list	*new_item;

	if (item->type == IT_KEY)
	{
		new_item = ft_lstnew(item);
		if (!new_item)
			ft_exit_error("Could not allocate memory for picked up item\n");
		ft_lstadd_back(&ft_game()->player->pocket, new_item);
		item->active = false;
		printf(COLOR_G"Picked up a key!\n"COLOR_X);
	}
}

void	pick_up(t_item *item)
{
	if (!item->active)
		return ;
	check_pick_up_map(item);
	check_pick_up_health(item);
	check_pick_up_key(item);
}
