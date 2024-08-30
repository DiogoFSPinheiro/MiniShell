/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:08:36 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/24 15:13:23 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(t_env *env, char *str)
{
	while (env->next != NULL)
	{
		if (!env->title)
			break ;
		if (ft_strcmp(str, env->title) != 1)
			env = env->next;
		else
			break;
	}
	if (env->title && ft_strcmp(str, env->title) == 1)
		return env->content;
	if (env->next && ft_strcmp(str, env->next->title))
		return env->next->title;
	return NULL;
}

char	*ft_path(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	return (buffer);
}
