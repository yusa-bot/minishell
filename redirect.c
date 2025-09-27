/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:57:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/27 22:27:30 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirect(const t_redirect *r, int target_fd, int oflags)
{
    int fd = -1;

    if (r->token_type == INFILE && r->heredoc_fd >= 0)
        fd = r->heredoc_fd;
	else if (r->token_type == INFILE)
        fd = open(r->expanded_str, O_RDONLY);
	else //OUTFILE
        fd = open(r->expanded_str, oflags, 0644);
    if (fd < 0)
	{
        write(STDERR_FILENO, "minishell: Invalid file descriptor\n", 36);
        return (EXIT_FAILURE);
    }
    if (dup2(fd, target_fd) < 0)//開いたfdをstdi/oに複製
	{
        perror("dup2");//fdはosが回収
        return (EXIT_FAILURE);
    }
    /////////////
    //// HEREDOCの場合とファイルの場合で異なる処理
    //if (r->token_type == INFILE && r->prepared_fd >= 0)
    //{
    //    // HEREDOCの場合：prepared_fdは使い回すので閉じない
    //    // dup2でSTDIN_FILENOにコピー済みなので、以降はそちらから読まれる
    //    // prepared_fdは他の処理で必要な可能性があるため保持
    //}
	// else //通常
    //     close(fd);
    //////////////
    close(fd);
	return (EXIT_SUCCESS);
}

int apply_redirect(const t_cmd *cmd, t_shell *shell)
{
    t_redirect *r;

    r = cmd->infile;
    while (r)
    {
        shell->status = handle_redirect(r, STDIN_FILENO, O_RDONLY);
		if (shell->status != EXIT_SUCCESS)
			return (shell->status);
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
        handle_redirect(r, STDOUT_FILENO, flags);
        r = r->next;
    }
	return (EXIT_SUCCESS);
}
