/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:31:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/09 19:29:37 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_norm(int j, int i, char *line, t_tk **list)
{
	if (line[j] == '\"' && j != i)
		ft_addtolist(list, ft_input(ft_substr(line, i, j - i), WORD));
	else if (j != i)
	{
		g_mode.g_check = 1;
		return (j + 1);
	}
	return (j + 1);
}

int	ft_norm2(int j)
{
	g_mode.g_check = 1;
	return (j + 1);
}

int	ft_checkdquotes(int i, char *line, t_tk **list)
{
	int	j;

	j = i;
	while (line[j] && line[j] != '\"')
	{
		if (line[j] == '$')
		{
			if (line[j - 1] != '\"' && i < j)
				ft_addtolist(list,
					ft_input(ft_substr(line, i, j - i), WORD));
			j = ft_checkdollar(j, line, list);
			if (line[j] == '\"')
				return (j + 1);
			else if (line[j] != '\"' && line[j] == '\0')
				j = ft_norm2(j);
			i = j;
		}
		if (line[j] == '\"')
			break ;
		if (line[j] != '$')
			j++;
	}
	return (ft_norm(j, i, line, list));
}

int	ft_checksquotes(int i, char *line, t_tk **list)
{
	int	j;

	j = i;
	while (line[j] && line[j] != '\'')
		j++;
	if (line[j] == '\'')
		ft_addtolist(list, ft_input(ft_substr(line, i, j - i), SQUOTE));
	else
	{
		g_mode.g_check = 1;
		return (j + 1);
	}
	return (j + 1);
}

int	ft_checkdollar(int i, char *line, t_tk **list)
{
	int	j;

	j = i + 1;
	if (line[j - 1] == '$' && line[j] == '?')
	{
		ft_addtolist(list, ft_input(ft_strdup(ft_itoa(g_mode.g_exit)), WORD));
		return (j + 1);
	}
	while (line[j] && ft_delimiter(line[j]))
		j++;
	ft_addtolist(list, ft_input(ft_substr(line, i, j - i), VAR));
	return (j);
}
