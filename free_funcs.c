/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:34:55 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/29 19:12:50 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *stack)
{
	t_token	*current;

	if (NULL == stack)
		return ;
	current = stack;
	while (current)
	{
		if (current->data)
			free(current->data);
		current = current->next;
	}
	free(stack);
	stack = NULL;
}

void	ft_free_env(t_env *env)
{
	t_env	*current;

	if (NULL == env)
		return ;
	current = env;
	while (current)
	{
		if (current->title)
		{
			free(current->title);
			free(current->content);
		}
		current = current->next;
	}
	free(env);
}
