/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:03 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/01 00:31:05 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lastparse(char *line, t_exenv exenv, t_fds	*fds)
{
	t_tk	*list;
	t_tk	*tmp;
	int 	tmp1;
	// int		i;
	
	tmp1 = dup(1);
	list = ft_lexer(line);
	list = ft_token_space(list);
	tmp = list;
	if (!ft_fullcheck(tmp))
		return ;
	list = ft_expand(list, exenv.env);
	exenv.args = ft_initialparsing(list);
	exenv.args = ft_corrector(exenv.args);
	(void) fds;
	// i = cmd_num(exenv.args);
	ft_redirection(fds, exenv);
	if (!check_pipe(exenv.args))
		parse_multicmd(exenv, fds);
	else
	{
		while (exenv.args)
		{
			if((exenv.args->type == OUT && exenv.args->next->type == OUT))
			{
				dup2(fds->out_f->next->fd, STDOUT_FILENO);
				close(fds->out_f->next->fd);
				fds->out_f = fds->out_f->next;
				exenv.args = exenv.args->next;
			}
			else if(exenv.args->type == OUT && exenv.args->next->type == COMMAND)
			{
				dup2(fds->out_f->next->fd, STDOUT_FILENO);
				close(fds->out_f->next->fd);
				exenv.args = exenv.args->next;
			}
			else if(exenv.args->type == APPEND && exenv.args->next->type == APPEND)
			{
				dup2(fds->app_f->next->fd, STDOUT_FILENO);
				close(fds->app_f->next->fd);
				fds->app_f = fds->app_f->next;
				exenv.args = exenv.args->next;
			}
			else if(exenv.args->type == APPEND && exenv.args->next->type == COMMAND)
			{
				dup2(fds->app_f->next->fd, STDOUT_FILENO);
				close(fds->app_f->next->fd);
				exenv.args = exenv.args->next;
			}
			else
				break;
		}
		if (exenv.args != NULL && exenv.args->type == COMMAND)
		{
			if (!ft_check_builtins(exenv))
				ft_builtins(exenv, fds);
			else
				parse_cmd(exenv);
		}
		dup2(tmp1, 1);
		close(tmp1);
	}
	// printlist(list); // print the lexer list
	ft_printarg(exenv.args);
}

int	main(int ac, char **av, char **env)
{
	(void)	av;
	t_exenv exenv;
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	exenv.envar = env;
	exenv.shlvl = 1;
	rl_catch_signals = 0;
	if (ac != 1)
	{
		printf("\033[0;31m Invalid Number Arguments !\n");
		return (1);
	}
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	exenv.env = ft_getenv(exenv.envar);
	exenv.exp = ft_getexp(exenv.envar);
	while (1)
	{
		exenv.line = readline("➜ minishell 💩💩$> ");
		if (!exenv.line)
			my_exit();
		lastparse(exenv.line, exenv, fds);
		add_history (exenv.line);
	}
}
