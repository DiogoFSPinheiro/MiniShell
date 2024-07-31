/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogosan <diogosan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:37:41 by diogosan          #+#    #+#             */
/*   Updated: 2024/07/31 16:11:38 by diogosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include "libraries/printf/ft_printf.h"

# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_exit
{
	SUCCESS,
	FAILURE,
}	t_exit;

/*
	comands:
	ECHO,
	CD,
	PWD,
	EXPORT,
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

typedef struct s_token
{
	char				*data;
	t_type				type;
	struct s_token		*next;
}	t_token;

void	hello_print(t_type name);
void	ft_print_info(t_token *token);

void	ft_init_token(t_token *token, char *data);
void	ft_data_type(t_token *token, bool reset);

char	*ft_input_spliter(char *str);
void	ft_find_expand(t_token **token);
void	ft_view_data(char *data);


int		ft_strcmp(const char *s1, const char *s2);
int		ft_check_triples(char *input);
int		ft_space_redirect(char *input);
int		ft_clean_size(char *str);
int		ft_skip_quotes(char *input, int *c, char i);
void	ft_skip_quotes_w(char *input, char **dst, int *c, int *i);
void	ft_space_skiper(char *str, int *c);

//------------Meh funcs----------------
void	ft_reset_int(int *c, int *i);
void	ft_space_helper(char *str, char **dst, int *c, int *i);
void	ft_count_helper(char *str, int *c, int *size);

int		ft_syntax_redirects(char *input);
int		ft_syntax_pipes(char *input);

//------------ft_quotes_split.c-------
char	**ft_quotes_split(char *s, char c);
int		words_quotes(char *s, char c);

//------------free_funcs.c -------
void	free_tokens(t_token *stack);

//------------syntax2.c -------
int		ft_validation_input(char *input);

#endif
