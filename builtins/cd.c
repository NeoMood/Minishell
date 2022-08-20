/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:31:11 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/20 15:50:06 by sgmira           ###   ########.fr       */
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

// void	keep_oldpwd(t_cd *cd)
// {
// 	if (cd->oldpwd)
// 		free(cd->oldpwd);
// 	cd->oldpwd = ft_strdup("OLD");
// 	cd->oldpwd = ft_strjoin(cd->oldpwd, cd->pwd);
// }

void	ft_cd(t_args *line, t_env *envar)
{
	if (!line->arg[1])
	{
		if(chdir(var_value(envar, "HOME")) == -1)
			printf("path not found\n");
	}
	else
	{
		if(chdir(line->arg[1]) == -1)
			printf("path not found\n");
	}
}