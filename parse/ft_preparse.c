/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:18:10 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/13 20:07:53 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args	*ft_merge(t_args *parse)
{
	t_args	*new;
	t_args	*tmp;

	new = NULL;
	while (parse)
	{
		tmp = parse;
		while (parse && parse->type != PIPE)
		{
			if (parse && (parse->type == IN || parse->type == OUT || parse->type == APPEND || parse->type == HEREDOC))
			{
				if (parse && parse->type == APPEND)
					ft_addbackarg(&new, ft_args_node(parse->arg, APPEND));
				else if (parse && (parse->type == OUT))
					ft_addbackarg(&new, ft_args_node(parse->arg, OUT));
				else if (parse && parse->type == IN)
					ft_addbackarg(&new, ft_args_node(parse->arg, IN));
				else if (parse && parse->type == HEREDOC)
					ft_addbackarg(&new, ft_args_node(parse->arg, HEREDOC));
			}
			parse = parse->next;
		}
		parse = tmp;
		while (parse && parse->type != PIPE)
		{
			if (parse && parse->type == COMMAND)
			{
				if (parse && parse->type == COMMAND)
					ft_addbackarg(&new, ft_args_node(parse->arg, COMMAND));
			}
			parse = parse->next;
		}
		if (parse && parse->type == PIPE)
			ft_addbackarg(&new, ft_args_node(parse->arg, PIPE));
		if (parse)
			parse = parse->next;
	}
	return (new);
}

t_args	*ft_joiner(t_args *parse)
{
	t_args	*tmp;
	t_args	*new;

	tmp = NULL;
	new = parse;
	while (new)
	{
		if (new && new->next && new->type == COMMAND && new->next->type == COMMAND)
		{
			new->arg = ft_join2darray(new->arg, new->next->arg);
			tmp = new->next;
			new->next = new->next->next;
			free(tmp);
		}
		else		
			new = new->next;
	}
	return (parse);
}
