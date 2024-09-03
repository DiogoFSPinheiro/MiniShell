/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:23:17 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/03 14:14:49 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>


static void	ft_no_quotes(char *str)
{
	unsigned long	c;
	bool			cut;

	c = 0;
	cut = false;
	if (str[0] == '\'' || str[0] == '\"')
		cut = true;
	while (str[c])
	{
		if (cut)
		{
			if (c != 0 && c != ft_strlen(str) - 1)
				write(1, &str[c], 1);
		}
		else
			write(1, &str[c], 1);
		c++;
	}
}

bool	ft_see_echo_flag(t_token **token)
{
	if ((*token)->next->type == FLAG
		&& ft_strcmp((*token)->next->data, "-n") == 1)
	{
		(*token) = (*token)->next;
		return (true);
	}
	return (false);
}

void	ft_echo(t_token *token)
{
	bool	first;
	bool	flag;

	flag = false;
	first = true;
	if (!token->next)
	{
		write(1, "\n", 2);
		return ;
	}
	flag = ft_see_echo_flag(&token);
	while (token->next)
	{
		token = token->next;
		if (token->type == R_OUT2 || token->type == R_OUT)
			token = token->next->next;
		if (!token)
			break ;
		if (token->type == STR && first == false)
			write(1, " ", 1);
		ft_no_quotes(token->data);
		first = false;
	}
	if (!flag)
		write(1, "\n", 1);
}
