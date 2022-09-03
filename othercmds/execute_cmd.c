/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:55:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/03 21:46:45 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/signal.h>
#include <sys/wait.h>

void    processing_cmd(char *path, char **cmd, char **env)
{
    mode.g_sig = 0;
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (execve(path, cmd, env) == -1)
    {
        ft_putstr_fd("Error!\n", 2);
		return ;
    }
	exit(EXIT_FAILURE);
}

int     list_size(t_env  *env)
{
    t_env   *clone;

    clone = env;
    int i;
    
    i = 0;
    while(clone)
    {
        i++;
        clone = clone->next;
    }
    return(i);
}

char    **get_newenv(t_env  *env)
{
    char **new_env;
    int i;
    new_env = malloc((sizeof(char *) * (list_size(env) + 1)));
    if(!new_env)
        return(NULL);
    i = 0;
    // if(new_env)
    //     ft_free(new_env);
    while(env)
    {
        new_env[i] = ft_strdup(env->key);
        new_env[i] = ft_strjoin(new_env[i], "=");
        new_env[i] = ft_strjoin(new_env[i], env->value);
        i++;
        env = env->next;
    }
    new_env[i] = NULL;
    return(new_env);
}

void   forking(char *path, char **cmd, char **new_env)
{
    int status;
    int pid;

    // char **new_env;
    // new_env = get_newenv(my_env);
    // while(new_env[i])
    // {
    //     printf("here: %s\n", new_env[i]);
    //     i++;
    // }
    pid = fork();
	if (pid < 0)
		return (perror("pipe"));
    mode.g_sig = 1;
	if (pid == 0)
		processing_cmd(path, cmd, new_env);
    waitpid(pid, &status, 0);
    mode.g_sig = 0;
    if (WIFEXITED(status))
        mode.g_exit = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGQUIT)
            printf("Quit: %d\n", WTERMSIG(status));
        else if (WTERMSIG(status) != SIGINT)
            printf("SIGNALED: %d\n", WTERMSIG(status));
    }
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
    // int i = 0;

    exenv.new_env = get_newenv(exenv.env);
    // while(exenv.new_env[i])
    // {
    //     printf("here: %s\n", exenv.new_env[i]);
    //     i++;
    // }
    if(access(exenv.args->arg[0], X_OK) == 0)
    {
        path = exenv.args->arg[0];
        cmd = get_cmd(exenv.args->arg);
    }
    else
    {
        if (exenv.args->arg[0] && exenv.args->arg[0][0] == '.' && exenv.args->arg[0][1] == '/')
        {
            path = get_path2(exenv.env, exenv.args->arg);
            if(!ft_strcmp(exenv.args->arg[0], "./minishell"))
                increase_shlvl(exenv);
        }
        else
            path = get_path(exenv.env, exenv.args->arg);
        cmd = exenv.args->arg;
    }
    forking(path, cmd, exenv.new_env);
}