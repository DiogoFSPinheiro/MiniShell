/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:34:55 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/30 10:36:05 by pebarbos         ###   ########.fr       */
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

void	free_cmd_tokens(t_token *stack)
{
	t_token	*current;
	t_token	*next;

	if (NULL == stack)
		return ;
	current = stack;
	while (current)
	{
		next = current->next;
		if (current->data)
			free(current->data);
		free(current);  
		current = next;    
	}
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

void	ft_free_cmd(t_commands *cmd)
{
	t_commands	*cur;

	if (cmd == NULL)
		return ;
	cur = cmd;
	while (cur)
	{
		free_cmd_tokens(cur->tokens);
		cur = cur->next; 
	}
	free(cmd);
}
