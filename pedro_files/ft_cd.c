/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:59:46 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/29 17:27:20 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_token *token, t_env **env)
{
	if (token->next == NULL)
	{
		if (ft_get_env(*env, "HOME") != NULL)
			chdir(ft_get_env(*env, "HOME"));
		else
			ft_built_err(token, no_home);
	}
	else if (token->next && token->next->next)
		ft_built_err(token, args_err);
	else if (token->next && access(token->next->data, F_OK) == 0)
	{
		if (access(token->next->data, R_OK) == 0)
			chdir(token->next->data);
		else
			ft_built_err(token, file_permissions);
	}
	else
		ft_built_err(token, no_file);
} // Falta actualizar o OLDPWD e o PWD

/*
bash: cd: pasta/: Permission denied       cd to a folder that has no permissions 
bash: cd: HOME not set                    try to cd after unseting HOME
bash: cd: non_existant: No such file or directory
*/