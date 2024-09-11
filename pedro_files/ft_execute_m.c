/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.co>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:12:08 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/11 20:04:49 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(char **args, char **envs, char *str, char *cmd)
{
	struct stat	buffer;

	if (execve(str, args, envs) == -1)
	{
		// caso eu nao consiga executar com o path(str)
		// uso o commando diretamente caso nao de vou ver o porque de nao dar
		// Vou enviar para a funcao dos erros para melhor leitura
		if (stat(str, &buffer) != 0 && !ft_strncmp(cmd, "./", 2))
			ft_printf_err("minishell: %s: No such file or directory\n", cmd);
		else if (stat(str, &buffer) != 0)
			ft_printf_err("command '%s' not found\n", cmd);
		else if (access(cmd, R_OK))
			ft_printf_err("minishell: %s: Permission denied\n", cmd);
		else if (S_ISDIR(buffer.st_mode))
			ft_printf_err("minishell: %s: Is a directory\n", cmd);
		else if ((buffer.st_mode))
			ft_printf_err("minishell: %s: Permission denied\n", cmd);
		else
			ft_printf_err("command '%s' No such file or directory\n", cmd);
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

//TODO dizer ao pedro que mexi aqui L 78 e L86
char	**ft_make_arg_arr(t_token *token)
{
	t_token	*temp;
	char	**args;
	int		i;

	i = 0;
	if (!token)
		return (NULL);
	temp = token;
	while (temp && temp->type <= PIPE)
	{
		temp = temp->next;
		i++;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	temp = token;
	while (temp && temp->type <= PIPE)
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
	ft_execute(args_arr, env_arr, apended, token->data);
	free_args(env_arr);
	free_args(args_arr);
	free(apended);
}
