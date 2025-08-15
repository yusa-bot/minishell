
#include "tokenizer_perser.h"

int	handle_metacharacter(t_token **token_lst, char *line)
{
	t_token *new;
	t_token_type token_type;
	t_quote_type quote_type;

	new = NULL;
	quote_type = NONE;
	if (ft_strncmp(line, ">>", 2) == 0)
	{
		token_type = APPEND;
		new = ft_tokenlst_new(ft_strdup(">>"), token_type, quote_type, 0);
	}
	else if (ft_strncmp(line, "<<", 2) == 0)
	{
		token_type = HEREDOC;
		new = ft_tokenlst_new(ft_strdup("<<"), token_type, quote_type, 0);
	}
	else if (*line == '|')
	{
		token_type = PIPE;
		new = ft_tokenlst_new(ft_strdup("|"), token_type, quote_type, 0);
	}
	else if (*line == '>')
	{
		token_type = REDIRECT_OUT;
		new = ft_tokenlst_new(ft_strdup(">"), token_type, quote_type, 0);
	}
	else
	{
		token_type = REDIRECT_IN;
		new = ft_tokenlst_new(ft_strdup("<"), token_type, quote_type, 0);
	}

	ft_tokenlst_add_back(token_lst, new);
	return (ft_strlen(new->str));
}

int	handle_word(t_token **token_lst, char *line)
{
	char *p;
	t_token *new;
	t_token_type token_type;
	t_quote_type quote_type;
	int	in_quote;
	int	word_len;
	int	is_joined_with_next;

	p = line;
	new = NULL;
	word_len = 0;
	token_type = WORD;
	quote_type = NONE;
	is_joined_with_next = 0;
	in_quote = 0;
	while (*p)
	{
		if (word_len && !in_quote && (*p == ' ' || *p == '\t' || *p == '"' || *p == '\'') )
		{
			break ;
		}
		if (quote_type != DOUBLE && *p == '\'')
		{
			if (in_quote)
			{
				p++;
				line++;//クオート分スキップ
				break ;
			}
			else
			{
				in_quote = 1;
				quote_type = SINGLE;
			}
		}
		else if (quote_type != SINGLE && *p == '"')
		{
			if (in_quote)
			{
				p++;
				line++;//クオート分スキップ
				break ;
			}
			else
			{
				in_quote = 1;
				quote_type = DOUBLE;
			}
		}
		else
		{
			word_len++;
		}
		p++;
	}
	if (word_len == 0)
		return (in_quote * 2);
	if (*p == '"' || *p == '\'')
		is_joined_with_next = 1;
	p = ft_strndup(line, word_len);//he''lloにも対応するft_tokendupを作る
	new = ft_tokenlst_new(p, token_type, quote_type, is_joined_with_next);
	ft_tokenlst_add_back(token_lst, new);
	return (ft_strlen(new->str) + in_quote * 2);
}

t_token *tokenize_line(char *line)
{
	t_token	*token_lst;
	t_token *new;
	t_token_type token_type;
	t_quote_type quote_type;
	char *str;

	token_lst = NULL;
	str = ft_strdup(line);
	token_type = 0;
	quote_type = 0;

	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
			break ;
		if (*line == '|' || *line == '<' ||  *line == '>')
			line += handle_metacharacter(&token_lst, line);
		else
			line += handle_word(&token_lst, line);
	}

	
	// new = ft_tokenlst_new(str, token_type, quote_type);
	// ft_tokenlst_add_back(&token_lst, new);

	// i = 0;
	// while (line[i])
	// {
	// 	if ()
	// }
	return (token_lst);
}

/*
current: code "handle_word"
・he''lloにも対応するft_tokendupを作る
・handle_word内で環境変数$に対応
*/
