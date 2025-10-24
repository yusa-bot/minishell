
#include "minishell.h"

void malloc_error(t_shell *sh, t_token **single_token_lst)
{
	ft_putendl_fd("minishell: Fatal error: Could not allocate memory for error message.", 2);
	ft_tokenlst_clear(sh->token);
	ft_cmdlst_clear(sh->cmd);
	ft_lst_clear(sh->env);
	ft_tokenlst_clear(single_token_lst);
	// g_exit_status = 2;
	exit(2);
}

void *syntax_error(t_shell *sh, char *unexpected_token)
{
	// (void)env_lst;
	char *full_msg;

	full_msg = ft_strjoin("minishell: syntax error near unexpected token `", unexpected_token);
	ft_tokenlst_clear(sh->token);
	if (full_msg)
		full_msg = ft_strjoin_safe(full_msg, "'");
	if (full_msg == NULL)
		malloc_error(sh, NULL);
	ft_putendl_fd(full_msg, 2);
	free (full_msg);
	// g_exit_status = 2;
	return (NULL);
}
