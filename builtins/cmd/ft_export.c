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

static	void ft_putexport_fd(t_env *env, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env->key, fd);
	ft_putstr_fd("=\"", fd);
	ft_putstr_fd(env->value, fd);
	ft_putstr_fd("\"\n", fd);
}

void ft_export(t_env *env_lst, int fd)
{
	char *prev_key;
	t_env	*env_to_put;

	prev_key = NULL;
	env_to_put = ft_lst_next(env_lst, &prev_key);
	while(env_to_put)
	{
		if (env_to_put->is_export)
			ft_putexport_fd(env_to_put, fd);
		env_to_put = ft_lst_next(env_lst, &prev_key);
	}
}

