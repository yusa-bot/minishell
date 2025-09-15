/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:31:32 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 20:59:34 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_pwd(t_env *env_lst, int fd)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
		  cwd = ft_get_env(env_lst, "PWD");
    ft_putstr_fd(cwd, fd);
    ft_putstr_fd("\n", fd);
    free(cwd);
    return (0);
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
