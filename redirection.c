/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:57:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/07 19:53:25 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//redir/apply_redirections を実装（親・子で共用）

// redir.c（親/子共用：成功0 失敗-1）
int apply_redirections(const t_cmd *c)
{
    t_redirect *r;
    int fd;

    for (r = c->infile; r; r = r->next)
    {
        // HEREDOC は事前にテンポラリfdにしておくと楽（ここでは通常入力だけ例示）
        fd = open(r->expanded_filename, O_RDONLY);
        if (fd < 0)
            perror("minishell");
        if (dup2(fd, STDIN_FILENO) < 0)
		{
			close(fd);
			perror("minishell");
			return -1;
		}
        close(fd);
    }
    for (r = c->outfile; r; r = r->next)
    {
        int flags = (r->token_type == APPEND) ? (O_WRONLY|O_CREAT|O_APPEND) : (O_WRONLY|O_CREAT|O_TRUNC);
        fd = open(r->expanded_filename, flags, 0644);
        if (fd < 0)
		{
			perror("minishell");
			return -1;
		}
        if (dup2(fd, STDOUT_FILENO) < 0)
		{
			close(fd);
			perror("minishell");
			return -1;
		}
        close(fd);
    }
    return 0;
}
