/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_textures_ui.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 17:07:14 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_end_screen_textures(void)
{
	t_gs	*game;

	game = ft_game();
	ft_load_texture(TEX_VICTORY, &game->textures.screen_victory);
	ft_load_texture(TEX_DEFEAT, &game->textures.screen_defeat);
}

void	ft_init_ui_textures(void)
{
	t_gs		*game;

	game = ft_game();
	ft_load_texture(TEX_UI_MM, &game->textures.ui_minimap);
	printf("Loaded UI minimap texture\n");
	ft_load_texture(TEX_UI_HEALTH, &game->textures.ui_health);
	printf("Loaded UI health texture\n");
}
