/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/05 16:52:36 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_envalue(t_env	*env, char *key, char *val)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			env->value = ft_strjoin(env->value, val);
		env = env->next;
	}
}

void	plequal_case(char	*key, char	*val, t_exenv *exenv, int i)
{
	key = get_key(exenv->args->arg[i], '+');
	val = ft_strchr(exenv->args->arg[i], '=');
	if (check_key(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		g_mode.g_exit = 1;
		return ;
	}
	if (if_exists(exenv->exp, key))
		add_value(exenv->exp, key, &val[1]);
	if (if_exists2(exenv->env, key))
		add_envalue(exenv->env, key, &val[1]);
	else if (!if_exists(exenv->exp, key)
		&& !if_exists2(exenv->env, key))
	{
		ft_lstadd_back(&exenv->exp,
			ft_createcell2(key, &val[1]));
		ft_addbacknode(&exenv->env, ft_createcell(key, &val[1]));
	}
}

void	equal_case(char	*key, char	*val, t_exenv *exenv, int i)
{
	val = ft_strchr(exenv->args->arg[i], '=');
	key = get_key(exenv->args->arg[i], '=');
	if (check_key(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		g_mode.g_exit = 1;
		return ;
	}
	if (if_exists(exenv->exp, key))
	{
		update_value(exenv->exp, key, &val[1]);
		update_envalue(exenv->env, key, &val[1]);
	}
	else if (!if_exists(exenv->exp, key))
	{
		ft_lstadd_back(&exenv->exp,
			ft_createcell2(key, &val[1]));
		ft_addbacknode(&exenv->env, ft_createcell(key, &val[1]));
	}
}

void	noequal_case(t_exenv *exenv, int i)
{
	if (check_key(exenv->args->arg[i]))
	{
		printf("export: `%s': not a valid identifier\n",
			exenv->args->arg[i]);
		g_mode.g_exit = 1;
		return ;
	}
	if (!if_exists(exenv->exp, exenv->args->arg[i]))
	{
		ft_lstadd_back(&exenv->exp,
			ft_createcell2(exenv->args->arg[i], ""));
		sort_exp(&exenv->exp);
	}
}

void	ft_export(t_exenv exenv)
{
	char	*val;
	char	*key;
	int		i;

	i = 1;
	val = NULL;
	key = NULL;
	if (exenv.args->arg[1])
	{
		while (exenv.args->arg[i])
		{
			if (ft_strchr(exenv.args->arg[i], '='))
			{
				if (check_plequal(exenv.args->arg[i]))
					plequal_case(key, val, &exenv, i);
				else
					equal_case(key, val, &exenv, i);
			}
			else if (!ft_strchr(exenv.args->arg[i], '='))
				noequal_case(&exenv, i);
			i++;
		}
	}
	else
		sort_n_print(&exenv);
}
