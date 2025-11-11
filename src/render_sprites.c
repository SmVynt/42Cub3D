/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:11:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 14:23:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_add_sprite_to_list(t_sprite *head, t_sprite *sprite)
{
	t_sprite	*current;

	if (!head || !sprite || !sprite->sp.visible)
		return ;
	current = head;
	while (current->next && current->next->sp.dist > sprite->sp.dist)
		current = current->next;
	sprite->next = current->next;
	current->next = sprite;
}

static void	prepare_sprite_list(mlx_image_t *image)
{
	int			i;

	if (!ft_game()->sh)
		return ;
	ft_game()->sh->next = NULL;
	ft_game()->sh->sp.dist = 100000.0f;
	i = 0;
	while (i < ft_game()->item_count)
	{
		ft_calculate_sprite(image, &ft_game()->items[i].sprite);
		if (ft_game()->items[i].active && ft_game()->items[i].pickupable
			&& ft_game()->items[i].sprite.sp.dist < 1.0)
			pick_up(&ft_game()->items[i]);
		if (ft_game()->items[i].active)
			ft_add_sprite_to_list(ft_game()->sh, &ft_game()->items[i].sprite);
		i++;
	}
	i = 0;
	while (i < ft_game()->char_count)
	{
		ft_calculate_sprite(image, &ft_game()->chars[i].sprite);
		ft_add_sprite_to_list(ft_game()->sh, &ft_game()->chars[i].sprite);
		i++;
	}
}

static void	render_sprite_list(mlx_image_t *image)
{
	t_sprite	*temp;

	if (!ft_game()->sh)
		return ;
	temp = ft_game()->sh->next;
	while (temp)
	{
		draw_sprite(image, temp);
		temp = temp->next;
	}
}

void	draw_sprites(mlx_image_t *image)
{
	prepare_sprite_list(image);
	render_sprite_list(image);
}
