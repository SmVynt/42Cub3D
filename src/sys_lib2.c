/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_lib2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/11 15:06:09 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strchar_index(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

t_list	*ft_lstinsert_sorted(t_list **head, void *content,
			int (*cmp)(void *, void *))
{
	t_list	*new_node;
	t_list	*curr;

	new_node = ft_lstnew(content);
	if (!new_node)
		return (NULL);
	if (!*head || cmp(content, (*head)->content) < 0)
	{
		new_node->next = *head;
		*head = new_node;
		return (new_node);
	}
	curr = *head;
	while (curr->next && cmp(content, curr->next->content) >= 0)
		curr = curr->next;
	new_node->next = curr->next;
	curr->next = new_node;
	return (new_node);
}
