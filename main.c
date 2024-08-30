/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pebarbos <pebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/30 10:40:39 by pebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_see_equal(char *str)
{
	int	c;

	c = 0;
	while (str[c] != '=')
		c++;
	return (c);
}

void	ft_create_env(char **envp, t_env **env)
{
	int		c;
	int		i;
	t_env	*cur;
	int		s;

	c = 0;
	i = ft_arraylen(envp);
	*env = (t_env *)ft_calloc(sizeof(t_env), i);
	cur = *env;
	while (c < i)
	{
		cur = *env + c;
		s = ft_see_equal(envp[c]);
		cur->title = ft_fine_strdup(envp[c], 0, s - 1);
		cur->content = ft_strdup(envp[c] + s + 1);
		if (envp[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
}

int	main(int c, char **v, char **envp)
{
	char		*input;
	char		*clean_input;
	t_token		*token;
	t_env		*env;
	t_commands	*commands;

	(void)c;
	(void)v;
	(void)commands;
	env = NULL;
	token = NULL;
	ft_create_env(envp, &env);
	while (1)
	{
		input = readline("MiniHell$> ");
		if (input == NULL || ft_strcmp(input, "exit") == SUCCESS)
		{
			free(input);
			ft_free_env(env);
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (ft_validation_input(input) == FAILURE)
				ft_println("Wrong Syntax");
			else
			{
				clean_input = ft_input_spliter(input);
				token = ft_calloc(sizeof(t_token), words_quotes(clean_input, ' '));
				free(clean_input);
				ft_init_token(token, input);
				ft_find_expand(&token, env);
				ft_execute_in(token, &env);
				//ft_print_info(token);
				commands = ft_build_commands(token);
				//ft_print_cmd(commands);
				free_tokens(token);
				ft_free_cmd(commands);
			}
			free(input);
		}
		
	}
	//ft_free_env(env);
	return (0);
}//random changes

void	ft_init_token(t_token *token, char *data) // data
{
	char	**info;
	char	*clean_input;
	int		c;
	t_token	*cur;

	c = 0;
	clean_input = ft_input_spliter(data);
	info = ft_quotes_split(clean_input, ' ');
	free(clean_input);
	while (info[c])
	{
		cur = token + c;
		cur->data = ft_strdup(info[c]);
		ft_data_type(cur);
		if (info[c + 1])
			cur->next = cur + 1;
		else
			cur->next = NULL;
		c++;
	}
	free_args(info);
}
