/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:55:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/01 21:39:59 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>

void    processing_cmd(char *path, char **cmd, char **env)
{
    if (execve(path, cmd, env) == -1)
    {
        puts("11HERE");
        ft_putstr_fd("Error!\n", 2);
		return ;
    }
	exit(EXIT_FAILURE);
}

void   forking(char *path, char **cmd, char **env)
{
    int status;
    int pid;

    pid = fork();
	if (pid < 0)
		return (perror("pipe"));
	if (pid == 0)
		processing_cmd(path, cmd, env);
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        mode.g_exit = WEXITSTATUS(status);
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

void    increase_shlvl(t_exenv exenv)
{
    exenv.shlvl++;

    puts("here");
    while(exenv.env)
	{
		if(!ft_strcmp(exenv.env->key, "SHLVL"))
			exenv.env->value = ft_strdup(ft_itoa(exenv.shlvl));
		exenv.env = exenv.env->next;
	}
    while(exenv.exp)
	{
		if(!ft_strcmp(exenv.exp->key, "SHLVL"))
			exenv.exp->value = ft_strdup(ft_itoa(exenv.shlvl));
		exenv.exp = exenv.exp->next;
	}
}

void    parse_cmd(t_exenv exenv)
{
    char *path;
    char **cmd;

    if(access(exenv.args->arg[0], X_OK) == 0)
    {
        path = exenv.args->arg[0];
        cmd = get_cmd(exenv.args->arg);
    }
    else
    {
        if(exenv.args->arg[0][0] == '.' && exenv.args->arg[0][1] == '/')
        {
            path = get_path2(exenv.env, exenv.args->arg);
            if(!ft_strcmp(exenv.args->arg[0], "./minishell"))
                increase_shlvl(exenv);
        }
        else
            path = get_path(exenv.env, exenv.args->arg);
        cmd = exenv.args->arg;
    }
    forking(path, cmd, exenv.envar);
}