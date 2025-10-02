/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:23:04 by psmolin           #+#    #+#             */
/*   Updated: 2025/04/23 19:40:23 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * The function ft_gnlrealloc reallocates memory for a string, copying the
 * contents of the old string to the new one. It also handles the case where
 * the new size is smaller than the old size.
 */
char	*ft_gnlrealloc(char *str, size_t old_size, size_t new_size)
{
	char	*new_str;
	size_t	i;

	if (new_size < old_size)
		old_size = new_size;
	new_str = (char *)malloc(new_size + 1);
	if (!new_str)
	{
		free (str);
		return (NULL);
	}
	if (str)
	{
		i = 0;
		while (i < old_size && i < new_size)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
		free(str);
	}
	else
		new_str[0] = '\0';
	return (new_str);
}

/*
 * The function ft_cleanbuffer shifts the contents of the buffer to the left
 * by num characters, effectively removing the first num characters from the
 * buffer. It also updates the length of the buffer accordingly.
 */
void	ft_cleanbuffer(t_buffer *buffer, size_t num)
{
	ssize_t	i;
	ssize_t	n;

	n = num;
	if (n >= buffer->length)
	{
		buffer->length = 0;
		buffer->text[0] = '\0';
		return ;
	}
	i = 0;
	while (i < buffer->length - n)
	{
		buffer->text[i] = buffer->text[n + i];
		i++;
	}
	while (i < BUFFER_SIZE)
		buffer->text[i++] = '\0';
	buffer->length -= n;
}

/*
 * The function ft_appendline appends the contents of the buffer to the line
 * structure. It dynamically allocates memory for the line text if needed,
 * and updates the line length and ended status accordingly.
 */
void	ft_appendline(t_tline *line, t_buffer *buffer)
{
	ssize_t	i;

	if (buffer->length == 0)
		line->ended = 1;
	i = 0;
	while (i < buffer->length)
	{
		if (line->text_length == line->text_alloc)
		{
			line->text_alloc *= 2;
			line->text = ft_gnlrealloc(line->text,
					line->text_length, line->text_alloc);
			if (!line->text)
				return ;
		}
		line->text[line->text_length] = buffer->text[i];
		line->text_length++;
		if (buffer->text[i] == '\n')
		{
			line->ended = 1;
			break ;
		}
		i++;
	}
	ft_cleanbuffer(buffer, i + 1);
}

/*
 * The function ft_readbuffer reads data from the file descriptor fd into the
 * buffer. It updates the length of the buffer and handles errors by cleaning
 * the buffer and setting its length to 0.
 */
int	ft_readbuffer(t_buffer *buffer, int fd)
{
	buffer->length = read(fd, buffer->text, BUFFER_SIZE);
	if (buffer->length == -1)
		return (-1);
	return (0);
}

/*
 * The function ft_initializeline initializes the line structure by allocating
 * memory for the text buffer and setting its initial values.
 */
int	ft_initializeline(t_tline *line)
{
	line->text = (char *)malloc(BUFFER_SIZE);
	if (!line->text)
		return (-1);
	line->text_length = 0;
	line->text_alloc = BUFFER_SIZE;
	line->ended = 0;
	return (0);
}
