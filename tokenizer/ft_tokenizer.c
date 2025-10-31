/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:58:26 by rtakayam          #+#    #+#             */
/*   Updated: 2025/10/31 18:22:55 by rinka            ###   ########.fr       */
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

static int	handle_char(char **prm ,int *word_len, int *in_quote, t_quote_type *quote_type)
{
	if (*word_len && !(*in_quote)
		&& (**prm == ' ' || **prm == '\t' || **prm == '"' || **prm == '\''
			|| **prm == '|' || **prm == '<' || **prm == '>'))
		return (1);
	if ((*quote_type != SINGLE && **prm == '"')
		|| (*quote_type != DOUBLE && **prm == '\''))
	{
		if (*quote_type != NONE)
		{
			(*prm)++;
			return (1);
		}
		*in_quote = 1;
		if (**prm == '\'')
			*quote_type = SINGLE;
		else if (**prm == '"')
			*quote_type = DOUBLE;
	}
	else
		(*word_len)++;
	return (0);
}

static int	handle_word(t_shell *sh, int is_joined_with_next, int in_quote, int word_len)
{
	char			*prm;
	t_token			*new;
	t_quote_type	quote_type;

	prm = sh->line;
	quote_type = NONE;
	while (prm && *prm)
	{
		if (handle_char(&prm ,&word_len, &in_quote, &quote_type))
			break ;
		prm++;
	}
	if (*prm && *prm != ' ' && *prm != '\t'
		&& *prm != '|' && !is_delimiter(prm))
		is_joined_with_next = 1;
	if (word_len == 0)
		prm = ft_strdup("");
	else
		prm = ft_strndup(&sh->line[in_quote], word_len);
	new = ft_tokenlst_new(prm, WORD, quote_type, is_joined_with_next);
	if (new == NULL)
		malloc_error(sh, NULL);
	ft_tokenlst_add_back(&sh->token, new);
	return (ft_strlen(new->str) + in_quote * 2);
}

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
			len = handle_metacharacter(sh);
		else
			len = handle_word(sh, 0, 0, 0);
		if (len <= 0)
			cursor++;
		else
			cursor += len;
	}
	sh->line = original_line;
	//line = ""の時、""を一つのトークンとする
}
