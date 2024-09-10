/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:07:30 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/10 17:28:12 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_to_file(const char *filename, char *str, t_env *env, bool d);
void	ft_change_heredoc(t_token **token, t_env *env);

void	ft_build_heredoc(t_commands **cmd, t_commands *head, t_env *env)
{
	t_token		*token;
	t_commands	*command;

	command = *cmd;
	while (command)
	{
		token = command->tokens;
		while (token)
		{
			if (token->type == R_IN2)
				ft_change_heredoc(&token, env);
			token = token->next;
		}
		command = command->next;
	}
	*cmd = head;
}

//TODO fix norm
void	ft_change_heredoc(t_token **token, t_env *env)
{
	t_token	*changer;
	char	*line = NULL;
	char	*buffer = NULL;
	bool	d = true;

	changer = (*token);
	free(changer->data);
	changer->data = ft_strdup("<");
	changer->type = R_IN;
	buffer = ft_calloc(1, sizeof(char));
	char	*str = ft_str_no_quotes(changer->next->data);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_println("Error: unexpected EOF");
			break ;
		}
		if (strcmp(line, str) == 0)
		{
			free(line);
			break ;
		}
		buffer = ft_strjoin_free(buffer, line);
		buffer = ft_strjoin_free(buffer, "\n");
		free(line);
	}
	if (*changer->next->data == '\'' || *changer->next->data == '\"')
		d = false;
	free(changer->next->data);
	
	changer->next->data = ft_strdup("heredoc");
	changer->next->type = HEREDOC;
	ft_write_to_file(changer->next->data, buffer, env, d);
	free(buffer);
	free(str);
}

void	ft_write_to_file(const char *filename, char *str, t_env *env, bool d)
{
	int		file;
	char	*expanded;

	expanded = str;
	if (d)
		expanded = ft_expand_variables2(str, env);
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
	if (d)
		free(expanded);
}
