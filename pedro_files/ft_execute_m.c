/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.co>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:12:08 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/16 00:02:03 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(char **args, char **envs, char *cmd, t_token *token)
{
	struct stat buffer;

	if (execve(cmd, args, envs) == -1)
	{
		if (stat(token->data, &buffer) != 0)
		{
			if (!ft_strncmp(cmd, "./", 2))
				ft_built_err(token, no_file);
			else
				ft_built_err(token, cmd_not_found);
		}
		else if (S_ISDIR(buffer.st_mode))
			ft_built_err(token, is_dir);
		else if (!(buffer.st_mode & S_IXUSR))
			ft_built_err(token, file_permissions);
		else
			ft_built_err(token, no_file);
	}
}


char	**ft_make_env_arr(t_env *env)
{
	t_env	*temp;
	char	**envs;
	char	*title;
	int		i;

	temp = env;
	i = 0;
	if (!env)
		return (NULL);
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	envs = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	temp = env;
	while (temp)
	{
		title = ft_strjoin(temp->title, "=");
		envs[i++] = ft_strjoin(title, temp->content);
		free(title);
		temp = temp->next;
	}
	return (envs);
}

char	**ft_make_arg_arr(t_token *token)
{
	t_token	*temp;
	char	**args;
	int		i;

	i = 0;
	if (!token)
		return (NULL);
	temp = token;
	while (temp && temp->type < 5)
	{
		temp = temp->next;
		i++;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	temp = token;
	while (temp && temp->type < 5)
	{
		args[i] = ft_strdup(temp->data);
		temp = temp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_send_to_execve(t_token *token, t_env *env)
{
	char	**args_arr;
	char	**env_arr;
	char	*apended;
	int		gona_use_this;

	gona_use_this = 0;
	env_arr = ft_make_env_arr(env);
	args_arr = ft_make_arg_arr(token);
	apended = ft_right_path(token, env, gona_use_this);
	ft_execute(args_arr, env_arr, apended, token);
	free_args(env_arr);
	free_args(args_arr);
	free(apended);
}
