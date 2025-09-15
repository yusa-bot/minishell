/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:29:04 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/14 16:33:25 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_env *ft_lst_new(char *key, char *value, int is_export)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->is_export = is_export;
	return (new);
}
