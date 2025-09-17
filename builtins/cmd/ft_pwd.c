/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:31:32 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/17 22:45:55 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_pwd(t_env *env_lst, int fd, t_shell *shell)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        cwd = ft_get_env(env_lst, "PWD");
        if (cwd == NULL)
        {
            perror("minishell: pwd");
            shell->status = EXIT_FAILURE;
            exit(EXIT_FAILURE);
        }
    }
    if (ft_putstr_fd(cwd, fd) < 0 || ft_putstr_fd("\n", fd) < 0)
    {
        perror("minishell: pwd");
        if (cwd && cwd != ft_get_env(env_lst, "PWD"))
            free(cwd);
        shell->status = EXIT_FAILURE;
        exit(EXIT_FAILURE);
    }
    if (cwd && cwd != ft_get_env(env_lst, "PWD"))
        free(cwd);
    shell->status = EXIT_SUCCESS;
    exit(EXIT_SUCCESS);
}

//int main(int argc, char **argv, char **envp)
//{
//	(void)argc;
//	(void)argv;
//	t_env *env_lst;
//	env_lst = ft_set_env(envp);
//	ft_pwd(env_lst);
//	ft_lst_clear(&env_lst);
//	return (0);
//}
