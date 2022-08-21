/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/21 17:47:03 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exp	*ft_lstlast(t_exp *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstlast(lst -> next));
}

void	ft_lstadd_back(t_exp **lst, t_exp	*new)
{
	t_exp	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlast(head);
		head -> next = new;
	}
	else
		(*lst) = new;
}

void	exp_print(t_exp **exp)
{
	t_exp	*new;

	new = *exp;
	while (new)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(new->key, 1);
		if (*new->value != '\0')
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd(new->value, 1);
		if (*new->value != '\0')
		{
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		new = new->next;
	}
}

void	sort_exp(t_exp **exp)
{
	char	*tmp;
	char	*tmpv;
	t_exp	*j;
	t_exp	*i;

	i = *exp;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
			{
				tmp = i -> key;
				i -> key = j -> key;
				j -> key = tmp;
				tmpv = i -> value;
				i -> value = j -> value;
				j -> value = tmpv;
			}
			j = j->next;
		}
		i = i->next;
	}
}

t_exp   *env_to_exp(t_env *env)
{
	t_exp   *exp;
	char	*key;
	char	*value;

	exp = NULL;
	while(env)
	{
		key = ft_strdup(env->key);
		value = ft_strdup(env->value);
		ft_addbacknode2(&exp, ft_createcell2(key, value));
		if (env)
			env = env->next;
	}
	return (exp);
}

void    ft_export(t_args *line, t_exp *exp)
{
	if(line->arg[1])
	{
		if(ft_strchr(line->arg[1], '='))
		{
			printf("KAYNA =\n");
		}
		else if(!ft_strchr(line->arg[1], '='))
		{
			ft_lstadd_back(&exp, ft_createcell2(line->arg[1], ""));
			sort_exp(&exp);
			// printf("MAKAYNACH =\n");
		}
	}
	else
		sort_exp(&exp);
	exp_print(&exp);
}