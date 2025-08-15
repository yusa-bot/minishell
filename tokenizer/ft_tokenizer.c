/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakayam <rtakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:58:26 by rtakayam          #+#    #+#             */
/*   Updated: 2025/08/15 19:21:52 by rtakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_perser.h"

int	handle_metacharacter(t_token **token_lst, char *line)
{
	t_token			*new;
	t_quote_type	quote_type;

	new = NULL;
	quote_type = NONE;
	if (ft_strncmp(line, ">>", 2) == 0)
		new = ft_tokenlst_new(ft_strdup(">>"), APPEND, quote_type, 0);
	else if (ft_strncmp(line, "<<", 2) == 0)
		new = ft_tokenlst_new(ft_strdup("<<"), HEREDOC, quote_type, 0);
	else if (*line == '|')
		new = ft_tokenlst_new(ft_strdup("|"), PIPE, quote_type, 0);
	else if (*line == '>')
		new = ft_tokenlst_new(ft_strdup(">"), REDIRECT_OUT, quote_type, 0);
	else
		new = ft_tokenlst_new(ft_strdup("<"), REDIRECT_IN, quote_type, 0);
	ft_tokenlst_add_back(token_lst, new);
	return (ft_strlen(new->str));
}

int	handle_word(t_token **token_lst, char *line)
{
	char			*p;
	t_token			*new;
	t_quote_type	quote_type;
	int				in_quote;
	int				word_len;
	int				is_joined_with_next;

	p = line;
	new = NULL;
	word_len = 0;
	quote_type = NONE;
	is_joined_with_next = 0;
	in_quote = 0;
	while (*p)
	{
		if (word_len && !in_quote
			&& (*p == ' ' || *p == '\t' || *p == '"' || *p == '\''))
			break ;
		if ((quote_type != SINGLE && *p == '"')
			|| (quote_type != DOUBLE && *p == '\''))
		{
			if (in_quote)
			{
				p++;
				line++;//クオート分スキップ
				break ;
			}
			in_quote = 1;
			if (*p == '\'')
				quote_type = SINGLE;
			else if (*p == '"')
				quote_type = DOUBLE;
		}
		else
			word_len++;
		p++;
	}
	if (word_len == 0)
		return (in_quote * 2);
	if (*p == '"' || *p == '\'')
		is_joined_with_next = 1;
	p = ft_strndup(line, word_len);
	if (p == NULL)
	{
		// ft_tokenlst_clear(token_lst);
		// error_exit("malloc error");
		return (0);
	}
	new = ft_tokenlst_new(p, WORD, quote_type, is_joined_with_next);
	//↑tokeniseのじてんではファイル名や変数名もWORDとしておく
	ft_tokenlst_add_back(token_lst, new);
	return (ft_strlen(new->str) + in_quote * 2);
}

t_token	*tokenize_line(char *line)
{
	t_token	*token_lst;

	token_lst = NULL;
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
			break ;
		if (*line == '|' || *line == '<' || *line == '>')
			line += handle_metacharacter(&token_lst, line);
		else
			line += handle_word(&token_lst, line);
	}
	return (token_lst);
}

/*
current: code "handle_word"
・he''lloにも対応するft_tokendupを作る
・handle_word内で環境変数$に対応
*/
