
// #include "minishell.h"

// // t_cmd *ft_cmdlst_init(void)
// // {
// // 	t_cmd *new_cmd;

// // 	new_cmd = malloc(sizeof(t_cmd));
// // 	if (new_cmd == NULL)
// // 		return (NULL):
// // 		new_cmd->argv = NULL;
// // 		new_cmd->env_vars = NULL;
// // 		new_cmd->infile = NULL;
// // 		new_cmd->outfile = NULL;
// // 		new_cmd->append = 0;
// // 		new_cmd->next = NULL;
// // 		return (new_cmd);
// // }

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

// char *expense_vars(char *original, t_token **token_lst, t_env *env_lst)
// {
// }

// //current1: 環境変数展開＆is＿jointedの連結
// //t_cmd関連関数の前に完成させてテストする（その前にt_envを持ってきてファイル構成テストも）
// t_token join_words(t_token **cmd_start, t_token **token_lst, t_env *env_lst)
// {
// 	t_token *new_lst;
// 	t_token *newnode;
// 	t_token *current_lst;
// 	char *new_str;

// 	current_lst = *cmd_start;
// 	while (current_lst && current_lst->tokne_type != PIPE)//is_joined結合
// 	{
// 		if (is_delimiter(current_lst->str))//><>><<の時
// 		{
// 			newnode = ft_tokenlst_dup(current_lst);//まだ作ってない
// 			if (newnode == NULL)
// 			{//mallocエラー
// 				ft_tokenlst_clear(new_lst);
// 				ft_tokenlst_clear(token_lst);
// 				ft_envlst_clear(env_lst);
// 			 malloc_error();
// 			}
// 			ft_tokenlst_add_back(&new_lst, newnode);
// 			current_lst = current_lst->next;
// 			continue ;
// 		}
// 		new_str = NULL;
// 		while (current_lst)
// 		{
// 			if (!new_str)
// 				new_str = ft_strdup(current_lst->str);
// 			current_lst = current_lst->next;
// 			if (current_lst->quote_type != SINGLE && ft_strchr(current_lst->str, '$'))//まず変数展開
// 			{
// 				//変数展開
// 			}
// 			new_str = ft_strjoin_safe(new_str, current_lst->str);
// 			if (new_str == NULL)
// 			{//mallocエラー
// 			 ft_tokenlst_clear(new_lst);
// 				ft_tokenlst_clear(token_lst);
// 				ft_envlst_clear(env_lst);
// 			 malloc_error();
// 			}
// 			if (current_lst->is_joined_with_next == 1)
// 		}
// 		new = ft_tokenlst_new(new_str, WORD, 0, 0);
// 		if (newnode == NULL)
// 		{
// 			//mallocエラー処理
// 		}
// 		ft_tokenlst_add_back(&new_lst, newnode);
// 		current_lst = current_lst->next;
// 	}
// 	return (new_lst);
// }

// //current2：コマンド一個分の情報格納する関数
// //t_env持ってきて変数展開する
// t_cmd *ft_parse_single_cmd(t_token **cmd_start, t_token **token_lst, t_env *env_lst)
// {
// // 	t_token *current_lst
// 	t_cmd res;
// 	char		**cmd_args;
// 	char **env_vars;
// 	char	*infile;
// 	char	*outfile;
// 	int	append;//

// 	infile = NULL;
// 	outfile = NULL;
// 	if (current_lst->token_type == PIPE)//どこでチェックが最適か
// 		syntax_error("|", token_lst);
//  join_words(cmd_start, token_lst, env_lst)
// 	// if (is_vars_assign(current_lst->str)) //（KEY=の構文に当てはまるか)
// 	//env_vars = handle_temp_variables(&current_lst)
// 	// while (current_lst && current_lst->tokne_type != PIPE)
// 	// {
// 	// 	if (is_delimiter(current_lst->str))
// 	// 	{
// 	// 		if (current_lst->next == NULL)
// 	// 			syntax_error("newline", token_lst, &env_lst);
// 	// 		if (s_delimiter(current_lst->next->str) || current_lst->next->token_type = PIPE)
// 	// 			syntax_error(current_lst->next->str, token_lst, &env_lst);
			
// 	// 	}
// 	// }

// 	//current: t_cmd用のft_lst_utils実装
// }



// t_cmd perse_tokens(t_token *token_lst)
// {
// 	t_cmd *new;
// 	t_token *tmp;

// 	tmp = token_lst;
// 	while (tmp)
// 	{
// 		new = ft_parse_single_cmd(&tmp, &token_lst);
// 		if (new = NULL)
// 		{
// 			ft_tokenlst_clear(token_lst);
// 			return (NULL);
// 		}

// 	}
// }