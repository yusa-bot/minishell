/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_expanded_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:18:26 by rinka             #+#    #+#             */
/*   Updated: 2025/09/14 16:33:25 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	is_valid_assignment(char *str)//key部分のquote_type=NONEは検証済みなのでkeyの文字だけチェック
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char *ft_dupkey(char *str)//hello$TEST"world"の$TEST抜き出し
{
	char *key;
	int i;

	i = 0;
	while(str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	key = ft_strndup(str, i);
	return (key);
}

char *expand_key(char *key, t_token **token_lst, t_env *env_lst)
{
	char *res;

	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
		{
			res = ft_strdup(env_lst->value);
			if (res == NULL)
			{//mallocエラー
				ft_tokenlst_clear(token_lst);
				ft_lst_clear(&env_lst);
			 malloc_error();
			}////////
			return (res);
		}
		env_lst = env_lst->next;
	}
	return (ft_strdup(""));
}

char *expand_vars(const t_token *original, t_token **token_lst, t_env *env_lst)
{
	char *key;
	char *res;
	char *value;
	char *current;

	current = original->str;
	res = NULL;
	while (*current)
	{
		if (*current == '$' && *(current + 1) && (ft_isalpha(*(current + 1)) || *(current + 1) == '_' || *(current + 1) == '?'))
		{
			current++;
			if (*current == '?')
			{
				// value = 直前の終了コード
				res = ft_strjoin_safe(res, "0000");//仮
				current += 1;
			}
			else
			{
				//keyを抜きとってexpense_keyで一つ変数展開
				key = ft_dupkey(current);
				value = expand_key(key, token_lst, env_lst);
				res = ft_strjoin_safe(res, value);
				current += ft_strlen(key);
				free(key);
				free(value);
			}
		}
		else if (*current == '$')
		{
			if (*(current + 1) || original->quote_type != NONE || !original->is_joined_with_next)
				res = ft_strjoin_safe(res, "$");
			current += 1;
		}
		else
		{
			if (ft_strchr(current, '$'))
			{
				value = ft_strndup(current, ft_strchr(current, '$') - current);
			}
			else
			{
				value = ft_strdup(current);
			}
			res = ft_strjoin_safe(res, value);
			current += ft_strlen(value);
			free (value);
		}
	}
	if (!res)
	{
		res = ft_calloc(sizeof(char), 1);
	}
	return (res);
}

//t_cmd関連関数の前に完成させてテストする（その前にt_envを持ってきてファイル構成テストも）
t_token *join_expanded_tokens(t_token **cmd_start, t_token **token_lst, t_env *env_lst)
{
	t_token *new_lst;
	t_token *newnode;
	t_token *current_lst;
	char *new_str;
	t_token_type	token_type;
	char *original_var;

	new_lst = NULL;
	current_lst = *cmd_start;
	// token_type = WORD;ß
	if (current_lst->token_type == PIPE)//どこでチェックが最適か
		syntax_error("|", token_lst,&env_lst);
	// while (current_lst && current_lst->quote_type != NONE && ft_strchr(current_lst->str, '='))
	// {

	// }
	while (current_lst && current_lst->token_type != PIPE)//is_joined結合
	{
		original_var = NULL;
		token_type = WORD;
		if (is_delimiter(current_lst->str))//><>><<の時
		{
			newnode = ft_tokenlst_dup(current_lst);
			if (newnode == NULL)
			{//mallocエラー
				ft_tokenlst_clear(&new_lst);
				ft_tokenlst_clear(token_lst);
				ft_lst_clear(&env_lst);
			 malloc_error();
			}////////
			ft_tokenlst_add_back(&new_lst, newnode);
			current_lst = current_lst->next;
			continue ;
		}
		new_str = NULL;
		while (current_lst)//now: $"~"（str="$" && is_join_next=1）の時、$は空文字
		{
			if (current_lst->quote_type != SINGLE && ft_strchr(current_lst->str, '$'))//まず変数展開
			{
				//変数展開
				char *old_str = current_lst->str;
				char *expanded_str = expand_vars(current_lst, token_lst, env_lst);
				if (is_delimiter(ft_tokenlst_last(new_lst)->str))
					original_var = ft_strjoin_safe(original_var, old_str);
				current_lst->str = expanded_str;
				free(old_str);
			}
			if (!new_str && current_lst->quote_type == NONE && ft_strchr(current_lst->str, '=') && is_valid_assignment(current_lst->str))
				token_type = VARIABLE_ASSIGNMENT;
			if (!new_str)
				new_str = ft_strdup(current_lst->str);
			else
				new_str = ft_strjoin_safe(new_str, current_lst->str);
			if (new_str == NULL)
			{//mallocエラー
			 ft_tokenlst_clear(&new_lst);
				ft_tokenlst_clear(token_lst);
				ft_lst_clear(&env_lst);
			 malloc_error();
			}///////
			if (current_lst->is_joined_with_next == 0)
			{
				current_lst = current_lst->next;
				break ;
			}
			current_lst = current_lst->next;
		}
		//↓一時的な環境変数がTEST~=testのような無効な構文の場合、TEST~=testはコマンド名として扱われる。
		newnode = ft_tokenlst_new(new_str, token_type, 0, 0);
		if (newnode == NULL)
		{//mallocエラー処理
			ft_tokenlst_clear(&new_lst);
			ft_tokenlst_clear(token_lst);
			ft_lst_clear(&env_lst);
			malloc_error();
		}///
		if (original_var)//current : redirectでnex_str == ""でoriginal_varの時、元の変数名を保存これをparser.cでも引き継ぐ
		{
			if (ft_tokenlst_last(new_lst)->token_type == REDIRECT_IN)
				newnode->original_str = original_var;
			else if (ft_tokenlst_last(new_lst)->token_type == REDIRECT_OUT || ft_tokenlst_last(new_lst)->token_type == APPEND)
				newnode->original_str = original_var;
		}
		ft_tokenlst_add_back(&new_lst, newnode);
	}
	*cmd_start = current_lst;
	if (*cmd_start)
		*cmd_start = (*cmd_start)->next;
	return (new_lst);
}
