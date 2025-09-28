/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:48:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/28 17:01:11 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_apply_redirect()
{
	//pipe専用のfd作る？
}

int run_pipe(t_cmd *cmd_lst, t_env **env_lst, t_shell *shell)
{
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    pid_t pid;


	printf("run_pipe called\n");
	shell->is_pipe = 1;
    while (cmd_lst)
    {
        if (cmd_lst->next)
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
				printf("Setting up input redirection for command: %s\n", cmd_lst->cmd_args[0]);
                if (dup2(in_fd, STDIN_FILENO) == -1)
				{
                    perror("dup2");
					exit(EXIT_FAILURE);
                }
                close(in_fd);
            }
            if (cmd_lst->next)
            {
				printf("Setting up pipe for command: %s\n", cmd_lst->cmd_args[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
                }
				close(pipefd[1]);
            }
			shell->status = pipe_apply_redirect(cmd_lst, shell);
			if (shell->status != EXIT_SUCCESS)
				exit(shell->status);
            exec_child(cmd_lst, env_lst, shell);
            exit(EXIT_SUCCESS);
        }
        else//pipeだったらこれが親
        {
            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (cmd_lst->next)
            {
                close(pipefd[1]);//書き込み側は親で不要
				printf("Pipe set up between commands\n");
                in_fd = pipefd[0];//次のコマンドの入力に渡す
            }
        }
        cmd_lst = cmd_lst->next;
    }
	while (wait(&shell->status) > 0)
	{
        if (wait(&shell->status) == pid)
        {
            if (WIFEXITED(shell->status))
                return (WEXITSTATUS(shell->status));
            else if (WIFSIGNALED(shell->status))
                return (128 + WTERMSIG(shell->status));
        }
	}
	return (shell->status);
}
