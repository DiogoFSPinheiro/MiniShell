/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:31:09 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/30 16:22:12 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_token *token, t_env **env)
{
	// each command is executed individualy
	// commands cant start with special chars EXEPTIONS _
	//find if there is a equal in each command
	while (token)
	{
		token = token->next;
	}
	return ;
}
