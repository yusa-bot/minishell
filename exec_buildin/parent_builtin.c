/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:24:47 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/24 20:16:15 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//redirect halper
static int fd_save(int *save_stdin, int *save_stdout)
{
    *save_stdin = dup(STDIN_FILENO);
    *save_stdout = dup(STDOUT_FILENO);
    if (*save_stdin < 0 || *save_stdout < 0)
        return (-1);
    return (0);
}

//redirect halper
static void fd_restore(int save_stdin, int save_stdout)
{
    if (save_stdin >= 0)
    {
        dup2(save_stdin, STDIN_FILENO);
        close(save_stdin);
    }
    if (save_stdout >= 0)
    {
        dup2(save_stdout, STDOUT_FILENO);
        close(save_stdout);
    }
}

int run_parent(t_cmd *cmd, t_env **env_lst, t_shell *shell)
{
    int save_in = -1;
    int save_out = -1;

    if (fd_save(&save_in, &save_out) < 0)
    {
        perror("dup");
        return (0);
    }
	shell->status = apply_redirect(cmd, shell);
    if (shell->status != EXIT_SUCCESS)
    {
        fd_restore(save_in, save_out);
		perror("redirect");
        return (0);
    }
    shell->status = run_builtin(cmd->cmd_args, env_lst, shell);
    fd_restore(save_in, save_out);
	return (shell->status);
}
