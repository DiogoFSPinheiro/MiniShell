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

void	ft_build_heredoc(t_commands **cmd, t_commands *head)
{
	t_token	*token;
	char	*line = NULL;

	token = (*cmd)->tokens;
	while (1)
	{
		line = readline("> ");

		if (strcmp(line, "ola") == 0)
		{
			free(line);
			break ;
		}
		free(line);

	}
	(*cmd) = head;
	ft_println("%s", (*cmd)->tokens->data);
}
