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

#include "cub3d.h"

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
	if (audio->shaky_sound)
		audio_stop(audio->shaky_sound);
	if (audio->victory)
		audio_stop(audio->victory);
	if (audio->absorbtion)
		audio_stop(audio->absorbtion);
}
