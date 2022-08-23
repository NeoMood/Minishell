/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:55:12 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/23 23:06:01 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    parse_multicmd(t_args *args, t_env *env, char **envar)
{
    char *path;
    while(args)
    {
        if (args->type == COMMAND)
		{
            path = get_path(env, args->arg);
            free(path);
        }
		args = args->next;
    }
}