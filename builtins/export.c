/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/22 17:09:32 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_index(const char *s, int c)
{
	int		i;
	char	cc;
	char	*ss;

	i = 0;
	ss = (char *) s;
	cc = (char) c;
	while (ss[i] != cc && ss[i])
		i++;
	if (ss[i] == cc)
		return (i);
	else
		return (0);
}

char	*get_key(const char *s, int c)
{
	int i;
	int j;
	char *key;
	
	key = ft_strdup("");
	j = get_index(s, c);
	i = 0;
	while(i < j)
	{
		key[i] = s[i];
		i++;
	}
	return(key);
}

int		if_exists(t_exp	*exp, char *key)
{
	t_exp	*tmp;

	tmp = exp;
	while(tmp)
	{
		if(!ft_strcmp(tmp->key, key))
			return(1);
		tmp = tmp->next;
	}
	return(0);
}

int		if_exists2(t_env	*env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while(tmp)
	{
		if(!ft_strcmp(tmp->key, key))
			return(1);
		tmp = tmp->next;
	}
	return(0);
}

t_exp	*ft_lstlast(t_exp *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstlast(lst -> next));
}

void	ft_lstadd_back(t_exp **lst, t_exp	*new)
{
	t_exp	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlast(head);
		head -> next = new;
	}
	else
		(*lst) = new;
}

void	exp_print(t_exp **exp)
{
	t_exp	*new;

	new = *exp;
	while (new)
	{
		if(new->key)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(new->key, 1);
			if (*new->value != '\0')
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd(new->value, 1);
			if (*new->value != '\0')
			{
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		new = new->next;
	}
}

void	sort_exp(t_exp **exp)
{
	char	*tmp;
	char	*tmpv;
	t_exp	*j;
	t_exp	*i;

	i = *exp;
	while (i)
	{
		if(i->key)
		{
			j = i->next;
			while (j)
			{
				if (ft_strcmp(i->key, j->key) > 0)
				{
					tmp = i -> key;
					i -> key = j -> key;
					j -> key = tmp;
					tmpv = i -> value;
					i -> value = j -> value;
					j -> value = tmpv;
				}
				j = j->next;
			}
		}
		i = i->next;
	}
}

// t_exp   *env_to_exp(t_env *env)
// {
// 	t_exp   *exp;
// 	char	*key;
// 	char	*value;

// 	exp = NULL;
// 	while(env)
// 	{
// 		if(env->key)
// 		{
// 			key = ft_strdup(env->key);
// 			value = ft_strdup(env->value);
// 			ft_addbacknode2(&exp, ft_createcell2(key, value));
// 		}
// 		env = env->next;
// 	}
// 	return (exp);
// }

t_exp   *ft_getexp(char **env)
{
	t_exp	*save;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	save = NULL;
	while (env[i])
	{
        key = ft_substr(env[i], 0,ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		ft_addbacknode2(&save, ft_createcell2(key, value));
		i++;
	}
    return (save);
}

int	check_plequal(char *arg)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if(arg[i] == '+' && arg[i + 1] == '=')
			return(1);
		i++;
	}
	return(0);
}

void	update_value(t_exp	*exp, char *key, char *val)
{
	while(exp)
	{
		if(!ft_strcmp(exp->key, key))
			exp->value = ft_strdup(val);
		exp = exp->next;
	}
}

void	update_envalue(t_env	*env, char *key, char *val)
{
	while(env)
	{
		if(!ft_strcmp(env->key, key))
			env->value = ft_strdup(val);
		env = env->next;
	}
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i] != '\0')
		++i;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		++j;
	}
	dest[i] = '\0';
	return (dest);
}

void	add_value(t_exp	*exp, char *key, char *val)
{
	while(exp)
	{
		if(!ft_strcmp(exp->key, key))
			ft_strcat(exp->value, val);
		exp = exp->next;
	}
}

void	add_envalue(t_env	*env, char *key, char *val)
{
	while(env)
	{
		if(!ft_strcmp(env->key, key))
			ft_strcat(env->value, val);
		env = env->next;
	}
}

void    ft_export(t_args *line, t_exp *exp, t_env *env)
{
	char *val;
	char *key;
	int	i;
	
	i = 1;
	if(line->arg[1])
	{
		while(line->arg[i])
		{
			if(ft_strchr(line->arg[i], '='))
			{
				if(check_plequal(line->arg[i]))
				{
					key = get_key(line->arg[i], '+');
					val = ft_strchr(line->arg[i], '=');
					if(if_exists(exp, key))
						add_value(exp, key, &val[1]);
					if(if_exists2(env, key))
						add_envalue(env, key, &val[1]);
					else
					{
						ft_lstadd_back(&exp, ft_createcell2(key, &val[1]));
						ft_addbacknode(&env, ft_createcell(key, &val[1]));
					}
				}
				else
				{
					val = ft_strchr(line->arg[i], '=');
					key = get_key(line->arg[i], '=');
					if(if_exists(exp, key))
					{
						update_value(exp, key, &val[1]);
						update_envalue(env, key, &val[1]);
					}
					else if(!if_exists(exp, key))
					{
						ft_lstadd_back(&exp, ft_createcell2(key, &val[1]));
						ft_addbacknode(&env, ft_createcell(key, &val[1]));
						
					}
				}
			}
			else if(!ft_strchr(line->arg[i], '='))
			{
				if(!if_exists(exp, line->arg[i]))
				{
					puts("Here");
					ft_lstadd_back(&exp, ft_createcell2(line->arg[i], ""));
					sort_exp(&exp);
				}
			}
			i++;
		}
	}
	else
	{
		sort_exp(&exp);
		exp_print(&exp);
	}
}