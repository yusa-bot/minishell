/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:57:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/26 13:10:25 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A.r->expanded_argを開いたfd(heredoc : pipe済みfd) -> B.STDIN/OUT に複製
	// -> 環境自体の入力/出力を変える(Aは閉じても、環境にBが保存されている)
int handle_redirect(t_shell *sh, const t_redirect *rdr, int target_fd, int oflags)
{
    char    *msg;
    fprintf(stderr, "handle_redirect\n");
    int fd = -1;

	if (rdr->token_type == INFILE)
        fd = open(rdr->expanded_arg, O_RDONLY);
	else //OUTFILE
        fd = open(rdr->expanded_arg, oflags, 0644);
    if (fd < 0)
	{
        msg = ft_strjoin("minishell :", rdr->expanded_arg);
        perror(msg);
        free(msg);
        sh->status = EXIT_FAILURE;
        return (sh->status);
    }
    if (dup2(fd, target_fd) < 0)//開いたfdをstdi/oに複製
	{
        //msg = ft_strjoin("minishell :", target_fd);
        perror("minishell :");
        //free(msg);
        close(fd);
        sh->status = EXIT_FAILURE;
        return (sh->status);
    }
    //heredoc tmpfile
    close(fd);
	return (EXIT_SUCCESS);
}

//in/outそれぞれでfd処理
int apply_redirect(t_shell *sh)
{
    fprintf(stderr, "apply_redirect\n");
    t_redirect *rdr;

	rdr = NULL;
	if (sh->cmd->infile)
    	rdr = sh->cmd->infile;
    while (rdr)
    {
        fprintf(stderr, "rdr infile\n");
        sh->status = handle_redirect(sh, rdr, STDIN_FILENO, O_RDONLY);
        rdr = rdr->next;
    }
	if (!sh->cmd->outfile)
    {
        fprintf(stderr, "!sh->cmd->outfile\n");
		return (EXIT_SUCCESS);
    }
    rdr = sh->cmd->outfile;
    while (rdr)
    {
        fprintf(stderr, "rdr outfile\n");
        int flags = O_WRONLY | O_CREAT;
        if (rdr->token_type == APPEND)
            flags |= O_APPEND;//追記
        else
            flags |= O_TRUNC;//上書き
        handle_redirect(sh, rdr, STDOUT_FILENO, flags);
        rdr = rdr->next;
    }
	return (EXIT_SUCCESS);
}
