/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:55:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/24 23:05:41 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    processing_cmd(char *path, char **cmd, char **env)
{
    if (execve(path, cmd, env) == -1)
		return ;
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

void    parse_cmd(char **cmd, t_exenv exenv)
{
    char *path;

    if(cmd[0][0] == '.' && cmd[0][1] == '/')
        path = get_path2(exenv.env, cmd);
    else
        path = get_path(exenv.env, cmd);
    forking(path, cmd, exenv.envar);
}