/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/20 17:55:30 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    env_to_exp(t_exp *exp, t_env *env)
{
    char	*key;
	char	*value;
    
    while(env->next)
    {
        key = ft_strdup(env->key);
        value = ft_strdup(env->value);
        ft_addbacknode2(&exp, ft_createcell2(key, value));
        env = env->next;
    }
}

void    ft_export(t_args *line, t_env *env)
{
    (void)line;
    t_exp *exp;
    
    exp = NULL;
    env_to_exp(exp, env);
    // puts("Here");
    // printf("%s=\"%s\"\n", exp->key, exp->value);
    while(exp->next)
    {
        printf("%s=\"%s\"\n", exp->key, exp->value);
        exp = exp->next;
    }
    
}