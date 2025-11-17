/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:21:04 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/17 16:09:21 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include <stdbool.h>

typedef struct s_audio
{
	void	*engine;
	void	*footstep_sound;
	void	*door_sound;
	void	*shaky_sound;
	void	*hit_sound;
	void	*hit_lava_sound;
	void	*pickup_sound;
	void	*bg_music;
	bool	initialized;
}	t_audio;

// Initialize/cleanup
bool	audio_init(t_audio *audio);
void	audio_cleanup(t_audio *audio);

// Load sounds
bool	audio_load_sound(t_audio *audio, const char *file, void **sound);

// Play sounds
void	audio_play(void *sound);
void	audio_play_music(void *sound, bool loop);
void	audio_stop(void *sound);

// Volume control
void	audio_set_volume(void *sound, float volume); // 0.0 to 1.0

#endif