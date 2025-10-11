/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:58:26 by rtakayam          #+#    #+#             */
/*   Updated: 2025/10/10 12:54:51 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_metacharacter(t_token **token_lst, char *line, t_env *env_lst)
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
	// ft_tokenlst_clear(&new);///mallocチェックokメモリリークまだ
	// new = NULL;///
	if (!new)
		malloc_error(token_lst, NULL, &env_lst, NULL);
	ft_tokenlst_add_back(token_lst, new);
	return (ft_strlen(new->str));
}

int	handle_word(t_token **token_lst, char *line, t_env *env_lst)
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
	if (*p && *p != ' ' && *p != '\t')
		is_joined_with_next = 1;
	if (word_len == 0)
		p = ft_strdup("");
	else
		p = ft_strndup(line, word_len);
	new = ft_tokenlst_new(p, WORD, quote_type, is_joined_with_next);
	// new = NULL;//mallocチェックokメモリリークまだ
	if (new == NULL)
		malloc_error(token_lst, NULL, &env_lst, NULL);
	//↑tokeniseのじてんではファイル名や変数名もWORDとしておく
	ft_tokenlst_add_back(token_lst, new);
	return (ft_strlen(new->str) + in_quote * 2);
}

//current1009 : mallocないで解放してexitするように変更
t_token	*tokenize_line(char *line, t_env *env_lst)
{
	t_token	*token_lst;
	int len;

	token_lst = NULL;
	len = 0;
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
			break ;
		if (*line == '|' || *line == '<' || *line == '>')
		{
			len = handle_metacharacter(&token_lst, line, env_lst);
			//↑malloc_errorは処理済み
			line += len;
		}
		else
		{
			len = handle_word(&token_lst, line, env_lst);
			//↑malloc_errorは処理済み
			line += len;
		}
	}
	//line = ""の時、""を一つのトークンとする
	return (token_lst);
}

//要修正 : ca''t'' -e の時、cat-eになってしまう