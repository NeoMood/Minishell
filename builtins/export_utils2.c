/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:44:14 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 22:46:03 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exp	*ft_lstlast(t_exp *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstlast(lst -> next));
}

void	ft_lstadd_back(t_exp **lst, t_exp *nv)
{
	t_exp	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlast(head);
		head -> next = nv;
	}
	else
		(*lst) = nv;
}

void	exp_print(t_exp **exp)
{
	t_exp	*new;

	new = *exp;
	while (new)
	{
		if (new->key)
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

t_exp	*ft_getexp(char **env)
{
	t_exp	*save;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	save = NULL;
	while (env[i])
	{
		key = ft_substr(env[i], 0,
				ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		ft_addbacknode2(&save, ft_createcell2(key, value));
		i++;
	}
	return (save);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isdigit(key[0]))
		return (1);
	while (key[i])
	{
		if (key[i] < 48 || (key[i] > 57 && key[i] < 65)
			|| (key[i] > 90 && key[i] < 97) || key[i] > 122)
			return (1);
		i++;
	}
	return (0);
}
