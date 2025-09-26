/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/26 14:01:25 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	if (size <= 0)
		return (len);
	i = 0;
	while ((i < size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_print(const char *str)
{
	return (write(1, str, ft_strlen(str)));
}
// char	*ft_strip_from_n(char *str)
// {
// 	char	*new_str;
// 	int		len;

// 	len = 0;
// 	if (!str)
// 		return (NULL);
// 	if (str[0] == '\n')
// 	{
// 		free(str);
// 		return (NULL);
// 	}
// 	while (str[len] && str[len] != '\n')
// 		len++;
// 	new_str = malloc(sizeof(char) * (len + 1));
// 	if (!new_str)
// 		return (NULL);
// 	ft_strlcpy(new_str, str, (len + 1));
// 	new_str[len] = '\0';
// 	free(str);
// 	return (new_str);
// }
