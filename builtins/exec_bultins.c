/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bultins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:13:27 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/27 22:15:43 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins(t_exenv exenv, t_fds    *fds)
{
    // t_args  *tmp;

    // tmp = exenv.args;
    // while(tmp)
    // {
    //     printf("~~%u\n", tmp->type);
    //     if(tmp->type == IN)
    //     {
    //         printf("-----fd_in: %d\n", fds->in_fd);
    //         dup2(fds->in_fd, STDIN_FILENO);
    //     }
    //     if(tmp->type == OUT)
    //     {
    //         printf("-----fd_out: %d\n", fds->out_fd);
    //         dup2(fds->out_fd, STDOUT_FILENO);
    //     }
    //     tmp = tmp->next;   
    // }
    (void)fds;
    // if(exenv.args->type == OUT)
	// {
	// 	dup2(fds->out_fd, STDOUT_FILENO);
	// 	exenv.args = exenv.args->next;
	// }
    if(exenv.args->type == COMMAND)
    {
        if (!ft_strcmp(exenv.args->arg[0], "cd"))
            ft_cd(exenv);
        else if (!ft_strcmp(exenv.args->arg[0], "pwd"))
            ft_pwd();
        else if (!ft_strcmp(exenv.args->arg[0], "env"))
            ft_env(exenv);
        else if (!ft_strcmp(exenv.args->arg[0], "echo"))
            ft_echo(exenv);
        else if (!ft_strcmp(exenv.args->arg[0], "export"))
            ft_export(exenv);
        else if (!ft_strcmp(exenv.args->arg[0], "unset"))
            ft_unset(exenv);
    }
}