/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:45:35 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/02 19:09:08 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_in(t_token *token, t_env **env)
{
	int		fd;
	pid_t	pid;
	t_token	*cur;
	t_token	*dup;

	fd = STDIN_FILENO;
	cur = token;
	while (cur->type != R_IN)
		cur = cur->next;
	if (cur) // see more than one redirect
	{
		while (cur && cur->type == R_IN)
		{
			cur = cur->next;
			if (cur && cur->data)
			{
				if (fd != STDIN_FILENO)
					close(fd);
				else
					fd = open(cur->data, O_RDONLY);
				if (fd < 0)
				{
					perror("open");
					return ;
				}
			}
			cur = cur->next;
		}
	}

	pid = fork();
	if (pid == 0) // Child process
	{
		dup = ft_token_dup(token);
		if (fd != STDIN_FILENO)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (ft_built_in(dup, env) == 1)
			ft_send_to_execve(dup, *env);

		free_tokens(token);
		free_tokens(dup);
		ft_free_env(*env);
		exit(0);
	}
	else // Parent process
	{
		wait(NULL);
		if (fd != STDOUT_FILENO)
			close(fd);
	}
}

//TODO start tomorrow
void	ft_handle_redirects(t_token *token, t_env **env)
{
	int		fd_in;
	int		fd_out;
	int		append;
	pid_t	pid;

	append = 0;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;

	pid = fork();
	if (pid == 0) // Child process
	{
		dup = ft_token_dup(token);
		if (fd != STDIN_FILENO)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (ft_built_in(dup, env) == 1)
			ft_send_to_execve(dup, *env);

		free_tokens(token);
		free_tokens(dup);
		ft_free_env(*env);
		exit(0);
	}
	else // Parent process
	{
		wait(NULL);
		if (fd != STDOUT_FILENO)
			close(fd);
	}
}

}
