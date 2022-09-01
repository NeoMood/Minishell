/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:51:49 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/01 14:48:18 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void ft_error(t_exenv exenv)
{
    write (1, "exit\n", 5);
    printf ("Minishell: exit: %s: numeric argument required\n", exenv.args->arg[1]);
    exit (1);
}

static void	ft_handlelong(t_exenv exenv)
{
    int	j;

    j = 0;
    while (exenv.args->arg[1][j])
    {
        if (!ft_strcmp(exenv.args->arg[1], "9223372036854775807"))
        {
            g_exit = 255; 
            write (1, "exit\n", 5);
            exit (0);
        }
        else
        {
            g_exit = 255;
            ft_error(exenv);
        }
        j++;
    }
}

static void	ft_negativenum(int j, t_exenv exenv)
{
    int	l;

    l = 0;
    if (exenv.args->arg[1][j] == '-')
    {
        l = j;
        while (exenv.args->arg[1][l])
        {
            l++;
            if (ft_isdigit(exenv.args->arg[1][l]))
            {
                g_exit = 256 + ft_atoi(exenv.args->arg[1]) % 256;
                write (1, "exit\n", 5);
                exit (0);
            }
            else
                ft_error(exenv);
            l++;
        }
    }
}

static void	ft_postifnum(int j, t_exenv exenv)
{
    int	len;
    int	l;
    
    
    l = j;
    len = ft_strlen(exenv.args->arg[1]);
    if (len < 19)
    {
        if (ft_isdigit(exenv.args->arg[1][l]))
        {
            g_exit = ft_atoi(&exenv.args->arg[1][l]) % 256;
            write (1, "exit\n", 5);
            exit (0);
        }
        else
            ft_error(exenv);
    }
    else
        ft_handlelong(exenv);
}

int	ft_exit(t_exenv exenv)
{
    int	i;
    int	j;

    i = 0;
    if (exenv.args->arg[1])
    {
        while (exenv.args->arg[1][i])
        {
            j = 0;
            if (exenv.args->arg[1][j] == '-')
                ft_negativenum(j, exenv);
            else
                ft_postifnum(j, exenv);
            i++;
        }
    }
    else 
    {
        write (1, "exit\n", 5);
        exit (0);
    }
    return 0;
}