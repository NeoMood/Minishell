/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:52:26 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/02 15:54:33 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_delimiter(char c)
{
	if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z')
		&& !(c >= 'a' && c <= 'z') && c != '_' && c != '?')
		return (0);
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f')
		return(1);
	return (0);
}

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char    **ft_table(char **tmp2, char *tmp1)
{
    char	**final_arr;
    int		i;

	i = 0;
    if (!tmp1)
        final_arr = NULL;
    if (!tmp2)
        final_arr = malloc(sizeof(char *) * 2);
    else
    {
        while (tmp2[i])
            i++;
        final_arr = malloc (sizeof(char *) * (i + 2));
        i = -1;
        while (tmp2[++i])
            final_arr[i] = ft_strdup(tmp2[i]);
		ft_free(tmp2);
    }
    final_arr[i++] = ft_strdup(tmp1);
    final_arr[i] = NULL;
    return (final_arr);
}

int	event(void)
{
	return (0);
}
