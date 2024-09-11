/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:06:05 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/11 16:38:39 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_redirect(t_token *token);

int	ft_handle_redirects(t_commands *cmd)
{
	t_token	*token;

	token = cmd->tokens;
	while (token)
	{
		if (token->type == R_IN || token->type == R_OUT
			|| token->type == R_OUT2)
		{
			if (ft_do_redirect(token) == FAILURE)
				return (FAILURE);
			token = token->next;
		}
		token = token->next;
	}
	return (SUCCESS);
}

int	ft_redirect_out(t_token *token)
{
	int		fd;

	if (token->type == R_OUT2)
		fd = open(token->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(token->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd > 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (fd);
}

int	ft_redirect_in(t_token *token)
{
	int		fd;

	fd = open(token->next->data, O_RDONLY);
	if (fd > 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (fd);
}

int	ft_do_redirect(t_token *token)
{
	int	fd;

	fd = -1;
	if (token->type == R_OUT || token->type == R_OUT2)
		fd = ft_redirect_out(token);
	else if (token->type == R_IN)
		fd = ft_redirect_in(token);
	if (fd == -1)
	{
		ft_printf_err("error");
		return (FAILURE);
	}
	return (SUCCESS);
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
