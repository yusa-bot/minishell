/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:11:30 by rtakayam          #+#    #+#             */
/*   Updated: 2025/08/24 12:12:43 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type
{
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
}	t_token_type;

typedef enum e_quote_type
{
	NONE,//クオート無し
	SINGLE,// ''
	DOUBLE,// ""
}	t_quote_type;

typedef struct s_token
{
	char			*str;
	t_token_type	token_type;
	t_quote_type	quote_type;
	int				is_joined_with_next;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char		**cmd_args;
	char		**env_vars;//一時的な環境変数
	char	*infile;
	char	*outfile;
	int	append;
	struct s_cmd	*next;
}	t_cmd;

t_token	*tokenize_line(char *line);

//ft_tokenlst_utils.c
void	ft_tokenlst_delone(t_token *lst);
void	ft_tokenlst_clear(t_token **lst);
t_token	*ft_tokenlst_last(t_token *lst);
void	ft_tokenlst_add_back(t_token **lst, t_token *new);
void	ft_tokenlst_add_front(t_token **lst, t_token *new);
t_token	*ft_tokenlst_new(char *str, t_token_type token_type,
			t_quote_type quote_type, int is_joined_with_next);

#endif