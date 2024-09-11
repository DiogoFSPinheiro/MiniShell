/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.co>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:12:29 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/11 19:49:03 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_sorted(t_env *env)
{
	int	i;

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
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env)
	{
		if (!ft_strcmp("_", env->title) && env->content != NULL)
		{
			ft_printf("declare -x %s%s\"", env->title, "=");
			while (env->content[i])
			{
				if (env->content[i] == '\"')
					ft_printf("\\");
				write(1, &env->content[i++], 1);
			}
			i = 0;
			ft_printf("\"\n");
		}
		else if (env->content == NULL)
			ft_printf("declare -x %s\n", env->title);
		if (!env->next)
			return ;
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
			if (ft_strncmp((*cur)->title, (*cur)->next->title,
					ft_strlen((*cur)->title)) > 0)
			{
				ft_swap_nodes(cur);
			}
			cur = &(*cur)->next;
		}
	}
}
