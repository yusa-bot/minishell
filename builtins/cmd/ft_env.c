/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:41:21 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/18 21:05:54 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_putenv_fd(t_env *env, int fd)
{
    if (ft_putstr_fd(env->key, fd) < 0
        || ft_putstr_fd("=", fd) < 0
        || ft_putstr_fd(env->value, fd) < 0
        || ft_putstr_fd("\n", fd) < 0)
    {
        perror("minishell: env");
		return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int ft_env(t_env *lst, int fd)
{
    t_env *tmp;

    tmp = lst;
    while (tmp)
    {
        if (tmp->is_export)
		{
            if (ft_putenv_fd(tmp, fd) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
        tmp = tmp->next;
    }
    return (EXIT_SUCCESS);
}