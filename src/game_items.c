/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/10 02:04:45 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pick_up(t_item *item)
{
	if (!item->active)
		return ;
	if (item->type == IT_MAP)
	{
		item->active = false;
		ft_lstadd_back(&ft_game()->player->pocket, ft_lstnew(item));
		ft_game()->mmap.picked = true;
		ft_game()->mmap.opening = true;
		ft_game()->mmap.enabled = true;
		ft_game()->minimap->enabled = true;
		ft_game()->miniplayer->enabled = true;
	}
	if (item->type == IT_HEALTH)
	{
		if (ft_player_try_heal(item->pickup_value))
			item->active = false;
	}
	if (item->type == IT_KEY)
	{
		ft_lstadd_back(&ft_game()->player->pocket, ft_lstnew(item));
		item->active = false;
	}
}
