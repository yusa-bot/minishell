/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:31:10 by rinka             #+#    #+#             */
/*   Updated: 2025/08/10 00:36:43 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

#include <stdio.h>

void ft_unset(t_env **lst, char *delkey)
{
	t_env *dellst;
	t_env *tmp;

	tmp = *lst;
	if (ft_strcmp(tmp->key, delkey) == 0)
	{
		dellst = tmp;
		ft_lstdelone(dellst);
		tmp = tmp->next;
		return ;
	}
	while(tmp->next)
	{
		if (ft_strcmp((tmp->next)->key, delkey) == 0)
		{
			dellst = tmp->next;
			tmp->next = (tmp->next)->next;
			ft_lstdelone(dellst);
			return ;
		}
		tmp = tmp->next;
	}
}
