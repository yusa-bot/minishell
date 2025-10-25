/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:48:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/25 13:50:31 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_handler(t_shell *sh)
{
	if (sh->cmd && sh->cmd->next)
		sh->status = exec_pipe(sh);
	else if (is_builtin_parent(sh->cmd->cmd_args))
		sh->status = exec_parent(sh);
	else
		sh->status = exec_child_handler(sh);
}

int exec_pipe(t_shell *sh)
{
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    pid_t pid;

	printf("exec_pipe called\n");
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
