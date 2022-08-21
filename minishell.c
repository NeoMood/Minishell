/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:03 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/21 16:48:22 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_args  *ft_corrector(t_args *parse)
{
    parse = ft_merge(parse); // correct parseing
	parse = ft_joiner(parse); // joiner word
    return (parse);
}

static void	lastparse(char *line, char **env)
{
	t_env	*envi;
	t_exp	*exp;
	t_args *parse;
	t_tk	*list;
	t_tk	*tmp;
	
	envi = ft_getenv(env);
	exp = env_to_exp(envi);
	list = ft_lexer(line);
	tmp = list;
	if (!ft_fullcheck(tmp))
		return ;
	list = ft_expand(list, envi);
	parse = ft_initialparsing(list); // parsing list
	parse = ft_corrector(parse); // correct parseing
	
	ft_builtins(parse, envi, exp);
	// ft_redirection(parse);
	// printlist(list); // print the lexer list
	// ft_printarg(parse); // print the parser list
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

	rl_catch_signals = 0;
	if (ac != 1)
	{
		printf("\033[0;31m Invalid Number Arguments !\n");
		return (1);
	}
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("Minishell-1.0 $> ");
		if (!line)
			ft_exit();
		lastparse(line, env);
		add_history (line);
	}
}
