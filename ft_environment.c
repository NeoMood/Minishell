/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:52:37 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/26 15:12:07 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *ft_getenv(char **envp)
{
	t_env	*save;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	save = NULL;
	while (envp[i])
	{
        key = ft_substr(envp[i], 0,ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '=')));
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
	t_env  *tmp;
	// int		len;

	tmp = env;
	// len = ft_strlen(varname);
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, varname) == 0)
			break ;
		tmp = tmp->next;
	}
	return(tmp->value);
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
			// list->token = WORD;
			free(temp);
		}
		list = list->next;
    }
	return (tmp);
}

// char	*expansion(t_env *envar, char *str)
// {
// 	t_env	*tmp;
// 	int		length;

// 	tmp = envar;
// 	while (tmp && tmp->next)
// 	{
// 		length = ft_strlen(tmp->key);
// 		if (ft_strncmp(tmp->key, str, length) == 0)
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }
