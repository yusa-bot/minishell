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

t_cmd *ft_parser(t_token *token_lst, t_env *env_lst);

t_token *join_expanded_tokens(t_token **cmd_start, t_token **token_lst, t_env *env_lst);

//ft_parser_utils.c
t_token *ft_tokenlst_dup(t_token *lst);
void	ambiguous_redirect_error(char *original, char *res, t_token **token_lst, t_env *env_lst);

//ft_cmdlst_utils.c 
t_cmd	*ft_cmdlst_new(char **cmd_args, char **env_vars, char *infile, char *outfile, int append);
void	ft_cmdlst_delone(t_cmd *lst);
void	ft_cmdlst_clear(t_cmd **lst);
t_cmd	*ft_cmdlst_last(t_cmd *lst);
void	ft_cmdlst_add_back(t_cmd **lst, t_cmd *new);

#endif