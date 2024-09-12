/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:51:48 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/12 18:49:33 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

int	ft_set_quotes_bool(char c, int *in_double_quote, int *in_single_quote)
{
	int	done;

	done = 0;
	if (c == '\'' && !*in_double_quote)
	{
		*in_single_quote = !*in_single_quote;
		done = 1;
	}
	else if (c == '"' && !*in_single_quote)
	{
		*in_double_quote = !*in_double_quote;
		done = 1;
	}
	return (done);
}

int	ft_token_counter_until_redd(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != R_OUT && token->type != R_OUT2
		&& token->type != R_IN && token->type != R_IN2)
	{
		i++;
		token = token->next;
	}
	return (i);
}

bool	ft_see_q_n_s(char a)
{
	if (!a)
		return (FAILURE);
	if (a == '\'' || a == '\"' || a == ' ')
		return (SUCCESS);
	return (FAILURE);
}

void	ft_increment_int(int *c, int *size)
{
	(*c)++;
	(*size)++;
}

void	ft_copy_and_free(char *env_value, char *result, int *j)
{
	char	*mem_free;

	mem_free = env_value;
	if (env_value)
	{
		while (*env_value)
			result[(*j)++] = *env_value++;
	}
	free(mem_free);
}
