/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:31:11 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/24 22:42:27 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *get_envpath(char **env, char *target)
// {
// 	int i;
// 	int j;
// 	int x;

// 	i = 0;
// 	while(env[i])
// 	{
// 		j = 0;
// 		x = 0;
// 		while(target[j] == env[i][x])
// 		{
// 			if (env[i][j + 1] == '=')
// 			{
// 				return (&env[i][x + 2]);
// 			}
// 			j++;
// 			x++;
// 		}
// 		i++;
// 	}
// 	return(0);
// }

// char *get_varpath(char *var)
// {
// 	int i;

// 	i = 0;
// 	while(var[i])
// 	{
// 		if(var[i] == '=')
// 			return(&var[i + 1]);
// 		i++;
// 	}
// 	return(0);
// }

void	change_pwd(t_exenv exenv, char *dest)
{
	char cwd[1024];

    getcwd(cwd, sizeof(cwd));
	
	while(exenv.env)
	{
		if(!ft_strcmp(exenv.env->key, dest))
			exenv.env->value = ft_strdup(cwd);
		exenv.env = exenv.env->next;
	}
	while(exenv.exp)
	{
		if(!ft_strcmp(exenv.exp->key, dest))
			exenv.exp->value = ft_strdup(cwd);
		exenv.exp = exenv.exp->next;
	}
}

void	ft_cd(t_args *line, t_exenv exenv)
{
	change_pwd(exenv, "OLDPWD");
	if (!line->arg[1])
	{
		if(chdir(var_value(exenv.env, "HOME")) == -1)
			printf("path not found\n");
	}
	else
	{
		if(chdir(line->arg[1]) == -1)
			printf("path not found\n");
	}
	change_pwd(exenv, "PWD");
}