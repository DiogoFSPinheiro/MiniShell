/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:12:08 by pebarbos          #+#    #+#             */
/*   Updated: 2024/08/26 15:09:19 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(t_token *token, char **args, char **envs, char *str, char *command)
{
	struct stat buffer;
	
	(void)token;
	if (execve(str, args, envs) == -1)
	{ // caso eu nao consiga executar com o path(str) uso o commando diretamente caso nao de vou ver o porque de nao dar
		if (execve(command, args, envs) == -1)
		{ // Vou enviar para a funcao dos erros para melhor leitura
			if (stat(str, &buffer) != 0 && !ft_strncmp(token->data, "./", 2))
				ft_printf_err("minishell: %s: No such file or directory\n", command);
			else if (stat(str, &buffer) != 0)
				ft_printf_err("command '%s' not found\n", command);
			else if (access(command, R_OK))
				ft_printf_err("minishell: %s: Permission denied\n", command);
			else if (S_ISDIR(buffer.st_mode))
				ft_printf_err("minishell: %s: Is a directory\n", command);
			else if ((buffer.st_mode))
				ft_printf_err("minishell: %s: Permission denied\n", command);
			//else if (!ft_strncmp(token->data, "./", 3))
			//	ft_printf_err("command '%s' not found\n", command);
			else
				ft_printf_err("command '%s' No such file or directory\n", command);
		}
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
		return NULL;
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
	char 	**args;
	int		i;

	i = 0;
	if (!token)
		return NULL;
	temp = token;
	while(temp)
	{
		temp = temp->next;
		i++;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	temp = token;
	while(temp)
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

	env_arr = ft_make_env_arr(env);
	args_arr = ft_make_arg_arr(token);
	apended = ft_right_path(token, env);
	ft_execute(token, args_arr, env_arr, apended, token->data);
	free_args(env_arr);
	free_args(args_arr);
	free(apended);
}