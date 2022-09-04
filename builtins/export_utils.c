/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:39:12 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 22:40:42 by sgmira           ###   ########.fr       */
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
	int		i;
	int		j;
	char	*key;
	char	*tmp;

	j = get_index(s, c);
	i = 0;
	tmp = (char *)malloc(sizeof(char) * j + 1);
	while (i < j)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	key = ft_strdup(tmp);
	free(tmp);
	return (key);
}

int	if_exists(t_exp	*exp, char *key)
{
	t_exp	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	if_exists2(t_env	*env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_plequal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}
