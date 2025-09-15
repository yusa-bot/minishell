/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:31:32 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 13:33:39 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_pwd(t_env *env_lst)
{
    char *cwd;

    cwd = getcwd(NULL, 0); //mallocされる
    if (cwd == NULL)
		cwd = ft_get_env(env_lst, "PWD");
    printf("%s\n", cwd);
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
