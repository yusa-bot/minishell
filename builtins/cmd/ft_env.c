/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:41:21 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 12:59:04 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_putenv_fd(t_env *env, int fd)
{
	ft_putstr_fd(env->key, fd);
	ft_putstr_fd("=", fd);
	ft_putstr_fd(env->value, fd);
	ft_putstr_fd("\n", fd);
}

void ft_env(t_env *lst, int fd)
{
	t_env *tmp;

	tmp = lst;
	while(tmp)
	{
		if (tmp->is_export)
			ft_putenv_fd(tmp, fd);
		tmp = tmp->next;
	}
}
