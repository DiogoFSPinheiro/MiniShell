/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:30:03 by diogosan          #+#    #+#             */
/*   Updated: 2024/08/30 16:18:51 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	client_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf("\nMiniHell$> ");
	}
	if (sig == SIGQUIT)
		ft_println("exit");
}

int	main(int c, char **v, char **envp)
{
	char		*input;
	char		*clean_input;
	t_token		*token;
	t_env		*env;
	//t_commands	*commands;
	struct sigaction	sa;

	(void)c;
	(void)v;
	env = NULL;
	token = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = client_handler;
	sa.sa_flags = SA_RESTART;
	set_up_sigaction(&sa);
	ft_create_env(envp, &env);
	while (1)
	{
		input = readline("MiniHell$> ");
		if (input == NULL || ft_strcmp(input, "exit") == SUCCESS)
		{
			free(input);
			ft_free_env(env);
			ft_println("exit");
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
				//commands = ft_build_commands(token);
				//ft_print_cmd(commands);
				free_tokens(token);
				//ft_free_cmd(commands);
			}
			free(input);
		}
	}
	//ft_free_env(env);
	return (0);
}

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
