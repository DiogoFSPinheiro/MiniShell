/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:31:09 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/02 19:05:40 by pebarbos         ###   ########.fr       */
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
		if (!ft_strcmp("_", env->title)) // this one env is not printed for some reason
			ft_printf("declare -x %s%s\"%s\"\n", env->title, "=", env->content);
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

void	ft_modify_env(t_env	*env, char *command)
{
	(void)env;
	(void)command;
}

void	ft_add_env(t_env *env, char *command)
{
	t_env	*new_node;
	int		c;

	new_node = NULL;
	if (ft_strchr(command, '='))
		ft_modify_env(env, command);
	else
	{
		while (env->next)
			env = env->next;
		new_node = malloc(sizeof(t_env));
		c = ft_see_equal(command);
		new_node->title = ft_fine_strdup(command, 0, c -1);
		new_node->content = ft_strdup(command + c + 1);
		new_node->next = NULL;
		(env)->next = new_node;
	}
}
	// find if command already exists
	// find if command has += if so appends if not frees and allocs a duped version
	// find if command has "" or '' it creates and has a Null. or space
	// if its a new env this folowing appens

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
		ft_add_env(*env, token->data);
		token = token->next;
	}
	return ;
}
	// each command is executed individualy
	// commands cant start with special chars EXEPTIONS _
	//find if there is a equal in each command