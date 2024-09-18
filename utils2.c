/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:53:08 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/18 15:25:33 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_space_skiper(char *str, int *c)
{
	while (str[*c] == ' ' || str[*c] == '\t')
		(*c)++;
}

void	ft_reset_int(int *c, int *i)
{
	(*c) = 0;
	(*i) = 0;
}

void	ft_count_helper(char *str, int *c, int *size)
{
	if (*c > 0 && str[*c - 1] == ' ' && str[*c + 1] == ' ')
		return ;
	if (*c > 0 && str[*c - 1] != ' ')
		(*size)++;
	if (str[*c + 1] != ' ')
		(*size)++;
}

void	ft_skip_quotes_w(char *input, char **dst, int *c, int *i)
{
	char	w;

	w = input[*c];
	(*dst)[(*i)++] = input[*c];
	(*c)++;
	while (input[*c] || input[*c] != '\0')
	{
		if (input[*c] == w)
		{
			(*dst)[*i] = input[*c];
			return ;
		}
		(*dst)[(*i)++] = input[*c];
		(*c)++;
	}
}

void	ft_space_helper(char *str, char **dst, int *c, int *i)
{
	if (*c > 0 && str[*c - 1] == ' ' && str[*c + 1] == ' ')
	{
		(*dst)[*i] = str[*c];
		return ;
	}
	if (*c > 0 && str[*c - 1] != ' ')
		(*dst)[(*i)++] = ' ';
	(*dst)[*i] = str[*c];
	if (str[*c + 1] != ' ')
		(*dst)[++(*i)] = ' ';
}
