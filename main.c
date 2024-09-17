/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/17 19:05:39 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error = 0;

void	ft_refresh_fds(int *in, int *out)
{
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
}

void	client_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf("\nMiniHell$> ");
	}

}

void	ft_cicle(int fd_in, int fd_out, t_env **env)
{
	char				*input;
	t_token				*token;

	while (1)
	{
		ft_refresh_fds(&fd_in, &fd_out);
		input = readline("MiniHell$> ");
		if (input == NULL)
		{
			free(input);
			ft_free_env(*env);
			ft_println("exit");
			break ;
		}
		else if (*input)
		{
			token = ft_parser(input);
			if (token)
				ft_execute_in(token, env);
			unlink("heredoc");
			free(input);
		}
	}
}

int	main(int c, char **v, char **envp)
{
	t_env				*env;
	int					fd_in;
	int					fd_out;

	(void)c;
	(void)v;
	set_up_sigaction();
	ft_set_fds(&fd_in, &fd_out);
	ft_create_env(envp, &env);
	ft_cicle(fd_in, fd_out, &env);
	return (0);
}

