/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:40:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/13 21:06:39 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// delimiterまで読み込み、pipeのread側FDを返す。失敗時 -1
static int build_heredoc_fd(const char *delim_arg, int do_expand, void *env)
{
    int fds[2];
    char *line = NULL;
    char *delim = NULL;

    if (pipe(fds) < 0)
		return -1;

    g_sig = 0;

    delim = unquote_all(delim_arg);//置き換える
	if (!delim)
	{
		close(fds[0]);
		close(fds[1]);
		return -1;
	}

    while (!g_sig)
	{
        line = readline("> ");
        if (!line)
			break;
        if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}

        char *out = NULL;
        if (do_expand)
			out = expand_vars(line, env);//置き換える
        else
			out = ft_strdup(line);
        free(line);
		line = NULL;
        if (!out)
		{
			g_sig = 1;
			break;
		}

        // 行+改行を書き込む
        write(fds[1], out, strlen(out));
        write(fds[1], "\n", 1);
        free(out);
    }

    free(delim);
    close(fds[1]);

    if (g_sig)
	{
        close(fds[0]);
        return -1;
    }
    return fds[0];
}

// クォートあり→展開しない
int is_quoted_delim(const char *delim)
{
    if (!delim || !*delim)
        return (0);
    int len = ft_strlen(delim);
    if (len >= 2)
    {
        if ((delim[0] == '\'' && delim[len-1] == '\'') ||
            (delim[0] == '"' && delim[len-1] == '"'))
            return (1);
    }
    return (0);
}


//ここではｒを回す。
int prepare_heredoc_for_cmd(t_cmd *cmd, void *env)
{
	t_redirect *r = cmd->infile;
    while (r)
	{
		if (r->token_type == HEREDOC)
		{
			int expand = !is_quoted_delim(r->original_str);
            int fd = build_heredoc_fd(r->original_str, expand, env);
            if (fd < 0)
				return -1;
            r->prepared_fd = fd;
            r->token_type = INFILE;
        }
		r = r->next;
    }
    return 0;
}
