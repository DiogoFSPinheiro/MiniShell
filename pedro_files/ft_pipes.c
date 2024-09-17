/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:07:27 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/17 16:08:00 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_error;
// cn is the token for clean up renamed because line was too long
void	ft_execute_n_exit(t_commands *cmd, t_env **env, int *fd, t_commands *cn)
{
	if (cmd->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_handle_redirects(cmd->tokens);
	if (ft_built_in(cmd->tokens, env) != SUCCESS)
		ft_send_to_execve(cmd->tokens, *env);
	ft_free_cmd(cn);
	ft_free_env(*env);
	exit(g_error);
}

int	ft_create_child(void)
{
	int	my_child;
	
	my_child = fork();
	if (my_child == -1)
		exit(EXIT_FAILURE);
	return (my_child);
}

t_commands	*ft_do_parent(int *previous_fd, int fd[2], t_commands *cmd)
{
	close(fd[1]);
	if (*previous_fd != -1)
		close(*previous_fd);
	*previous_fd = fd[0];
	cmd = cmd->next;
	return (cmd);
}

void	ft_wait_and_get_err()
{
	int status;
		
	while (wait(&status) > 0);
	g_error = WEXITSTATUS(status);
	return ;
}

void	ft_pipe_it(t_commands *cmd, t_env **env)
{
	int			fd[2];
	int			previous_fd;
	int			my_child;
	t_commands	*delete_me;

	previous_fd = -1;
	delete_me = cmd;
	while (cmd)
	{
		if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
		my_child = ft_create_child();
		if (my_child == 0)
		{
			if (previous_fd != -1)
			{
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}
			ft_execute_n_exit(cmd, env, fd, delete_me);
		}
		else
			cmd = ft_do_parent(&previous_fd, fd, cmd);
	}
	ft_wait_and_get_err();
}


