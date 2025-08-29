#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char		**cmd_args;
	char		**env_vars;//一時的な環境変数
	char	*infile;
	char	*outfile;
	int	append;
	struct s_cmd	*next;
}	t_cmd;

// t_cmd *parse_tokens(t_token *token_lst, t_env *env_lst);

t_token *join_expanded_tokens(t_token **cmd_start, t_token **token_lst, t_env *env_lst);

//ft_parser_utils.c
t_token *ft_tokenlst_dup(t_token *lst);
void	ambiguous_redirect_error(char *original, char *res, t_token **token_lst, t_env *env_lst);

#endif