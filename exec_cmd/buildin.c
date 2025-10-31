/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:23:08 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/31 15:09:50 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin_parent(char **args)
{
    if (!args || !args[0])
        return (0);
    return (!ft_strcmp(args[0], "cd")
         || !ft_strcmp(args[0], "export")
         || !ft_strcmp(args[0], "unset")
         || !ft_strcmp(args[0], "exit"));
}

int is_builtin_child(char **args)
{
	if (!args || !args[0])
		return (0);
	return (!ft_strcmp(args[0], "echo")
		 || !ft_strcmp(args[0], "pwd")
		 || !ft_strcmp(args[0], "env"));
}

int run_builtin(t_shell *sh, char **args)
{
	if (!args || !args[0])
		return (sh->status);
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, &sh->env));
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(STDOUT_FILENO, sh));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(&sh->env, args));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, sh));
    else if (!ft_strcmp(args[0], "echo"))
        return (ft_echo(args, STDOUT_FILENO));
    else if (!ft_strcmp(args[0], "pwd"))
        return (ft_pwd(sh->env, STDOUT_FILENO));
    else if (!ft_strcmp(args[0], "env"))
        return (ft_env(sh, STDOUT_FILENO));
	else
		return (sh->status);
}
// STDOUT_FILENO けしても　-> txtとかもいける.
