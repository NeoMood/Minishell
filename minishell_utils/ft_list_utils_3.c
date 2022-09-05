/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:33:14 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/05 22:05:19 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_createcell(char *key, char	*value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	ft_addbackthegarbe(&g_mode.trash, ft_newgarbage(env));
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

t_exp	*ft_createcell2(char *key, char	*value)
{
	t_exp	*exp;

	exp = malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	ft_addbackthegarbe(&g_mode.trash, ft_newgarbage(exp));
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
