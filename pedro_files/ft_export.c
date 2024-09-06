/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:31:09 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/05 19:30:53 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_sorted(t_env *env)
{
	int i;

	while (env && env->next)
	{
		i = 0;
		if (env->title[i] > env->next->title[i])
			return (1);
		while (env->title[i] == env->next->title[i])
		{	
			if (env->title[i] > env->next->title[i])
				return (1);
			i++;
		}
		env = env->next;
	}
	return (0);
}
void	ft_print_exported(t_env *env)
{
	if (!env)
		return;
	while (env)
	{
		if (!ft_strcmp("_", env->title) && env->content != NULL)
			ft_printf("declare -x %s%s\"%s\"\n", env->title, "=", env->content);
		else if (env->content == NULL)
			ft_printf("declare -x %s\n", env->title);
		if (!env->next)
			return;
		env = env->next;
	}
}

void	ft_duplicate_envs(t_env *env, t_env **duped)
{
	t_env	*new_node;
	t_env	*cur;

	cur = NULL;
	while (env)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		if (env->content == NULL)
			new_node->content = NULL;
		else
			new_node->content = ft_strdup(env->content);
		new_node->title = ft_strdup(env->title);
		new_node->next = NULL;
		if (*duped == NULL)
			*duped = new_node;
		else if (cur != NULL)
			cur->next = new_node;
		cur = new_node;
		env = env->next;
	}
}
void	ft_swap_nodes(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	next = current->next;
	current->next = next->next;
	next->next = current;
	*env = next;
}

void	ft_sort(t_env **env)
{
	t_env	**cur;
	
	while (ft_sorted((*env)))
	{
		cur = env;
		while ((*cur)->next)
		{
			if (ft_strncmp((*cur)->title, (*cur)->next->title, ft_strlen((*cur)->title)) > 0)
			{
				ft_swap_nodes(cur);
			}
			cur = &(*cur)->next;
		}
	}
}

void	ft_sort_and_print(t_env *env)
{
	t_env	*duplicated;
	
	duplicated = NULL;
	ft_duplicate_envs(env, &duplicated);
	ft_sort(&duplicated);
	ft_print_exported(duplicated);
	ft_free_env(duplicated);
}

t_env	*ft_create_new(char *tit, char *cont)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->title = ft_strdup(tit);
	new_node->content = cont;
	new_node->next = NULL;
	return (new_node);
}

void	ft_modify_env(t_env	*env, char *tit, char *cont, int i)
{
	int	f;

	f = 0;
	while (env)
	{
		if (env->title && ft_strcmp(env->title, tit) && tit[0] != '_')
		{
			f++;
			if (env->content && i == 1)
			{
				free(env->content);
				env->content = NULL;
				env->content = ft_strdup(cont);
			}
			else
				env->content = ft_strjoin_free(env->content, cont);
			return ;
		}
		if (env->next == NULL)
			break;
		env = env->next;
	}
	if (f == 0)
		env->next = ft_create_new(tit, cont);
}
// 	f e uma flag para ver se ja existe ou nao nas envs

char	*ft_get_title(char *str, int	c)
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

void	ft_change_add_env(t_env *env, char *command)
{
	int		c;
	char	*tit;
	char	*cont;

	c = ft_see_equal(command);
	cont = NULL;
	tit = ft_get_title(command, c);
	if (strcmp(tit, "_") == 0)
	{
		free(tit);
		return;
	}
	if (ft_strnstr(command, "=", ft_strlen(command)))
		cont = ft_fine_strdup(command, c + 1, ft_strlen(command));
	else if (ft_strnstr(command, "=", ft_strlen(command)))
		cont = ft_fine_strdup(command, c + 1, ft_strlen(command));
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
	// find if command already exists
	// if command is _ Must do nothing
	// find if command has "" or '' it creates and has a Null. or space
	// if its a new env this folowing appens

int		ft_valid_title(char *str)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return 0;
	if (str[i] == '_')
		i++;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=' && i > 0)
			return (1);
		if (str[i] == '=' && i > 0) //if 0 there is nothing behind "="
				return (1);
		if (ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return 1;
}

void	ft_export(t_token *token, t_env **env)
{
	if (!token->next)
	{
		ft_sort_and_print(*env);
		return ;
	}
	if (token && token->next && token->next->type >= FLAG)
		ft_built_err(token, flag_err);
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
	// each command is executed individualy
	// commands cant start with special chars EXEPTIONS _
	//find if there is a equal in each command