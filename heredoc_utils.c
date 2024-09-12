/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:34:51 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/11 16:38:58 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_no_quotes(char *str)
{
	char	*trimed;
	int		c;
	int		i;
	int		max;

	trimed = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	c = 0;
	i = 0;
	max = ft_strlen(str);
	if (*str == '\'' || *str == '\"')
	{
		c++;
		max--;
	}
	while (c < max)
	{
		trimed[i] = str[c];
		c++;
		i++;
	}
	return (trimed);
}
