/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:53:01 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/21 11:06:51 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>

void	ft_clean_up(t_commands *cmd, t_env **env)
{
	ft_free_cmd(cmd);
	ft_free_env(*env);
}

bool	is_all_number(char *str)
{
	int	c;

	c = 0;
	while (str[c])
	{
		if (!ft_isdigit(str[c]))
			return (FAILURE);
		c++;
	}
	return (SUCCESS);
}

void	ft_exit(t_commands *cmd, t_env **env)
{
	if (cmd->tokens->next == NULL)
	{
		ft_clean_up(cmd, env);
		exit(ft_change_global_err(-1));
	}
	else if (cmd->tokens->next && !cmd->tokens->next->next)
	{
		if (is_all_number(cmd->tokens->next->data) == FAILURE)
			ft_built_err(cmd->tokens, alpha_on_num);
		else
			ft_change_global_err(ft_atoi(cmd->tokens->next->data));
		ft_clean_up(cmd, env);
		exit(ft_change_global_err(-1));
	}
	else if (cmd->tokens->next && cmd->tokens->next->next != NULL)
	{
		ft_println("exit");
		ft_built_err(cmd->tokens, args_err);
	}
}
