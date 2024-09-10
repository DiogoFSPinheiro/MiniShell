/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:06:43 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/10 17:09:22 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_built_in(t_token *token, t_env **env)
{
	if (!token)
		return (FAILURE);
	else if (ft_strcmp(token->data, "env") == SUCCESS)
		ft_env(*env, token);
	else if (ft_strcmp(token->data, "pwd") == SUCCESS)
		ft_pwd(token);
	else if (ft_strcmp(token->data, "echo") == SUCCESS)
		ft_echo(token);
	else if (ft_strcmp(token->data, "cd") == SUCCESS)
		ft_cd(token, env);
	else if (ft_strcmp(token->data, "export") == SUCCESS)
		ft_export(token, env);
	else if (ft_strcmp(token->data, "unset") == SUCCESS)
		ft_unset(env, token);
	else
		return (FAILURE);
	return (SUCCESS);
}

/*
void	ft_send_to_execve(t_token *token, t_env *env)
{
	char	**args_arr;
	char	**env_arr;
	char	**paths;
	char	*found;
	char	*apended;

	//paths = NULL;
	env_arr = ft_make_env_arr(env);
	args_arr = ft_make_arg_arr(token);
	if (ft_get_env(env, "PATH") != NULL)
	{
		paths = ft_split(ft_get_env(env, "PATH"), ':');
		found = ft_path_to_executable(paths, token->data); 
	}
	else // At this point i know i didnt find the program in the PATHS of the env so i use pwd
		found = ft_path();
	if (ft_in_there(token->data, "./") == 0)
	{
		found = ft_strjoin(found, "/");
		apended = ft_strjoin(found, token->data);
	}
	else
		apended = token->data;
	if (execve(apended, args_arr, env_arr) == -1)// o path leva o programa o path e lido pelas envs
		ft_printf_err("command '%s' not found\n", token->data);
	ft_free_shit_up(env_arr, args_arr, found, apended, paths);
}

int	ft_in_there(char *hay, char *needle)
{
	int	i;
	int j;
	
	i = 0;
	j = 0;
	while (hay[i] != '\0')
	{
		j = 0;
		while (hay[i] && hay[i] == needle[j])
		{
			if(needle[j + 1] == '\0')
				return (1);
			j++;
			i++;
		}
		i++;
	}
	return (0);
}*/