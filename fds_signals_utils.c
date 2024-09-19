/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_signals_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:28:18 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/19 17:29:02 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc_sig(int sig)
{
	static bool		end;	

	if (sig == SIGINT)
	{
		rl_done = 1;
		end = true;
	}
	if (sig == -2)
	{
		end = false;
		rl_event_hook = NULL;
		rl_done = 0;
	}
	if (end == true)
		return (FAILURE);
	return (SUCCESS);
}

void	ft_refresh_fds(int *in, int *out)
{
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
}
