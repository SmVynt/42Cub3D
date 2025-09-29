/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:22:59 by psmolin           #+#    #+#             */
/*   Updated: 2025/04/04 11:53:34 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_buffer
{
	char	text[BUFFER_SIZE];
	ssize_t	length;
}	t_buffer;

typedef struct s_tline
{
	char	*text;
	size_t	text_length;
	size_t	text_alloc;
	int		ended;
}	t_tline;

char	*get_next_line(int fd);
int		ft_readbuffer(t_buffer *buffer, int fd);
char	*ft_gnlrealloc(char *str, size_t old_size, size_t new_size);
void	ft_cleanbuffer(t_buffer *buffer, size_t n);
void	ft_appendline(t_tline *line_set, t_buffer *buffer);
int		ft_initializeline(t_tline *line_set);

#endif