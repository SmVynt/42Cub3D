/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:34:21 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/17 17:39:55 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION
#include "cub3d.h"

bool	audio_init(t_audio *audio)
{
	ma_engine	*engine;

	engine = malloc(sizeof(ma_engine));
	if (!engine)
		return (false);
	if (ma_engine_init(NULL, engine) != MA_SUCCESS)
	{
		free(engine);
		return (false);
	}
	audio->engine = engine;
	audio->initialized = true;
	return (true);
}

bool	audio_load_sound(t_audio *audio, const char *file, void **sound_ptr)
{
	ma_sound	*sound;

	sound = malloc(sizeof(ma_sound));
	if (!sound)
		return (false);
	if (ma_sound_init_from_file(audio->engine, file, 0,
			NULL, NULL, sound) != MA_SUCCESS)
	{
		free(sound);
		return (false);
	}
	*sound_ptr = sound;
	return (true);
}

void	audio_play(void *sound)
{
	if (sound)
	{
		ma_sound_seek_to_pcm_frame(sound, 0);
		ma_sound_start(sound);
	}
}

void	audio_play_music(void *sound, bool loop)
{
	if (sound)
	{
		ma_sound_set_looping(sound, loop);
		ma_sound_start(sound);
	}
}

void	audio_set_volume(void *sound, float volume)
{
	if (sound)
		ma_sound_set_volume(sound, volume);
}
