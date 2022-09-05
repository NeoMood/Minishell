/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:48:53 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/05 23:14:33 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_util(char	*tmp, char	*tmpv, t_exp	**i, t_exp	**j)
{
	tmp = (*i)->key;
	(*i)->key = (*j)->key;
	(*j)->key = tmp;
	tmpv = (*i)->value;
	(*i)->value = (*j)->value;
	(*j)->value = tmpv;
}

void	sort_exp(t_exp **exp)
{
	char	*tmp;
	char	*tmpv;
	t_exp	*j;
	t_exp	*i;

	tmp = NULL;
	tmpv = NULL;
	i = *exp;
	while (i)
	{
		if (i->key)
		{
			j = i->next;
			while (j)
			{
				if (ft_strcmp(i->key, j->key) > 0)
					sort_util(tmp, tmpv, &i, &j);
				j = j->next;
			}
		}
		i = i->next;
	}
}

void	update_value(t_exp	*exp, char *key, char *val)
{
	while (exp)
	{
		if (!ft_strcmp(exp->key, key))
			exp->value = ft_strdup(val);
		exp = exp->next;
	}
}

void	update_envalue(t_env	*env, char *key, char *val)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			env->value = ft_strdup(val);
		env = env->next;
	}
}

void	add_value(t_exp	*exp, char *key, char *val)
{
	while (exp)
	{
		if (!ft_strcmp(exp->key, key))
			exp->value = ft_strjoin(exp->value, val);
		exp = exp->next;
	}
}
