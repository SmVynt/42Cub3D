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
#include "../lib/miniaudio.h"
#include "audio.h"
#include <stdlib.h>

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

void	audio_cleanup(t_audio *audio)
{
	if (!audio->initialized)
		return ;
	if (audio->footstep_sound)
		ma_sound_uninit(audio->footstep_sound);
	if (audio->door_sound)
		ma_sound_uninit(audio->door_sound);
	if (audio->pickup_sound)
		ma_sound_uninit(audio->pickup_sound);
	if (audio->hit_sound)
		ma_sound_uninit(audio->hit_sound);
	if (audio->hit_lava_sound)
		ma_sound_uninit(audio->hit_lava_sound);
	if (audio->shaky_sound)
		ma_sound_uninit(audio->shaky_sound);
	if (audio->bg_music)
		ma_sound_uninit(audio->bg_music);
	if (audio->victory)
		ma_sound_uninit(audio->victory);
	if (audio->absorbtion)
		ma_sound_uninit(audio->absorbtion);
	ma_engine_uninit(audio->engine);
	free(audio->engine);
	audio->initialized = false;
}

bool	audio_load_sound(t_audio *audio, const char *file, void **sound_ptr)
{
	ma_sound	*sound;

	sound = malloc(sizeof(ma_sound));
	if (!sound)
		return (false);
	if (ma_sound_init_from_file(audio->engine, file, 0, NULL, NULL, sound) != MA_SUCCESS)
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

void	audio_stop(void *sound)
{
	if (sound)
		ma_sound_stop(sound);
}

void	audio_stop_all(t_audio *audio)
{
	if (!audio->initialized)
		return ;
	if (audio->footstep_sound)
		audio_stop(audio->footstep_sound);
	if (audio->door_sound)
		audio_stop(audio->door_sound);
	if (audio->hp_sound)
		audio_stop(audio->hp_sound);
	if (audio->pickup_sound)
		audio_stop(audio->pickup_sound);
	if (audio->hit_sound)
		audio_stop(audio->hit_sound);
	if (audio->hit_lava_sound)
		audio_stop(audio->hit_lava_sound);
	if (audio->shaky_sound)
		audio_stop(audio->shaky_sound);
	if (audio->bg_music)
		audio_stop(audio->bg_music);
	if (audio->victory)
		audio_stop(audio->victory);
	if (audio->absorbtion)
		audio_stop(audio->absorbtion);
}

void	audio_set_volume(void *sound, float volume)
{
	if (sound)
		ma_sound_set_volume(sound, volume);
}
