/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:14:41 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/19 18:16:58 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_treated_len(char *cont)
{
	int		i;
	int		len;
	int		open;
	char	c;

	i = 0;
	len = 0;
	open = 0;
	c = '\0';
	while (cont[i++])
	{
		if (open && cont[i] == c)
			open = 0;
		else if (!open && (cont[i] == '\'' || cont[i] == '\"'))
		{
			open = 1;
			c = cont[i];
		}
		else
			len++;
	}
	return (len);
}

int	ft_valid_title(char *str)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	if (str[i] == '_')
		i++;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=' && i > 0)
			return (1);
		if (str[i] == '=' && i > 0)
			return (1);
		if (ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_finecont_nomorequotes(char *cont, int i, int j, int open)
{
	char	*treated_cont;
	char	c;

	c = '\0';
	treated_cont = (char *)malloc((count_treated_len(cont) + 1) * sizeof(char));
	if (!treated_cont)
		return (NULL);
	while (cont[i])
	{
		if (open && cont[i] == c)
			open = 0;
		else if (!open && (cont[i] == '\'' || cont[i] == '\"'))
		{
			open = 1;
			c = cont[i];
		}
		else
			treated_cont[j++] = cont[i];
		i++;
	}
	treated_cont[j] = '\0';
	free(cont);
	return (treated_cont);
}
