/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:57:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/16 19:38:02 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirect(const t_redirect *r, int target_fd, int oflags)
{
    int fd = -1;

    if (r->token_type == INFILE && r->prepared_fd >= 0)
        fd = r->prepared_fd; //HEREDOCから来たやつ
	else if (r->token_type == INFILE)
        fd = open(r->expanded_str, O_RDONLY);
	else //OUTFILE
        fd = open(r->expanded_str, oflags, 0644);
    if (fd < 0)
	{
        perror(r->expanded_str);//
        return -1;
    }
    if (dup2(fd, target_fd) < 0)//開いたfdをstdi/oに複製
	{
        perror("dup2");//
        close(fd);
        return -1;
    }


    /////////////
    //// HEREDOCの場合とファイルの場合で異なる処理
    //if (r->token_type == INFILE && r->prepared_fd >= 0)
    //{
    //    // HEREDOCの場合：prepared_fdは使い回すので閉じない
    //    // dup2でSTDIN_FILENOにコピー済みなので、以降はそちらから読まれる
    //    // prepared_fdは他の処理で必要な可能性があるため保持
    //}
    //////////////

    else //通常
        close(fd);
    return 0;
}

int apply_redirect(const t_cmd *cmd)
{
    t_redirect *r;

    r = cmd->infile;
    while (r)
    {
        if (handle_redirect(r, STDIN_FILENO, O_RDONLY) < 0)
            return -1;
        r = r->next;
    }
    r = cmd->outfile;
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
