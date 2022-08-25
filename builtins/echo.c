/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:13:17 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/25 02:33:31 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_echo(t_exenv exenv)
{
    int i;

    i = 0;
    if(!ft_strcmp(exenv.args->arg[1], "-n"))
    {
        i = 2;
        while(exenv.args->arg[i])
        {
            printf("%s", exenv.args->arg[i]);
            i++;
        }
    }
    else
    {
        i = 1;
        while(exenv.args->arg[i])
        {
            printf("%s", exenv.args->arg[i]);
            // printf(" ");
            i++;
        }
        printf("\n");
    }
}