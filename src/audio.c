/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:34:21 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/17 10:40:34 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION
#include "../lib/miniaudio.h"
#include "audio.h"
#include <stdlib.h>

bool	audio_init(t_audio *audio)
{
	void	*engine;

	engine = malloc(sizeof(ma_engine));
	if (!engine || ma_engine_init(NULL, engine) != MA_SUCCESS)
		return (free(engine), false);
	audio->engine = engine;
	audio->music = NULL;
	audio->initialized = true;
	return (true);
}

void	audio_cleanup(t_audio *audio)
{
	if (!audio || !audio->initialized)
		return ;
	if (audio->music)
		ma_sound_uninit(audio->music);
	ma_engine_uninit(audio->engine);
	free(audio->engine);
	free(audio->music);
}

bool	audio_load_music(t_audio *audio, const char *file)
{
	void	*music;

	music = malloc(sizeof(ma_sound));
	if (!music)
		return (false);
	if (ma_sound_init_from_file(audio->engine, file, 0, NULL, NULL, music) != MA_SUCCESS)
		return (free(music), false);
	ma_sound_set_looping(music, 1);
	ma_sound_set_volume(music, 0.3);
	ma_sound_start(music);
	audio->music = music;
	return (true);
}
