/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:11:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 11:19:42 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calculate_sprite(mlx_image_t *image, t_sprite *sprite)
{
	t_player		*player;
	t_spriterender	*sp;
	t_vec2			sp_dir;

	sp = &sprite->sp;
	if (!sprite->texture || !sprite->texture->pixels)
		return ;
	sp->visible = true;
	sprite->next = NULL;
	player = ft_game()->player;
	sp_dir = (t_vec2){sprite->pos.x - player->pos.x, sprite->pos.y - player->pos.y};
	sp->dist = ft_vec2_length(sp_dir);
	sp->angle = ft_angle_between_vec2((t_vec2){player->lookdir.x, player->lookdir.y}, sp_dir);
	if (sp->dist < 0.2f || fabs(sp->angle) > FOV_RAD / 2 + M_PI / 20)
	{
		sp->visible = false;
		return ;
	}
	sp->dist *= cos(sp->angle);
	sp->screen_pos.x = (float)(image->width / 2.0f + (sp->angle / FOV_RAD) * image->width);
	sp->screen_pos.y = (float)(image->height / 2.0f);
	sp->max_size = (1.0f / sp->dist) * ft_game()->render.projection_plane_dist;
	sp->size.u = (int)(sprite->texture->width * sp->max_size / STANDARD_SPRITE_SIZE);
	sp->size.v = (int)(sprite->texture->height * sp->max_size / STANDARD_SPRITE_SIZE);
	sp->start.u = (int)(sp->screen_pos.x) - sp->size.u / 2;
	sp->start.v = (int)(sp->screen_pos.y) - sp->size.v + sp->max_size * (0.5f - sprite->bottom_offset / 2);
	sp->start.v += sp->max_size * 0.5f * ft_game()->player->jump_height + player->lookupdown;
}

void	ft_add_sprite_to_list(t_sprite *head, t_sprite *sprite)
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
