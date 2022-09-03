/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:05:20 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/03 21:01:18 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_file	*ft_lstnewfd(int fd)
{
	t_file	*new_fd;

	new_fd = (t_file *) ft_malloc (sizeof (t_file));
	if (!new_fd)
		return (NULL);
	new_fd->fd = fd;
	new_fd->next = NULL;
	return (new_fd);
}

t_file	*ft_lstlastfd(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstlastfd(lst -> next));
}

void	ft_fdadd_back(t_file **lst, t_file *nv)
{
	t_file	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlastfd(head);
		head->next = nv;
	}
	else
		(*lst) = nv;
}

t_exp	*ft_lstlast(t_exp *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstlast(lst -> next));
}


void	ft_lstadd_back(t_exp **lst, t_exp *nv)
{
	t_exp	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlast(head);
		head -> next = nv;
	}
	else
		(*lst) = nv;
}
