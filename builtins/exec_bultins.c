/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bultins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:13:27 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/22 01:30:40 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins(t_args *new, t_env *envar, t_exp *exp)
{
    if (!ft_strcmp(new->arg[0], "cd"))
        ft_cd(new, envar);
    else if (!ft_strcmp(new->arg[0], "pwd"))
        ft_pwd();
    else if (!ft_strcmp(new->arg[0], "env"))
        ft_env(envar);
    else if (!ft_strcmp(new->arg[0], "echo"))
        ft_echo(new);
    else if (!ft_strcmp(new->arg[0], "export"))
        ft_export(new, exp);
    else if (!ft_strcmp(new->arg[0], "unset"))
        ft_unset(new, envar);
}