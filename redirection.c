/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:57:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/07 21:30:30 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// リダイレクション処理のヘルパー関数
static int handle_redirect(t_redirect *r, int target_fd, int flags)
{
    int fd;

    fd = open(r->expanded_filename, flags, 0644);
    if (fd < 0)
    {
        perror("minishell");
        return -1;
    }
    if (dup2(fd, target_fd) < 0)
    {
        close(fd);
        perror("minishell");
        return -1;
    }
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
        // HEREDOCは事前にテンポラリfdにしておくと楽（ここでは通常入力だけ例示）
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
