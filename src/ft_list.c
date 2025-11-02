/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:27:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/02 21:27:01 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list	*tmp;
	t_list	*node_to_del;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node_to_del = tmp;
		tmp = tmp->next;
		ft_lstdelone(node_to_del, (*del));
	}
	*lst = NULL;
}
