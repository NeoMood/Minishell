/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:05:20 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/03 23:40:06 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file	*ft_lstlastfd(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstlastfd(lst -> next));
}

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
