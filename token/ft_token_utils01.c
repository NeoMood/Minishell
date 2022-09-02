/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:31:49 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/01 22:19:16 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkdquotes(int i, char *line, t_tk **list)
{
	int	j;
	int	k;

	j = i;
	while (line[j])
	{
		if (line[j] == '$')
		{
			if (line[j - 1] != '\"' && i < j)
				ft_addtolist(list, ft_input(ft_substr(line, i + 1, j - i - 1), WORD));
			k = ft_checkdollar(j, line, list);
			if (line[k] == '\"')
				return (k + 1);
			else if (line[k] != '\"' && line[k] == '\0')
			{
				printf("Syntax Error\n");
				return(j + 1);
			}
			i = k;
		}
		j++;
		if (line[j] == '\"')
			break ;
	}
	if (line[j] == '\"' && j != i + 1)
		ft_addtolist(list, ft_input(ft_substr(line, i + 1, j - i - 1), WORD));
	else if (j != i + 1)
	{
		printf("Syntax Error\n");
		return (j + 1);
	}
	return (j + 1);
}

int	ft_checksquotes(int i, char *line, t_tk **list)
{
	int	j;

	j = i + 1;
	while (line[j] && line[j] != '\'')
		j++;
	if (line[j] == '\'')
		ft_addtolist(list, ft_input(ft_substr(line, i, j - i), SQUOTE));
	else
	{
		printf("Syntax Error\n");
		exit (1);
	}
	return (j + 1);
}

int	ft_checkdollar(int i, char *line, t_tk **list)
{
	int	j;

	j = i + 1;
	if (line[j - 1] == '$' && line[j] == '?')
	{
		ft_addtolist(list, ft_input(ft_strdup(ft_itoa(mode.g_exit)), WORD));
		return (j + 1);
	}
	while (line[j] && ft_delimiter(line[j]))
		j++;
	ft_addtolist(list, ft_input(ft_substr(line, i, j - i), VAR));
	return (j);
}

int	ft_getword(char *line, int i)
{
	int count;

	count = i;
	while (line[i] && line[i] != ' ' && line[i] != '|'
        && line[i] != '>' && line[i] != '<' && line[i] != '$')
	{
		count++;
		i++;
	}
	return (count);
}
