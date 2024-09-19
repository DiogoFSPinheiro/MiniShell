/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:30:09 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/19 13:51:19 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
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

	start = *i;
	while (str[*i + 1] != ' ' && str[*i + 1] != '\0'
		&& str[*i + 1] != '$' && str[*i + 1] != '"' && str[*i + 1] != '\''
		&& str[*i + 1] != '\n' && str[*i + 1] != '\t')
		(*i)++;
	var_name = ft_fine_strdup(str, start, *i);
	if (ft_see_spe_char(*(var_name + 1)) == SUCCESS)
		*total_length += (ft_strlen(var_name) + 1);
	content = ft_get_content(env, var_name + 1);
	free(var_name);
	if (content && content->content != NULL)
		*total_length += ft_strlen(content->content);
	else
		*total_length += 20;
}

int	ft_get_full_size(char *str, t_env *env) //this has a double
{
	int		total_length;
	t_ints	val;

	total_length = 0;
	val = (t_ints){.i = 0, .j = 0, .in_single_quote = 0, .in_double_quote = 0};
	while (str[val.i] != '\0' )
	{
		if (ft_set_quotes_bool(str[val.i], &val.in_double_quote,
				&val.in_single_quote))
			;
		else if (str[val.i] == '$' && !val.in_single_quote
			&& str[val.i + 1] != ' ' && str[val.i + 1] != '\''
			&& str[val.i + 1] != '\"')
			ft_cout_size(str, env, &val.i, &total_length);
		else
			total_length++;
		val.i++;
	}
	return (total_length);
}

int	ft_get_full_size2(char *str, t_env *env)
{
	int		total_length;
	t_ints	val;

	total_length = 0;
	val = (t_ints){.i = 0, .j = 0, .in_single_quote = 0, .in_double_quote = 0};
	while (str[val.i] != '\0')
	{
		if (str[val.i] == '$' && str[val.i + 1] != ' '
			&& str[val.i + 1] != '\'' && str[val.i + 1] != '\"')
			ft_cout_size(str, env, &val.i, &total_length);
		else
			total_length++;
		val.i++;
	}
	return (total_length);
}
