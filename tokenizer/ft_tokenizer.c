/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:58:26 by rtakayam          #+#    #+#             */
/*   Updated: 2025/10/26 14:21:13 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_metacharacter(t_shell *sh)
{
	t_token			*new;
	t_quote_type	quote_type;

	new = NULL;
	quote_type = NONE;
	if (ft_strncmp(sh->line, ">>", 2) == 0)
		new = ft_tokenlst_new(ft_strdup(">>"), APPEND, quote_type, 0);
	else if (ft_strncmp(sh->line, "<<", 2) == 0)
		new = ft_tokenlst_new(ft_strdup("<<"), HEREDOC, quote_type, 0);
	else if (*sh->line == '|')
		new = ft_tokenlst_new(ft_strdup("|"), PIPE, quote_type, 0);
	else if (*sh->line == '>')
		new = ft_tokenlst_new(ft_strdup(">"), REDIRECT_OUT, quote_type, 0);
	else
		new = ft_tokenlst_new(ft_strdup("<"), REDIRECT_IN, quote_type, 0);
	// ft_tokenlst_clear(&new);///mallocチェックokメモリリークまだ
	// new = NULL;///
	if (!new)
		malloc_error(sh, NULL);
	ft_tokenlst_add_back(&sh->token, new);
	return (ft_strlen(new->str));
}

int	handle_word(t_shell *sh)
{
	char			*prm;
	t_token			*new;
	t_quote_type	quote_type;
	int				in_quote;
	int				word_len;
	int				is_joined_with_next;
	const char	*cur_line;

	cur_line = sh->line;
	prm = sh->line;
	new = NULL;
	word_len = 0;
	quote_type = NONE;
	is_joined_with_next = 0;
	in_quote = 0;

	while (*prm)
	{
		if (word_len && !in_quote
			&& (*prm == ' ' || *prm == '\t' || *prm == '"' || *prm == '\''
				|| *prm == '|' || *prm == '<' || *prm == '>'))
			break ;
		if ((quote_type != SINGLE && *prm == '"')
			|| (quote_type != DOUBLE && *prm == '\''))
		{
			if (in_quote)
			{
				prm++;
				cur_line++;//クオート分スキップ
				break ;
			}
			in_quote = 1;
			if (*prm == '\'')
				quote_type = SINGLE;
			else if (*prm == '"')
				quote_type = DOUBLE;
		}
		else
			word_len++;
		prm++;
	}
	if (*prm && *prm != ' ' && *prm != '\t'
		&& *prm != '|' && *prm != '<' && *prm != '>')
		is_joined_with_next = 1;
	if (word_len == 0)
		prm = ft_strdup("");
	else
		prm = ft_strndup(cur_line, word_len);
	new = ft_tokenlst_new(prm, WORD, quote_type, is_joined_with_next);
	// new = NULL;//mallocチェックokメモリリークまだ
	if (new == NULL)
		malloc_error(sh, NULL);
	ft_tokenlst_add_back(&sh->token, new);
	return (ft_strlen(new->str) + in_quote * 2);
}

// line が進んでしまってfree(line)の時promptの先頭をfreできなくなっていたので修正
// -> ここが都度挙動が変わってしまう原因だったと思われる
//current1009 : mallocないで解放してexitするように変更
void	tokenize_line(t_shell *sh)
{
	char	*cursor;
	char	*original_line;
	int		len;

	if (!sh || !sh->line)
		return ;
	original_line = sh->line;
	cursor = sh->line;
	while (cursor && *cursor)
	{
		while (*cursor == ' ' || *cursor == '\t')
			cursor++;
		if (*cursor == '\0')
			break ;

		sh->line = cursor;
		if (*cursor == '|' || *cursor == '<' || *cursor == '>')
			len = handle_metacharacter(sh);//malloc_errorは処理済み
		else
			len = handle_word(sh);//malloc_errorは処理済み
		if (len <= 0)
			cursor++;
		else
			cursor += len;
	}
	sh->line = original_line;
	//line = ""の時、""を一つのトークンとする
}
