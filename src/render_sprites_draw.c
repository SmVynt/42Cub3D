/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:11:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/23 19:18:51 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_sprite_animation(t_sprite *sprite)
{
	sprite->anim.anim_timer += ft_game()->dt;
	if (sprite->anim.anim_timer >= sprite->anim.frame_duration)
	{
		sprite->anim.anim_timer = 0.0;
		sprite->anim.curr_frame++;
	}
	sprite->texture = sprite->anim.frames[sprite->anim.curr_frame
		% sprite->anim.n_frames];
}

static bool	is_behind_wall(t_spriterender *sp, int screen_x)
{
	return (sp->dist > ft_game()->render.depth[screen_x / PIXEL_SIZE]);
}

static t_point	calculate_texture_coord(int x, int y, t_spriterender *sp,
				mlx_texture_t *texture)
{
	t_point	tex_coord;

	tex_coord.u = (int)((double)x / (double)sp->size.x
			* (double)texture->width);
	tex_coord.v = (int)((double)y / (double)sp->size.y
			* (double)texture->height);
	return (tex_coord);
}

static void	draw_sprite_column(mlx_image_t *image, t_sprite *sprite,
				t_spriterender *sp, int x)
{
	int		y;
	t_point	tex_coord;

	y = (PIXEL_SIZE - sp->start.u % PIXEL_SIZE) % PIXEL_SIZE;
	while (y < sp->size.y)
	{
		sp->screen.v = sp->start.v + y;
		if (sp->screen.v >= 0 && sp->screen.v < (int)image->height)
		{
			tex_coord = calculate_texture_coord(x, y, sp, sprite->texture);
			draw_square(image, PIXEL_SIZE,
				(t_point){sp->screen.u, sp->screen.v},
				ft_get_pixel_color(sprite->texture, tex_coord));
		}
		y += PIXEL_SIZE;
	}
}

void	draw_sprite(mlx_image_t *image, t_sprite *sprite)
{
	t_spriterender	*sp;
	int				x;

	if (sprite->animated)
		update_sprite_animation(sprite);
	if (!sprite->texture || !sprite->texture->pixels)
		return ;
	if (!sprite->sp.visible)
		return ;
	sp = &sprite->sp;
	x = (PIXEL_SIZE - sp->start.u % PIXEL_SIZE) % PIXEL_SIZE;
	while (x < (int)sp->size.x)
	{
		sp->screen.u = sp->start.u + x + PIXEL_SIZE / 2;
		if (sp->screen.u >= 0 && sp->screen.u < (int)image->width)
		{
			if (is_behind_wall(sp, sp->screen.u))
			{
				x += PIXEL_SIZE;
				continue ;
			}
			draw_sprite_column(image, sprite, sp, x);
		}
		x += PIXEL_SIZE;
	}
}
