/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:59:29 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/23 10:05:14 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cmd_clear(t_cmd **cmd_lst)
{
    t_cmd *cur;
    t_cmd *next;

    if (!cmd_lst || !*cmd_lst)
        return;
    cur = *cmd_lst;
    while (cur)
    {
        next = cur->next;
        if (cur->cmd_args)
        {
            for (int i = 0; cur->cmd_args[i]; i++)
                free(cur->cmd_args[i]);
            free(cur->cmd_args);
        }
        if (cur->env_vars)
        {
            for (int i = 0; cur->env_vars[i]; i++)
                free(cur->env_vars[i]);
            free(cur->env_vars);
        }
        // infile/outfileのリストも解放
        t_redirect *r = cur->infile;
        while (r)
        {
            t_redirect *r_next = r->next;
            free(r->original_arg);
            free(r->expanded_arg);
            free(r);
            r = r_next;
        }
        r = cur->outfile;
        while (r)
        {
            t_redirect *r_next = r->next;
            free(r->original_arg);
            free(r->expanded_arg);
            free(r);
            r = r_next;
        }
        free(cur);
        cur = next;
    }
    *cmd_lst = NULL;
}

void continue_free(t_token **token_lst, t_cmd **cmd_lst)
{
    if (!cmd_lst && !token_lst)
        return;
    if (*token_lst)
		ft_tokenlst_clear(token_lst);
    if (*cmd_lst)
        ft_cmd_clear(cmd_lst);
}

void free_split(char **arr)
{
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
