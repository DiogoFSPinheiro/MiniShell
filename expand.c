/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:56:07 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/10 17:07:42 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO to many funcs here, need to separate

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

static void	ft_view_data(t_token **token, t_env *env) // TODO fix norm here
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
			cur->data = ft_finecont_nomorequotes(cur->data, 0, 0, 0);
	}
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

// o que mudar aqui, tenho que mudar no utils3 no ft_cout_size()
static char	*ft_expand_var(char *str, int *i, t_env *env)
{
	int		var_start;
	char	*var_name;
	t_env	*content;

	var_start = *i + 1;
	while (str[*i + 1] != ' ' && str[*i + 1] != '\0'
		&& str[*i + 1] != '"' && str[*i + 1] != '\'' && str[*i + 1] != '$'
		&& str[*i + 1] != '\n')
		(*i)++;
	var_name = ft_fine_strdup(str, var_start, *i);
	if (ft_strcmp(var_name, "?") == SUCCESS)
	{
		free(var_name);
		return ("Error Code");
	}
	content = ft_get_content(env, var_name);
	free(var_name);
	if (content)
		return (content->content);
	return (NULL);
}

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

char	*ft_expand_variables2(char *str, t_env *env)
{
	char	*result;
	char	*env_value;
	t_ints	val;

	val = (t_ints){.i = 0, .j = 0, .in_single_quote = 0, .in_double_quote = 0};
	result = (char *)ft_calloc(ft_get_full_size2(str, env) + 1, sizeof(char));
	while (str[val.i] != '\0')
	{
		if (str[val.i] == '$')
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

char	*ft_strdup_no_quotes(char const *src)
{
	int		c;
	int		size;
	int		i;
	char	*dest;

	dest = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!dest || ft_strlen(src) < 3)
		return (0);
	size = ft_strlen(src) - 1;
	c = 0;
	i = 0;
	if (src[i] == '\"' || src[i] == '\'')
		i++;
	while (i < size)
	{
		dest[c] = src[i];
		c++;
		i++;
	}
	if (src[i] != '\"' && src[i] != '\'')
		dest[c] = src[i];
	else
		dest[c] = '\0';
	dest[++c] = '\0';
	return (dest);
}
