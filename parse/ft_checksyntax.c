/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksyntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:27:57 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/05 17:16:40 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_checkfirst(t_tk *list)
{
	t_tk	*head;

	head = list;
	while (list)
	{
		if (list->token == RINPUT && list->next == NULL)
			return (0);
		else if (list->token == ROUTPUT && list->next == NULL)
			return (0);
		else if (list->token == PIP && list->next == NULL)
			return (0);
		else if (list->token == DOUTPUT && list->next == NULL)
			return (0);
		else if (list->token == DINPUT && list->next == NULL)
			return (0);
		else if (head->token == PIP)
			return (0);
		list = list->next;
	}
	return (1);
}

int	ft_checksyntaxpip(t_tk *list)
{
	while (list)
	{
		if (list->token == PIP && (list->next && list->next->token == PIP))
			return (0);
		if (list->token == PIP && (list->next && list->next->next
				&& list->next->token == SP && list->next->next->token == PIP))
			return (0);
		list = list->next;
	}
	return (1);
}

int	ft_fullcheck(t_tk *list)
{
	if (!ft_checksyntaxpip(list) || !ft_checkfirst(list) || g_mode.g_check == 1)
	{
		printf("minishell: Syntax Error\n");
		g_mode.g_exit = 258;
		g_mode.g_check = 0;
		return (0);
	}
	return (1);
}
