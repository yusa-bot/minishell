/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:48:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 18:07:35 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_pipe(t_cmd *cmd, t_env **env)
{
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    pid_t pid;

    while (cmd)
    {
        if (cmd->next)
            pipe(pipefd);
        pid = fork();
        if (pid == 0)//子
        {
            if (in_fd != STDIN_FILENO)//最初ではなかったらdup
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (cmd->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            run_child(cmd, env);
            exit(0);
        }
        else//親
        {
            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (cmd->next)
            {
                close(pipefd[1]);//書き込み側は親で不要
                in_fd = pipefd[0];//次のコマンドの入力に渡す
            }
        }
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);//全プロセス
    return 0;
}
