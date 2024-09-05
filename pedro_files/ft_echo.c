/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:23:17 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/05 18:19:29 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_no_quotes(char *str);
static bool	ft_see_echo_flag(t_token **token);
static void	ft_see_if_print(t_token **token, bool *first);

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
	while (token && token->next)
	{
		ft_see_if_print(&token, &first);
		first = false;
	}
	if (!flag)
		write(1, "\n", 1);
}

static void	ft_no_quotes(char *str)
{
	unsigned long	c;
	bool			cut;

	c = 0;
	cut = false;
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

static bool	ft_see_echo_flag(t_token **token)
{
	if ((*token)->next->type == FLAG
		&& ft_strcmp((*token)->next->data, "-n") == 1)
	{
		(*token) = (*token)->next;
		return (true);
	}
	return (false);
}

static void	ft_see_if_print(t_token **token, bool *first)
{
	*token = (*token)->next;
	while (*token && ((*token)->type == R_OUT2 || (*token)->type == R_OUT))
		*token = (*token)->next->next;
	if (!*token)
		return ;
	if ((*token)->type == STR && !(*first))
		write(1, " ", 1);
	if ((*token)->type == STR)
		ft_no_quotes((*token)->data);

}
