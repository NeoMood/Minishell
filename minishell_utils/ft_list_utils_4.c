/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:22:13 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/27 22:03:55 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args  *ft_args_node(char **ar, e_type type)
{
    t_args	*new;
	
	new = malloc(sizeof(t_args));
	if (!new)
		return (NULL);
	new->arg = ar;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_args *ft_last_arg(t_args *new)
{
	while (new)
	{
		if (new->next == NULL)
			break ;
		new = new->next;
	}
	return (new);
}

void	ft_addbackarg(t_args **new, t_args *nv)
{
	t_args *tmp;

	tmp = (*new);
	if ((*new))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = nv;	
	}
	else
		*new = nv;
}

void	ft_addfrontarg(t_args **lst, t_args *new)
{
	new->next = *lst;
	*lst = new;
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