/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:31:10 by rinka             #+#    #+#             */
/*   Updated: 2025/08/24 12:04:51 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_env **lst, char *delkey)
{
	t_env *dellst;
	t_env *tmp;

	tmp = *lst;
	if (ft_strcmp(tmp->key, delkey) == 0)
	{
		dellst = tmp;
		ft_envlst_delone(dellst);
		tmp = tmp->next;
		return ;
	}
	while(tmp->next)
	{
		if (ft_strcmp((tmp->next)->key, delkey) == 0)
		{
			dellst = tmp->next;
			tmp->next = (tmp->next)->next;
			ft_envlst_delone(dellst);
			return ;
		}
		tmp = tmp->next;
	}
}
