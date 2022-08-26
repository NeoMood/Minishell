/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:03 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/26 17:54:57 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_args  *ft_corrector(t_args *parse)
{
    parse = ft_merge(parse); // correct parseing
	parse = ft_joiner(parse); // joiner word
    return (parse);
}

int	check_pipe(t_args *args)
{
	while (args)
	{
		if (args->type == PIPE)
			return (0);
		args = args->next;
	}
	return (1);
}

static void	lastparse(char *line, t_exenv exenv)
{
	// t_args *parse;
	t_tk	*list;
	t_tk	*tmp;

	list = ft_lexer(line);
	tmp = list;
	if (!ft_fullcheck(tmp))
		return ;
	list = ft_expand(list, exenv.env);
	exenv.args = ft_initialparsing(list); // parsing list
	exenv.args = ft_corrector(exenv.args); // correct parseing
	ft_redirection(&exenv);
	if (!check_pipe(exenv.args))
		parse_multicmd(exenv);
	else
	{
		if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
			|| !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
			|| !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
			ft_builtins(exenv);
		else
			parse_cmd(exenv);
	}
	// printlist(list); // print the lexer list
	// ft_printarg(exenv.args); // print the parser list
}

static void	ft_exit(void)
{
	rl_on_new_line();
	rl_redisplay();
	printf("exit\n");
	exit (1);
}

int	main(int ac, char **av, char **env)
{
	(void)	av;
	char	*line;
	t_exenv exenv;

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
		// line = readline("Minishell-1.0 $> ");
		line = readline("➜ minishell 💩💩$> ");
		if (!line)
			ft_exit();
		if (ft_strncmp(line, "\n", 1) && !line[1])
			continue ;
		lastparse(line, exenv);
		add_history (line);
	}
}
