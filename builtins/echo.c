/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:13:17 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/03 18:11:01 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = -1;
	while (arr[i])
        i++;
	return (i);
}

int	n_check(char *arg)
{
	int	indx;

	if (!ft_strncmp(arg, "-n", 2))
	{
		indx = 2;
		while (arg[indx] && arg[indx] == 'n')
			indx++;
		if (!arg[indx])
			return (1);
	}
	return (0);
}

void	ft_echo(char **data)
{
	int	i;
	int len;
	int	nl;

	len = arr_len(data);
	if (len == 1)
    {
        printf("\n");
		return ;
    }
	nl = 0;
	i = 1;
	while (data[i] && n_check(data[i]) == 1)
		i++;
	if (i > 1)
		nl = 1;
	while (data[i])
	{
		printf("%s", data[i]);
		if (i++ != len - 1)
			printf(" ");
	}
	if (!nl)
		printf("\n");
	return ;
}
