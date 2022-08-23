/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:55:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/23 18:14:48 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    processing_cmd(char *path, char **cmd, char **env)
{
    if (execve(path, cmd, env) == -1)
		perror("execve");
	exit(EXIT_FAILURE);
}


void   forking(char *path, char **cmd, char **env)
{
    int pid;

    pid = fork();
	if (pid < 0)
		return (perror("pipe"));
	if (pid == 0)
		processing_cmd(path, cmd, env);

    wait(&pid);
}


void    parse_cmd(char **cmd, t_env *env, char **envar)
{
    char *path;
    path = get_path(env, cmd);
    
    forking(path, cmd, envar);
}