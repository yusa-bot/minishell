
#include "minishell.h"

// //コマンド一個分の情報格納する関数
// t_cmd *ft_parse_single_cmd(t_token **cmd_start, t_token *token_lst, t_env *env_lst)
// {
// 	t_token *current_lst;
// 	t_cmd res;
// 	t_token *joined_token;
// 	// char		**cmd_args;
// 	// char **env_vars;
// 	// char	*infile;
// 	// char	*outfile;
// 	// int	append;//

// 	// infile = NULL;
// 	// outfile = NULL;
// 	current_lst = *cmd_start;
// 	if (current_lst->token_type == PIPE)//どこでチェックが最適か
// 		syntax_error("|", &token_lst);
//  joined_token = join_words(cmd_start, token_lst, env_lst);
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

// 	ft_tokenlst_clear(&joined_token);

// 	//current: t_cmd用のft_lst_utils実装
// }



// t_cmd *ft_parser(t_token *token_lst, t_env *env_lst)
// {
// 	t_cmd *new;
// 	t_token *tmp;

// 	t_token *joined_token_lst = join_expanded_tokens(&token_lst, &token_lst, env_lst);//
// 	free(token_lst);
// 	// t_cmd cms_lst = *parse_tokens(token_lst, env_lst);
// 	t_token *tmp = joined_token_lst;
// 	while (tmp)
// 	{
// 		printf("str: %s\n", tmp->str);
// 		printf("token_type: %d\n", tmp->token_type);
// 		printf("quote_type: %d\n", tmp->quote_type);
// 		printf("joint_next: %d\n\n", tmp->is_joined_with_next);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// 	if (tmp == NULL) 
// 		printf("null tarminated\n");
// 	ft_tokenlst_clear(&joined_token_lst);

// 	tmp = token_lst;
// 	while (tmp)
// 	{
// 		new = ft_parse_single_cmd(&tmp, token_lst, &env_lst);
// 		if (new = NULL)
// 		{
// 			ft_tokenlst_clear(token_lst);
// 			return (NULL);
// 		}

// 	}
// 	return (new);
// }