/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/23 09:57:34 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	client_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_change_global_err(130);
		ft_printf("\nMiniHell$> ");
	}
}

void	ft_transform_t_to_s(char **str)
{
	char	*temp;
	int		c;

	temp = *str;
	c = 0;
	while (temp[c])
	{
		if (temp[c] == '\t')
			temp[c] = ' ';
		else if (temp[c] == '\'' || temp[c] == '"')
			ft_skip_quotes(temp, &c, temp[c]);
		else if (temp[c])
			c++;
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
			ft_transform_t_to_s(&input);
			token = ft_parser(input);
			if (token)
				ft_execute_in(token, env, 0);
			set_up_sigaction();
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
	ft_change_global_err(0);
	ft_set_fds(&fd_in, &fd_out);
	ft_create_env(envp, &env);
	ft_cicle(fd_in, fd_out, &env);
	return (0);
}
