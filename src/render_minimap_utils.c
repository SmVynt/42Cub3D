/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 19:52:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	draw_entity_on_minimap(t_vec2 entity_pos, t_point image_center,
		double zoom, uint32_t color)
{
	t_player	*player;
	mlx_image_t	*image;
	t_vec2		coords;
	double		rotation_angle;

	player = ft_game()->player;
	image = ft_game()->miniplayer;
	coords = (t_vec2){
		(entity_pos.x - player->pos.x) * zoom,
		(entity_pos.y - player->pos.y) * zoom
	};
	if ((int)coords.x < -image_center.u || (int)coords.x > image_center.u
		|| (int)coords.y < -image_center.v || (int)coords.y > image_center.v)
		return (false);
	rotation_angle = -atan2(player->lookdir.y, player->lookdir.x) - HALF_PI;
	coords = ft_mat4_transform_vec2(ft_mat4_rotation_z(rotation_angle), coords);
	draw_circle(image, (t_point){(int)(coords.x) + image_center.u,
		(int)(coords.y) + image_center.v}, 3, color);
	return (true);
}

void	draw_chars_on_minimap(mlx_image_t *img, double zoom, t_point img_center)
{
	int			i;

	(void) img;
	i = -1;
	while (++i < ft_game()->char_count)
	{
		if (ft_game()->chars[i].alive == false)
			continue ;
		draw_entity_on_minimap(ft_game()->chars[i].sprite.pos, img_center,
			zoom, MM_COLOR_ENEMIES);
	}
}

void	draw_items_on_minimap(mlx_image_t *img, double zoom, t_point img_center)
{
	int			i;
	uint32_t	color;

	(void) img;
	i = -1;
	while (++i < ft_game()->item_count)
	{
		if (ft_game()->items[i].type == IT_HEALTH)
			color = MM_COLOR_HEALTH;
		if (ft_game()->items[i].type == IT_KEY)
			color = MM_COLOR_KEY;
		else
			continue ;
		if (ft_game()->items[i].active == false)
			continue ;
		draw_entity_on_minimap(ft_game()->items[i].sprite.pos, img_center,
			zoom, color);
	}
}
