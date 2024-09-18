/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/18 16:30:27 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/printf/ft_printf.h"
#include "minishell.h"
#include <stdbool.h>

extern int g_error;
static char	*ft_expand_var(char *str, int *i, t_env *env);
static void	ft_view_data(t_token **token, t_env *env);
char		*ft_strdup_no_quotes(char const *src);

void	ft_find_expand(t_token **token, t_env *env)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		ft_view_data(&cur, env);
		cur = cur->next;
	}
}

static void	ft_view_data(t_token **token, t_env *env)
{
	t_token	*cur;
	char	*str;

	cur = *token;
	if (!cur->data)
		return ;
	str = ft_strchr(cur->data, '$');
	if (str)
	{
		if (!*++str)
			return ;
		else
		{
			str = ft_expand_variables(cur->data, env);
			free(cur->data);
			cur->data = ft_strdup(str);
			free(str);
		}
	}
	else
	{
		if (ft_strchr(cur->data, '\"') || ft_strchr(cur->data, '\''))
			cur->data = ft_finecont_nomorequotes(cur->data, 0, 0, 0); //TODO avisar o pedro para tirar esta func do export dele
	}
}

// o que mudar aqui, tenho que mudar no utils3 no ft_cout_size()
static char	*ft_expand_var(char *str, int *i, t_env *env)
{
	int		var_start;
	char	*var_name;
	t_env	*content;

	var_start = *i;
	while (str[*i + 1] != ' ' && str[*i + 1] != '\0'
		&& str[*i + 1] != '"' && str[*i + 1] != '\'' && str[*i + 1] != '$'
		&& str[*i + 1] != '\n' && str[*i + 1] != '\t')
		(*i)++;
	var_name = ft_fine_strdup(str, var_start, *i);
	if (ft_strcmp(var_name, "?") == SUCCESS)
	{
		free(var_name);
		return (ft_itoa(g_error));
	}
	if (ft_see_spe_char(*(var_name + 1)) == SUCCESS)
		return (var_name);
	content = ft_get_content(env, var_name + 1);
	free(var_name);
	if (content)
		return (ft_strdup(content->content));
	return (NULL);
}

//TODO if i have problems here i think it must be the 
// ft_see_quotes and spaces on line 98
//this has a double
char	*ft_expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*env_value;
	t_ints	val;

	val = (t_ints){.i = 0, .j = 0, .in_single_quote = 0, .in_double_quote = 0};
	result = (char *)ft_calloc(ft_get_full_size(str, env) + 1, sizeof(char));
	while (str[val.i] != '\0')
	{
		if (ft_set_quotes_bool(str[val.i], &val.in_double_quote,
				&val.in_single_quote))
			;
		else if (str[val.i] == '$' && !val.in_single_quote
			&& ft_see_q_n_s(str[val.i + 1]) != SUCCESS)
		{
			env_value = ft_expand_var(str, &val.i, env);
			ft_copy_and_free(env_value, result, &val.j);
		}
		else
			result[val.j++] = str[val.i];
		val.i++;
	}
	result[val.j] = '\0';
	return (result);
}

char	*ft_expand_variables2(char *str, t_env *env)
{
	char	*result;
	char	*env_value;
	char	*mem_free;
	t_ints	val;

	val = (t_ints){.i = 0, .j = 0, .in_single_quote = 0, .in_double_quote = 0};
	result = (char *)ft_calloc(ft_get_full_size2(str, env) + 1, sizeof(char));
	while (str[val.i] != '\0')
	{
		if (str[val.i] == '$' && str[val.i + 1] != ' '
			&& str[val.i + 1] != '\'' && str[val.i + 1] != '\"')
		{
			env_value = ft_expand_var(str, &val.i, env);
			mem_free = env_value;
			if (env_value)
				while (*env_value)
					result[val.j++] = *env_value++;
			free(mem_free);
		}
		else
			result[val.j++] = str[val.i];
		val.i++;
	}
	result[val.j] = '\0';
	return (result);
}
