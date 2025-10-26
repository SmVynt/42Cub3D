/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:05:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/25 17:55:26 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MINI_H
# define LIBFT_MINI_H

# include <stdlib.h>

size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_strchar(const char *s, int c);
int			ft_strchar_index(const char *s, int c);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// int		ft_dir(int a, int b);
// char	*ft_strip_from_n(char *str);
// t_map	*ft_copy_map(t_map *src);
// void	ft_free_map(t_map *map);
// void	ft_allocate_map(t_map *map, t_gs *game);

// void	ft_update_end(t_gs *game);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstinsert_sorted(t_list **head, void *content,
			int (*cmp)(void *, void *));
void	ft_lstdelone(t_list *lst, void (*del)(void	*));
void	ft_lstclear(t_list **lst, void (*del)(void	*));

#endif
