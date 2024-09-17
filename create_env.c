/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:57:14 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/17 18:45:30 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_see_equal(char *str)
{
	int	c;

	c = 0;
	while (str[c] && str[c] != '=')
		c++;
	return (c);
}

void	ft_create_basic_envs(t_env **env)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->title = ft_strdup("_");
	new_node->content = ft_strdup("/usr/bin/env");
	new_node->next = NULL;
	*env = new_node;
}

void	ft_create_env(char **envp, t_env **env)
{
	int		c;
	int		i;
	t_env	*new_node;
	t_env	*cur;

	i = 0;
	*env = NULL;
	if (envp[0] == NULL)
		ft_create_basic_envs(env);
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		c = ft_see_equal(envp[i]);
		new_node->title = ft_fine_strdup(envp[i], 0, c -1);
		new_node->content = ft_strdup(envp[i] + c + 1);
		new_node->next = NULL;
		if (*env == NULL)
			*env = new_node;
		else
			cur->next = new_node;
		cur = new_node;
		i++;
	}
}
