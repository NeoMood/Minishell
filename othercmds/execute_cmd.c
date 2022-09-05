/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:55:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/05 19:46:49 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/signal.h>
#include <sys/wait.h>

void	processing_cmd(char *path, char **cmd, char **env)
{
	g_mode.g_sig = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(path, cmd, env) == -1)
		exit(EXIT_FAILURE);
}

void	forking(char *path, char **cmd, char **new_env)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("pipe"));
	g_mode.g_sig = 1;
	if (pid == 0)
		processing_cmd(path, cmd, new_env);
	waitpid(pid, &status, 0);
	g_mode.g_sig = 0;
	if (WIFEXITED(status))
		g_mode.g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			printf("Quit: %d\n", WTERMSIG(status));
			g_mode.g_exit = 131;
		}
		else if (WTERMSIG(status) != SIGINT)
			g_mode.g_exit = WTERMSIG(status);
	}
}

char	**get_cmd(char **cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(cmd[0], '/');
	while (tmp[i])
		i++;
	cmd[0] = ft_strdup(tmp[i - 1]);
	return (cmd);
}

void	increase_shlvl(t_exenv exenv)
{
	exenv.shlvl++;
	while (exenv.env)
	{
		if (!ft_strcmp(exenv.env->key, "SHLVL"))
			exenv.env->value = ft_strdup(ft_itoa(exenv.shlvl));
		exenv.env = exenv.env->next;
	}
	exenv.shlvl++;
	while (exenv.exp)
	{
		if (!ft_strcmp(exenv.exp->key, "SHLVL"))
			exenv.exp->value = ft_strdup(ft_itoa(exenv.shlvl));
		exenv.exp = exenv.exp->next;
	}
}

void	parse_cmd(t_exenv exenv)
{
	char	*path;
	char	**cmd;

	exenv.new_env = get_newenv(exenv.env);
	if (access(exenv.args->arg[0], X_OK) == 0)
	{
		path = exenv.args->arg[0];
		cmd = get_cmd(exenv.args->arg);
	}
	else
	{
		if (exenv.args->arg[0] && exenv.args->arg[0][0] == '.'
			&& exenv.args->arg[0][1] == '/')
		{
			path = get_path2(exenv.env, exenv.args->arg);
			if (!ft_strcmp(exenv.args->arg[0], "./minishell"))
				increase_shlvl(exenv);
		}
		else
			path = get_path(exenv.env, exenv.args->arg);
		cmd = exenv.args->arg;
	}
	forking(path, cmd, exenv.new_env);
}
