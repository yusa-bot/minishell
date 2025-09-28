/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:40:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/28 12:32:34 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int read_to_heredoc_fd(t_redirect *rdr)
{
    int fds[2];
    char *line = NULL;


	printf("read_to_heredoc_fd called, delim=%s\n", rdr->original_str);
    if (pipe(fds) < 0)
		return (-1);
	setup_signals_child();//
    g_sig = 0;
    while (!g_sig)
	{
        line = readline("> ");
        if (!line)
		{
			write(2, "warning: here-document delimited by end-of-file (wanted `", 58);
			write(2, rdr->original_str, strlen(rdr->original_str));
			write(2, "`)\n", 1);
            break;
		}
        if (ft_strcmp(line, rdr->original_str) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		printf("heredoc input: %s\n", line);
        write(fds[1], line, strlen(line));
        write(fds[1], "\n", 1);
    }
    close(fds[1]);
    if (g_sig)//status = 130
	{
        close(fds[0]);
        return -1;
    }
    return fds[0];
}

//cat << EOF1 | grep hello << EOF2

//二重whileでループ中にdelim判断をしているので、複数heredocも対応
int prepare_heredocs(t_cmd *cmd_lst)
{
	printf("prepare_heredocs called\n");

	t_redirect *rdr;
    while (cmd_lst)
    {
		if (!cmd_lst->infile)
		{
			printf("no infile\n");
			return (EXIT_SUCCESS);
		}
		// printf("has infile\n");
		rdr = cmd_lst->infile;
        while (rdr)
        {
			printf("token_type: %d, original_str: %s\n", rdr->token_type, rdr->original_str);
            if (rdr->token_type == HEREDOC)
            {
                rdr->heredoc_fd = read_to_heredoc_fd(rdr);
                if (rdr->heredoc_fd < 0)
                    return (EXIT_FAILURE); // Ctrl-C や malloc fail
            }
			rdr = rdr->next;
        }
		cmd_lst = cmd_lst->next;
	}
	return (EXIT_SUCCESS);
}