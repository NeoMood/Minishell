/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:13:17 by sgmira            #+#    #+#             */
/*   Updated: 2022/09/04 15:06:53 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int n_check(char *arg)
// {
//     int i;

//     if (!ft_strncmp(arg, "-n", 2))
// 	{
// 		i = 2;
// 		while (arg[i] && arg[i] == 'n')
// 			i++;
// 		if (!arg[i])
// 			return (1);
// 	}
// 	return (0);
// }

// void    ft_echo(t_exenv exenv)
// {
//     int i;

//     i = 0;
//     puts("HERE");
//     if(!ft_strcmp(exenv.args->arg[1], "-n"))
//     {
//         i = 2;
//         // while (exenv.args->arg[i] && exenv.args->arg[i] == 'n')
// 		// 	i++;
//         // if (!arg[i])
// 		// 	return ;
//         printf("~~~~%s\n", exenv.args->arg[i]);
//         while(exenv.args->arg[i])
//         {
//             printf("%s", exenv.args->arg[i]);
//             i++;
//         }
//     }
//     else
//     {
//         i = 1;
//         while(exenv.args->arg[i])
//         {
//             printf("%s", exenv.args->arg[i]);
//             // printf(" ");
//             i++;
//         }
//         printf("\n");
//     }
// }

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
	int	len;
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
