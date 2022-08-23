/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:03 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/23 01:51:16 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_args  *ft_corrector(t_args *parse)
{
    parse = ft_merge(parse); // correct parseing
	parse = ft_joiner(parse); // joiner word
    return (parse);
}

static void	lastparse(char *line, t_env	*env, t_exp	*exp)
{
	t_args *parse;
	t_tk	*list;
	t_tk	*tmp;
	(void) exp;

	list = ft_lexer(line);
	tmp = list;
	if (!ft_fullcheck(tmp))
		return ;
	list = ft_expand(list, env);
	parse = ft_initialparsing(list); // parsing list
	parse = ft_corrector(parse); // correct parseing
		// printf("\n\n\n\nggggg\n\n\n\n\n\n");
	if(!ft_strcmp(parse->arg[0], "cd") || !ft_strcmp(parse->arg[0], "pwd")
		|| !ft_strcmp(parse->arg[0], "env") || !ft_strcmp(parse->arg[0], "echo")
		|| !ft_strcmp(parse->arg[0], "export") || !ft_strcmp(parse->arg[0], "unset"))
		ft_builtins(parse, env, exp);
	else
		puts("Invalid");
	ft_redirection(parse);
	printlist(list); // print the lexer list
	ft_printarg(parse); // print the parser list
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
	(void ) env;
	char	*line;
	t_env	*envi;
	t_exp	*exp;

	rl_catch_signals = 0;
	if (ac != 1)
	{
		printf("\033[0;31m Invalid Number Arguments !\n");
		return (1);
	}
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	envi = ft_getenv(env);
	exp = ft_getexp(env);
	while (1)
	{
		line = readline("Minishell-1.0 $> ");
		// if (ft_strcmp(line, "\n"))
		// 	continue;
		if (!line)
			ft_exit();
		lastparse(line, envi, exp);
		add_history (line);
	}
}
