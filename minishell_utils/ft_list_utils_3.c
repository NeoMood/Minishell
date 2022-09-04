/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:33:14 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 15:46:39 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_createcell(char *key, char	*value)
{
	t_env	*env;

	env = ft_malloc(sizeof(t_env));
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

	exp = ft_malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	exp->key = key;
	exp->value = value;
	exp->next = NULL;
	return (exp);
}

t_env	*ft_last_node(t_env	*nv)
{
	while (nv)
	{
		if (nv->next == NULL)
			break ;
		nv = nv->next;
	}
	return (nv);
}

t_exp	*ft_last_node2(t_exp *nv)
{
	while (nv)
	{
		if (nv->next == NULL)
			break ;
		nv = nv->next;
	}
	return (nv);
}

void	ft_addbacknode(t_env **env, t_env *nv)
{
	if (*env)
		ft_last_node(*env)->next = nv;
	else
		*env = nv;
}

void	ft_addbacknode2(t_exp **exp, t_exp *nv)
{
	if (*exp)
		ft_last_node2(*exp)->next = nv;
	else
		*exp = nv;
}

void	printenv(t_env *ev)
{
	while (ev)
	{
		printf("%s %s\n", ev->key, ev->value);
		ev = ev->next;
	}
}
