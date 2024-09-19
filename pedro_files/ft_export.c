/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:31:09 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/19 18:19:12 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_and_print(t_env *env)
{
	t_env	*duplicated;

	duplicated = NULL;
	ft_duplicate_envs(env, &duplicated);
	ft_sort(&duplicated);
	ft_print_exported(duplicated);
	ft_free_env(duplicated);
}

void	ft_modify_env(t_env	*env, char *tit, char *cont, int i)
{
	int	f;

	f = 0;
	while (env)
	{
		if (env->title && ft_strcmp(env->title, tit))
		{
			f++;
			if (env->content && i == 1 && !ft_strcmp(tit, "_"))
			{
				free(env->content);
				env->content = NULL;
				env->content = ft_strdup(cont);
			}
			else if (!ft_strcmp(tit, "_"))
				env->content = ft_strjoin_free(env->content, cont);
			return ;
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	if (f == 0)
		env->next = ft_create_new(tit, cont);
}

// 	f e uma flag para ver se ja existe ou nao nas envs
char	*ft_get_title(char *str, int c)
{
	char	*tit;

	if (ft_strnstr(str, "+=", ft_strlen(str)))
		tit = ft_fine_strdup(str, 0, c -2);
	else if (ft_strnstr(str, "=", ft_strlen(str)))
		tit = ft_fine_strdup(str, 0, c -1);
	else
		tit = ft_strdup(str);
	return (tit);
}

//if i have error maybe its the if on line 167
void	ft_change_add_env(t_env *env, char *command)
{
	int		c;
	char	*tit;
	char	*cont;

	c = ft_see_equal(command);
	cont = NULL;
	tit = ft_get_title(command, c);
	if (ft_strnstr(command, "=", ft_strlen(command)))
	{
		if (c == (int)ft_strlen(command))
			cont = NULL;
		else
			cont = ft_fine_strdup(command, c + 1, ft_strlen(command));
	}
	if (ft_strnstr(command, "+=", ft_strlen(command)))
		ft_modify_env(env, tit, cont, 0);
	else if (ft_strnstr(command, "=", ft_strlen(command)))
		ft_modify_env(env, tit, cont, 1);
	else
		ft_modify_env(env, tit, cont, 0);
	free(tit);
	if (cont != NULL)
		free(cont);
}

void	ft_export(t_token *token, t_env **env)
{
	ft_change_global_err(0);
	if (!token->next)
	{
		ft_sort_and_print(*env);
		return ;
	}
	if (token && token->next && token->next->type >= FLAG)
	{
		ft_built_err(token, flag_err);
		return ;
	}
	token = token->next;
	while (token)
	{
		if (ft_valid_title(token->data))
			ft_change_add_env(*env, token->data);
		else
			ft_built_err(token, invalid_identifier);
		token = token->next;
	}
	return ;
}
