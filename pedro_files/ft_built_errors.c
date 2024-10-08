/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:18:01 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/21 17:27:43 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// use -1 to get the error that is in there use any other to chage it
int	ft_change_global_err(int err)
{
	static int	error_code;

	if (err == -1)
		return (error_code);
	error_code = err;
	return (error_code);
}

void	ft_last_errors(t_token *token, t_builins err_type)
{
	if (err_type == no_directory)
		ft_printf_err("Minishell: %s: %s: Not a directory\n",
			token->data, token->next->data);
	else if (err_type == invalid_identifier)
		ft_printf_err("Minishell: export: `%s': not a valid identifier\n",
			token->data);
	if (ft_change_global_err(-1) == 0)
		ft_change_global_err(1);
}

void	ft_more_errors(t_token *tkn, t_builins err_type)
{
	if (err_type == no_file && !ft_strcmp(tkn->data, "cd"))
	{
		ft_printf_err("Minishell: %s: No such file or directory\n", tkn->data);
		ft_change_global_err(127);
	}
	else if (err_type == cmd_not_found)
	{
		ft_printf_err("Minishell: command '%s' not found\n", tkn->data);
		ft_change_global_err(127);
	}
	else if (err_type == alpha_on_num)
	{
		ft_printf_err("Minishell: %s: %s: numeric argument required\n",
			tkn->data, tkn->next->data);
		ft_change_global_err(2);
	}
	else if (err_type == args_err)
		ft_printf_err("Minishell: %s: too many arguments\n", tkn->data);
	else if (err_type == no_file)
		ft_printf_err("Minishell: %s: %s: "
			"No such file or directory\n", tkn->data, tkn->next->data);
	else if (err_type == no_home)
		ft_printf_err("Minishell: %s: HOME not set\n", tkn->data);
	ft_last_errors(tkn, err_type);
}

// The error is set to 0 at the start to reset it,
// i know it will change in this func
void	ft_built_err(t_token *token, t_builins err_type)
{
	ft_change_global_err(0);
	if (err_type == flag_err_env || err_type == flag_err)
	{
		ft_printf_err("Minishell: %s : -%c: invalid option\n%s: "
			"usage: has no options in Minishell\n", token->data,
			token->next->data[1], token->data);
		if (err_type == flag_err_env)
			ft_change_global_err(125);
		else
			ft_change_global_err(2);
	}
	else if (err_type == file_permissions && !ft_strcmp(token->data, "cd"))
	{
		ft_printf_err("Minishell: %s: Permission denied\n", token->data);
		ft_change_global_err(126);
	}
	else if (err_type == is_dir)
	{
		ft_printf_err("Minishell: %s: Is a directory\n", token->data);
		ft_change_global_err(126);
	}
	else if (err_type == file_permissions)
		ft_printf_err("Minishell: %s: %s: Permission denied\n",
			token->data, token->next->data);
	ft_more_errors(token, err_type);
}

// flag errors exept env
// env flag error is 125
// flag errror is usually 2
// ---------- ERRORS----------
/*
bash: cd: pasta/: Permission denied       cd to a folder that has no permissions 
bash: cd: HOME not set                    try to cd after unseting HOME


env: ‘random_text’: No such file or directory
 ****env error next command is not a tile
env: invalid option -- 'y'						 env error with flags
Try 'env --help' for more information.			 has no options in Minishell
env: ‘pedro_files/’: Permission denied           env error file exists 

*/