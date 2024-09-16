/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:52:30 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/03 22:40:51 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_env(t_env **env, char *command)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		if (ft_strcmp((*env)->title, command) && !ft_strcmp((*env)->title, "_"))
		{
			*env = temp->next;
			free(temp->title);
			free(temp->content);
			free(temp);
		}
		if ((*env) == NULL)
			return ;
		env = &(*env)->next;
	}
}

void	ft_unset(t_env **env, t_token *token)
{
	ft_change_global_err(0);
	if (token->next && token->next->type == FLAG)
	{
		ft_built_err(token, flag_err);
		return ;
	}
	if (!env || !token->next)
		return ;
	token = token->next;
	while (token)
	{
		ft_remove_env(env, token->data);
		token = token->next;
	}
}
