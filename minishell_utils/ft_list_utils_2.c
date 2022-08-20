/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:32:51 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/09 18:04:35 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tk *ft_input(char *data, int token)
{
	t_tk	*list;

	list = NULL;
	list = malloc(sizeof(t_tk));
	if(!list)
		return (NULL);
	list->input = data;
	list->token = token;
	list->next = NULL;
	return (list);
}

t_tk	*ft_findlast(t_tk *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break;
		lst = lst->next;	
	}
	return (lst);
}

void	ft_addtolist(t_tk **list, t_tk *new)
{
	if (*list)
		ft_findlast(*list)->next = new;
	else
		*list = new;
}

void	ft_freelist(t_tk *list)
{
	t_tk	*tmp;

	while (list)
	{
		tmp = list;
		free (tmp->input);
       	free (tmp->next->input);
		tmp = tmp->next;
	}
}

void	printlist(t_tk *list)
{
	while (list)
	{
		printf("%d ---- [%s]\n",list->token, list->input);
		list = list->next;
	}
	puts("_______________\n");
}
