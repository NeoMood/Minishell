/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:55:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/24 17:33:30 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    processing_cmd(char *path, char **cmd, char **env)
{
    if (execve(path, cmd, env) == -1)
		return ;
	exit(EXIT_FAILURE);
}

// void    processing_execfile(char **cmd, char **env)
// {
//     if (execve(NULL, cmd, env) == -1)
// 		return ;
// 	exit(EXIT_FAILURE);
// }


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

// void   forking2(char **cmd, char **env)
// {
//     int pid;

//     pid = fork();
// 	if (pid < 0)
// 		return (perror("pipe"));
// 	if (pid == 0)
// 		processing_execfile(cmd, env);

//     wait(&pid);
// }


void    parse_cmd(char **cmd, t_env *env, char **envar)
{
    char *path;

    if(cmd[0][0] == '.' && cmd[0][1] == '/')
        path = get_path2(env, cmd);
    else
        path = get_path(env, cmd);
    forking(path, cmd, envar);
}