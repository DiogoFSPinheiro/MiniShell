/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:30:09 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/30 16:33:45 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_get_content(t_env *env, char *title)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->title, title) == SUCCESS)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

static void	ft_cout_size(char *str, t_env *env, int *i, int *total_length)
{
	t_env	*content;
	char	*var_name;
	int		start;

	start = *i + 1;
	while (str[*i + 1] != ' ' && str[*i + 1] != '\0'
		&& str[*i + 1] != '$' && str[*i + 1] != '"' && str[*i + 1] != '\'')
		(*i)++;
	var_name = ft_fine_strdup(str, start, *i);
	content = ft_get_content(env, var_name);
	free(var_name);
	if (content)
		*total_length += strlen(content->content);
	else
		*total_length += 20;
}

int	ft_get_full_size(char *str, t_env *env)
{
	int		total_length;
	t_ints	val;

	total_length = 0;
	val = (t_ints){.i = 0, .j = 0, .in_single_quote = 0, .in_double_quote = 0};
	while (str[val.i] != '\0')
	{
		if (ft_set_quotes_bool(str[val.i], &val.in_double_quote,
				&val.in_single_quote))
			;
		else if (str[val.i] == '$' && !val.in_single_quote)
			ft_cout_size(str, env, &val.i, &total_length);
		else
			total_length++;
		val.i++;
	}
	return (total_length);
}

void	set_up_sigaction(struct sigaction *sa)
{
	sigaction(SIGINT, sa, NULL);
}
