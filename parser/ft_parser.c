
#include "minishell.h"

// char *check_filename(t_cmd *cmd_lst)
// {
// 	char *res;
// 	int	cmd_lst_index;
// 	int i;

// 	cmd_lst_index = 0;
// 	while (cmd_lst)
// 	{
// 		if (cmd_lst->nonexist)
// 	}
// }

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

int	set_infile_name(t_token *lst, t_redirect **infile, t_redirect **outfile)
{
	t_redirect *new_file;
	while (lst)
	{
		if (is_delimiter(lst->str))
		{
			if (lst->token_type == REDIRECT_IN || lst->token_type == HEREDOC)
			{
				new_file = ft_redirectlst_init();
				if (infile == NULL)
				{
					if (*outfile)
						ft_redirectlst_clear(outfile);
					return (1);
				}
				if ((lst->next)->original_str)
				{
					new_file->original_filename = ft_strdup((lst->next)->original_str);
					if (new_file->original_filename == NULL)
					{
						ft_redirectlst_clear(outfile);
						ft_redirectlst_clear(infile);
						return (1);
					}
				}
				new_file->expanded_filename = ft_strdup((lst->next)->str);
				if (new_file->expanded_filename == NULL)
				{
					ft_redirectlst_clear(outfile);
					ft_redirectlst_clear(infile);
					return (1);
				}
				new_file->token_type = lst->token_type;
				ft_redirectlst_add_back(infile, new_file);
			}
			else if (lst->token_type == REDIRECT_OUT || lst->token_type == APPEND)
			{
				new_file = ft_redirectlst_init();
				if (outfile == NULL)
				{
					if (*infile)
						ft_redirectlst_clear(infile);
					return (1);
				}
				if ((lst->next)->original_str)
				{
					new_file->original_filename = ft_strdup((lst->next)->original_str);
					if (new_file->original_filename == NULL)
					{
						ft_redirectlst_clear(outfile);
						ft_redirectlst_clear(infile);
						return (1);
					}
				}
				new_file->expanded_filename = ft_strdup((lst->next)->str);
				if (new_file->expanded_filename == NULL)
				{
					ft_redirectlst_clear(outfile);
					ft_redirectlst_clear(infile);
					return (1);
				}
				new_file->token_type = lst->token_type;
				ft_redirectlst_add_back(outfile, new_file);
			}
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
	return (cmd_args);
}

//コマンド一個分の情報格納する関数
t_cmd	*ft_parse_single_cmd(t_token *single_token_lst, t_token *token_lst, t_env *env_lst)
{
	t_cmd *res;
	t_token *current_lst;
	char		**cmd_args;
	int arg_count = 0;
	char **env_vars;
	int var_count = 0;
	t_redirect	*infile;
	t_redirect	*outfile;

	current_lst = single_token_lst;
	printf("---------arg_var_count--------\n");
	count_args_vars(single_token_lst, &arg_count, &var_count);
	printf("var_count: %d, arg_count: %d\n", var_count, arg_count);
	env_vars = NULL;
	if (var_count)//env_varsに一時的な環境変数の情報格納
	{
		printf("---------set_env_vars--------\n");//
		env_vars = set_env_vars(&current_lst, var_count);//current_lst->str);//
		if (env_vars == NULL)
		{//malloc_error
			ft_tokenlst_clear(&single_token_lst);
			ft_tokenlst_clear(&token_lst);
			ft_envlst_clear(&env_lst);
			malloc_error();
		}//
	}

	printf("---------set_infile_name--------\n");//
	infile = NULL;
	outfile = NULL;
	if (set_infile_name(current_lst, &infile, &outfile))
	{//malloc_error
		ft_free_str_array(env_vars);
		ft_tokenlst_clear(&single_token_lst);
		ft_tokenlst_clear(&token_lst);
		ft_envlst_clear(&env_lst);
		malloc_error();
	}//
	// printf("infile: %s, outfile: %s\n", infile->expanded_filename, outfile->expanded_filename);///

	// if ((infile && ft_strlen(infile) == 0)|| (outfile && ft_strlen(outfile) == 0))
	// {
	// 	if (infile && ft_strlen(infile) == 0)
	// 	{
	// 		nonexist_filename = get_filename_var(current_lst, 0);
	// 	}
	// 	else
	// 	{
	// 		nonexist_filename = get_filename_var(current_lst, 1);
	// 	}

	// }

	cmd_args = NULL;
	printf("---------set_cmd_args--------\n");//
	if (arg_count)
	{
		cmd_args = set_cmd_args(current_lst, arg_count);
		if (cmd_args == NULL)
		{//malloc_error
			ft_free_str_array(env_vars);
			if (infile)
				free (infile);
			if (outfile)
				free (outfile);
			ft_tokenlst_clear(&single_token_lst);
			ft_tokenlst_clear(&token_lst);
			ft_envlst_clear(&env_lst);
			malloc_error();
		}//
	}

	res = ft_cmdlst_new(cmd_args, env_vars, infile, outfile);
	return (res);
	}

t_cmd *ft_parser(t_token *token_lst, t_env *env_lst)
{
	t_cmd *cmd_lst;
	t_cmd *new;
	t_token *tmp;
	t_token *current_lst;
	t_token *joined_token_lst;

	cmd_lst = NULL;///
	current_lst = token_lst;
	while (current_lst)
	{
		joined_token_lst = join_expanded_tokens(&current_lst, &token_lst, env_lst);//
		tmp = joined_token_lst;
		while (tmp)
		{
			printf("str: %s\n", tmp->str);
			printf("original_str: %s\n", tmp->original_str);
			printf("token_type: %d\n", tmp->token_type);
			printf("quote_type: %d\n", tmp->quote_type);
			printf("joint_next: %d\n\n", tmp->is_joined_with_next);
			tmp = tmp->next;
		}
		printf("\n");
		if (tmp == NULL) 
			printf("null tarminated\n");
	
		if (is_delimiter(ft_tokenlst_last(joined_token_lst)->str))
		{
			if (!current_lst)
				syntax_error("newline", &token_lst,&env_lst);
			syntax_error("|", &token_lst,&env_lst);
		}
		new = ft_parse_single_cmd(joined_token_lst, token_lst, env_lst);
		printf("---------add_cmd_lst--------\n");//
		ft_cmdlst_add_back(&cmd_lst, new);
		// ft_tokenlst_clear(&joined_token_lst);
	}
	return (cmd_lst);
}

//TEST=test TEST2=test2 < infile.txt cat | grep apple | wc -l >> outfile.txt