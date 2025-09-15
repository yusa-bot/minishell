/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:23:24 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/14 20:34:41 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_parent(const char *name)
{
    return (!ft_strcmp(name, "cd")
         || !ft_strcmp(name, "export")
         || !ft_strcmp(name, "unset")
         || !ft_strcmp(name, "exit"));
}


