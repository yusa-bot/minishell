#ifndef TOKENIZER_PEARSER_H
# define TOKENIZER_PEARSER_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"

typedef enum	e_token_type {
	CMD,// コマンド
	ARG,// 引数
	PIPE,// |
	VARIABLE,//$変数
	REDIRECT_IN,// < 
	REDIRECT_OUT,// >
	APPEND,// >>
	HEREDOC,// <<
	FILENAME,//ファイル名
	WORD,//コマンドか$変数か引数（未確定）
} t_token_type;

typedef enum e_quote_type {
	NONE,//クオート無し
	SINGLE,// ''
	DOUBLE,// ""
} t_quote_type;

typedef struct s_token {
	 char *str;
		t_token_type token_type;
		t_quote_type quote_type;
		int	is_joined_with_next;
		struct s_token *next;
} t_token;

t_token *tokenize_line(char *line);

//ft_utils.c
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);

// //ft_utils.c
// int	ft_strcmp(const char *s1, const char *s2);
// char	*ft_strndup(const char *s, size_t n);

//ft_tokenlst_utils.c
void	ft_tokenlst_delone(t_token *lst);
void	ft_tokenlst_clear(t_token **lst);
t_token *ft_tokenlst_last(t_token *lst);
void	ft_tokenlst_add_back(t_token **lst, t_token *new);
void	ft_tokenlst_add_front(t_token **lst, t_token *new);
t_token *ft_tokenlst_new(char *str, t_token_type token_type, t_quote_type quote_type, int is_joined_with_next);

// void ft_put_exports(t_env *env_lst, int fd);

// void ft_unset(t_env **lst, char *delkey);

#endif