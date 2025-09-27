/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:40:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/27 22:25:38 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int build_heredoc_fd(t_redirect *r)
{
    int fds[2];
    char *line = NULL;

    if (pipe(fds) < 0)
		return -1;
    g_sig = 0;
    while (!g_sig)
	{
        line = readline("> ");
        if (!line)
			break;
        if (ft_strcmp(line, r->original_str) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}

        // 行+改行を書き込む
        write(fds[1], r->expanded_str, strlen(r->expanded_str));
        write(fds[1], "\n", 1);
        free(r->expanded_str);
    }

    free(r->expanded_str);
    close(fds[1]);

    if (g_sig)
	{
        close(fds[0]);
        return -1;
    }
	r->heredoc_fd = fds[0];
    // return fds[0];
}

int prepare_heredocs(t_cmd *cmds, t_env *env)
{
    for (t_cmd *cmd = cmds; cmd; cmd = cmd->next)
    {
        for (t_redirect *redir = cmd->infile; redir; redir = redir->next)
        {
            if (redir->token_type == HEREDOC)
            {
                redir->heredoc_fd = build_heredoc_fd(redir);
                if (redir->heredoc_fd < 0)
                    return (ERROR); // Ctrl-C や malloc fail などで中止
            }
        }
    }
    return (SUCCESS);
}
