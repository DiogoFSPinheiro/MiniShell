/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:20:00 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/12 17:23:59 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_token(t_token *token, char *data);

t_token	*ft_parser(char *input)
{
	char	*clean_input;
	t_token	*token;

	add_history(input);
	if (ft_validation_input(input) == FAILURE)
		ft_println("Wrong Syntax");
	else
	{
		clean_input = ft_input_spliter(input);
		token = ft_calloc(sizeof(t_token), words_quotes(clean_input, ' '));
		free(clean_input);
		ft_init_token(token, input);
		return (token);
	}
	return (NULL);
}

void	ft_init_token(t_token *token, char *data)
{
	char	**info;
	char	*clean_input;
	int		c;
	t_token	*cur;

	c = 0;
	clean_input = ft_input_spliter(data);
	info = ft_quotes_split(clean_input, ' ');
	free(clean_input);
	while (info[c])
	{
		cur = token + c;
		cur->data = ft_strdup(info[c]);
		ft_data_type(cur);
		if (info[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
	free_args(info);
}
