/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:31:09 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/30 17:10:04 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_and_print(t_env *env)
{
	(void)env;
	return;	
}

void	ft_export(t_token *token, t_env **env)
{
	if (!token->next)
	{
		ft_sort_and_print(env);
		return ;
	}
	if (token && token->next && token->next->type <= FLAG)
		ft_built_err(token, flag_err);
	token = token->next;
	(void)env;
	while (token)
	{
		
		token = token->next;
	}
	return ;
}
	// each command is executed individualy
	// commands cant start with special chars EXEPTIONS _
	//find if there is a equal in each command