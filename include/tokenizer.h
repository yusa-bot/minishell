/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:11:30 by rtakayam          #+#    #+#             */
/*   Updated: 2025/08/31 13:17:29 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type
{
	CMD,// コマンド(いらないかも)
	ARG,// 引数（いらないかも）
	PIPE,// |
	VARIABLE,//$変数
	REDIRECT_IN,// < 
	REDIRECT_OUT,// >
	APPEND,// >>
	HEREDOC,// <<
	FILENAME,//ファイル名
	WORD,//コマンドか$変数か引数（未確定）
	VARIABLE_ASSIGNMENT,//一時的な変数代入
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