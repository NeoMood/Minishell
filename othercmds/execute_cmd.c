/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:55:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/25 15:35:20 by sgmira           ###   ########.fr       */
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

char **get_cmd(char **cmd)
{
    char **tmp;
    int     i;

    i = 0;
    tmp = ft_split(cmd[0], '/');
    while(tmp[i])
        i++;
    cmd[0] = ft_strdup(tmp[i - 1]);
    return(cmd);
}

void    parse_cmd(t_exenv exenv)
{
    char *path;
    char **cmd;

    // printf("%s\n", exenv.args->arg[0]);
    if(access(exenv.args->arg[0], X_OK) == 0)
    {
        path = exenv.args->arg[0];
        cmd = get_cmd(exenv.args->arg);
    }
    else
    {
        if(exenv.args->arg[0][0] == '.' && exenv.args->arg[0][1] == '/')
            path = get_path2(exenv.env, exenv.args->arg);
        else
            path = get_path(exenv.env, exenv.args->arg);
        cmd = exenv.args->arg;
    }
    forking(path, cmd, exenv.envar);
}