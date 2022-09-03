/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:22:13 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/03 18:25:55 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args  *ft_args_node(char **ar, e_type type)
{
    t_args	*new;
	
	new = ft_malloc(sizeof(t_args));
	if (!new)
		return (NULL);
	new->arg = ar;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_args *ft_last_arg(t_args *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_addbackarg(t_args **pars, t_args *nv)
{
	t_args *tmp;

	tmp = (*pars);
	if ((*pars))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = nv;	
	}
	else
		*pars = nv;
}

void	ft_printarg(t_args *args)
{
	int i = 0;
	while (args)
	{
		i = 0;
		while (args->arg[i])
		{
			printf ("[%s]", args->arg[i]);
			i++;
		}
		printf(" == %d\n", args->type);
		args = args->next;
	}
}