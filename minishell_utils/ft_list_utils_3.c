/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:33:14 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/20 17:50:45 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_createcell(char *key, char	*value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

t_exp	*ft_createcell2(char *key, char	*value)
{
	t_exp	*exp;

	exp = malloc(sizeof(t_env));
	if (!exp)
		return (NULL);
	exp->key = key;
	exp->value = value;
	exp->next = NULL;
	return (exp);
}

t_env	*ft_last_node(t_env	*new)
{
	while (new)
	{
		if (new->next == NULL)
			break ;
		new = new->next;
	}
	return (new);
}

t_exp	*ft_last_node2(t_exp	*new)
{
	while (new)
	{
		if (new->next == NULL)
			break ;
		new = new->next;
	}
	return (new);
}

void	ft_addbacknode(t_env **env, t_env *new)
{
    if (*env)
		ft_last_node(*env)->next = new;
	else
		*env = new;
}

void	ft_addbacknode2(t_exp **exp, t_exp *new)
{
    if (*exp)
		ft_last_node2(*exp)->next = new;
	else
		*exp = new;
}

void    printenv(t_env *ev)
{
    while (ev)
    {
        printf("%s %s\n", ev->key, ev->value);
        ev = ev->next;
    }
}