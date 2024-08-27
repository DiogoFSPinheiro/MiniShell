/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:06:54 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/27 16:53:33 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// So estou a verificar ate ao penultimo porque o pipe nunca pode ser o ultimo
// E isso ja tem a verificacao do parser
int		ft_there_is_pipe(t_token *token)
{
	while (token->next)
	{
		if (token->next->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void	ft_piper(t_token *token, t_env *env)
{
	t_token *temp;
	int		i;
//	int		pipes_fd[2];

	
	i = fork();
	temp = token;
	if (temp == NULL)
		return ;
	//pipe(token->pipes_fd[1]);
	if (!ft_built_in(token, env))
		ft_send_to_execve(token, env);
	//if (i == 0)
	//	exit ;
	while (temp && temp->next)
	{
		temp = temp->next;
		if (temp->type == PIPE)
			break ;
	}
	temp = temp->next;
	if (temp != NULL)
		ft_piper(temp, env);
	return ;
}

void	ft_execute_in(t_token *token, t_env *env)
{
	int	forked;
	
	forked = 1;
	if (ft_there_is_pipe(token)) // sempre que existe ha pelomenos 1 pipe
		ft_piper(token, env);
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
		while (wait(NULL) > 0);
	}
	if (forked == 0 && ft_built_in(token, env) == 1)
		ft_send_to_execve(token, env);
	if (forked == 0)
	{
		free_tokens(token);
		ft_free_env(env);
		exit(0);
	}
}



char	*ft_path_to_executable(char **paths, char *command)
{
	int	i;
	DIR		*dir;
	struct dirent *entry;
	
	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK) == 0)
		{
			if (paths[i] == NULL)
				return NULL;
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
char *ft_right_path(t_token *token, t_env *env)
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
		return(token->data);
	if (!ft_strnstr(token->data, "./", ft_strlen(token->data))) 
	{
		found = ft_strjoin(found, "/");
		apended = ft_strjoin(found, token->data);
	}
	else
		apended = ft_strdup(token->data);
	if(found)
		free(found);
	free_args(paths);
	return (apended);
}

