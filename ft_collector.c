/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:41:52 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 15:36:46 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(size_t allocation)
{
	void	*str;

	str = malloc (allocation);
	if (!str)
		exit (1);
	if (!mode.trash)
		mode.trash = ft_newgarbage(str);
	else
		ft_addbackthegarbe(&mode.trash, ft_newgarbage(str));
	return (str);
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

void	ft_freegarbe(t_free *list)
{
	t_free	*tmp;

	while (list)
	{
		tmp = list;
		free (tmp->ptr);
		free (tmp->next->ptr);
		tmp = tmp->next;
	}
}
