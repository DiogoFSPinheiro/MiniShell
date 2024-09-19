/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:18:52 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/19 14:25:32 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_error;

bool	ft_find_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == R_IN2)
			return (SUCCESS);
		token = token->next;
	}
	return (FAILURE);
}

void	ft_execute_in(t_token *token, t_env **env)
{
	t_commands	*cmd;
	int			forked;
	int			status;

	forked = 1;
	ft_prep_cmd_struct(&cmd, token, *env);
	if (cmd->next)
		ft_pipe_it(cmd, env);
	else if (ft_handle_redirects(cmd->tokens) != FAILURE
		&& ft_built_in(cmd, env) != SUCCESS)
	{
		set_inner_shell_signals();
		forked = fork();
		while (wait(&status) > 0)
			;
		g_error = WEXITSTATUS(status);
	}
	if (forked == 0)
	{
		ft_change_global_err(0);
		ft_exec_n_cleanup(cmd, *env);
		exit(g_error);
	}
	ft_heredoc_sig(-2);
	ft_free_cmd(cmd);
}

char	*ft_path_to_executable(char **paths, char *command, int using_it)
{
	DIR				*dir;
	struct dirent	*entry;

	while (paths[using_it] != NULL)
	{
		if (access(paths[using_it], F_OK) == 0)
		{
			if (paths[using_it] == NULL)
				return (NULL);
			dir = opendir(paths[using_it]);
			if (dir == NULL)
				return (NULL);
			entry = readdir(dir);
			while (entry != NULL)
			{
				if (strcmp(entry->d_name, command) == 0)
					return (ft_strdup(paths[using_it]));
				entry = readdir(dir);
			}
			closedir(dir);
		}
		using_it++;
	}
	return (NULL);
}

// At line 112 i know i didnt find the program in 
//the PATHS of the env so i use pwd
char	*ft_right_path(t_token *token, t_env *env, int iswear)
{
	char	**paths;
	char	*found;
	char	*apended;

	paths = NULL;
	if (ft_get_env(env, "PATH") != NULL)
	{
		paths = ft_split(ft_get_env(env, "PATH"), ':');
		found = ft_path_to_executable(paths, token->data, iswear);
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
