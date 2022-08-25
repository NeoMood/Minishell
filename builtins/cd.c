/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:31:11 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/25 23:25:00 by sgmira           ###   ########.fr       */
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

void	ft_cd(t_exenv exenv)
{
	// t_exenv exp;

	// exp = exevn;
	// change_pwd(exenv, "OLDPWD");
	if (!exenv.args->arg[1])
	{
		if(chdir(var_value(exenv.head, "HOME")) == -1)
			printf("path not found\n");
	}
	else
	{
		if(chdir(exenv.args->arg[1]) == -1)
			printf("path not found\n");
	}
	change_pwd(exenv, "PWD");
}