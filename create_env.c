/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:57:14 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/18 00:02:28 by pebarbos         ###   ########.fr       */
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
	t_env	*shlvl;

	new_node = malloc(sizeof(t_env));
	new_node->title = ft_strdup("_");
	new_node->content = ft_strdup("/usr/bin/env");
	shlvl = malloc(sizeof(t_env));
	shlvl->title = ft_strdup("SHLVL");
	shlvl->content = ft_strdup("1");
	shlvl->next = NULL;
	new_node->next = shlvl;
	*env = new_node;
}

t_env	*ft_create_env_node(char *envp_entry)
{
	t_env	*new_node;
	int		c;
	int		shlvl;
	char	*shlvel;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	c = ft_see_equal(envp_entry);
	if (!ft_strncmp(envp_entry, "SHLVL", 5))
	{
		shlvl = ft_atoi(envp_entry + c + 1);
		shlvl++;
		shlvel = ft_itoa(shlvl);
		new_node->content = shlvel;
	}
	else
		new_node->content = ft_strdup(envp_entry + c + 1);
	new_node->title = ft_fine_strdup(envp_entry, 0, c - 1);
	new_node->next = NULL;
	return (new_node);
}

void	ft_create_env(char **envp, t_env **env)
{
	int		i;
	t_env	*new_node;
	t_env	*cur;

	i = 0;
	*env = NULL;
	if (envp[0] == NULL)
		ft_create_basic_envs(env);
	while (envp[i])
	{
		new_node = ft_create_env_node(envp[i]);
		if (!new_node)
			return ;
		if (*env == NULL)
			*env = new_node;
		else
			cur->next = new_node;
		cur = new_node;
		i++;
	}
}
