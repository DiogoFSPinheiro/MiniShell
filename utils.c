/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:57:32 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/18 15:25:26 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	c;

	c = 0;
	if (ft_strlen(s2) > ft_strlen(s1))
		return (FAILURE);
	while (s1[c])
	{
		if (s1[c] != s2[c])
			return (FAILURE);
		c++;
	}
	return (SUCCESS);
}

int	ft_check_triples(char *input)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (c < 2 && input[c + 1] != '\0')
	{
		if (input[c] == input[c + 1])
			i++;
		c++;
	}
	if (i == 2)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_space_redirect(char *input)
{
	int		c;

	c = 0;
	if (input[c] == '>' || input[c] == '<')
		c++;
	while (input[c] == ' ' || input[c] == '\t')
		c++;
	if (input[c] == '>' || input[c] == '<')
		return (FAILURE);
	return (SUCCESS);
}

char	*ft_strcat(char *str1, char *str2)
{
	int		size;
	int		c;
	char	*str;

	c = 0;
	size = ft_strlen(str1) + ft_strlen(str2);
	str = ft_calloc(size + 1, sizeof(char));
	if (str1)
	{
		while (*str1)
			str[c++] = *str1++;
	}
	if (str2)
	{
		while (*str2)
			str[c++] = *str2++;
	}
	str[c] = '\0';
	return (str);
}

char	*ft_array_strjoin(char **array)
{
	int		size;
	int		c;
	int		i;
	char	*str;
	char	*temp;

	size = 0;
	c = -1;
	i = -1;
	while (array[++c] != NULL)
		size += ft_strlen(array[c]) + 1;
	str = ft_calloc(size + 1, sizeof(char));
	temp = str;
	c = -1;
	while (array[++c] != NULL)
	{
		while (array[c][++i] != '\0')
			*str++ = array[c][i];
		i = -1;
	}
	*str = '\0';
	return (temp);
}
