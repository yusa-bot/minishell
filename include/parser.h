#ifndef PARSER_H
# define PARSER_H

typedef struct s_redirect
{
	char *original_filename;
	char *expanded_filename;
	t_token_type token_type;
	struct s_redirect *next;
	int prepared_fd; // HEREDOC用に準備されたFDを保持
} t_redirect;

typedef struct s_cmd
{
	char		**cmd_args;
	char		**env_vars;//一時的な環境変数
	t_redirect	*infile;
	t_redirect	*outfile;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;


t_cmd *ft_parser(t_token *token_lst, t_env *env_lst);

t_token *join_expanded_tokens(t_token **cmd_start, t_token **token_lst, t_env *env_lst);

//ft_parser_utils.c
t_token *ft_tokenlst_dup(t_token *lst);
void	ambiguous_redirect_error(char *original);

//ft_cmdlst_utils.c
t_cmd	*ft_cmdlst_new(char **cmd_args, char **env_vars, t_redirect *infile, t_redirect *outfile);
void	ft_cmdlst_delone(t_cmd *lst);
void	ft_cmdlst_clear(t_cmd **lst);
t_cmd	*ft_cmdlst_last(t_cmd *lst);
void	ft_cmdlst_add_back(t_cmd **lst, t_cmd *new);
//ft_redirectlst
t_redirect *ft_redirectlst_init(void);
t_redirect	*ft_redirectlst_new(char *expanded_filename, char *original_filename, t_token_type token_type);
void	ft_redirectlst_clear(t_redirect **lst);
t_redirect	*ft_redirectlst_last(t_redirect *lst);
void	ft_redirectlst_add_back(t_redirect **lst, t_redirect *new);

#endif
