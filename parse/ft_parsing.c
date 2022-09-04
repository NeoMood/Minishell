/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:40:32 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 15:34:11 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_collectword(t_tk **list, t_args **word)
{
	char	**tmp1;
	char	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	while ((*list) && ((*list)->token == WORD || (*list)->token == VAR
			|| (*list)->token == SP || (*list)->token == SQUOTE))
	{
		tmp = ft_strjoin_v2(tmp, (*list)->input);
		if ((*list) && (*list)->next && (*list)->next->token == SP)
			(*list) = (*list)->next;
		tmp1 = ft_table(tmp1, tmp);
		tmp = NULL;
		(*list) = (*list)->next;
	}
	tmp1 = ft_table(tmp1, tmp);
	ft_addbackarg(word, ft_args_node(tmp1, COMMAND));
}

void	ft_collectpip(t_tk **list, t_args **pip)
{
	char	**tmp1;

	tmp1 = NULL;
	(*list) = (*list)->next;
	tmp1 = ft_table (NULL, NULL);
	ft_addbackarg(pip, ft_args_node(tmp1, PIPE));
}

void	ft_collectinput(t_tk **list, t_args **redirection)
{
	char	**tmp1;
	char	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	(*list) = (*list)->next;
	if ((*list) && (*list)->token == SP)
		(*list) = (*list)->next;
	while ((*list) && ((*list)->token == WORD
			|| (*list)->token == VAR || (*list)->token == SQUOTE))
	{
		if ((*list)->token == SP)
			(*list) = (*list)->next;
		tmp = ft_strjoin_v2 (tmp, (*list)->input);
		(*list) = (*list)->next;
	}
	tmp1 = ft_table(tmp1, tmp);
	ft_addbackarg(redirection, ft_args_node(tmp1, IN));
}

void	ft_collectoutput(t_tk **list, t_args **redirection)
{
	char	**tmp1;
	char	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	(*list) = (*list)->next;
	if ((*list) && (*list)->token == SP)
		(*list) = (*list)->next;
	while ((*list) && ((*list)->token == WORD
			|| (*list)->token == VAR || (*list)->token == SQUOTE))
	{
		if ((*list)->token == SP)
			(*list) = (*list)->next;
		tmp = ft_strjoin_v2 (tmp, (*list)->input);
		(*list) = (*list)->next;
	}
	tmp1 = ft_table(tmp1, tmp);
	ft_addbackarg(redirection, ft_args_node(tmp1, OUT));
}

void	ft_collectappend(t_tk **list, t_args **redirection)
{
	char	**tmp1;
	char	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	(*list) = (*list)->next;
	if ((*list) && (*list)->token == SP)
		(*list) = (*list)->next;
	while ((*list) && ((*list)->token == WORD
			|| (*list)->token == VAR || (*list)->token == SQUOTE))
	{
		tmp = ft_strjoin_v2 (tmp, (*list)->input);
		(*list) = (*list)->next;
	}
	tmp1 = ft_table(tmp1, tmp);
	ft_addbackarg(redirection, ft_args_node(tmp1, APPEND));
}

void	ft_collectheredoc(t_tk **list, t_args **herdoc)
{
	char	**tmp1;
	char	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	(*list) = (*list)->next;
	if ((*list) && (*list)->token == SP)
		(*list) = (*list)->next;
	while ((*list) && ((*list)->token == WORD
			|| (*list)->token == VAR || (*list)->token == SQUOTE))
	{
		tmp = ft_strjoin_v2 (tmp, (*list)->input);
		(*list) = (*list)->next;
	}
	tmp1 = ft_table(tmp1, tmp);
	ft_addbackarg(herdoc, ft_args_node(tmp1, HEREDOC));
}

t_args	*ft_initialparsing(t_tk *list)
{
	t_args	*parse;

	parse = NULL;
	while (list)
	{
		if (list && (list->token == WORD
				|| list->token == SQUOTE || list->token == VAR))
			ft_collectword(&list, &parse);
		else if (list && list->token == PIP)
			ft_collectpip(&list, &parse);
		else if (list && list->token == RINPUT)
			ft_collectinput(&list, &parse);
		else if (list && list->token == ROUTPUT)
			ft_collectoutput(&list, &parse);
		else if (list && list->token == DOUTPUT)
			ft_collectheredoc(&list, &parse);
		else if (list && list->token == DINPUT)
			ft_collectappend(&list, &parse);
		else
			list = list->next;
	}
	return (parse);
}
