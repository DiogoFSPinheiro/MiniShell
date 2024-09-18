/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:53:01 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/17 23:50:12 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_error;

// Estou com o mesmo problema de antes em que quando liberto o cmd dentro de pipes
// ja perdi o primeiro cmd 
void	ft_exit(t_commands *cmd, t_env **env)
{
	int exit_code;

	if (cmd->tokens->next == NULL)
	{
		ft_free_cmd(cmd);
		ft_free_env(*env);
		exit(g_error);
	}
	else if (cmd->tokens->next)
	{
		exit_code = ft_atoi(cmd->tokens->next->data);
		ft_free_env(*env);
		ft_free_cmd(cmd);
		exit(exit_code);
	}
	else if (cmd->tokens->next && cmd->tokens->next->next != NULL)
	{
		ft_built_err(cmd->tokens, args_err);
	}
}