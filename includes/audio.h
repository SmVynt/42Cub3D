/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:21:04 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/17 10:21:07 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include <stdbool.h>

typedef struct s_audio
{
	void	*engine;
	void	*music;
	bool	initialized;
}	t_audio;

bool	audio_init(t_audio *audio);
void	audio_cleanup(t_audio *audio);
bool	audio_load_music(t_audio *audio, const char *file);

#endif