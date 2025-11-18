/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:21:04 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/17 17:51:40 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include <stdbool.h>

# define AUDIO_FOOTSTEP		"audio/run.wav"
# define AUDIO_DOOR_OPEN	"audio/metal-door.wav"
# define AUDIO_PICKUP		"audio/leather_inventory.wav"
# define AUDIO_PICKUP_HP	"audio/key-176034.wav"
# define AUDIO_HIT			"audio/lightning-spell.wav"
# define AUDIO_HIT_LAVA		"audio/lava.wav"
# define AUDIO_SHAKING		"audio/shaky2.wav"
# define AUDIO_VICTORY		"audio/spaceship.wav"
# define AUDIO_ABSORBTION	"audio/absorbtion3.wav"
# define AUDIO_BG_MUSIC		"audio/bg_music.wav"

typedef struct s_audio
{
	void	*engine;
	void	*footstep_sound;
	void	*door_sound;
	void	*shaky_sound;
	void	*hit_sound;
	void	*hit_lava_sound;
	void	*pickup_sound;
	void	*hp_sound;
	void	*victory;
	void	*absorbtion;
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
void	audio_stop_all(t_audio *audio);

// Volume control
void	audio_set_volume(void *sound, float volume); // 0.0 to 1.0

#endif
