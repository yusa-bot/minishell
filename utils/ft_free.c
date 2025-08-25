
#include "minishell.h"

void malloc_error()
{
	ft_putendl_fd("minishell: Fatal error: Could not allocate memory for error message.", 2);
	exit(2);
}

void	syntax_error(char *unexpected_token, t_token **token_lst)
{
	char *full_msg;

	full_msg = ft_strjoin("minishell: syntax error near unexpected token `", unexpected_token);
	ft_tokenlst_clear(token_lst);
	if (full_msg)
		full_msg = ft_strjoin_safe(full_msg, "'");
	if (full_msg == NULL)
		malloc_error();
	ft_putendl_fd(full_msg, 2);
	exit(2);
}