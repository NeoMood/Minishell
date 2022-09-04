/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:15:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 15:29:05 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_path(t_env *env)
{
	t_env	*clone;

	clone = env;
	while (clone)
	{
		if (!ft_strcmp(clone->key, "PATH"))
			return (clone->value);
		clone = clone->next;
	}
	return (NULL);
}

char	*env_pwd(t_env *env)
{
	t_env	*clone;

	clone = env;
	while (clone)
	{
		if (!ft_strcmp(clone->key, "PWD"))
			return (clone->value);
		clone = clone->next;
	}
	return (NULL);
}

int	get_error(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(2, "invalid command!\n", 18);
		mode.g_exit = 127;
		return (1);
	}
	else
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
		write(2, ": No such file or directory\n", 29);
		mode.g_exit = 127;
		return (1);
	}
	return (1);
}

char	*get_path(t_env *env, char **cmd)
{
	char	**paths;
	char	*path;
	int		i;

	if (!env)
		return (NULL);
	paths = ft_split(env_path(env), ':');
	i = 0;
	if (paths)
	{
		while (paths[i])
		{
			path = ft_strdup(paths[i]);
			path = ft_strjoin_v2(path, "/");
			path = ft_strjoin_v2(path, cmd[0]);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			i++;
		}
	}
	get_error (cmd[0]);
	return (NULL);
}

void	get_filerror(char **cmd)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

char	*get_path2(t_env *env, char **cmd)
{
	char	*path;
	char	cwd[1024];

	(void) env;
	getcwd(cwd, sizeof(cwd));
	path = ft_strdup(cwd);
	path = ft_strjoin_v2(path, "/");
	path = ft_strjoin_v2(path, &cmd[0][2]);
	if (access(cmd[0], X_OK) == 0)
		return (path);
	else
	{
		get_filerror(cmd);
		return (NULL);
	}
}
