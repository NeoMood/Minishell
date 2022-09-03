/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:32:51 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/03 18:55:32 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tk *ft_input(char *data, int token)
{
	t_tk	*list;

	list = NULL;
	list = ft_malloc(sizeof(t_tk));
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

void	ft_addtolist(t_tk **list, t_tk *lst)
{
	if (*list)
		ft_findlast(*list)->next = lst;
	else
		*list = lst;
}

void	printlist(t_tk *list)
{
	if (list == NULL)
		return ;
	while (list)
	{
		printf("%d ---- [%s]\n",list->token, list->input);
		list = list->next;
	}
	puts("_______________\n");
}
