/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:07:27 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/18 16:38:24 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_error;

void	ft_make_temp(t_commands *cmd, t_commands *temp, t_token *tokens)
{
	t_token	*new;
	t_token *current;

	tokens = cmd->tokens;
	if (!tokens)
	{
		temp->tokens = NULL;
		return;
	}
	temp->tokens = malloc(sizeof(t_token));
	temp->tokens->data = ft_strdup(tokens->data);
	temp->tokens->type = tokens->type;
	temp->tokens->next = NULL;
	current = temp->tokens;
	tokens = tokens->next;
	while (tokens)
	{
		new = malloc(sizeof(t_token));
		new->data = ft_strdup(tokens->data);
		new->type = tokens->type;
		new->next = NULL;
		current->next = new;
		current = new;
		tokens = tokens->next;
	}
}

// cn is the token for clean up renamed because line was too long
void	ft_execute_n_exit(t_commands *cmd, t_env **env, int *fd, t_commands *cn)
{
	t_commands	*temp;
	t_token		*tokens;

	temp = malloc(sizeof(t_commands));
	temp->tokens = NULL;
	temp->next = NULL;
	tokens = NULL;
	ft_make_temp(cmd, temp, tokens);
	if (cmd->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		g_error = 0;
	}
	close(fd[0]);
	close(fd[1]);
	ft_free_cmd(cn);
	ft_handle_redirects(temp->tokens);
	if (ft_built_in(temp, env) != SUCCESS)
		ft_send_to_execve(temp->tokens, *env);
	ft_free_cmd(temp);
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
