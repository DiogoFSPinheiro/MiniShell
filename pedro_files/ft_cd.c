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

char	*ft_get_new_old(t_env *env)
{
	char	*pwd;

	pwd = NULL;
	while (env)
	{
		if (ft_strcmp(env->title, "PWD"))
		{
			if (env->content == NULL)
				return NULL;
			pwd = ft_strdup(env->content);
			return (pwd);
		}
		env = env->next;
	}
	return (pwd);
}

void	ft_change_pwd(t_env *env)
{
	char	*old_pwd;

	old_pwd = ft_get_new_old(env);
	while (env)
	{
		if (ft_strcmp(env->title, "PWD"))
		{
			free(env->content);
			env->content = ft_path();
		}
		else if (ft_strcmp(env->title, "OLDPWD"))
		{
			free(env->content);
			env->content = old_pwd;
		}
		env = env->next;
	}// im going to replace the loops to make thee PWD and change to the new one efirst and the second just to update the old
	//if one or the other not found create new
}

void	ft_cd(t_token *token, t_env **env)
{
	if (token->next == NULL)
	{
		if (ft_get_env(*env, "HOME") != NULL)
		{
			chdir(ft_get_env(*env, "HOME"));
			ft_change_pwd(*env);
		}
		else
			ft_built_err(token, no_home);
	}
	else if (token->next && token->next->next)
		ft_built_err(token, args_err);
	else if (token->next && access(token->next->data, F_OK) == 0)
	{
		if (access(token->next->data, R_OK) == 0)
		{
			chdir(token->next->data);
			ft_change_pwd(*env);
		}
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