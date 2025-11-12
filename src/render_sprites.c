/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:11:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 17:49:38 by nmikuka          ###   ########.fr       */
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

void	draw_sprite(mlx_image_t *image, t_sprite *sprite)
{
	t_spriterender	*sp;
	int				x;
	int				y;

	if (sprite->animated)
	{
		sprite->anim.anim_timer += ft_game()->dt;
		if (sprite->anim.anim_timer >= sprite->anim.frame_duration)
		{
			sprite->anim.anim_timer = 0.0f;
			sprite->anim.curr_frame++;
		}
		// printf("here is the fire %zu %f\n", (int)ft_game()->dt % sprite->n_frames, MAX_DT / ft_game()->dt);
		sprite->texture = sprite->anim.frames[sprite->anim.curr_frame % sprite->anim.n_frames];
	}
	if (!sprite->texture || !sprite->texture->pixels)
		return ;
	sp = &sprite->sp;
	if (!sp->visible)
		return ;
	x = (PIXEL_SIZE - sp->start.u % PIXEL_SIZE) % PIXEL_SIZE;
	while (x < sp->size.u)
	{
		sp->screen.u = sp->start.u + x + PIXEL_SIZE / 2;
		if (sp->screen.u >= 0 && sp->screen.u < (int)image->width)
		{
			if (sp->dist > ft_game()->render.depth[sp->screen.u / PIXEL_SIZE])
			{
				x += PIXEL_SIZE;
				continue ;
			}
			y = (PIXEL_SIZE - sp->start.v % PIXEL_SIZE) % PIXEL_SIZE;
			while (y < sp->size.v)
			{
				sp->screen.v = sp->start.v + y;
				if (sp->screen.v >= 0 && sp->screen.v < (int)image->height)
				{
					draw_square(image, PIXEL_SIZE, (t_point){sp->screen.u, sp->screen.v},
						ft_get_pixel_color(sprite->texture, (t_point){
							(int)((float)x / (float)sp->size.u * (float)sprite->texture->width),
							(int)((float)y / (float)sp->size.v * (float)sprite->texture->height)}));
				}
				y += PIXEL_SIZE;
			}
		}
		x += PIXEL_SIZE;
	}
}
