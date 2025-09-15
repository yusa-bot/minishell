/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:19:18 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 14:19:20 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void malloc_error()
{
	ft_putendl_fd("minishell: Fatal error: Could not allocate memory for error message.", 2);
	exit(2);
}

void	syntax_error(char *unexpected_token, t_token **token_lst, t_env **env_lst)
{
	char *full_msg;

	ft_lst_clear(env_lst);
	full_msg = ft_strjoin("minishell: syntax error near unexpected token `", unexpected_token);
	ft_tokenlst_clear(token_lst);
	if (full_msg)
		full_msg = ft_strjoin_safe(full_msg, "'");
	if (full_msg == NULL)
		malloc_error();
	ft_putendl_fd(full_msg, 2);
	exit(2);
}
