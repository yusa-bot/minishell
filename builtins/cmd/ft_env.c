/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:41:21 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/17 22:53:20 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_putenv_fd(t_env *env, int fd, t_shell *shell)
{
    if (ft_putstr_fd(env->key, fd) < 0
        || ft_putstr_fd("=", fd) < 0
        || ft_putstr_fd(env->value, fd) < 0
        || ft_putstr_fd("\n", fd) < 0)
    {
        perror("minishell: env");
		shell->status = EXIT_FAILURE;
        exit(EXIT_FAILURE);
    }
    return (0);
}

int ft_env(t_env *lst, int fd, t_shell *shell)
{
    t_env *tmp;

    tmp = lst;
    while (tmp)
    {
        if (tmp->is_export)
            ft_putenv_fd(tmp, fd, shell);
        tmp = tmp->next;
    }
    exit(EXIT_SUCCESS);
}