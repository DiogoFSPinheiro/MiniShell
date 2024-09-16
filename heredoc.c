/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:07:30 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/16 18:29:40 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/printf/ft_printf.h"
#include "minishell.h"
#include <unistd.h>

void	ft_write_to_file(const char *filename, char *str, t_env *env, bool d);
void	ft_change_heredoc(t_token **token, t_env *env);
char	*ft_read_heredoc(char *str);

void	ft_build_heredoc(t_commands **cmd, t_commands *head, t_env *env)
{
	t_token		*token;
	t_commands	*command;

	set_heredoc_signals();
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

void	ft_change_heredoc(t_token **token, t_env *env)
{
	t_token	*changer;
	char	*buffer;
	bool	d;
	char	*str;

	d = true;
	changer = (*token);
	free(changer->data);
	changer->data = ft_strdup("<");
	changer->type = R_IN;
	str = ft_str_no_quotes(changer->next->data);
	buffer = ft_read_heredoc(str);
	if (*changer->next->data == '\'' || *changer->next->data == '\"')
		d = false;
	free(changer->next->data);
	changer->next->data = ft_strdup("heredoc");
	changer->next->type = HEREDOC;
	ft_write_to_file(changer->next->data, buffer, env, d);
	free(buffer);
	free(str);
}

char	*ft_read_heredoc(char *str)
{
	char	*buffer;
	char	*line;

	buffer = ft_calloc(1, sizeof(char));
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_println("Error: unexpected EOF -> (wanted `%s')", str);
			break ;
		}
		if (ft_strcmp(line, str) == SUCCESS)
		{
			free(line);
			break ;
		}
		buffer = ft_strjoin_free(buffer, line);
		buffer = ft_strjoin_free(buffer, "\n");
		free(line);
	}
	return (buffer);
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
