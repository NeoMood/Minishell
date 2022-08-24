/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:31:11 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/24 22:44:29 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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