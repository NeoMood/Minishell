/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:52:37 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/03 18:12:27 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	**our_env(char **env)
{
	char	**our_env;
	int	i;

	i = 0;
	while(env[i])
		i++;
	our_env = malloc(sizeof(char *) * (i + 1));
	if (!our_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		our_env[i] = env[i];
		i++;
	}
	our_env[i] = NULL;
	return (our_env);
}

t_env	*ft_getenv(char **envp)
{
	t_env	*save;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	save = NULL;
	while (envp[i])
	{
		key = ft_substr(envp[i], 0,
				ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '=')));
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		ft_addbacknode(&save, ft_createcell(key, value));
		i++;
	}
	return (save);
}

char	*ft_getvalue(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*var_value(t_env *env, char *varname)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, varname) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp->value);
}

t_tk	*ft_expand(t_tk *list, t_env *ev)
{
	t_tk	*tmp;
	char	*temp;

	tmp = list;
	while (list && list->token != DOUTPUT)
	{
		if (list->token == VAR)
		{
			temp = list->input;
			list->input = ft_strdup(ft_getvalue(ev, list->input + 1));
			free(temp);
		}
		list = list->next;
	}
	return (tmp);
}
