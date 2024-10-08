/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:08:11 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/18 23:47:59 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_token *token, t_env *env)
{
	char	cwd[256];
	char	*pwd;

	ft_change_global_err(0);
	if (token->next && token->next->type == 4)
	{
		ft_built_err(token, flag_err);
		return ;
	}
	if (token)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_printf("%s\n", cwd);
		else
		{
			ft_printf_err("I dont know where i am, what did you do??\n");
			pwd = ft_get_env(env, "PWD");
			if (pwd != NULL)
				ft_printf_err("Just kidding, you are at\n%s\n", pwd);
		}
	}
}
