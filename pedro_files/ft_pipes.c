/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.co>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:07:27 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/10 23:32:04 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe_it(t_commands *cmd, t_env **env)
{
	int		fd[2];
	int		previous_fd;
	pid_t	my_child;

	previous_fd = -1;
	while (cmd)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		my_child = fork();
		if (my_child == -1)
			exit(EXIT_FAILURE);
		if (my_child == 0)
		{
			if (previous_fd != -1)
			{
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}
			if (cmd->next != NULL)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (!ft_built_in(cmd->tokens, env))
				ft_send_to_execve(cmd->tokens, *env);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]);
			if (previous_fd != -1)
				close(previous_fd);
			previous_fd = fd[0];
			cmd = cmd->next;
		}
	}
	while (wait(NULL) > 0);
	return (my_child);
}

