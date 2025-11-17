/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:52:39 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/17 12:39:17 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void setup_audio(t_gs *game)
{
	if (!audio_init(&game->audio))
		printf("Warning: Audio initialization failed\n");
	else
	{
		audio_load_sound(&game->audio, AUDIO_FOOTSTEP,
			&game->audio.footstep_sound);
		audio_load_sound(&game->audio, AUDIO_FOOTSTEP,
			&game->audio.door_sound);
		audio_load_sound(&game->audio, AUDIO_PICKUP,
			&game->audio.pickup_sound);
		audio_load_sound(&game->audio, AUDIO_BG_MUSIC,
			&game->audio.bg_music);

		audio_set_volume(game->audio.footstep_sound, 0.3);
		audio_set_volume(game->audio.bg_music, 0.3);
		audio_play_music(game->audio.bg_music, true);
	}
}

int	main(int argc, char **argv)
{
	t_gs	*game;

	ft_initialize();
	ft_checkinput(argc, argv);
	game = ft_game();
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	if (!game->mlx)
		ft_exit_error("Could not initialize MiniLibX\n");
	printf(COLOR_G"MiniLibX initialized!\n"COLOR_X);
	ft_createhooks();
	ft_setgame();
	draw(WIDTH, HEIGHT, game);
	mlx_loop(game->mlx);
	ft_exit();
	return (0);
}
