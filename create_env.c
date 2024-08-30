/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:57:14 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/30 13:58:50 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	ft_see_equal(char *str)
{
	int	c;

	c = 0;
	while (str[c] != '=')
		c++;
	return (c);
}

void	ft_create_env(char **envp, t_env **env)
{
	int		c;
	int		i;
	t_env	*cur;
	int		s;

	c = 0;
	i = ft_arraylen(envp);
	*env = (t_env *)ft_calloc(sizeof(t_env), i);
	cur = *env;
	while (c < i)
	{
		cur = *env + c;
		s = ft_see_equal(envp[c]);
		cur->title = ft_fine_strdup(envp[c], 0, s - 1);
		cur->content = ft_strdup(envp[c] + s + 1);
		if (envp[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
}
