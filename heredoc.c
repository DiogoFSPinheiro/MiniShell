/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:07:30 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/05 19:31:17 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_to_file(const char *filename, const char *str);
void	ft_change_heredoc(t_token **token);

void	ft_build_heredoc(t_commands **cmd, t_commands *head)
{
	t_token	*token;
	t_token	*token_head;
	t_commands *command;

	command = (*cmd);
	token = (*cmd)->tokens;
	token_head = token;
	while(command)
	{
		while (token)
		{
			if (token->type == R_IN2)
				ft_change_heredoc(&token);
			token = token->next;
		}
		token = token_head;
		(*cmd)->tokens = token_head;
		command = command->next;
	}
	token = token_head;
	(*cmd)->tokens = token_head;
	(*cmd) = head;
}

void	ft_change_heredoc(t_token **token)
{
	t_token *changer;
	char	*line = NULL;
	char 	*buffer = NULL;
	
	changer = (*token);
	free(changer->data);
	changer->data = ft_strdup("<");
	changer->type= R_IN;
	buffer = ft_calloc(1, sizeof(char));
	while (1)
	{
		line = readline("> ");
		if (strcmp(line, changer->next->data) == 0)
		{
			free(line);
			break ;
		}
		buffer = ft_strjoin_free(buffer, line);
		buffer = ft_strjoin_free(buffer, "\n");
		free(line);
	}
	free(changer->next->data);
	changer->next->data = ft_strdup("heredoc.txt");
	write_to_file(changer->next->data, buffer);
	free(buffer);
}

void	write_to_file(const char *filename, const char *str)
{
	int file;

	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		perror("Error opening file heredoc");
		return;
	}
	write(file, str, strlen(str));
	if (close(file) < 0)
	{
		perror("Error closing file heredoc");
	}
}
