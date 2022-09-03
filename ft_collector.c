/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:41:52 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/03 18:02:52 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(void *allocation)
{
	t_free	*list;
	void	*str;

	list = NULL;
	str = malloc (sizeof(allocation));
	if (!str)
		return (NULL);
	return (str);
	ft_addbackthegarbe(&list, ft_newgarbage(str));
}

t_free	*ft_newgarbage(void *ptr)
{
    t_free	*trash;

	trash = malloc(sizeof(t_free));
	if (!trash)
		return (NULL);
	trash->ptr = ptr;
	trash->next = NULL;
	return (trash);
}

void	ft_addbackthegarbe(t_free **lst, t_free *nv)
{
	t_free	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstgarbage(head);
		head->next = nv;
	}
	else
		(*lst) = nv;
}

t_free	*ft_lstgarbage(t_free *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstgarbage(lst->next));
}
