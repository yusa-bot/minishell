/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:30:18 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/26 10:43:31 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	continue_free(t_shell *sh)
{
	ft_tokenlst_clear(&sh->token);
    ft_cmdlst_clear(&sh->cmd);
}

void	malloc_error(t_shell *sh, t_token **single_token_lst) //全部このmsg出すべき箇所にしかこの関数使っていなくて🤩
{
	ft_putendl_fd("minishell: Fatal error: Could not allocate memory for error message.", 2);
	ft_tokenlst_clear(&sh->token);
	ft_cmdlst_clear(&sh->cmd);
	ft_lst_clear(&sh->env);
	ft_tokenlst_clear(single_token_lst);
	sh->status = 2; //マクロ化
	exit(sh->status); // g_exit_status = 2;
}

void	*syntax_error(t_shell *sh, char *unexpected_token)
{
	// (void)env_lst;
	char *full_msg;

	full_msg = ft_strjoin("minishell: syntax error near unexpected token `", unexpected_token);
	ft_tokenlst_clear(&sh->token);
	if (full_msg)
		full_msg = ft_strjoin_oneptr(full_msg, "'");
	if (full_msg == NULL)
		malloc_error(sh, NULL);
	ft_putendl_fd(full_msg, 2);
	free (full_msg);
	sh->status = 2;
	return (NULL);
}
