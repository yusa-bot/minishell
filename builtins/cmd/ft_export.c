/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:31:03 by rinka             #+#    #+#             */
/*   Updated: 2025/09/14 17:43:12 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env *ft_lst_next(t_env *env_lst, char **prev_key)
{
	t_env *res;

	res = NULL;
	while (env_lst)
	{
		if (!*prev_key || ft_strcmp(*prev_key, env_lst->key) < 0)
		{
			if (!res || ft_strcmp(res->key, env_lst->key) > 0)
				res = env_lst;
		}
		env_lst = env_lst->next;
	}
	if (res)
		*prev_key = res->key;
	return (res);
}

static int ft_putexport_fd(t_env *env_lst, int fd)
{
    if (ft_putstr_fd("declare -x ", fd) < 0
        || ft_putstr_fd(env_lst->key, fd) < 0
        || ft_putstr_fd("=\"", fd) < 0
        || ft_putstr_fd(env_lst->value, fd) < 0
        || ft_putstr_fd("\"\n", fd) < 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int ft_export(t_env *env_lst, int fd)
{
    char    *prev_key;
    t_env   *env_to_put;

    prev_key = NULL;
    env_to_put = ft_lst_next(env_lst, &prev_key);
    while (env_to_put)
    {
        if (env_to_put->is_export)
        {
            if (ft_putexport_fd(env_to_put, fd) == EXIT_FAILURE)
                return (EXIT_FAILURE);
        }
        env_to_put = ft_lst_next(env_lst, &prev_key);
    }
    return (EXIT_SUCCESS);
}
