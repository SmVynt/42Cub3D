/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:09:35 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 20:02:25 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_sprite_visible(double dist, double angle)
{
	if (dist < 0.2f)
		return (false);
	if (fabs(angle) > FOV_RAD / 2 + M_PI / 20)
		return (false);
	return (true);
}

static void	calculate_sprite_screen_position(t_spriterender *sp,
				mlx_image_t *image)
{
	sp->screen_pos.x = (double)(image->width / 2.0
			+ (sp->angle / FOV_RAD) * image->width);
	sp->screen_pos.y = (double)(image->height / 2.0);
}

static void	calculate_sprite_size(t_sprite *sprite, t_spriterender *sp)
{
	sp->max_size = (1.0 / sp->dist)
		* ft_game()->render.projection_plane_dist;
	sp->size.u = (int)(sprite->texture->width * sp->max_size
			/ STANDARD_SPRITE_SIZE);
	sp->size.v = (int)(sprite->texture->height * sp->max_size
			/ STANDARD_SPRITE_SIZE);
}

static void	calculate_sprite_offset(t_sprite *sprite, t_spriterender *sp,
				t_player *player)
{
	double	vertical_offset;

	sp->start.u = (int)(sp->screen_pos.x) - sp->size.u / 2;
	sp->start.v = (int)(sp->screen_pos.y) - sp->size.v;
	vertical_offset = sp->max_size * (0.5 - sprite->bottom_offset / 2);
	sp->start.v += vertical_offset;
	sp->start.v += sp->max_size * 0.5 * player->jump_height
		+ player->lookupdown;
}

void	ft_calculate_sprite(mlx_image_t *image, t_sprite *sprite)
{
	t_player		*player;
	t_spriterender	*sp;
	t_vec2			sp_dir;

	sp = &sprite->sp;
	if (!sprite->texture || !sprite->texture->pixels)
		return ;
	sprite->next = NULL;
	player = ft_game()->player;
	sp_dir.x = sprite->pos.x - player->pos.x;
	sp_dir.y = sprite->pos.y - player->pos.y;
	sp->dist = ft_vec2_length(sp_dir);
	sp->angle = ft_angle_between_vec2(player->lookdir, sp_dir);
	sp->visible = is_sprite_visible(sp->dist, sp->angle);
	if (!sp->visible)
		return ;
	sp->dist *= cos(sp->angle);
	calculate_sprite_screen_position(sp, image);
	calculate_sprite_size(sprite, sp);
	calculate_sprite_offset(sprite, sp, player);
}
