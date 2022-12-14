/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:03 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/09 17:47:53 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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
	if (!ft_redirection(fds, exenv))
		execution_part(&exenv, &fds, tmp1, tmp2);
}

void	ft_readline(t_exenv	*exenv, t_fds	**fds)
{
	while (1)
	{
		exenv->line = readline("➜ minishell $> ");
		if (!exenv->line)
			my_exit();
		lastparse(exenv->line, (*exenv), (*fds));
		add_history (exenv->line);
		free (exenv->line);
	}
	ft_show_c();
}

void	update_shlvl(t_exenv	exenv)
{
	while (exenv.env)
	{
		if (!ft_strcmp(exenv.env->key, "SHLVL"))
		{
			if ((ft_atoi(exenv.env->value) < 0))
				exenv.env->value = ft_itoa(0);
			else
				exenv.env->value = ft_itoa((ft_atoi(exenv.env->value) + 1));
		}
		exenv.env = exenv.env->next;
	}
	while (exenv.exp)
	{
		if (!ft_strcmp(exenv.exp->key, "SHLVL"))
		{
			if ((ft_atoi(exenv.exp->value) < 0))
				exenv.exp->value = ft_itoa(0);
			else
				exenv.exp->value = ft_itoa((ft_atoi(exenv.exp->value) + 1));
		}
		exenv.exp = exenv.exp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_exenv	exenv;
	t_fds	*fds;

	(void)av;
	fds = malloc(sizeof(t_fds));
	ft_addbackthegarbe(&g_mode.trash, ft_newgarbage(fds));
	exenv.envar = env;
	g_mode.g_exit = 0;
	g_mode.g_sig = 0;
	g_mode.g_check = 0;
	ft_hide_c();
	if (ac != 1)
	{
		printf("\033[0;31m Invalid Number Arguments !\n");
		return (1);
	}
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	exenv.env = ft_getenv(exenv.envar);
	exenv.exp = ft_getexp(exenv.envar);
	update_shlvl(exenv);
	ft_readline(&exenv, &fds);
	ft_freegarbe(g_mode.trash);
}
