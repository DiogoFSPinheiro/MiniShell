/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/17 17:19:55 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error = 0;

void	client_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf("\nMiniHell$> ");
	}
	if (sig == SIGQUIT)
		ft_println("exit");
}

void	ft_set_fds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

void	ft_refresh_fds(int *in, int *out)
{
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
}

int	main(int c, char **v, char **envp)
{
	char				*input;
	t_token				*token;
	t_env				*env;
	struct sigaction	sa;
	int					fd_in;
	int					fd_out;

	(void)c;
	(void)v;
	sigemptyset(&sa.sa_mask);
	set_up_sigaction(&sa);
	ft_set_fds(&fd_in, &fd_out);
	ft_create_env(envp, &env);
	while (1)
	{
		ft_refresh_fds(&fd_in, &fd_out);
		input = readline("MiniHell$> ");
		if (input == NULL || ft_strcmp(input, "exit") == SUCCESS)
		{
			free(input);
			ft_free_env(env);
			ft_println("exit");
			break ;
		}
		else if (*input)
		{
			token = ft_parser(input);
			if (token)
				ft_execute_in(token, &env);
			unlink("heredoc");
			free(input);
		}
	}
	return (0);
}


