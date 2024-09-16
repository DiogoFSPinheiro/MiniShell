/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.co>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:22 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/14 18:56:26 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env, t_token *token)
{
	if (!env)
		return ;
	if (env->content == NULL)
		return ;
	if (token->next != NULL && token->next->type == FLAG)
	{
		ft_built_err(token, flag_err_env);
		return ;
	}
	while (env)
	{
		if (env->content != NULL)
			ft_printf("%s%s%s\n", env->title, "=", env->content);
		if (!env->next)
		{
			ft_change_global_err(0);
			return ;
		}
		env = env->next;
	}
	ft_change_global_err(0);
}
