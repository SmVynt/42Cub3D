/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/04 21:12:47 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	pick_up(t_item *item)
{
	if (!item->active)
		return ;
	item->active = false;
	printf("add item %i\n", item->sprite.texture->width);
	ft_lstadd_back(&ft_game()->player->pocket, ft_lstnew(item));
	if (item->type == IT_MAP)
	{
		ft_game()->mmap.picked = true;
		ft_game()->mmap.opening = true;
		ft_game()->mmap.enabled = true;
		printf("Picked up the map! You can now toggle the minimap with M.\n");

		ft_game()->minimap->enabled = true;
		ft_game()->miniplayer->enabled = true;
	}
}
