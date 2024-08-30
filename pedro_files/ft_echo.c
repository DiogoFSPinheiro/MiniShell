/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:23:17 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/24 15:02:19 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*ft_print_no_dups(char *str, char c)
{
	str++;
	while (*str && str[0] != c)
	{
		write(1, &str[0], 1);
		str++;
	}
	return str;
}

static void	ft_no_quotes(char *str)
{
	while (*str)
	{
		if (str[0] == '"' && *str)
			str = ft_print_no_dups(str, '"');
		if (str[0] == '\'' && *str)
			str = ft_print_no_dups(str, '\'');
		else if ((str[0] != '"' || str[0] == '\'') && *str)
			write(1, &str[0], 1);
		str++;
	}
}

void	ft_echo(t_token *token)
{
	t_token *temp;

	temp = token;
	if (!token->next)
	{
		write(1, "\n", 2);
		return ;
	}
	if (token->next->type == FLAG && ft_strcmp(token->next->data, "-n") == 1)
		temp = temp->next;
	while (temp->next)
	{
		temp = temp->next;
		ft_no_quotes(temp->data);
		if (temp->next)
			write(1, " ", 1);
	}
	if (ft_strcmp(token->next->data, "-n") != 1)
		write(1, "\n", 1); 
}
