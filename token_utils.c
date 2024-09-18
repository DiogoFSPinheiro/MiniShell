/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:00:41 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/18 15:29:09 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_see_space(char *str, int *c, int *size)
{
	if (str[*c] == '>' || str[*c] == '<')
	{
		if (str[*c + 1] == '>' || str[*c + 1] == '<')
		{
			(*c)++;
			(*size) += 2;
			if (str[*c + 1] != ' ')
				(*size)++;
		}
		else
		{
			if (*c > 0 && str[*c - 1] == ' ' && str[*c + 1] == ' ')
				return ;
			if (*c > 0 && str[*c - 1] != ' ')
				(*size)++;
			if (str[*c + 1] != ' ')
				(*size)++;
		}
		return ;
	}
	else
		ft_count_helper(str, c, size);
	return ;
}

static void	ft_set_space(char *str, char **dst, int *c, int *i)
{
	if (str[*c] == '>' || str[*c] == '<')
	{
		if (str[*c + 1] == '>' || str[*c + 1] == '<')
		{
			if (*c > 0 && str[*c - 1] != ' ')
				(*dst)[(*i)++] = ' ';
			(*dst)[(*i)++] = str[(*c)++];
			(*dst)[*i] = str[*c];
			if (str[*c + 1] != ' ')
				(*dst)[++(*i)] = ' ';
			return ;
		}
		else
		{
			ft_space_helper(str, dst, c, i);
			return ;
		}
	}
	else
		ft_space_helper(str, dst, c, i);
	return ;
}

int	ft_clean_size(char *str)
{
	int	c;
	int	size;

	ft_reset_int(&c, &size);
	ft_space_skiper(str, &c);
	while (str[c] != '\0')
	{
		if (str[c] != ' ')
		{
			while (str[c] != ' ' && str[c] != '\0')
			{
				if ((str[c] == '|' || str[c] == '<' || str[c] == '>'))
					ft_see_space(str, &c, &size);
				ft_increment_int(&c, &size);
			}
		}
		else
		{
			if (str[c] != '\0')
				size++;
			c++;
		}
	}
	size += 2;
	return (size);
}

static void	ft_process_characters(char *str, char *clean_input, int *c, int *i)
{
	while (str[*c] != ' ' && str[*c] != '\0')
	{
		if (str[*c] == '"' || str[*c] == '\'')
			ft_skip_quotes_w(str, &clean_input, c, i);
		else if (str[*c] == '|' || str[*c] == '<' || str[*c] == '>')
			ft_set_space(str, &clean_input, c, i);
		else
		{
			if (str[*c] != ' ' && str[*c] != '\0')
				clean_input[*i] = str[*c];
		}
		(*c)++;
		(*i)++;
	}
}

char	*ft_input_spliter(char *str)
{
	int		size;
	char	*clean_input;
	int		c;
	int		i;

	c = 0;
	i = 0;
	size = ft_clean_size(str);
	clean_input = ft_safe_calloc(size + 1, sizeof(char));
	ft_space_skiper(str, &c);
	while (str[c] != '\0')
	{
		if (str[c] != ' ')
			ft_process_characters(str, clean_input, &c, &i);
		else
		{
			clean_input[i++] = str[c++];
			ft_space_skiper(str, &c);
		}
	}
	clean_input[i] = '\0';
	return (clean_input);
}
