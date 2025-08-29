
#include "minishell.h"

t_token *ft_tokenlst_dup(t_token *lst)
{
	t_token *res;

	res = ft_tokenlst_new(lst->str, lst->token_type, lst->quote_type, lst->is_joined_with_next);

	return (res);
}

void	ambiguous_redirect_error(char *original, char *res, t_token **token_lst, t_env *env_lst)
{
	char *full_msg;

	if (res)
		free(res);
	full_msg = ft_strjoin("minishell: ", original);
	ft_tokenlst_clear(token_lst);
	ft_envlst_clear(&env_lst);
	if (full_msg)
		full_msg = ft_strjoin_safe(full_msg, ": ambiguous redirect");
	if (full_msg == NULL)
		malloc_error();
	ft_putendl_fd(full_msg, 2);
	exit(1);
}
