/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:20:28 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/02 21:44:53 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tk	*ft_token_space(t_tk *list)
{
	t_tk	*new;
	t_tk	*tmp;

	new = list;
	tmp = NULL;
	while (new)
	{
		if (new && (new->token == SQUOTE || new->token == DQUOTE))
			new = new->next;
		if (new && new->next && new->token == SP && new->next->token == SP)
		{
			new->input = ft_strjoin_v2(new->input, new->next->input);
			tmp = new->next;
			new->next = new->next->next;
			free(tmp);
		}
		if (new)
			new = new->next;
	}
	return (list);
}
