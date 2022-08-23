/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:15:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/23 18:09:07 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *env_path(t_env *env)
{
    t_env *clone;

    clone = env;
    while(clone)
    {
        if(!ft_strcmp(clone->key, "PATH"))
            return(clone->value);
        clone=clone->next;
    }
    return(NULL);
}

char    *get_path(t_env *env,  char **cmd)
{
    char **paths;
    char *path;
    int i;
    // printf("%s\n", cmd[0]);
    paths = ft_split(env_path(env), ':');
    i = 0;

    while(paths[i])
    {
        path = ft_strdup(paths[i]);
		path = ft_strjoin_v2(path, "/");
		path = ft_strjoin_v2(path, cmd[0]);
        
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
    }
    return(NULL);
}