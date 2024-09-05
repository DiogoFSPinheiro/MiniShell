/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:37:41 by diogosan          #+#    #+#             */
/*   Updated: 2024/09/05 19:08:46 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include "libraries/printf/ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef enum e_exit
{
	FAILURE,
	SUCCESS,
}	t_exit;

/*
	comands:
	ECHO,
	CD,
	PWD,
	EXPORT,teste
	UNSET,
	ENV,
	EXIT,
*/

typedef struct s_env
{
	char			*title;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef enum e_type
{
	CMD,
	BUILT_IN,
	EXIT,
	STR,
	FLAG,
	PIPE,
	R_IN,
	R_IN2,
	R_OUT,
	R_OUT2,
}	t_type;

typedef enum e_bultins
{
	flag_err,
	args_err,
	no_file,
	env_err_flag,
	file_permissions,
	no_home,
	invalid_identifier
}	t_builins;

typedef struct s_token
{
	char				*data;
	t_type				type;
	struct s_token		*next;
}	t_token;

typedef struct s_commands
{
	struct s_token		*tokens;
	int					fd[2];
	struct s_commands	*next;
}	t_commands;

typedef struct s_ints
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
}	t_ints;

//------------tester.c----------------
void	ft_print_info(t_token *token);
void	ft_print_cmd(t_commands *cmd);

//------------main.c----------------
void	ft_init_token(t_token *token, char *data);

//------------type_check.c----------------
void	ft_data_type(t_token *token);

//------------expand.c----------------
void	ft_find_expand(t_token **token, t_env *env);
int		ft_set_quotes_bool(char c, int *in_double_quote, int *in_single_quote);
char	*ft_strdup_no_quotes(char const *src);

//------------token_utils.c----------------
int		ft_clean_size(char *str);
char	*ft_input_spliter(char *str);

//------------syntax.c----------------
int		ft_skip_quotes(char *input, int *c, char i);
int		ft_syntax_redirects(char *input);
int		ft_syntax_pipes(char *input);

//------------ft_quotes_split.c-------
char	**ft_quotes_split(char *s, char c);
int		words_quotes(char *s, char c);
void	ft_skip(char **str, char i);

//------------free_funcs.c -------
void	free_tokens(t_token *stack);
void	ft_free_env(t_env *env);
void	ft_free_cmd(t_commands *cmd);

//------------syntax2.c -------
int		ft_validation_input(char *input);

//------------utils.c -------
int		ft_strcmp(const char *s1, const char *s2);
int		ft_check_triples(char *input);
int		ft_space_redirect(char *input);
char	*ft_strcat(char *str1, char *str2);
char	*ft_array_strjoin(char **array);

//------------utils2.c -------
void	ft_space_skiper(char *str, int *c);
void	ft_reset_int(int *c, int *i);
void	ft_count_helper(char *str, int *c, int *size);
void	ft_skip_quotes_w(char *input, char **dst, int *c, int *i);
void	ft_space_helper(char *str, char **dst, int *c, int *i);

//------------utils3.c -------
t_env	*ft_get_content(t_env *env, char *title);
int		ft_get_full_size(char *str, t_env *env);
void	set_up_sigaction(struct sigaction *sa);
int		ft_token_counter_until_redd(t_token *token);

//------------build_commands.c -------
t_commands	*ft_build_commands(t_token *token);

//------------create_env.c -------
void	ft_create_env(char **envp, t_env **env);
int		ft_see_equal(char *str);

//------------redirections.c -------
int		ft_redirect_out(t_token *token);
int		ft_redirect_in(t_token *token);
int		ft_handle_redirects(t_commands *cmd);
t_token	*ft_token_dup(t_token *token);

//------------heredoc.c  -------
void	ft_build_heredoc(t_commands **cmd, t_commands *head);

//---------------PEDRO-----------------

//------------ft_execute.c------
int		ft_see_redirect(t_token *token);

//-----------------ft_execute_in.c------
void	ft_execute_in(t_token *token, t_env **env);
int		ft_built_in(t_token *token, t_env **env);
void	ft_send_to_execve(t_token *token, t_env *env);
int		ft_redd_or_pipes(t_token *token);


//-----------------ft_env.c-----------
void	ft_env(t_env *env, t_token *token);

//----------------ft_pwd.c ----------
void	ft_pwd(t_token *token);

//----------------ft_echo.c----------
void	ft_echo(t_token *token);

//-----------------ft_cd.c------------
void	ft_cd(t_token *token, t_env **env);

//-----------------ft_unset.c------------
void	ft_unset(t_env **env, t_token *token);

//---------------ft_built_err----------
void	ft_built_err(t_token *token, t_builins err_type);
char	*ft_path_to_executable(char **paths, char *command);

//---------------ft_export.c-------------
void    ft_export(t_token *token, t_env **env);

//----------------- utils----------------
char	*ft_path(void);
char	*ft_get_env(t_env *env, char *str);
char	*ft_strjoin_free(char *s1, char *s2);


char	*ft_right_path(t_token *token, t_env *env);


#endif
