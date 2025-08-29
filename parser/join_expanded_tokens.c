/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_expanded_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:18:26 by rinka             #+#    #+#             */
/*   Updated: 2025/08/29 13:43:46 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// t_cmd *ft_cmdlst_init(void)
// {
// 	t_cmd *new_cmd;

// 	new_cmd = malloc(sizeof(t_cmd));
// 	if (new_cmd == NULL)
// 		return (NULL):
// 		new_cmd->argv = NULL;
// 		new_cmd->env_vars = NULL;
// 		new_cmd->infile = NULL;
// 		new_cmd->outfile = NULL;
// 		new_cmd->append = 0;
// 		new_cmd->next = NULL;
// 		return (new_cmd);
// }

// t_cmd	*ft_cmdlst_new(char **cmd_args, char **env_vars, char *infile, char *outfile, int append)
// {
// 	t_cmd	*new;

// 	new = malloc(sizeof(t_cmd));
// 	if (new == NULL)
// 		return (NULL);
// 	new->cmd_args = cmd_args;
// 	new->env_vars = env_vars;
// 	new->infile = infile;
// 	new->outfile = outfile;
// 	new->append = append;
// 	return (new);
// }

char *ft_dupkey(char *str)//hello$TEST"world"の$TEST抜き出し
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
	(void)key;
	(void)token_lst;
	(void)env_lst;
	//有効変数処理＆return

	// if (is_redirect)
// 	{// ambiguous redirectエラー(t_cmdにafilename格納するときでいいかも)
// 		ambiguous_redirect_error(original, res, token_lst, env_lst);
// 	}
	printf("-----expand %s-----\n",key);////	
	return (ft_strdup("[expanddvalue]"));
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

//current: 環境変数展開＆is＿jointedの連結
//t_cmd関連関数の前に完成させてテストする（その前にt_envを持ってきてファイル構成テストも）
t_token *join_expanded_tokens(t_token **cmd_start, t_token **token_lst, t_env *env_lst)
{
	t_token *new_lst;
	t_token *newnode;
	t_token *current_lst;
	char *new_str;

	current_lst = *cmd_start;
	while (current_lst && current_lst->token_type != PIPE)//is_joined結合
	{
		if (is_delimiter(current_lst->str))//><>><<の時
		{
			newnode = ft_tokenlst_dup(current_lst);
			if (newnode == NULL)
			{//mallocエラー
				ft_tokenlst_clear(&new_lst);
				ft_tokenlst_clear(token_lst);
				ft_envlst_clear(&env_lst);
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
				current_lst->str = expanded_str;
				free(old_str);
			}
			if (!new_str)
				new_str = ft_strdup(current_lst->str);
			else
				new_str = ft_strjoin_safe(new_str, current_lst->str);
			if (new_str == NULL)
			{//mallocエラー
			 ft_tokenlst_clear(&new_lst);
				ft_tokenlst_clear(token_lst);
				ft_envlst_clear(&env_lst);
			 malloc_error();
			}///////
			if (current_lst->is_joined_with_next == 0)
			{
				current_lst = current_lst->next;
				break ;
			}
			current_lst = current_lst->next;
		}
		newnode = ft_tokenlst_new(new_str, WORD, 0, 0);
		if (newnode == NULL)
		{//mallocエラー処理
			ft_tokenlst_clear(&new_lst);
			ft_tokenlst_clear(token_lst);
			ft_envlst_clear(&env_lst);
			malloc_error();
		}///
		ft_tokenlst_add_back(&new_lst, newnode);
	}

	return (new_lst);
}