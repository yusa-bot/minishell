/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:39:45 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/25 13:39:48 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_tokenlst_dup(t_token *lst)
{
	t_token *res;

	res = ft_tokenlst_new(lst->str, lst->token_type, lst->quote_type, lst->is_joined_with_next);

	return (res);
}

void	*ambiguous_redirect_error(t_shell *sh, char *original, t_token *single_token_lst)
{
	char *full_msg;

	full_msg = ft_strjoin("minishell: ", original);
	free(original);
	if (full_msg)
		full_msg = ft_strjoin_safe(full_msg, ": ambiguous redirect");
	if (full_msg == NULL)
		malloc_error(sh, &single_token_lst);
	ft_putendl_fd(full_msg, 2);
	// g_exit_status = 1;
	return (NULL);
}
