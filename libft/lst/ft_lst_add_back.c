/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:26:15 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/19 16:54:33 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lst_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			last = ft_lst_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
