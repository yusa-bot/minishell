/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_lastx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:22:01 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/14 16:23:36 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_env   *ft_lst_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
