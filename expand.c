/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/14 18:40:20 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_expand_variables(char *str, t_env *env);
char	*ft_expand_var(char *str, int *i, t_env *env);
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

void	ft_view_data(t_token **token, t_env *env)
{
	t_token	*cur;
	char	*str;

	cur = *token;
	str = ft_strchr(cur->data, '$');
	if (str)
	{
		if (!*++str)
			return ;
		else
		{
			str = NULL;
			str = ft_expand_variables(cur->data, env);
			free(cur->data);
			cur->data = ft_strdup(str);
			free(str);
		}
	}
}


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

int	ft_set_quotes_bool(char c, int *in_double_quote, int *in_single_quote)
{
	int	done;

	done = 0;
	if (c == '\'' && !*in_double_quote)
	{
		*in_single_quote = !*in_single_quote;
		done = 1;
	}
	else if (c == '"' && !*in_single_quote)
	{
		*in_double_quote = !*in_double_quote;
		done = 1;
	}
	return (done);
}

char	*ft_expand_var(char *str, int *i, t_env *env)
{
	int		var_start;
	char	*var_name;
	t_env	*content;

	var_start = *i + 1;
	while (str[*i + 1] != ' ' && str[*i + 1] != '\0'
		&& str[*i + 1] != '"' && str[*i + 1] != '\'' && str[*i + 1] != '$')
		(*i)++;
	var_name = ft_fine_strdup(str, var_start, *i);
	content = ft_get_content(env, var_name);
	free(var_name);
	if (content)
		return (content->content);
	if (ft_strcmp(var_name, "?") == SUCCESS)
		return ("Error Code");
	return (NULL);
}


char	*ft_expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*env_value;
	t_ints	val;
	/*int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;*/

	val = (t_ints){.i = 0, .j = 0, .in_single_quote = 0, .in_double_quote = 0};
	result = (char *)ft_calloc(500, sizeof(char));
	/*i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;*/
	while (str[val.i] != '\0')
	{
		if (ft_set_quotes_bool(str[val.i], &val.in_double_quote, &val.in_single_quote))
			;
		else if (str[val.i] == '$' && !val.in_single_quote)
		{
			env_value = ft_expand_var(str, &val.i, env);
			if (env_value)
				while (*env_value)
					result[val.j++] = *env_value++;
		}
		else
			result[val.j++] = str[val.i];
		val.i++;
	}
	result[val.j] = '\0';
	return (result);
}


/*
char	*ft_expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*env_value;
	int		i;
	int		j;
	int		var_start;
	t_env	*content;
	char	*var_name;
	int in_single_quote = 0;
	int in_double_quote = 0;

	result = (char *)ft_calloc(500, sizeof(char));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_set_quotes_bool(str[i], &in_double_quote, &in_single_quote))
			;
		else if (str[i] == '$' && !in_single_quote)
		{
			var_start = i + 1;
			while (str[i + 1] != ' ' && str[i + 1] != '\0'
				&& str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '$')
				i++;
			var_name = ft_fine_strdup(str, var_start, i);
			content = ft_get_content(env, var_name);
			if (content || ft_strcmp(var_name, "?") == SUCCESS)
			{
				if (content)
					env_value = content->content;
				else
					env_value = "Error Code";
				while (*env_value)
					result[j++] = *env_value++;
			}
			free(var_name);
		}
		else
			if (i != 0 && i != (int)ft_strlen(str) - 1)
				result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
*/