/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 23:08:02 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/06 23:17:15 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkspace(int i, t_tk **list)
{
	ft_addtolist(list, ft_input(ft_strdup(" "), SP));
	return (i + 1);
}

int	ft_getword(char *line, int i)
{
	int	count;

	count = i;
	while ((line[i] && line[i] != ' ' && line[i] != '|'
			&& line[i] != '>' && line[i] != '<' && line[i] != '$'
			&& line[i] != '\'' && line[i] != '\"')
		|| (line[i] == ' ' && line[i - 1] == '\"' ))
	{
		count++;
		i++;
	}
	return (count);
}
