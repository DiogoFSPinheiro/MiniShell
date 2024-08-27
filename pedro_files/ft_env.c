/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:22 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/27 16:54:44 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env, t_token *token)
{
	if (!env)
		return;
	if (env->content == NULL && env->title == NULL)
	{
		ft_printf_err("There are no envs left\n");
		return ;
	}
	if (token->next != NULL && token->next->type == FLAG)
	{
		ft_built_err(token, flag_err);
		return ;
	}
	while (env)
	{
		ft_printf("%s%s%s\n", env->title, "=", env->content);
		if (!env->next)
			return;
		env = env->next;
	}
}
