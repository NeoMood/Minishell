/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:13 by sgmira            #+#    #+#             */
/*   Updated: 2022/08/21 23:11:52 by sgmira           ###   ########.fr       */
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
		{
			// printf("lstkey: %s -- newkey: %s\n", tmp->key, key);
			return(1);
		}
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
		i = i->next;
	}
}

t_exp   *env_to_exp(t_env *env)
{
	t_exp   *exp;
	char	*key;
	char	*value;

	exp = NULL;
	while(env)
	{
		key = ft_strdup(env->key);
		value = ft_strdup(env->value);
		ft_addbacknode2(&exp, ft_createcell2(key, value));
		if (env)
			env = env->next;
	}
	return (exp);
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
		{
			exp->value = ft_strdup(val);
		}
		exp = exp->next;
	}
}

void    ft_export(t_args *line, t_exp *exp)
{
	char *val;
	char *key;
	
	if(line->arg[1])
	{
		if(ft_strchr(line->arg[1], '='))
		{
			if(check_plequal(line->arg[1]))
			{
				printf("KAYNAAA\n");
			}
			else
			{
				val = ft_strchr(line->arg[1], '=');
				key = get_key(line->arg[1], '=');
				if(if_exists(exp, key))
				{
					printf("%d\n", if_exists(exp, key));
					update_value(exp, key, &val[1]);
				}
				else if(!if_exists(exp, key))
				{
					printf("%d\n", if_exists(exp, key));
					ft_lstadd_back(&exp, ft_createcell2(key, &val[1]));
				}
			}
		}
		else if(!ft_strchr(line->arg[1], '='))
		{
			ft_lstadd_back(&exp, ft_createcell2(line->arg[1], ""));
			sort_exp(&exp);
		}
	}
	else
	{
		sort_exp(&exp);
		exp_print(&exp);
	}
}