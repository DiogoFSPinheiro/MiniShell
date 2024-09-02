/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:06:05 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/02 17:46:03 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "minishell.h"

t_token	*ft_token_dup(t_token *token);

void	ft_redirect_out(t_token *token, t_env **env)
{
	int		fd;
	int		append;
	pid_t	pid;
	t_token	*cur;
	t_token	*dup;

	fd = STDOUT_FILENO;
	append = 0;
	cur = token;
	while (cur->type != R_OUT && cur->type != R_OUT2)
		cur = cur->next;

	if (cur) // see more than one redirect
	{
		while (cur && (cur->type == R_OUT || cur->type == R_OUT2))
		{
			if (cur->type == R_OUT2)
				append = 1;
			else
				append = 0;
			cur = cur->next;
			if (cur && cur->data)
			{
				if (fd != STDOUT_FILENO)
					close(fd);
				if (append)
					fd = open(cur->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					fd = open(cur->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);

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
		if (fd != STDOUT_FILENO)
		{
			dup2(fd, STDOUT_FILENO);
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

t_token	*ft_token_dup(t_token *token)
{
	int		size;
	int		i;
	t_token	*dup;
	t_token	*head;

	size = ft_token_counter_until_redd(token);
	if (size == 0)
		return (NULL);
	i = 0;
	dup = ft_calloc(size, sizeof(t_token));
	head = dup;
	while (i < size && token)
	{
		dup->data = ft_strdup(token->data);
		dup->type = token->type;
		if (i < size - 1)
			dup->next = dup + 1;
		else
			dup->next = NULL;
		token = token->next;
		dup = dup->next;
		i++;
	}
	return (head);
}
