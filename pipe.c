/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:48:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/17 00:23:07 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_pipe(t_cmd *cmd, t_env **env, t_shell shell)
{
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    pid_t pid;

    while (cmd)
    {
        if (cmd->next)
		{
            if (pipe(pipefd) == -1)
			{
				pipe_free(pipefd, in_fd);
                perror("pipe");
				exit(EXIT_FAILURE);
            }
        }
        pid = fork();
        if (pid < 0)
		{
			pipe_free(pipefd, in_fd);
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            setup_signals_child();
            if (in_fd != STDIN_FILENO)//最初ではなかったらdup
            {
                if (dup2(in_fd, STDIN_FILENO) == -1)
				{
					pipe_free(pipefd, in_fd);
                    perror("dup2");
					exit(EXIT_FAILURE);
                }
                close(in_fd);
            }
            if (cmd->next)
            {
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				{
					pipe_free(pipefd, in_fd);
					perror("dup2");
					exit(EXIT_FAILURE);
                }
                pipe_free(pipefd, in_fd);
            }
            if(!(exec_child(cmd, env, shell)))
				exit(EXIT_FAILURE);
            exit(EXIT_SUCCESS);
        }
        else//pipeだったらこれが親
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
    while (wait(NULL) > 0);ここもかきかえ
	return (1);
}
