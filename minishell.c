/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:13:03 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/29 18:03:08 by sgmira           ###   ########.fr       */
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

// void	check_file(t_args *args, t_fds	*fds)
// {
// 	while (args)
// 	{
// 		if(args->type == OUT && args->next->type == OUT)
// 			args = args->next;
// 		else if(args->type == OUT && args->next->type == COMMAND)
// 		{
// 			dup2(fds->out_fd, STDOUT_FILENO);
// 			args = args->next;
// 		}
// 		else
// 			break;
// 	}
// }

static void	lastparse(char *line, t_exenv exenv, t_fds	*fds)
{
	// t_args *parse;
	t_tk	*list;
	t_tk	*tmp;
	t_out	*tmp2;
	int		i;
	int 	t = dup(1);
	
	list = ft_lexer(line);
	tmp = list;
	if (!ft_fullcheck(tmp))
		return ;
	list = ft_expand(list, exenv.env);
	exenv.args = ft_initialparsing(list); // parsing list
	exenv.args = ft_corrector(exenv.args); // correct parseing
	i = cmd_num(exenv.args);
	ft_redirection(fds, exenv);
	tmp2 = fds->out;
	while(tmp2)
	{
		printf("%d\n", tmp2->fd);
		tmp2=tmp2->next;
	}
	// ft_printarg(exenv.args); // print the parser list
	// check_file(exenv.args, fds);
	// printf("%s\n", exenv.args->arg[0]);
	if (!check_pipe(exenv.args))
		parse_multicmd(exenv, fds);
	else
	{
		while (exenv.args)
		{
			if((exenv.args->type == OUT && exenv.args->next->type == OUT) || (exenv.args->type == APPEND && exenv.args->next->type == APPEND))
				exenv.args = exenv.args->next;
			else if(exenv.args->type == OUT && exenv.args->next->type == COMMAND)
			{
				fds->out = fds->out->next;
				printf("%d\n", fds->out->fd);
				dup2(fds->out->fd, STDOUT_FILENO);
				exenv.args = exenv.args->next;
			}
			else if(exenv.args->type == APPEND && exenv.args->next->type == COMMAND)
			{
				dup2(fds->ap_fd, STDOUT_FILENO);
				exenv.args = exenv.args->next;
			}
			else
				break;
		}
		if(!ft_strcmp(exenv.args->arg[0], "cd") || !ft_strcmp(exenv.args->arg[0], "pwd")
			|| !ft_strcmp(exenv.args->arg[0], "env") || !ft_strcmp(exenv.args->arg[0], "echo")
			|| !ft_strcmp(exenv.args->arg[0], "export") || !ft_strcmp(exenv.args->arg[0], "unset"))
			ft_builtins(exenv, fds);
		else
			parse_cmd(exenv);
		dup2(t, 1);
		close(t);
	}
	// }
	// printlist(list); // print the lexer list
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
		// line = readline("Minishell-1.0 $> ");
		line = readline("➜ minishell 💩💩$> ");
		if (!line)
			ft_exit();
 
		lastparse(line, exenv, fds);
		add_history (line);
	}
}
