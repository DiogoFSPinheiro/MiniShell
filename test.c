/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:45:35 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/03 10:10:47 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_in(t_token *token, t_env **env)
{
	int		fd;
	pid_t	pid;
	t_token	*cur;
	t_token	*dup;

	fd = STDIN_FILENO;
	cur = token;
	while (cur->type != R_IN)
		cur = cur->next;
	if (cur) // see more than one redirect
	{
		while (cur && cur->type == R_IN)
		{
			cur = cur->next;
			if (cur && cur->data)
			{
				if (fd != STDIN_FILENO)
					close(fd);
				else
					fd = open(cur->data, O_RDONLY);
				if (fd < 0)
				{
					perror("open");
					return ;
				}
			}
			cur = cur->next;
		}
	}
}

//TODO start tomorrow
void	ft_handle_redirects(t_token *token, t_env **env)
{
	int		fd_in;
	int		fd_out;
	int		append;
	pid_t	pid;

	append = 0;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;


}

