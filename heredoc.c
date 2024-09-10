/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:07:30 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/10 12:56:45 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/printf/ft_printf.h"
#include "minishell.h"

void	ft_write_to_file(const char *filename, char *str, t_env *env);
void	ft_change_heredoc(t_token **token, t_env *env);

void	ft_build_heredoc(t_commands **cmd, t_commands *head, t_env *env)
{
	t_token		*token;
	t_token		*token_head;
	t_commands	*command;

	command = (*cmd);
	token = (*cmd)->tokens;
	token_head = token;
	while (command)
	{
		while (token)
		{
			if (token->type == R_IN2)
				ft_change_heredoc(&token, env);
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

void	ft_change_heredoc(t_token **token, t_env *env)
{
	t_token	*changer;
	char	*line = NULL;
	char	*buffer = NULL;

	changer = (*token);
	free(changer->data);
	changer->data = ft_strdup("<");
	changer->type = R_IN;
	buffer = ft_calloc(1, sizeof(char));
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("error");
			break ;
		}
		if (strcmp(line, changer->next->data) == 0)
		{
			free(line);
			break ;
		}
		buffer = ft_strjoin_free(buffer, line);
		buffer = ft_strjoin_free(buffer, "\n");
		free(line);
	}
	if (!line)
	{
		free(buffer);
		return ;
	}
	free(changer->next->data);
	changer->next->data = ft_strdup("heredoc");
	ft_write_to_file(changer->next->data, buffer, env);
	free(buffer);
}

void	ft_write_to_file(const char *filename, char *str, t_env *env)
{
	int		file;
	char	*expanded;

	expanded = ft_expand_variables(str, env);
	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		perror("Error opening file heredoc");
		return ;
	}
	write(file, expanded, strlen(expanded));
	if (close(file) < 0)
	{
		perror("Error closing file heredoc");
	}
	free(expanded);
}
