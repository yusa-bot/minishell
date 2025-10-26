/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:48:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/26 14:56:55 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_shell *sh)
{
	fprintf(stderr, "exec_pipe called\n");
	int		pipefd[2];
	int		in_fd = STDIN_FILENO;
	pid_t	pid;

	pid_t	last_pid;
	size_t	child_count;
	int		wait_status;
	pid_t	waited;
	t_cmd	*cmd;
	t_cmd	*head;

	head = sh->cmd;
	cmd = head;
	last_pid = -1;
	child_count = 0;

	while (cmd)
	{
		const int	has_next = (cmd->next != NULL);

		if (has_next && pipe(pipefd) == -1)
			perror_exit("pipe");
		sh->cmd = cmd;
		pid = fork();
		if (pid < 0)
			perror_exit("fork");
		if (pid == 0)
		{
			int	child_status;

			setup_signals_child();
			if (in_fd != STDIN_FILENO)
			{
				if (dup2(in_fd, STDIN_FILENO) == -1)
					perror_exit("dup2");
				close(in_fd);
			}
			if (has_next)
			{
				close(pipefd[0]);
				if (dup2(pipefd[1], STDOUT_FILENO) == -1)
					perror_exit("dup2");
				close(pipefd[1]);
			}
			child_status = exec_child(sh);
			exit(child_status);
		}
		child_count++;
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (has_next)
		{
			close(pipefd[1]);
			in_fd = pipefd[0];
		}
		else
			in_fd = STDIN_FILENO;
		last_pid = pid;
		cmd = cmd->next;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	sh->cmd = head;
	while (child_count > 0)
	{
		waited = wait(&wait_status);
		if (waited == -1)
		{
			if (errno == EINTR)
				continue ;
			if (errno == ECHILD)
				break ;
			perror_exit("wait");
		}
		if (waited == last_pid)
		{
			if (WIFEXITED(wait_status))
				sh->status = WEXITSTATUS(wait_status);
			else if (WIFSIGNALED(wait_status))
				sh->status = 128 + WTERMSIG(wait_status);
		}
		child_count--;
	}
	return (sh->status);
}


//古い方 (後で見直し用)
//int run_pipe(t_shell *sh)
//{
//    int pipefd[2];
//    int in_fd = STDIN_FILENO;
//    pid_t pid;

//	printf("run_pipe called\n");
//    while (sh->cmd)
//    {
//        if (sh->cmd->next)
//		{
//            if (pipe(pipefd) == -1)
//			{
//                perror("pipe");
//				exit(EXIT_FAILURE);
//            }
//        }
//        pid = fork();
//        if (pid < 0)
//		{
//            perror("fork");
//            exit(EXIT_FAILURE);
//        }
//        if (pid == 0)
//        {
//            setup_signals_child();
//            if (in_fd != STDIN_FILENO)//最初ではなかったらdup
//            {
//				printf("Setting up input redirection for command: %s\n", sh->cmd->cmd_args[0]);
//                if (dup2(in_fd, STDIN_FILENO) == -1)
//				{
//                    perror("dup2");
//					exit(EXIT_FAILURE);
//                }
//                close(in_fd);
//            }
//            if (sh->cmd->next)
//            {
//				printf("Setting up pipe for command: %s\n", sh->cmd->cmd_args[0]);
//                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
//				{
//					perror("dup2");
//					exit(EXIT_FAILURE);
//                }
//				close(pipefd[1]);
//            }
//			sh->status = apply_redirect(sh);
//			if (sh->status != EXIT_SUCCESS)
//				exit(sh->status);
//            exec_child(sh);
//            exit(EXIT_SUCCESS);
//        }
//        else//pipeだったらこれが親
//        {
//            if (in_fd != STDIN_FILENO)
//                close(in_fd);
//            if (sh->cmd->next)
//            {
//                close(pipefd[1]);//書き込み側は親で不要
//				printf("Pipe set up between commands\n");
//                in_fd = pipefd[0];//次のコマンドの入力に渡す
//            }
//        }
//        sh->cmd = sh->cmd->next;
//    }
//	while (wait(&sh->status) > 0)
//	{
//        if (wait(&sh->status) == pid)
//        {
//            if (WIFEXITED(sh->status))
//                return (WEXITSTATUS(sh->status));
//            else if (WIFSIGNALED(sh->status))
//                return (128 + WTERMSIG(sh->status));
//        }
//	}
//	return (sh->status);
//}
