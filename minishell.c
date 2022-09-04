/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:03 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/04 21:30:10 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	out_check(t_fds	**fds)
{
	(*fds)->new_out = (*fds)->out_f->next->fd;
	if ((*fds)->out_f->next)
		(*fds)->out_f = (*fds)->out_f->next;
}

int	check_redirections2(t_exenv *exenv, t_fds	**fds)
{
	if (exenv->args->type == OUT)
		out_check(fds);
	else if (exenv->args->type == APPEND)
	{
		(*fds)->new_out = (*fds)->app_f->next->fd;
		if ((*fds)->app_f->next)
			(*fds)->app_f = (*fds)->app_f->next;
	}
	else if (exenv->args->type == IN)
	{
		(*fds)->new_in = (*fds)->in_f->next->fd;
		if ((*fds)->in_f->next)
			(*fds)->in_f = (*fds)->in_f->next;
	}
	else if (exenv->args->type == HEREDOC)
	{
		(*fds)->new_in = (*fds)->here_f->next->fd;
		if ((*fds)->here_f->next)
			(*fds)->here_f = (*fds)->here_f->next;
	}
	else
		return (-1);
	return (0);
}

void	check_redirections(t_exenv *exenv, t_fds	**fds)
{
	while (exenv->args)
	{
		if (check_redirections2(exenv, fds) == -1)
			break ;
		exenv->args = exenv->args->next;
	}
}

void	check_command(t_exenv *exenv, t_fds	**fds)
{
	if (exenv->args != NULL && exenv->args->type == COMMAND)
	{
		if ((*fds)->new_out != 1)
		{
			dup2((*fds)->new_out, STDOUT_FILENO);
			close((*fds)->new_out);
		}
		if ((*fds)->new_in != 0)
		{
			dup2((*fds)->new_in, STDIN_FILENO);
			close((*fds)->new_in);
		}
		if (!ft_check_builtins(*exenv))
			ft_builtins((*exenv), (*fds));
		else
			parse_cmd((*exenv));
	}
}

void	execution_part(t_exenv *exenv, t_fds **fds, int tmp1, int tmp2)
{
	if (!check_pipe(exenv->args))
		parse_multicmd((*exenv), (*fds));
	else
	{
		check_redirections(exenv, fds);
		check_command(exenv, fds);
		dup2(tmp1, 1);
		close(tmp1);
		dup2(tmp2, 0);
		close(tmp2);
	}
}

static void	lastparse(char *line, t_exenv exenv, t_fds	*fds)
{
	t_tk	*list;
	t_tk	*tmp;
	int		tmp1;
	int		tmp2;

	tmp1 = dup(1);
	tmp2 = dup(0);
	fds->new_out = 1;
	fds->new_in = 0;
	list = ft_lexer(line);
	list = ft_token_space(list);
	tmp = list;
	if (!ft_fullcheck(tmp))
		return ;
	list = ft_expand(list, exenv.env);
	exenv.args = ft_initialparsing(list);
	exenv.args = ft_corrector(exenv.args);
	ft_redirection(fds, exenv);
	execution_part(&exenv, &fds, tmp1, tmp2);
}

void	ft_readline(t_exenv	*exenv, t_fds	**fds)
{
	while (1)
	{
		exenv->line = readline("➜ minishell 💩💩$> ");
		if (!exenv->line)
			my_exit();
		lastparse(exenv->line, (*exenv), (*fds));
		add_history (exenv->line);
		free (exenv->line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_exenv	exenv;
	t_fds	*fds;

	(void)av;
	fds = ft_malloc(sizeof(t_fds));
	exenv.envar = env;
	exenv.shlvl = 1;
	rl_catch_signals = 0;
	g_mode.g_exit = 0;
	g_mode.g_sig = 0;
	if (ac != 1)
	{
		printf("\033[0;31m Invalid Number Arguments !\n");
		return (1);
	}
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	exenv.env = ft_getenv(exenv.envar);
	exenv.exp = ft_getexp(exenv.envar);
	ft_readline(&exenv, &fds);
	ft_freegarbe(g_mode.trash);
}
