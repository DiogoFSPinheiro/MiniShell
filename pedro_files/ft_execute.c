/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:06:54 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/02 17:21:18 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// So estou a verificar ate ao penultimo porque o pipe nunca pode ser o ultimo
// E isso ja tem a verificacao do parser
int	ft_see_redirect(t_token *token)
{
	while (token->next)
	{
		if (token->type == R_IN)
			return (R_IN);
		else if (token->type == R_IN2)
			return (R_IN2);
		else if (token->type == R_OUT)
			return (R_OUT);
		else if (token->type == R_OUT2)
			return (R_OUT2);
		token = token->next;
	}
	return (FAILURE);
}

void	ft_execute_in(t_token *token, t_env **env)
{
	int			forked;
	t_commands	*cmd;

	forked = 1;
	cmd = NULL;
	cmd = ft_build_commands(token);
	if (cmd->next)
	{
		ft_free_cmd(cmd);
		return ;
	}
	ft_free_cmd(cmd);
	// get FORKED MINIHELL    FIRST  -> prepare args and envs  <-
	// Builtins that dont kill the program and affect it: Only if pipes 
	//				CD, export, unset
	// builtins that have to kill that version of the program
	//				env, pwd, echo
	if (ft_strcmp(token->data, "cd") || ft_strcmp(token->data, "export")
		|| ft_strcmp(token->data, "unset"))
		ft_built_in(token, env);
	else
	{
		forked = fork();
		while (wait(NULL) > 0)
			;
	}
	if (forked == 0 && ft_built_in(token, env) == 1)
		ft_send_to_execve(token, *env);
	if (forked == 0)
	{
		free_tokens(token);
		ft_free_env(*env);
		exit(0);
	}
}

char	*ft_path_to_executable(char **paths, char *command)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;

	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK) == 0)
		{
			if (paths[i] == NULL)
				return (NULL);
			dir = opendir(paths[i]);
			while ((entry = readdir(dir)) != NULL)
			{
				if (strcmp(entry->d_name, command) == 0)
					return (ft_strdup(paths[i]));
			}
			closedir(dir);
		}
		i++;
	}
	return (NULL);
}

// At line 112 i know i didnt find the program in the PATHS of the env so i use pwd
char	*ft_right_path(t_token *token, t_env *env)
{
	char	**paths;
	char	*found;
	char	*apended;

	paths = NULL;
	if (ft_get_env(env, "PATH") != NULL)
	{
		paths = ft_split(ft_get_env(env, "PATH"), ':');
		found = ft_path_to_executable(paths, token->data);
	}
	else if (access(token->data, R_OK))
		found = ft_path();
	else
		return (token->data);
	if (!ft_strnstr(token->data, "./", ft_strlen(token->data)))
	{
		found = ft_strjoin_free(found, "/");
		apended = ft_strjoin(found, token->data);
	}
	else
		apended = ft_strdup(token->data);
	if (found)
		free(found);
	free_args(paths);
	return (apended);
}
