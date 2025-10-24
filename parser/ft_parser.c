/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:46:15 by rinka             #+#    #+#             */
/*   Updated: 2025/10/24 18:06:05 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	count_args_vars(t_token *lst,int *arg_count, int *var_count)
{
	*arg_count = 0;
	*var_count = 0;
	while (lst && lst->token_type == VARIABLE_ASSIGNMENT)//一時的な環境変数スキップ
	{
		(*var_count)++;
		lst = lst->next;
	}
	while (lst)
	{
			if (is_delimiter(lst->str))//syntaxerrorは後でチェック
			{
				lst = lst->next;
				if (lst)
				{
					lst->token_type = FILENAME;
					lst = lst->next;
				}
			}
			else//CMD,ARGを区別するかどうか(しなくてよさそう？)
			{
				(*arg_count)++;
				lst->token_type = WORD;
				lst = lst->next;
			}
	}
}

char	**set_env_vars(t_token **lst, int var_count)
{
	char	**env_vars;
	int	i;

	env_vars = malloc(sizeof(char *) * (var_count + 1));
	if (env_vars == NULL)
		return (NULL);
	i = 0;
	while (i < var_count)
	{
		env_vars[i] = ft_strdup((*lst)->str);
		if (env_vars[i] == NULL)
		{
			ft_free_str_array(env_vars);
			return (NULL);
		}
		i++;
		*lst = (*lst)->next;
	}
	env_vars[i] = NULL;
	return (env_vars);
}

static int	free_filename(t_redirect **infile, t_redirect **outfile, t_redirect *new_file)
{
	if (infile && *infile)
		ft_redirectlst_clear(infile);
	if (outfile && *outfile)
		ft_redirectlst_clear(outfile);
	if (new_file)
		ft_redirectlst_clear(&new_file);
	return (1);
}

//リダイレクト＆ファイル名格納
static int set_filename(t_redirect **new_file, t_token *lst, char ***tmpfiles)
{
	if ((lst->next)->original_str)
	{
		(*new_file)->original_arg = ft_strdup((lst->next)->original_str);
		if ((*new_file)->original_arg == NULL)
			return (1);
	}
	if (lst->token_type == HEREDOC)
	{
		(*new_file)->expanded_arg = ft_heredoc((lst->next)->str, NULL, NULL, tmpfiles);//エラー処理いったん仮
		if ((*new_file)->expanded_arg)
		{
			//openfileエラー
			return (1);
		}
	}
	else
	{
		(*new_file)->expanded_arg = ft_strdup((lst->next)->str);
		if ((*new_file)->expanded_arg == NULL)
			return (1);
	}
	return (1);
}


//呼び出し元でmalloc_errorの処理予定だったけどopenエラーと区別するためその場で解放の方がいいかも
static int	set_redirect_info(t_token *lst, t_redirect **infile, t_redirect **outfile, char ***tmpfiles)
{
	t_redirect *new_file;
	t_redirect **add_to;

	while (lst)
	{
		if (is_delimiter(lst->str))
		{
			(lst->next)->token_type = FILENAME;
			if (lst->token_type == REDIRECT_IN || lst->token_type == HEREDOC)
				add_to = infile;
			else if (lst->token_type == REDIRECT_OUT || lst->token_type == APPEND)
				add_to = outfile;
			new_file = ft_redirectlst_init();
			if (add_to == NULL)
				return (free_filename(infile, outfile, new_file));
			if (!set_filename(&new_file, lst, tmpfiles))
				return (free_filename(infile, outfile, new_file));
			new_file->token_type = lst->token_type;
			ft_redirectlst_add_back(add_to, new_file);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (0);
}

char	**set_cmd_args(t_token *current_lst, int arg_count)
{
	char	**cmd_args;
	int	i;

	cmd_args = malloc(sizeof(char *) * (arg_count + 1));
	if (cmd_args == NULL)
		return (NULL);
	i = 0;
	while (current_lst)
	{
		if (current_lst->token_type == WORD)
		{
			cmd_args[i] = ft_strdup(current_lst->str);
			if (cmd_args[i] == NULL)
			{
				ft_free_str_array(cmd_args);
				return (NULL);
			}
			i++;
		}
		current_lst = current_lst->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

//コマンド一個分の情報格納する関数
t_cmd	*ft_parse_single_cmd(t_token *single_token_lst, t_token *token_lst, t_env *env_lst, char ***tmpfiles)
{
	(void)env_lst;
	t_cmd *res;
	t_token *current_lst;
	int arg_count = 0;
	int var_count = 0;

	res = ft_cmdlst_init();
	current_lst = single_token_lst;
	count_args_vars(single_token_lst, &arg_count, &var_count);
	if (var_count)//env_varsに一時的な環境変数の情報格納
	{
		res->env_vars = set_env_vars(&current_lst, var_count);//current_lst->str);//
		if (res->env_vars == NULL)
			malloc_error(&token_lst, NULL, &env_lst, &single_token_lst);
	}
	if (set_redirect_info(current_lst, &(res->infile), (&res->outfile), tmpfiles))
		malloc_error(&token_lst, &res, &env_lst, &single_token_lst);
	//ft_globbing(&current_lst, &arg_count);
	if (arg_count)
	{
		res->cmd_args = set_cmd_args(current_lst, arg_count);
		if (res->cmd_args == NULL)
			malloc_error(&token_lst, &res, &env_lst, &single_token_lst);
	}
	return (res);
	}

t_cmd *ft_parser(t_token *token_lst, t_env *env_lst, char ***tmpfiles, t_shell *shell)
{
	t_cmd *cmd_lst;
	t_cmd *new;
	t_token *current_lst;
	t_token *joined_token_lst;

	cmd_lst = NULL;///
	current_lst = token_lst;
	joined_token_lst = NULL;
	while (current_lst)
	{
		joined_token_lst = join_expanded_tokens(&current_lst, &token_lst, env_lst, shell);//
		if (!joined_token_lst)///syntax_errorのみ
			return (NULL);
		// t_token *tmp = joined_token_lst;
		// while (tmp)/////
		// {
		// 	printf("str: %s\n", tmp->str);
		// 	printf("original_str: %s\n", tmp->original_str);
		// 	printf("token_type: %d\n", tmp->token_type);
		// 	printf("quote_type: %d\n", tmp->quote_type);
		// 	printf("joint_next: %d\n\n", tmp->is_joined_with_next);
		// 	tmp = tmp->next;
		// }
		// printf("\n");
		// if (tmp == NULL)
		// 	printf("null tarminated\n");///////

		if (is_delimiter(ft_tokenlst_last(joined_token_lst)->str))
		{
			if (!current_lst)
				syntax_error("newline", &token_lst,&env_lst);
			syntax_error("|", &token_lst,&env_lst);
			ft_tokenlst_clear(&joined_token_lst);
			return(NULL);
		}
		new = ft_parse_single_cmd(joined_token_lst, token_lst, env_lst, tmpfiles);
		ft_cmdlst_add_back(&cmd_lst, new);
	}
	return (cmd_lst);
}

////TEST=test TEST2=test2 < infile.txt cat | grep $PATH | wc -l >> outfile.txt | echo *
