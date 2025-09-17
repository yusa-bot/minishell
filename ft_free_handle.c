/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:59:29 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/17 20:52:55 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void continue_free(t_token *token_lst, t_cmd *cmd_lst)
{
	if (token_lst)
		ft_token_clear(&token_lst);
	if (cmd_lst)
		ft_cmd_clear(&cmd_lst);
}

