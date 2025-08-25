/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:31:00 by rinka             #+#    #+#             */
/*   Updated: 2025/08/24 12:04:34 by rinka            ###   ########.fr       */
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

void ft_put_envs(t_env *lst, int fd)
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