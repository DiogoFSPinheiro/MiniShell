/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:06:54 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/10 12:46:10 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <unistd.h>

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

void	ft_expand_cmd(t_commands **cmd, t_env *env)
{
	t_commands	*copy_cmd;

	copy_cmd = (*cmd);
	while (copy_cmd)
	{
		ft_find_expand(&copy_cmd->tokens, env);
		copy_cmd = copy_cmd->next;
	}
}

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

void	ft_build_heredoc(t_commands **cmd, t_commands *head)
{
//	t_token	*token;
	char	*line = NULL;
	size_t	len = 0;

//	token = (*cmd)->tokens;
	while (1)
	{
		write(1, "> ", 2);
		getline(&line, &len, stdin);

		if (strcmp(line, "ola\n") == 0)
		{
			free(line);
			break ;
		}

	}
	(*cmd) = head;
	ft_println("%s", (*cmd)->tokens);
}

void	ft_execute_in(t_token *token, t_env **env)
{
	t_commands	*cmd;
	int			forked;

	forked = 1;
	cmd = NULL;
	cmd = ft_build_commands(token);
	free_tokens(token);
	if (ft_find_heredoc(cmd->tokens) == SUCCESS)
		ft_build_heredoc(&cmd, cmd, *env);
	ft_expand_cmd(&cmd, *env);
	if (cmd->next)
	{
		ft_free_cmd(cmd); //do pipes mother fcker!!!!!
		return ;
	}
	ft_handle_redirects(cmd);
	if (ft_built_in(cmd->tokens, env) == SUCCESS)
		;
	else
	{
		forked = fork();
		while (wait(NULL) > 0)
			;
	}
	if (forked == 0)
	{
		ft_send_to_execve(cmd->tokens, *env);
		ft_free_cmd(cmd);
		ft_free_env(*env);
		exit(0);
	}
	ft_free_cmd(cmd);
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
