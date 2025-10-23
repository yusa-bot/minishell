/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:57:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/23 18:28:29 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A.r->expanded_strを開いたfd(heredoc : pipe済みfd) -> B.STDIN/OUT に複製
	// -> 環境自体の入力/出力を変える(Aは閉じても、環境にBが保存されている)
int handle_redirect(const t_redirect *rdr, int target_fd, int oflags)
{
    int fd = -1;

	if (rdr->token_type == INFILE)
        fd = open(rdr->expanded_arg, O_RDONLY);
	else //OUTFILE
        fd = open(rdr->expanded_arg, oflags, 0644);
    if (fd < 0)
	{
		write(STDERR_FILENO, "minishell: Invalid file descriptor\n", 36);
        return (EXIT_FAILURE);
    }
    if (dup2(fd, target_fd) < 0)//開いたfdをstdi/oに複製
	{
		printf("dup2 failed\n");
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

//in/outそれぞれでfd処理
int apply_redirect(const t_cmd *cmd, t_shell *shell)
{
    t_redirect *rdr;
	rdr = NULL;

	if (cmd->infile)
    	rdr = cmd->infile;
    while (rdr)
    {
        shell->status = handle_redirect(rdr, STDIN_FILENO, O_RDONLY);
		if (shell->status != EXIT_SUCCESS)
			return (shell->status);
        rdr = rdr->next;
    }
	if (!cmd->outfile)
		return (EXIT_SUCCESS);
    rdr = cmd->outfile;
    while (rdr)
    {
        int flags = O_WRONLY | O_CREAT;
        if (rdr->token_type == APPEND)
            flags |= O_APPEND;//追記
        else
            flags |= O_TRUNC;//上書き
        handle_redirect(rdr, STDOUT_FILENO, flags);
        rdr = rdr->next;
    }
	return (EXIT_SUCCESS);
}
