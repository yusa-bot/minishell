/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:48:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/24 13:26:52 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	pipe_apply_redirect()
// {
// 	//pipe専用のfd作る？
// }

int run_pipe(t_shell *sh)
{
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    pid_t pid;


	printf("run_pipe called\n");
    while (sh->cmd)
    {
        if (sh->cmd->next)
		{
            if (pipe(pipefd) == -1)
			{
                perror("pipe");
				exit(EXIT_FAILURE);
            }
        }
        pid = fork();
        if (pid < 0)
		{
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
			// dup2にて、STDI/Oで繋がる。
            setup_signals_child();
            if (in_fd != STDIN_FILENO)//最初ではなかったらdup
            {
				printf("Setting up input redirection for command: %s\n", sh->cmd->cmd_args[0]);
                if (dup2(in_fd, STDIN_FILENO) == -1)
				{
                    perror("dup2");
					exit(EXIT_FAILURE);
                }
                close(in_fd);
            }
            if (sh->cmd->next)
            {
				printf("Setting up pipe for command: %s\n", sh->cmd->cmd_args[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
                }
				close(pipefd[1]);
            }
			sh->status = apply_redirect(sh);
			if (sh->status != EXIT_SUCCESS)
				exit(sh->status);
            exec_child(sh);
            exit(EXIT_SUCCESS);
        }
        else//pipeだったらこれが親
        {
            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (sh->cmd->next)
            {
                close(pipefd[1]);//書き込み側は親で不要
				printf("Pipe set up between commands\n");
                in_fd = pipefd[0];//次のコマンドの入力に渡す
            }
        }
        sh->cmd = sh->cmd->next;
    }
	while (wait(&sh->status) > 0)
	{
        if (wait(&sh->status) == pid)
        {
            if (WIFEXITED(sh->status))
                return (WEXITSTATUS(sh->status));
            else if (WIFSIGNALED(sh->status))
                return (128 + WTERMSIG(sh->status));
        }
	}
	return (sh->status);
}
