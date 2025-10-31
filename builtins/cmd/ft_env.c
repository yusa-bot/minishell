/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:41:21 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/28 11:08:37 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_putenv_fd(t_env *env_lst, int fd)
{
    if (ft_putstr_fd(env_lst->key, fd) < 0
        || ft_putstr_fd("=", fd) < 0
        || ft_putstr_fd(env_lst->value, fd) < 0
        || ft_putstr_fd("\n", fd) < 0)
            perror_exit("minishell: env");
    return (EXIT_SUCCESS);
}

int ft_env(t_shell *sh, int fd)
{
    t_env *tmp;

    tmp = sh->cmd->tmp_env;
    while (tmp)
    {
        if (ft_putenv_fd(tmp, fd) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        tmp = tmp->next;
    }
    tmp = sh->env;
    while (tmp)
    {
        if (tmp->is_export && !ft_get_env(sh->cmd->tmp_env, tmp->key))
		{
            if (ft_putenv_fd(tmp, fd) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
        tmp = tmp->next;
    }
    return (EXIT_SUCCESS);
}
