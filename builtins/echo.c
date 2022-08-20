/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:13:17 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/20 15:42:18 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_echo(t_args *line)
{
    int i;

    i = 0;
    if(!ft_strcmp(line->arg[1], "-n"))
    {
        i = 2;
        while(line->arg[i])
        {
            printf("%s", line->arg[i]);
            i++;
        }
    }
    else
    {
        i = 1;
        while(line->arg[i])
        {
            printf("%s", line->arg[i]);
            printf(" ");
            i++;
        }
        printf("\n");
    }
}