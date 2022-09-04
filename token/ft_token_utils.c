/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:34:43 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 15:35:31 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checkpip(int i, t_tk **list)
{
	ft_addtolist(list, ft_input(ft_strdup("|"), PIP));
	return (i + 1);
}

int	ft_checkroutput(int i, t_tk **list)
{
	ft_addtolist(list, ft_input(ft_strdup(">"), ROUTPUT));
	return (i + 1);
}

int	ft_checkrinput(int i, t_tk **list)
{
	ft_addtolist(list, ft_input(ft_strdup("<"), RINPUT));
	return (i + 1);
}

int	ft_checkdinput(int i, t_tk **list)
{
	ft_addtolist(list, ft_input(ft_strdup(">>"), DINPUT));
	return (i + 2);
}

int	ft_checkdoutput(int i, t_tk **list)
{
	ft_addtolist(list, ft_input(ft_strdup("<<"), DOUTPUT));
	return (i + 2);
}

int	ft_checkspace(int i, t_tk **list)
{
	ft_addtolist(list, ft_input(ft_strdup(" "), SP));
	return (i + 1);
}
