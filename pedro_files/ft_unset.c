/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:52:30 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/29 19:32:01 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_env **env, t_token *token)
{
	t_env	*temp;
	
	temp = *env;
	ft_printf("Entrou  %s\n", (*env)->title);
	if (!env || !token->next)
		return ;
	if (ft_strcmp((*env)->title, token->next->data))
	{	
	 	*env = temp->next;
	 	free(temp->title);
		free(temp->content);
		temp = NULL;
	 	return ;
	}
	else
		while (env)
		{	
			if (ft_strcmp(temp->title, token->next->data))
				temp = temp->next;

			*env = (*env)->next;
			//break ;
		//	env = env->next;	
		}
	return ;
}