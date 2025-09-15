/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:11:30 by rtakayam          #+#    #+#             */
/*   Updated: 2025/09/14 20:03:21 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type
{
	PIPE,
	VARIABLE,
	REDIRECT_IN,// <
	REDIRECT_OUT,// >
	APPEND,// >>
	HEREDOC,// <<
	FILENAME,
	INFILE,//リダイレクトのファイル名（確定）
	WORD,
	VARIABLE_ASSIGNMENT,
}	t_token_type;

typedef enum e_quote_type
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote_type;

typedef struct s_token
{
	char			*str;
	char			*original_str;
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
