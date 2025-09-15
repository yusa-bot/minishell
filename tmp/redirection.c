/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:57:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/13 21:08:52 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 既存 handle_redirect に prepared_fd を考慮させる例
int handle_redirect(const t_redirect *r, int target_fd, int oflags)
{
    int fd = -1;

    if (r->token_type == INFILE && r->prepared_fd >= 0)
        fd = r->prepared_fd;// HEREDOCから来たやつ
	else if (r->token_type == INFILE)
        fd = open(r->expanded_str, O_RDONLY);
	else
        fd = open(r->expanded_str, oflags, 0644);// OUTFILE/APPEND
    if (fd < 0)
	{
        perror(r->expanded_str);
        return -1;
    }
    if (dup2(fd, target_fd) < 0)
	{
        perror("dup2");
        close(fd);
        return -1;
    }
    // HEREDOCのread側FDはdup2後に閉じてOK（以降はdup先から読まれる）
    close(fd);
    return 0;
}

// 親/子共用：成功0 失敗-1）
int apply_redirections(const t_cmd *c)
{
    t_redirect *r;

    r = c->infile;
    while (r)
    {
        if (handle_redirect(r, STDIN_FILENO, O_RDONLY) < 0)
            return -1;
        r = r->next;
    }
    r = c->outfile;
    while (r)
    {
        int flags = O_WRONLY | O_CREAT;
        if (r->token_type == APPEND)
            flags |= O_APPEND;//追記
        else
            flags |= O_TRUNC;//上書き
        if (handle_redirect(r, STDOUT_FILENO, flags) < 0)
            return -1;
        r = r->next;
    }
    return 0;
}
