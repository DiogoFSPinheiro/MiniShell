/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:18:01 by pebarbos          #+#    #+#             */
/*   Updated: 2024/09/03 19:22:58 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_built_err(t_token *token, t_builins err_type)
{
	if (err_type == flag_err)
		ft_printf_err("Minishell: %s : -%c: invalid option\n%s: "
			"usage: has no options in Minishell\n", token->data,
			token->next->data[1], token->data);
	if (err_type == args_err)
		ft_printf_err("Minishell: %s: too many arguments\n", token->data);
	if (err_type == file_permissions)
		ft_printf_err("Minishell: %s: %s: Permission denied\n",
			token->data, token->next->data);
	if (err_type == no_file)
		ft_printf_err("Minishell: %s: %s: "
			"No such file or directory\n", token->data, token->next->data);
	if (err_type == no_home)
		ft_printf_err("Minishell: %s: HOME not set\n", token->data);
	if (err_type == file_permissions)
		ft_printf_err("Minishell: %s: Permission denied\n", token->data);
	if (err_type == invalid_identifier)
		ft_printf_err("Minishell: export: `%s': not a valid identifier\n", token->data); //err code 1
}

 // flag errors exept env
// ---------- ERRORS----------
/*
bash: cd: pasta/: Permission denied       cd to a folder that has no permissions 
bash: cd: HOME not set                    try to cd after unseting HOME


env: ‘random_text’: No such file or directory	 ****env error next command is not a tile
env: invalid option -- 'y'						 env error with flags
Try 'env --help' for more information.			 has no options in Minishell
env: ‘pedro_files/’: Permission denied           env error file exists 

*/