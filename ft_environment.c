/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:52:37 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 21:49:23 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_newenv(t_env	*env)
{
	char	**new_env;
	int		i;

	new_env = malloc((sizeof(char *) * (list_size(env) + 1)));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env)
	{
		new_env[i] = ft_strdup(env->key);
		new_env[i] = ft_strjoin(new_env[i], "=");
		new_env[i] = ft_strjoin(new_env[i], env->value);
		i++;
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
